#include "InventoryItemsField.h"
#include "IInventory.h"
#include "RegisteryEntity.h"
InventoryItemsField::InventoryItemsField(World* world ,Controller* controller, int* coutItemInHotPanel)
{
	this->world = world;
	this->controller = controller;
	this->coutItemInHotPanel = coutItemInHotPanel;
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
	int countY = id / countItemsX;
	int countX = id - countY * countItemsX; // �������� ����� ������, �� � countX ��� ������� ��������� �������
	if (countX > countItemsX || countY > countItemsY)
	{
		std::cout << "��� ������ ��������� � ��������, id ����� �� ������� ������� � ������ InventoryItemsField." << std::endl;
		std::cout << "������������ ������ = " << countItemsX * countItemsY << ", � �������� id �����" << id << "." << std::endl;
		throw;
	}

	return itemCell[countX][countY];
}

void InventoryItemsField::UpdateCells()
{

	if (dynamic_cast<IInventory*>(controller->target))
	{
		for (int x = *coutItemInHotPanel; dynamic_cast<IInventory*>(controller->target)->inventories[0]->slots.size() > 0 & x < dynamic_cast<IInventory*>(controller->target)->inventories[0]->slots.size(); x++)
		{

			ItemHotCell* cell = getItemContainer(x - *coutItemInHotPanel);
			int ID = dynamic_cast<IInventory*>(controller->target)->inventories[0]->slots[x - 1].id;
			if (dynamic_cast<IInventory*>(controller->target)->inventories[0]->slots[x - 1].isEmpty == false)
			cell->drawItem = true;
			cell->item->carcass->tbo = RegisteryEntity::entity[ID]->rect->tbo;
			cell->item->carcass->textureRect = RegisteryEntity::entity[ID]->textureRect;
			cell->item->Color = vec4(255, 255, 255, 255);

			if (cell->clickBool == true)
			{
				if (dynamic_cast<IInventory*>(controller->target)->inventories[0]->slots[x - 1].isEmpty == false)
					Cursor::grappedInventoryCell = cell;

			}
			if (Cursor::grappedInventoryCell == cell)
			{
				cell->drawItem = false;
				if ((cell->hoverBool == false) & (RenderWindow::mouseLeft == true))
				{
					Cursor::grappedInventoryCell = nullptr;
					//dynamic_cast<IInventory*>(controller->target)->inventories[0]->slots.erase(dynamic_cast<IInventory*>(controller->target)->inventories[0]->slots.begin() + x);
					dynamic_cast<IInventory*>(controller->target)->inventories[0]->slots[x - 1].isEmpty = true;
					dynamic_cast<IInventory*>(controller->target)->inventories[0]->slots[x - 1].stuckCount = 0;
					dynamic_cast<IInventory*>(controller->target)->inventories[0]->full = false;
					dynamic_cast<InventoredMob*>(controller->target)->Take(dynamic_cast<ITakeble*>(RegisteryEntity::addEntity(world, ID, (Cursor::getMousePosition(RenderWindow::window) - world->globalPosition))), 0);
					//cell->drawItem = true;
				}
			}else
			{
				//std::cout << "Nu tut pusto" << std::endl;
			}
		}
	}
}
Alterable InventoryItemsField::draw(Renderer* renderer, Alterable alters)
{
	UpdateCells();
	alters = Panel::draw(renderer, alters);
	for (int x = 0; x < countItemsX; x++)
		for (int y = 0; y < countItemsY; y++)
		{
			renderer->draw(itemCell[x][y], alters);
		}
	return Alterable();
}


