#pragma once

#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>
#include <CorbinGui/EditorGame.h>
#include <QtGui/QKeyEvent>
#include <ExportHeader.h>

class GameObjectTree;
class ENGINE_SHARED GameObjectViewer : public QTreeWidget {

	EditorGame * game;
	GameObjectTree* getItem(Entity * dude);
public:
	GameObjectViewer(EditorGame * game);
	void init();
	void reload();
	void keyPressEvent(QKeyEvent *ev);

	void renameCurrentObject();

	void keyReleaseEvent(QKeyEvent *ev);
	static Entity * convertTree2Entity(QTreeWidgetItem * treeItem);

};