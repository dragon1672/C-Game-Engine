#pragma once

#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

class GameObjectViewer : public QTreeWidget {
public:
	GameObjectViewer() {
		setColumnCount(1);
	}
	void init() {

	}
};