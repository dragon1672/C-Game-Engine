#pragma once

#include <CorbinGui/Dependents/Command.h>

class EditFloat : public Command {
public:
	float * data;
	float newGuy;
	float old;

	virtual void DO()
	{
		old = *data;
		*data = newGuy;
	}

	virtual void UNDO()
	{
		*data = old;
	}

};