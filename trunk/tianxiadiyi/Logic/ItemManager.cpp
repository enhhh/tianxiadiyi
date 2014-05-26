#include "ItemManager.h"

static ItemManager* itemManager = NULL;

ItemManager::ItemManager()
{
	selectItemId = 0;

	for (int i = 0; i < 6; i++)
	{
		Gem* gem = new Gem(i);

		gemVector.push_back(gem);
	}

	for (int i = 0; i < 34; i++)
	{
		Equipment* equipment = new Equipment(i+1);
		
		equipmentVector.push_back(equipment);
		itemVector.push_back(equipment);
	}

	pageNum = 0;
	maxPageNum = (itemVector.size()-1) / 16 + 1;

	if (itemVector.size() == 0)
	{
		maxPageNum = 0;
	}
}

ItemManager::~ItemManager()
{
}

ItemManager* ItemManager::getTheOnlyInstance()
{
	if (!itemManager)
	{
		itemManager = new ItemManager();
	}

	return itemManager;
}

vector<Equipment*> ItemManager::getEquipmentList( int type )
{
	vector<Equipment*> equipmentVector;

	return equipmentVector;
}