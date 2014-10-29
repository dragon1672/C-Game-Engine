#include "GameObjectViewer.h"
#include <Engine/Tools/Printer.h>


class GameObjectTree : public QTreeWidgetItem {
public:
	Entity * GameObj;
	GameObjectTree(Entity * obj) : QTreeWidgetItem((QTreeWidget*)0, QStringList(QString(obj->Name()))), GameObj(obj) {}
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

void GameObjectViewer::keyPressEvent(QKeyEvent *ev)
{
	if(ev->key() == Qt::Key_Delete)
		game->RemoveCurrentEntity();
}

void GameObjectViewer::keyReleaseEvent(QKeyEvent *ev)
{
	//printer.LogMessage(ev->text().toStdString().c_str());
}

void GameObjectViewer::update()
{
	while(this->topLevelItemCount() > 0) delete takeTopLevelItem(0);

	QList<QTreeWidgetItem *> items;
	auto topLevelGameObjects = game->Game()->getTopLevelEntities();
	for (uint i = 0; i < topLevelGameObjects.size(); ++i) {
		items.append(getItem(topLevelGameObjects[i]));
	}
	insertTopLevelItems(0, items);
}

void GameObjectViewer::init()
{
	update();
}

GameObjectViewer::GameObjectViewer(EditorGame * game) : game(game)
{
	setColumnCount(1);
	setWindowTitle("Game Object List");
	
	game->Game()->entityListChange.push_back([this](Entity*){this->update();});
}

Entity * GameObjectViewer::convertTree2Entity(QTreeWidgetItem * treeItem)
{
	return treeItem != nullptr ? ((GameObjectTree*)treeItem)->GameObj : nullptr;
}
