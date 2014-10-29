#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>

#include <Engine/Entity/Entity.h>



class ComponentEditor : public QWidget {
public:
	ComponentEditor() {

	}


	void changeEntity(Entity * toUpdateTo);
};