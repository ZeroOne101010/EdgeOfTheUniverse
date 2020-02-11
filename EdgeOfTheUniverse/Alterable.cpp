#include "Alterable.h"
Alterable Alterable::Default;

//Alter Alterable::getAlters()
//{
//	return alter;
//}


Alterable Alterable::operator*=(Alterable alter)
{
	Position += alter.Position;
	RelSize *= alter.RelSize;
	Origin += alter.Origin;
	Rotation *= alter.Rotation;
	return *this;
}
