#pragma once
class ItemConteiner
{
public:
	ItemConteiner(int id, int stackCount = 0);
	bool full;
	int stuckCount;
	int id;
};

