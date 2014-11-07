#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QListWidget>

class ResourceViewer : public QWidget {
	QListWidget * myList;
public:
	//create buttons for adding
	//show list under each second for name editing/deleting
	ResourceViewer();

	void updateList();
};