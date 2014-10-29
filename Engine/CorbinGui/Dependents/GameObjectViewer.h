#pragma once

#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>
#include <Engine/Systems/GameObjectManager.h>
#include <QtGui/QKeyEvent>
#include <ExportHeader.h>

class GameObjectTree;
class ENGINE_SHARED GameObjectViewer : public QTreeWidget {
	GameObjectManager * game;
	Entity * currentlySelected;
	GameObjectTree* getItem(Entity * dude);
public:
	Entity * CurrentlySelected() const { return currentlySelected; }
	GameObjectViewer(GameObjectManager * game);
	void init();
	void update();
	void keyPressEvent(QKeyEvent *ev);

	void keyReleaseEvent(QKeyEvent *ev);


};