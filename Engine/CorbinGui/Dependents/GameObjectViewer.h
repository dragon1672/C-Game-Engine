#pragma once

#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>
#include <Engine/Systems/GameObjectManager.h>
#include <QtGui/QKeyEvent>

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
		QTreeWidgetItem * ret = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString(dude->Name())));
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
	void keyPressEvent(QKeyEvent *ev)
	{
		if(ev->key() == Qt::Key_Delete)
			printer.LogMessage(ev->text().toStdString().c_str());
	}

	void keyReleaseEvent(QKeyEvent *ev)
	{
		//printer.LogMessage(ev->text().toStdString().c_str());
	}


};