#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>

#include <Engine/Entity/Entity.h>
#include <ExportHeader.h>


class ComponentEditorPrivates;
class ENGINE_SHARED ComponentEditor : public QWidget {
	ComponentEditorPrivates * privates;
public:
	ComponentEditor();
	~ComponentEditor();

	void update();

	void changeEntity(Entity * toUpdateTo, std::function<bool(Component*)> validComponentCheck);
};