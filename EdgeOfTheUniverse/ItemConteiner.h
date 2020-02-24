#pragma once
class ItemConteiner
{
public:
	ItemConteiner(int id, int stackCount = 0);
	bool full;
	bool isEmpty = true;
	int stuckCount;
	int id;
};

