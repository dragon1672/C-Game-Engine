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
		printer.LogMessage(ev->text().toStdString().c_str());
}

void GameObjectViewer::keyReleaseEvent(QKeyEvent *ev)
{
	//printer.LogMessage(ev->text().toStdString().c_str());
}

void GameObjectViewer::update()
{
	while(this->topLevelItemCount() > 0) delete takeTopLevelItem(0);

	QList<QTreeWidgetItem *> items;
	auto topLevelGameObjects = game->getTopLevelEntities();
	for (uint i = 0; i < topLevelGameObjects.size(); ++i) {
		items.append(getItem(topLevelGameObjects[i]));
	}
	insertTopLevelItems(0, items);
}

void GameObjectViewer::init()
{
	update();
}

GameObjectViewer::GameObjectViewer(GameObjectManager * game) : game(game)
{
	setColumnCount(1);
	game->entityListChange.push_back([this](Entity*){this->update();});
	connect(this,&QTreeWidget::currentItemChanged,[this](QTreeWidgetItem *current, QTreeWidgetItem *previous){
		this->currentlySelected = current != nullptr ? ((GameObjectTree*)current)->GameObj : nullptr;
		printer.LogMessage(currentlySelected->Name());
	});
}
