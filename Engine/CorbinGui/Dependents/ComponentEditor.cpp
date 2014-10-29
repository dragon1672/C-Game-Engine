#include "ComponentEditor.h"
#include <Engine/TypeDefs.h>

#include <QtWidgets/QLabel>
#include <Engine/Tools/QT/LinkedSlider.h>
#include <QtWidgets/QLineEdit>
#include <QtGui/QValidator>
#include <array>

#pragma region Component Editors


class SingleComponentEditor : public QWidget {
public:
	virtual void updateFromModel() = 0;
};

#include <glm/glm.hpp>

template<uint N>
class QTVecEditor : public SingleComponentEditor {
	float * vec;
	static const uint size = N;
	QLineEdit * editors[size]; // supports up to vec4
	void init(QString title="") {
		QHBoxLayout * layout = new QHBoxLayout();
		this->setLayout(layout);
		if(title != "") {
			layout->addWidget(new QLabel(title));
		}
		std::string names = "xyz";
		for(uint i=0;i<size;i++) {
			editors[i] = new QLineEdit();	editors[i]->setValidator( new QDoubleValidator() );

			layout->addWidget(new QLabel(names[i]+":"));	layout->addWidget(editors[i]);
			connect(editors[i],&QLineEdit::textEdited,[&,this,i](const QString &newGuy){ this->vec[i] = (float)(newGuy.toDouble()); });
		}
	}
	void updateFromModel() {
		for(uint i=0;i<size;i++) {
			editors[i]->setText(QString::number(vec[i]));
		}
	}
public:
	QTVecEditor(float * data,QString title = "") {
		static_assert(size > 0,"Vector must be larger than 0");
		vec = data;
		init(title);
	}
};

#include <Engine/Tools/MatrixInfo.h>

class TranslationEdtor : public SingleComponentEditor {
	MatrixInfo * matrix;
	QLabel * title;
	SingleComponentEditor * vecEditors[3];
public:
	TranslationEdtor(MatrixInfo * matrix) {
		this->matrix = matrix;
		QHBoxLayout * layout = new QHBoxLayout();
		this->setLayout(layout);
		title = new QLabel("Transform Info");
		layout->addWidget(title);
		vecEditors[0] = new QTVecEditor<3>(&(matrix->pos[0]  ),"Pos:"  );	layout->addWidget(vecEditors[0]);
		vecEditors[1] = new QTVecEditor<3>(&(matrix->rot[0]  ),"Rot:"  );	layout->addWidget(vecEditors[1]);
		vecEditors[2] = new QTVecEditor<3>(&(matrix->scale[0]),"Scale:");	layout->addWidget(vecEditors[2]);
	}
	void updateFromModel() {
		vecEditors[0]->updateFromModel();
		vecEditors[1]->updateFromModel();
		vecEditors[2]->updateFromModel();
	}
};

#pragma endregion

#pragma region map
#include <map>

class EditorCreatorInterface {
public:
	virtual SingleComponentEditor * getNewInstance(void * data) = 0;
};

template<class T>
class EditorCreator : public EditorCreatorInterface {
public:
	SingleComponentEditor * getNewInstance(void * data) {
		static_assert(false,"No editor exists");
		return nullptr;
	}
};

template<>
class EditorCreator<TranslationEdtor> : public EditorCreatorInterface {
public:
	SingleComponentEditor * getNewInstance(void * data) {
		return new TranslationEdtor((MatrixInfo*)data);
	}
};

namespace {
	std::map<std::string,EditorCreatorInterface*> initMap() {
		std::map<std::string,EditorCreatorInterface*> map;     
		map[typeid(MatrixInfo).name()] = new EditorCreator<TranslationEdtor>();

		return map;
	}
	std::map<std::string,EditorCreatorInterface*> map = initMap();
}

#pragma endregion


void ComponentEditor::changeEntity(Entity * toUpdateTo, std::function<bool(Component*)> validComponentCheck)
{
	std::vector<SingleComponentEditor *> list;
	auto allcomps = toUpdateTo->getAllComponents();
	list.push_back(map[typeid(MatrixInfo).name()]->getNewInstance(toUpdateTo->getTrans()));
	for (uint i = 0; i < allcomps.size(); i++) {
		if(validComponentCheck(allcomps[i])) {
			list.push_back(map[typeid(*allcomps[i]).name()]->getNewInstance(allcomps[i]));
		}
	}

}
