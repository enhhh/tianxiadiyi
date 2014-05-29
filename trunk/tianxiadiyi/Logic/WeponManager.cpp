#include "WeponManager.h"

static WeponManager* weponManager = NULL;

WeponManager::WeponManager()
{
	itemManager = ItemManager::getTheOnlyInstance();
	weponTakeUpManager = WeponTakeUpManager::getTheOnlyInstance();

	init();
}

WeponManager::~WeponManager()
{
}

WeponManager* WeponManager::getTheOnlyInstance()
{
	if (!weponManager)
	{
		weponManager = new WeponManager();
	}

	return weponManager;
}

void WeponManager::init()
{
	for (int i = 0; i < 4; i++)
	{
		gemSpriteArray[i].weponGem.gem = NULL;
		gemSpriteArray[i].sprite = NULL;
	}

	gemFillSprite.weponGem.gem = NULL;
	gemFillSprite.sprite = NULL;

	int gemNum = itemManager->getGemNum();
	pageNum = 0;
	maxPageNum = (gemNum-1) / 4 + 1;

	selectGemId = 0;

	if (gemNum == 0)
	{
		maxPageNum = 0;
	}

	if (gemNum > 0)
	{
		weponGemArray = new WeponGem[maxPageNum*4];

		for (int i = 0; i < maxPageNum*4; i++)
		{
			weponGemArray[i].id = -1;
			weponGemArray[i].gem = NULL;
		}

		int j = 0;

		for (int i = 0; i < itemManager->maxPageNum*16; i++)
		{
			Item* item = itemManager->itemArray[i];

			if (item != NULL)
			{
				if (item->type == GEM)
				{
					WeponGem weponGem = {i, (Gem*)item};
					weponGemArray[j++] = weponGem;
				}
			}
		}
	}

	equipment = weponTakeUpManager->equipment;
}

void WeponManager::fill()
{
	WeponGem weponGem = weponGemArray[selectGemId];
	Gem* gem = equipment->gem;

	if (gem != NULL)
	{
		Gem* t = (Gem*)itemManager->itemArray[weponGem.id];
		itemManager->itemArray[weponGem.id] = equipment->gem;
		equipment->gem = t;

		weponGemArray[selectGemId].id = -1;
		weponGemArray[selectGemId].gem = NULL;
	}
	else
	{
		equipment->gem = weponGem.gem;
		itemManager->itemArray[weponGem.id] = NULL;
	}
}

