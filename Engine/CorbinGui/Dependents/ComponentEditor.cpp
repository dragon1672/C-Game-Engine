#include "ComponentEditor.h"
#include <Engine/TypeDefs.h>

#include <QtWidgets/QLabel>
#include <Engine/Tools/QT/LinkedSlider.h>
#include <QtWidgets/QLineEdit>
#include <QtGui/QValidator>
#include <Engine/Tools/CollectionEditing.h>
#include <QtWidgets/QGroupBox>
#include <Engine/DebugTools/DebugMemHeader.h>
#include <Engine/Defines/SafeNewAndDelete.h>
#include <Engine/Tools/Printer.h>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QCheckBox>
#include <Engine/Tools/QT/ButtonInfo.h>
#include <Engine/Entity/Components/CameraComponent.h>
#include <Engine/Systems/CameraManager.h>
#include <QtGui/QPalette>

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


class AdminEditor : public QWidget {
	Component * c;
	QCheckBox * enabled;
	QLineEdit * name;
	
public:
	AdminEditor(Component * c, bool haveEnable, bool haveName, bool haveRemove) :
		c(c),
		enabled(nullptr),
		name(nullptr)
	{
		setLayout(new QHBoxLayout());
		if(haveEnable) {
			enabled = new QCheckBox("Enable: ");
			layout()->addWidget(enabled);
			connect(enabled,&QCheckBox::stateChanged,[=](){ 
				c->active = enabled->isChecked();
			});
		}
		if(haveName) {
			auto title = new QLabel("Name: ");
			layout()->addWidget(title);
			name = new QLineEdit();
			layout()->addWidget(name);
			connect(name,&QLineEdit::editingFinished,[=](){ 
				c->Name(name->text().toStdString());
			});
		}
		if(haveRemove) {
			ButtonInfo removeBtn;
			removeBtn.init("Remove",[=](){
				camManager.removeCam((CameraComponent*)c);
				c->Parent()->removeComponent(c);
			});
			layout()->addWidget(removeBtn.button);
		}

	}
	void update() {
		if(enabled != nullptr && enabled->isChecked() != c->active)
			enabled->setChecked(c->active);
		if(name != nullptr && name->text().toStdString() != c->Name())
			name->setText(c->Name().c_str());
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
	QLineEdit * editors[size];
	QDoubleValidator validator;
	void init(QString title, std::string names) {
		QHBoxLayout * layout = new QHBoxLayout();
		this->setLayout(layout);
		if(title != "") {
			layout->addWidget(new QLabel(title));
		}
		for(uint i=0;i<size;i++) {
			editors[i] = new QLineEdit();	editors[i]->setValidator(&validator);
			char letter = names[clamp(i,0,names.length()-1)];
			QString name = QString(letter);
			layout->addWidget(new QLabel(name+": "));	layout->addWidget(editors[i]);
			connect(editors[i],&QLineEdit::textEdited,[&,this,i](const QString &newGuy){ this->vec[i] = (float)(newGuy.toDouble()); });
		}
	}
	void updateFromModel() {
		for(uint i=0;i<size;i++) {
			if(editors[i]->text().toDouble() != vec[i]) {
				editors[i]->setText(QString::number(vec[i]));
			}
		}
	}
public:
	QTVecEditor(float * data,QString title = "", std::string names = "xyzw?") {
		static_assert(size > 0,"Vector must be larger than 0");
		vec = data;
		init(title,names);
	}
};

#include <Engine/Tools/MatrixInfo.h>

class TranslationEdtor : public SingleComponentEditor {
	MatrixInfo * matrix;
	SingleComponentEditor * vecEditors[3];
public:
	TranslationEdtor(MatrixInfo * matrix) {
		setMinimumSize(300,150);
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
		comboBox->addItem("Null"-1);							 \
		for (uint i = 0; i < tmp.size(); i++) {					 \
			QString name(tmp[i]->Name().c_str());				 \
			double id = tmp[i]->getID();						 \
			comboBox->addItem(name,id);							 \
			if(first == tmp[i]) index = i+1;					 \
		}														 \
		comboBox->setCurrentIndex(index);						 \
		return comboBox;										 \
	}


MAKE_COMBO_BOX_MAKER(Script);
MAKE_COMBO_BOX_MAKER(Mesh);
MAKE_COMBO_BOX_MAKER(TextureInfo);
MAKE_COMBO_BOX_MAKER(ShaderProgram);

#pragma endregion


#pragma region Script ComponentEditor

#include <Engine/Entity/Components/ScriptComponent.h>


class ScriptEdtor : public SingleComponentEditor {
	ScriptComponent * script;
	QComboBox *comboBox;
	AdminEditor * admin;
	QGroupBox * scriptVarsContainer;
public:
	ScriptEdtor(ScriptComponent * script) {
		setMinimumSize(300,150);
		setWindowTitle("Script Component");

		this->script = script;
		QVBoxLayout * layout = new QVBoxLayout();
		this->setLayout(layout);

		admin = new AdminEditor(script,true,false,true);
		layout->addWidget(admin);

		comboBox = loadComboBox<Script>(script->myScript());


		void (QComboBox:: *indexChangedSignal)(int) = &QComboBox::currentIndexChanged;
		connect(comboBox,indexChangedSignal,[this](int i) {
			this->script->myScript(this->comboBox->currentData().toDouble());
			this->updateVars();
		});

		scriptVarsContainer = new QGroupBox("Script Editor Prams");
		scriptVarsContainer->setLayout(new QVBoxLayout());

		layout->addWidget(comboBox);
		layout->addWidget(scriptVarsContainer);
	}
	void updateVars() {
		while (auto item = scriptVarsContainer->layout()->takeAt( 0 ) ) {
			delete item->widget();
			delete item;
		}
		std::vector<std::string> entries;

		if(script->myScript() != nullptr) {
			std::string src = script->myScript()->Src();
			const char * srcStr = "GameManager.getEntityFromName";
			int index = src.find(srcStr);
			while(0 <= index && (unsigned)index < src.size()) {
				int firstP = src.find('(',index);
				int lastP = src.find(')',index);
				int countOfStartP = 0;
				for (int i = firstP+1; i <= lastP; i++) {
					if(src[i] == '(') countOfStartP++;
				}
				if(countOfStartP != 0) countOfStartP++;
				while(countOfStartP > 0) {
					lastP = src.find(')',lastP+1);
					countOfStartP--;
				}
				entries.push_back(src.substr(firstP+1,lastP-firstP-1));
				index = src.find(srcStr,index+1);
			}
		}

		for (uint i = 0; i < entries.size(); i++)
		{
			QLineEdit * entry = new QLineEdit();
			QPalette  myPallet = entry->palette();
			QColor col = myPallet.color(QPalette::Button);
			myPallet.setColor(QPalette::Base, col);
			myPallet.setColor(QPalette::Text, Qt::black);
			entry->setReadOnly(true);
			entry->setPalette(myPallet);

			entry->setText(entries[i].c_str());

			scriptVarsContainer->layout()->addWidget(entry);
		}
	}
	void updateFromModel() {
		admin->update();
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
	widg = new QWidget();																							   \
	tLay = new QHBoxLayout();																						   \
	widg->setLayout(tLay);																							   \
	tLay->addWidget(new QLabel(QString(MATERIAL_GLEW(name," Texture: "))));											   \
	{																												   \
		auto box = loadComboBox<TextureInfo>(mat->##name##());														   \
		tLay->addWidget(box);																						   \
		void (QComboBox:: *indexChangedSignal)(int) = &QComboBox::currentIndexChanged;								   \
		connect(box, indexChangedSignal, [=]{																		   \
			this->mat->##name##(box->currentData().toDouble());														   \
		});																											   \
	}																												   \
	layout->addWidget(widg);																						   \



class MaterialEdtor : public SingleComponentEditor {
	Material * mat;
	SingleComponentEditor * color;
public:
	MaterialEdtor(Material * mat) {
		setWindowTitle("Material Editor");
		this->mat = mat;
		QVBoxLayout * layout = new QVBoxLayout();
		this->setLayout(layout);
		layout->addWidget(color = new QTVecEditor<4>(&(mat->color[0]),"","rgba?"));

		QWidget * widg;
		QHBoxLayout * tLay;

		ADD_MATERIAL_GUI_TEXTURE(Diffuse);
		//ADD_MATERIAL_GUI_TEXTURE(NormalMap);
		//ADD_MATERIAL_GUI_TEXTURE(AmbOcc);
		//ADD_MATERIAL_GUI_TEXTURE(AlphaMask);

	}
	void updateFromModel() {
		color->updateFromModel();
	}
};

class RenderableEditor : public SingleComponentEditor {
	RenderableComponent * script;
	AdminEditor * admin;
public:
	RenderableEditor(RenderableComponent * script) {
		setMinimumSize(300,400);
		setWindowTitle("Renderable Component");
		this->script = script;
		QVBoxLayout * layout = new QVBoxLayout();
		this->setLayout(layout);

		admin = new AdminEditor(script,true,false,true);
		layout->addWidget(admin);

		QWidget * widg = new QWidget();																
		QHBoxLayout * tLay = new QHBoxLayout();														
		widg->setLayout(tLay);															
		tLay->addWidget(new QLabel(QString("Geo: ")));			
		{																					
			auto box = loadComboBox<Mesh>(script->Geo());
			tLay->addWidget(box);
			void (QComboBox:: *indexChangedSignal)(int) = &QComboBox::currentIndexChanged;
			connect(box, indexChangedSignal, [=] {
				script->Geo(box->currentData().toDouble());
			});
		}
		layout->addWidget(widg);
		widg = new QWidget();																
		tLay = new QHBoxLayout();														
		widg->setLayout(tLay);															
		tLay->addWidget(new QLabel(QString("Shader: ")));			
		{																					
			auto box = loadComboBox<ShaderProgram>(script->Shader());
			tLay->addWidget(box);
			void (QComboBox:: *indexChangedSignal)(int) = &QComboBox::currentIndexChanged;
			connect(box, indexChangedSignal, [=] {
				auto tmp = resourceManager.getShaderProgram(box->currentData().toDouble());
				script->Shader(tmp);
			});
		}
		layout->addWidget(widg);

		layout->addWidget(new MaterialEdtor(&(script->material)));
	}
	void updateFromModel() {
		admin->update();
	}
};

template<>
class EditorCreator<RenderableEditor> : public EditorCreatorInterface {
public:
	SingleComponentEditor * getNewInstance(void * data) {
		return new RenderableEditor((RenderableComponent*)data);
	}
};

#pragma endregion



class CamEditor : public SingleComponentEditor {
	CameraComponent * script;
	AdminEditor * admin;
	QLineEdit * nearPlane;
	QLineEdit * farPlane; //textEdited
	QDoubleValidator validator;
public:
	CamEditor(CameraComponent * script) {
		setMinimumSize(300,200);
		setWindowTitle("Camera Component");
		this->script = script;
		QVBoxLayout * layout = new QVBoxLayout();
		this->setLayout(layout);

		admin = new AdminEditor(script,true,false,true);
		layout->addWidget(admin);

		nearPlane = new QLineEdit();	nearPlane->setValidator(&validator);
		layout->addWidget(new QLabel("Near Plane: "));	layout->addWidget(nearPlane);
		connect(nearPlane,&QLineEdit::textEdited,[=](const QString &newGuy){ script->nearPlane = (float)(newGuy.toDouble()); });

		farPlane = new QLineEdit();	farPlane->setValidator(&validator);
		layout->addWidget(new QLabel("Far Plane: "));	layout->addWidget(farPlane);
		connect(farPlane,&QLineEdit::textEdited,[=](const QString &newGuy){ script->farPlane = (float)(newGuy.toDouble()); });
	}
	void updateFromModel() {
		admin->update();
	}
};

template<>
class EditorCreator<CamEditor> : public EditorCreatorInterface {
public:
	SingleComponentEditor * getNewInstance(void * data) {
		return new CamEditor((CameraComponent*)data);
	}
};

class ComponentWrapper : public QWidget {
public:
	ComponentWrapper(QWidget * component, QString title) {
		setLayout(new QVBoxLayout());
		QGroupBox * boxy = new QGroupBox(title);
		QVBoxLayout * boxLayout = new QVBoxLayout();
		boxy->setLayout(boxLayout);
		boxLayout->addWidget(component);
		layout()->addWidget(boxy);
	}
};


#pragma region privates
#include <map>
#include <Engine/Defines/Vectors.h>

#define ADD_INTERFACE_TO_MAP(class_name, adaptor) map[typeid(##class_name##).name()] = new EditorCreator<##adaptor##>()

class ComponentEditorPrivates {
public:
	Entity * toUpdateTo;
	QVBoxLayout * layout;
	std::map<std::string,EditorCreatorInterface*> map;
	ComponentEditorPrivates() : toUpdateTo(nullptr) {
		//init map here
		layout = new QVBoxLayout();
		ADD_INTERFACE_TO_MAP(MatrixInfo,TranslationEdtor);
		ADD_INTERFACE_TO_MAP(ScriptComponent,ScriptEdtor);
		ADD_INTERFACE_TO_MAP(RenderableComponent,RenderableEditor);
		ADD_INTERFACE_TO_MAP(CameraComponent,CamEditor);
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
		TrackedEditors.clear();
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

	void reload()
	{
		while (auto item = layout->takeAt( 0 )) {
			delete item->widget();
			delete item;
		}

		clearList();

		if(toUpdateTo==nullptr) return;

		std::vector<Component*> allcomps;
		if(toUpdateTo != nullptr) {
			allcomps.push_back(toUpdateTo->getTrans());
			Collections::AddToFirstVector(allcomps,toUpdateTo->getAllComponents());
		}
		initList(allcomps);
		std::vector<SingleComponentEditor *>& list = TrackedEditors;


		auto vbox = new QVBoxLayout();
		QWidget* widget = new QWidget;
		QScrollArea * scrollarea = new QScrollArea();
		widget->setLayout(vbox);
		scrollarea->setWidget(widget);

		scrollarea->setWidgetResizable(true);

		for (uint i = 0; i < list.size(); i++) {
			auto tmp = new ComponentWrapper(list[i],list[i]->windowTitle());
			vbox->addWidget(tmp);
		}
		layout->addWidget(scrollarea);
	}



};

#pragma endregion


void ComponentEditor::changeEntity(Entity * toUpdateTo) {
	privates->toUpdateTo = toUpdateTo;
	privates->reload();
}

#include <Engine/Systems/Events/EventManager.h>
#include <Engine/Systems/Events/Events/ComponentAddedEvent.h>
#include <Engine/Systems/Events/Events/ComponentRemovedEvent.h>
#include <Engine/Systems/Events/Events/ResourceLoadedEvent.h>

ComponentEditor::ComponentEditor()
{
	setMinimumWidth(350);
	setWindowTitle("Component Editor");
	privates = new ComponentEditorPrivates();
	setLayout(privates->layout);
	eventManager.Subscribe<ComponentAddedEvent>([this](EventData*d,Object*s) {
		this->reload();
	});
	eventManager.Subscribe<ComponentRemovedEvent>([this](EventData*d,Object*s) {
		this->reload();
	});
	eventManager.Subscribe<ResourceLoadedEvent>([this](EventData*d,Object*s) {
		this->reload();
	});
}

void ComponentEditor::update()
{
	privates->update();
}

ComponentEditor::~ComponentEditor()
{
	delete privates;
}

void ComponentEditor::reload()
{
	privates->reload();
}
