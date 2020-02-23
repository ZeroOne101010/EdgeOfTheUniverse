#pragma once
class ItemConteiner
{
public:
	ItemConteiner(int itemID, int stackCount = 0);
	bool full;
	int stuckCount;
	int itemID;
};

