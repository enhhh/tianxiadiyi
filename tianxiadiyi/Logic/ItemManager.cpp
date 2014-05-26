#include "ItemManager.h"

static ItemManager* itemManager = NULL;

ItemManager::ItemManager()
{
	for (int i = 0; i < 6; i++)
	{
		Gem* gem = new Gem(i);

		gemVector.push_back(gem);
		itemVector.push_back(gem);
	}

	for (int i = 0; i < 34; i++)
	{
		Equipment* equipment = new Equipment(i+1);
		
		equipmentVector.push_back(equipment);
		itemVector.push_back(equipment);
	}

	pageNum = 0;
	maxPageNum = (itemVector.size()-1) / 16 + 1;

	selectItemId = 0;

	if (itemVector.size() == 0)
	{
		maxPageNum = 0;
	}

	if (maxPageNum > 0)
	{
		itemArray = new Item*[maxPageNum*16];

		for (int i = 0; i < maxPageNum*16; i++)
		{
			itemArray[i] = NULL;
		}

		for (int i = 0; i < 40; i++)
		{
			itemArray[i] = itemVector[i];
		}
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