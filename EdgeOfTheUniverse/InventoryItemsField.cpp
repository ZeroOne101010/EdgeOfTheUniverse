#include "InventoryItemsField.h"

InventoryItemsField::InventoryItemsField()
{
	Color = vec4(20, 20, 20, 150);
	itemCell = new ItemHotCell * *[countItemsX];

	for (int x = 0; x < countItemsX; x++)
	{
		itemCell[x] = new ItemHotCell * [countItemsY];
	}

	int offset = 4;

	for (int x = 0; x < countItemsX; x++)
		for (int y = 0; y < countItemsY; y++)
		{
			itemCell[x][y] = new ItemHotCell();
			itemCell[x][y]->Activable = false;
			buttonGroup.Add(itemCell[x][y]);
			itemCell[x][y]->Position = vec2((itemCell[x][y]->size.x + offset) * x + offset, (itemCell[x][y]->size.y + offset) * y + offset);
		}
	size = vec2((itemCell[0][0]->size.x + offset) * countItemsX + offset, (itemCell[0][0]->size.y + offset) * countItemsY + offset);
}

InventoryItemsField::~InventoryItemsField()
{
	for (int x = 0; x < countItemsX; x++)
		for (int y = 0; y < countItemsY; y++)
		{
			delete itemCell[x][y];
		}

	for (int x = 0; x < countItemsX; x++)
	{
		delete[countItemsY] itemCell[x];
	}

	delete[countItemsX] itemCell;
}

ItemHotCell* InventoryItemsField::getItemContainer(int id)
{
	int countX = id / countItemsY;
	int countY = id - countItemsX * countItemsY; // �������� ����� ������, �� � countX ��� ������� ��������� �������

	if (countX > countItemsX || countY > countItemsY)
	{
		std::cout << "��� ������ ��������� � ��������, id ����� �� ������� ������� � ������ InventoryItemsField." << std::endl;
		std::cout << "������������ ������ = " << countItemsX * countItemsY << ", � �������� id �����" << id << "." << std::endl;
		throw;
	}

	return itemCell[countX][countY];
}

Alterable InventoryItemsField::draw(Renderer* renderer, Alterable alters)
{
	alters = Panel::draw(renderer, alters);
	for (int x = 0; x < countItemsX; x++)
		for (int y = 0; y < countItemsY; y++)
		{
			renderer->draw(itemCell[x][y], alters);
		}
	return Alterable();
}
