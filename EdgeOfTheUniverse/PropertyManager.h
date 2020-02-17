#pragma once
#include "Property.h"
#include <vector>
#include <map>
class PropertyManager
{
public:
    std::vector<Property*> propertyList;
    std::map<std::string, Property*> propertyTable;
    int allSize;

    PropertyManager();
    ~PropertyManager();
    void addProperty(int value, int sizeProperty, std::string nameProperty);
    Property* getProperty(std::string nameProperty);
    int getValueProperty(std::string nameProperty);
    void setValueProperty(std::string nameProperty, int value);

};

