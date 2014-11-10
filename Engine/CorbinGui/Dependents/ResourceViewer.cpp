#include "ResourceViewer.h"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QHBoxLayout>


#include <Engine/Systems/ResourceManager.h>
#include <Engine/Tools/CollectionEditing.h>
#include <Engine/Systems/Events/EventManager.h>
#include <Engine/Systems/Events/Events/ResourceLoadedEvent.h>

class ResourceListItem : public QListWidgetItem {
public:
	Resource * myResource;
	ResourceListItem(Resource * myResource) : myResource(myResource), QListWidgetItem(myResource->Name().c_str()) {}
};


ResourceViewer::ResourceViewer()
{
	setWindowTitle("Resource Viewer");
	setLayout(new QHBoxLayout());
	myList = new QListWidget();
	layout()->addWidget(myList);
	updateList();
	eventManager.Subscribe<ResourceLoadedEvent>([this](EventData*d,Object*s){
		this->updateList();
	});
}

void ResourceViewer::updateList()
{
	myList->clear();
	//connect(myList,QListWidget::)

	layout()->addWidget(myList);
	auto resourceMaker = [](Resource*r){ return new ResourceListItem(r); };
	auto list = Collections::Select<Mesh*,ResourceListItem*>(resourceManager.getAllMesh(),resourceMaker);
	Collections::AddToFirstVector(list,Collections::Select<TextureInfo*,  ResourceListItem*>(resourceManager.getAllTextureInfo(),  resourceMaker));
	Collections::AddToFirstVector(list,Collections::Select<ShaderProgram*,ResourceListItem*>(resourceManager.getAllShaderProgram(),resourceMaker));
	Collections::AddToFirstVector(list,Collections::Select<Script*,       ResourceListItem*>(resourceManager.getAllScript(),       resourceMaker));
	for (uint i = 0; i < list.size(); i++) {
		myList->addItem(list[i]);
	}
}
