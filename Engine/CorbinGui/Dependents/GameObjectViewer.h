#pragma once

#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>
#include <Engine/Systems/GameObjectManager.h>

class GameObjectViewer : public QTreeWidget {
	GameObjectManager * game;
public:
	GameObjectViewer(GameObjectManager * game) : game(game) {
		setColumnCount(1);
		game->entityListChange.push_back([this](Entity*){this->update();});
	}
	void init() {
		update();
	}
	void update() {
		while(this->topLevelItemCount() > 0) delete takeTopLevelItem(0);

		QList<QTreeWidgetItem *> items;
		auto topLevelGameObjects = game->getTopLevelEntities();
		for (uint i = 0; i < topLevelGameObjects.size(); ++i) {
			items.append(getItem(topLevelGameObjects[i]));
		}
		insertTopLevelItems(0, items);
	}
	QTreeWidgetItem* getItem(Entity * dude) {
		QTreeWidgetItem * ret = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString(dude->getName())));
		if(dude->children.size() > 0)
		{
			QList<QTreeWidgetItem *> items;
			for (const auto& elem : dude->children) {
				items.append(getItem(elem));
			}
			ret->addChildren(items);
		}
		return ret;
	}
};