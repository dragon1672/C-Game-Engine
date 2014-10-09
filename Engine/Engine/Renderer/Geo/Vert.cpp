#include "Vert.h"

int data[] = { 3,4,3,3,2 };

int * Vert::getAtribs()
{
	return data;
}

int Vert::getNumOfAtribs()
{
	return sizeof(data) / sizeof(*data);
}
