#include "Vert.h"

namespace {
	int data[] = { 3,4,3,4,2 };
}

int * Vert::getAtribs()
{
	return data;
}

int Vert::getNumOfAtribs()
{
	return sizeof(data) / sizeof(*data);
}
