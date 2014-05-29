#include "ItemManager.h"

static ItemManager* itemManager = NULL;

ItemManager::ItemManager()
{
	for (int i = 0; i < 8; i++)
	{
		Gem* gem = new Gem(i);

		gemVector.push_back(gem);
		itemVector.push_back(gem);
	}

	for (int i = 0; i < 76; i++)
	{
		Equipment* equipment = new Equipment(i+1);
		
		equipmentVector.push_back(equipment);
		itemVector.push_back(equipment);
	}

	selectItemId = 0;

	pageNum = 0;
	maxPageNum = (itemVector.size()-1) / 16 + 1;

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

		for (int i = 0; i < itemVector.size(); i++)
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

int ItemManager::getGemNum()
{
	int num = 0;

	for (int i = 0; i < itemManager->maxPageNum*16; i++)
	{
		Item* item = itemManager->itemArray[i];

		if (item != NULL)
		{
			if (item->type == GEM)
			{
				num++;
			}
		}
	}

	return num;
}

void ItemManager::sort()
{
	selectItemId = 0;

	int j = 0;

	for (int i = 0; i < itemManager->maxPageNum*16; i++)
	{
		Item* item = itemManager->itemArray[i];

		if (item != NULL)
		{
			itemManager->itemArray[j++] = itemManager->itemArray[i];
		}
	}

	for (int i = j; i < itemManager->maxPageNum*16; i++)
	{
		itemManager->itemArray[i++] = NULL;
	}

	pageNum = 0;
	maxPageNum = (j-1) / 16 + 1;

	if (j == 0)
	{
		maxPageNum = 0;
	}
}

void ItemManager::sell()
{
	itemManager->itemArray[itemManager->selectItemId] = NULL;
}
