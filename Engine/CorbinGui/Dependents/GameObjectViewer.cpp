#include "GameObjectViewer.h"
#include <Engine/Tools/Printer.h>
#include <Engine/Systems/Events/EventManager.h>


class GameObjectTree : public QTreeWidgetItem {
public:
	Entity * GameObj;
	GameObjectTree(Entity * obj) : QTreeWidgetItem((QTreeWidget*)0, QStringList(QString(obj->Name().c_str()))), GameObj(obj) {}
};

GameObjectTree* GameObjectViewer::getItem(Entity * dude)
{
	GameObjectTree * ret = new GameObjectTree(dude);
	auto kids = dude->Children();
	if(kids.size() > 0)
	{
		QList<QTreeWidgetItem *> items;
		for (const auto& elem : kids) {
			items.append(getItem(elem));
		}
		ret->addChildren(items);
	}
	return ret;
}

#include <QtWidgets/QInputDialog>

void GameObjectViewer::keyPressEvent(QKeyEvent *ev)
{
	if(ev->key() == Qt::Key_Delete) {
		game->RemoveCurrentEntity();
		auto tmp = this->currentItem();
		this->setCurrentItem(nullptr);
		emit this->currentItemChanged(tmp,nullptr);
	}
	if(ev->key() == Qt::Key_F2) {
		this->renameCurrentObject();
	}
}

void GameObjectViewer::keyReleaseEvent(QKeyEvent *ev)
{
	//printer.LogMessage(ev->text().toStdString().c_str());
}

void GameObjectViewer::update()
{
	while(this->topLevelItemCount() > 0) delete takeTopLevelItem(0);

	QList<QTreeWidgetItem *> items;
	auto topLevelGameObjects = gameManager.getTopLevelEntities();
	for (uint i = 0; i < topLevelGameObjects.size(); ++i) {
		if(!game->IsEditorObject()(topLevelGameObjects[i]))
			items.append(getItem(topLevelGameObjects[i]));
	}
	insertTopLevelItems(0, items);
	auto tmp = this->currentItem();
	this->setCurrentItem(nullptr);
	emit this->currentItemChanged(tmp,nullptr);
}

void GameObjectViewer::init()
{
	update();
}

#include <Engine/Systems/Events/Events/EntityParentChangedEvent.h>
#include <Engine/Systems/Events/Events/ObjectChangedNameEvent.h>
#include <Engine/Systems/Events/Events/EntityAddedEvent.h>
#include <Engine/Systems/Events/Events/EntityRemovedEvent.h>

GameObjectViewer::GameObjectViewer(EditorGame * game) : game(game)
{
	setColumnCount(1);
	setWindowTitle("Game Object List");
	
	eventManager.Subscribe("EntityParentChangedEvent",[this](EventData*d,Object*sender){this->update();});
	eventManager.Subscribe("ObjectChangedNameEvent",[this](EventData*d,Object*sender){
		ObjectChangedNameEvent* data = (ObjectChangedNameEvent*)d;
		if(std::string(typeid(*(data->dude)).name()) == std::string(typeid(Entity).name()))
			if(data->dude == ((GameObjectTree*)currentItem())->GameObj) {
				currentItem()->setText(0,data->newName.c_str());
			} else {
				this->update();
			}
	});
	eventManager.Subscribe("EntityAddedEvent",[this](EventData*d,Object*sender){this->update();});
	eventManager.Subscribe("EntityRemovedEvent",[this](EventData*d,Object*sender){this->update();});
}

Entity * GameObjectViewer::convertTree2Entity(QTreeWidgetItem * treeItem)
{
	return treeItem != nullptr ? ((GameObjectTree*)treeItem)->GameObj : nullptr;
}

void GameObjectViewer::renameCurrentObject()
{
	bool pressedOk;
	QString newName = QInputDialog::getText(this,"Rename Entity","New Name:",QLineEdit::Normal,((GameObjectTree*)this->currentItem())->GameObj->Name().c_str(),&pressedOk);
	if(pressedOk) ((GameObjectTree*)this->currentItem())->GameObj->Name(newName.toStdString());
}
