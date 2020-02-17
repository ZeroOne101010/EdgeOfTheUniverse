#include "PropertyManager.h"

PropertyManager::PropertyManager()
{
	allSize = 0;
}

PropertyManager::~PropertyManager()
{
	int length = propertyList.size();
	for (int x = 0; x < length; x++)
	{
		delete propertyList[x];
	}
}

void PropertyManager::addProperty(int value, int sizeProperty, std::string nameProperty)
{
	Property* property = new Property(value, sizeProperty, nameProperty);
	propertyTable[nameProperty] = property;
	propertyList.push_back(property);
	allSize += sizeProperty;
}

Property* PropertyManager::getProperty(std::string nameProperty)
{
	return propertyTable[nameProperty];
}

int PropertyManager::getValueProperty(std::string nameProperty)
{
	return getProperty(nameProperty)->value;
}

void PropertyManager::setValueProperty(std::string nameProperty, int value)
{
	Property* property = getProperty(nameProperty);
	property->value = value;
}
