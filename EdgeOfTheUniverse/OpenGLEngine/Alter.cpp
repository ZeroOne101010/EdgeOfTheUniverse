#include "Alter.h"
Alter Alter::operator*=(Alter alter)
{
	this->position += alter.position;
	this->relSize *= alter.relSize;

	return *this;
}
