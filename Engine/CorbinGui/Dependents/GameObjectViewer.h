#pragma once

#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>
#include <Engine/Systems/GameObjectManager.h>
#include <QtGui/QKeyEvent>
#include <ExportHeader.h>

class GameObjectTree;
class ENGINE_SHARED GameObjectViewer : public QTreeWidget {

	GameObjectManager * game;
	GameObjectTree* getItem(Entity * dude);
public:
	GameObjectViewer(GameObjectManager * game);
	void init();
	void update();
	void keyPressEvent(QKeyEvent *ev);

	void keyReleaseEvent(QKeyEvent *ev);
	static Entity * convertTree2Entity(QTreeWidgetItem * treeItem);

};