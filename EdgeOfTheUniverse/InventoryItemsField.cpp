#include "InventoryItemsField.h"
#include "IInventory.h"
#include "RegisteryEntity.h"
InventoryItemsField::InventoryItemsField(Controller* controller, int* coutItemInHotPanel)
{
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
	int countX = id - countY * countItemsX; // Значение будет другим, тк у countX при делении убирается остаток
	if (countX > countItemsX || countY > countItemsY)
	{
		std::cout << "При поиске предметов в инвенаре, id вышло за границы массива в классе InventoryItemsField." << std::endl;
		std::cout << "Максивальный размер = " << countItemsX * countItemsY << ", а введённое id равно" << id << "." << std::endl;
		throw;
	}

	return itemCell[countX][countY];
}

void InventoryItemsField::UpdateCells()
{
	if (dynamic_cast<IInventory*>(controller->target))
	{
		for (int x = *coutItemInHotPanel; dynamic_cast<IInventory*>(controller->target)->inventories[0]->slots.size() > 0 & x <  dynamic_cast<IInventory*>(controller->target)->inventories[0]->slots.size(); x++)
		{
			ItemHotCell* cell = getItemContainer(x - *coutItemInHotPanel);
			int ID = dynamic_cast<IInventory*>(controller->target)->inventories[0]->slots[x].id;
			cell->drawItem = true;
			cell->item->carcass->tbo = RegisteryEntity::entity[ID]->rect->tbo;
			cell->item->carcass->textureRect = RegisteryEntity::entity[ID]->textureRect;
			cell->item->Color = vec4(255, 255, 255, 255);

			if (cell->clickBool == true)
			{
				Cursor::grappedInventoryCell = cell;
			}
			if (Cursor::grappedInventoryCell == cell)
			{
				cell->drawItem = false;
				if ((cell->hoverBool == false) & (RenderWindow::mouseLeft == true))
				{
					Cursor::grappedInventoryCell = nullptr;
					cell->drawItem = true;
				}
			}
		}
	}
}
void InventoryItemsField::UpdteKeepedCell()
{

	//Cursor::grappedInventoryCell->keepedItem.Color = vec4(255, 255, 255, 255);

	//keepedItem.Size = item->carcass->Size;
	//keepedItem.Position = Cursor::getMousePosition(RenderWindow::window) - globalPosition;
	//keepedItem.Origin = vec2(-keepedItem.Size.x / 2, -keepedItem.Size.y / 2);
	//keepedItem.textureRect = item->carcass->textureRect;
	//keepedItem.tbo = item->carcass->tbo;
	//keepedItem.Color = vec4(255, 255, 255, 255);
	if (dynamic_cast<IInventory*>(controller->target))
	{
		for (int x = *coutItemInHotPanel; dynamic_cast<IInventory*>(controller->target)->inventories[0]->slots.size() > 0 & x < dynamic_cast<IInventory*>(controller->target)->inventories[0]->slots.size(); x++)
		{

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
	//UpdteKeepedCell();
	return Alterable();
}


