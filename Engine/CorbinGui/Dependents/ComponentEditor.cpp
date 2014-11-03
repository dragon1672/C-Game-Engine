#include "ComponentEditor.h"
#include <Engine/TypeDefs.h>

#include <QtWidgets/QLabel>
#include <Engine/Tools/QT/LinkedSlider.h>
#include <QtWidgets/QLineEdit>
#include <QtGui/QValidator>
#include <array>
#include <Engine/Tools/CollectionEditing.h>
#include <QtWidgets/QGroupBox>

#pragma region Component Editors
class SingleComponentEditor : public QWidget {
public:
	virtual void updateFromModel() = 0;
};

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
#pragma  endregion

namespace {
	int clamp(int src, int min, int max) {
		if(src < min) return min;
		if(src > max) return max;
		return src;
	}
}

#pragma region Transform component editor

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
		std::string names = "xyzw?";
		for(uint i=0;i<size;i++) {
			editors[i] = new QLineEdit();	editors[i]->setValidator( new QDoubleValidator() );
			char letter = names[clamp(i,0,names.length()-1)];
			QString name = QString(letter);
			layout->addWidget(new QLabel(name+": "));	layout->addWidget(editors[i]);
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
	SingleComponentEditor * vecEditors[3];
public:
	TranslationEdtor(MatrixInfo * matrix) {
		setWindowTitle("Transform Info");
		this->matrix = matrix;
		QVBoxLayout * layout = new QVBoxLayout();
		this->setLayout(layout);
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

template<>
class EditorCreator<TranslationEdtor> : public EditorCreatorInterface {
public:
	SingleComponentEditor * getNewInstance(void * data) {
		return new TranslationEdtor((MatrixInfo*)data);
	}
};

#pragma endregion

#pragma region ComboBox Resource Loaders
#include <QtWidgets/QComboBox>

#include <Engine/Systems/Resources/Mesh.h>
#include <Engine/Systems/Resources/Script.h>
#include <Engine/Systems/Resources/ShaderProgram.h>
#include <Engine/Systems/Resources/TextureInfo.h>

template<typename T> QComboBox * loadComboBox(T* first) { static_assert(false,"No Resource Found"); }

#define MAKE_COMBO_BOX_MAKER(class_name) \
	template<> QComboBox * loadComboBox<##class_name##>(##class_name##*first) {	 \
		QComboBox * comboBox = new QComboBox;					 \
		int index= -1;											 \
		auto tmp = resourceManager.getAll##class_name##();		 \
		for (uint i = 0; i < tmp.size(); i++) {					 \
			QString name(tmp[i]->Name().c_str());				 \
			int id = tmp[i]->getID();							 \
			comboBox->addItem(name,id);							 \
			if(first == tmp[i]) index = i;						 \
		}														 \
		comboBox->setCurrentIndex(index);						 \
		return comboBox;										 \
	}

MAKE_COMBO_BOX_MAKER(Script);
MAKE_COMBO_BOX_MAKER(Mesh);
MAKE_COMBO_BOX_MAKER(ShaderProgram);
MAKE_COMBO_BOX_MAKER(TextureInfo);

#pragma endregion


#pragma region Script ComponentEditor

#include <Engine/Entity/Components/ScriptComponent.h>


class ScriptEdtor : public SingleComponentEditor {
	ScriptComponent * script;
	QComboBox *comboBox;
public:
	ScriptEdtor(ScriptComponent * script) {
		setWindowTitle("Script Component");
		this->script = script;
		QVBoxLayout * layout = new QVBoxLayout();
		this->setLayout(layout);

		comboBox = loadComboBox<Script>(script->script);


		void (QComboBox:: *indexChangedSignal)(int) = &QComboBox::currentIndexChanged;
		connect(comboBox,indexChangedSignal,[this](int i) {
			this->script->script = resourceManager.getScript(this->comboBox->currentData().toInt());
		});


		layout->addWidget(comboBox);
	}
	void updateFromModel() {

	}
};

template<>
class EditorCreator<ScriptEdtor> : public EditorCreatorInterface {
public:
	SingleComponentEditor * getNewInstance(void * data) {
		return new ScriptEdtor((ScriptComponent*)data);
	}
};

#pragma endregion

#pragma region Renderable ComponentEditor

#include <Engine/Entity/Components/RenderableComponent.h>

#define MATERIAL_STRING(x) #x
#define MATERIAL_GLEW(a,b) MATERIAL_STRING(a##b)

#define ADD_MATERIAL_GUI_TEXTURE(name)\
	widg = new QWidget();										   \
	tLay = new QHBoxLayout();									   \
	widg->setLayout(tLay);										   \
	tLay->addWidget(new QLabel(QString(MATERIAL_GLEW(name," Texture: "))));			   \
	tLay->addWidget(loadComboBox<TextureInfo>(mat->##name##()));	   \
	layout->addWidget(widg);									   \


class MaterialEdtor : public SingleComponentEditor {
	Material * mat;
	SingleComponentEditor * color;
public:
	MaterialEdtor(Material * mat) {
		setWindowTitle("Material Editor");
		this->mat = mat;
		QVBoxLayout * layout = new QVBoxLayout();
		this->setLayout(layout);
		layout->addWidget(color = new QTVecEditor<4>(&(mat->color[0])));

		QWidget * widg;
		QHBoxLayout * tLay;
		ADD_MATERIAL_GUI_TEXTURE(Diffuse);
		ADD_MATERIAL_GUI_TEXTURE(NormalMap);
		ADD_MATERIAL_GUI_TEXTURE(AmbOcc);
		ADD_MATERIAL_GUI_TEXTURE(AlphaMask);

	}
	void updateFromModel() {
		color->updateFromModel();
	}
};

class RenderableEdtor : public SingleComponentEditor {
	RenderableComponent * script;
public:
	RenderableEdtor(RenderableComponent * script) {
		setWindowTitle("Renderable Component");
		this->script = script;
		QVBoxLayout * layout = new QVBoxLayout();
		this->setLayout(layout);
		layout->addWidget(new MaterialEdtor(&(script->material)));
	}
	void updateFromModel() {

	}
};

template<>
class EditorCreator<RenderableEdtor> : public EditorCreatorInterface {
public:
	SingleComponentEditor * getNewInstance(void * data) {
		return new RenderableEdtor((RenderableComponent*)data);
	}
};

#pragma endregion

#pragma region privates
#include <map>
#include <Engine/Defines/Vectors.h>

#define ADD_INTERFACE_TO_MAP(class_name, adaptor) map[typeid(##class_name##).name()] = new EditorCreator<##adaptor##>()

class ComponentEditorPrivates {
public:
	std::map<std::string,EditorCreatorInterface*> map;
	ComponentEditorPrivates() {
		//init map here
		ADD_INTERFACE_TO_MAP(MatrixInfo,TranslationEdtor);
		ADD_INTERFACE_TO_MAP(ScriptComponent,ScriptEdtor);
		ADD_INTERFACE_TO_MAP(RenderableComponent,RenderableEdtor);
	}
	template<typename T> bool hasEditorFor(Component*c) {
		return map.find(typeid(T).name()) != map.end();
	}
	bool hasEditorFor(Component*c) {
		return map.find(typeid(*c).name()) != map.end();
	}
	template<typename T>SingleComponentEditor * getEditor(Component * c) {
		return map[typeid(T).name()]->getNewInstance(c);
	}
	SingleComponentEditor * getEditor(Component * c) {
		return map[typeid(*c).name()]->getNewInstance(c);
	}
	~ComponentEditorPrivates() {
		for(auto i : map) {
			delete i.second;
		}
	}

	std::vector<SingleComponentEditor *> TrackedEditors;
	void clearList() {
		CLEAR_VECTOR(TrackedEditors);
	}
	void initList(std::vector<Component *>& list) {
		clearList();
		for (uint i = 0; i < list.size(); i++) {
			if(hasEditorFor(list[i])) {
				TrackedEditors.push_back(getEditor(list[i]));
			}
		}
	}

	void update() {
		for (uint i = 0; i < TrackedEditors.size(); i++) {
			TrackedEditors[i]->updateFromModel();
		}
	}


};

#pragma endregion

void ComponentEditor::changeEntity(Entity * toUpdateTo, std::function<bool(Component*)> validComponentCheck) {
	std::vector<Component*> allcomps;
	if(toUpdateTo != nullptr) {
		allcomps.push_back(toUpdateTo->getTrans());
		auto tmp = toUpdateTo->getAllComponents();
		for (uint i = 0; i < tmp.size(); i++) {
			allcomps.push_back(tmp[i]);
		}

		allcomps = Collections::Where<Component*>(allcomps,validComponentCheck);

	}
	privates->initList(allcomps);
	std::vector<SingleComponentEditor *>& list = privates->TrackedEditors;
		
	QLayoutItem* item;
	while ( ( item = layout()->takeAt( 0 ) ) != NULL ) {
		delete item->widget();
		delete item;
	}
	for (uint i = 0; i < list.size(); i++) {
		QGroupBox * boxy = new QGroupBox(list[i]->windowTitle());
		QHBoxLayout * boxLayout = new QHBoxLayout();
		boxy->setLayout(boxLayout);
		boxLayout->addWidget(list[i]);
		layout()->addWidget(boxy);
	}
}

ComponentEditor::ComponentEditor()
{
	setLayout(new QVBoxLayout());
	setWindowTitle("Component Editor");
	privates = new ComponentEditorPrivates();
}

void ComponentEditor::update()
{
	privates->update();
}

ComponentEditor::~ComponentEditor()
{
	delete privates;
}
