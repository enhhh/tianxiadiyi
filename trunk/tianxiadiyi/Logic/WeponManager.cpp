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

	equipment = weponTakeUpManager->equipment;
	
	// 装备是否有宝石
	gemFillSprite.weponGem.gem = NULL;

	if (equipment->gem != NULL)
	{
		gemFillSprite.weponGem.gem = weponManager->equipment->gem;
	}

	int gemNum = 0;
	int gemType = 0;

	if (equipment != NULL)
	{
		switch(equipment->attribute.zhongLei)
		{
		case BING_FU:
			// 血石
			gemType = XUE_SHI;
			gemNum = itemManager->getGemNum(XUE_SHI);
			break;
		case KAI_JIA:
			// 玄武石
			gemType = XUAN_WU_SHI;
			gemNum = itemManager->getGemNum(XUAN_WU_SHI);
			break;
		case PI_FENG:
			// 清龙石
			gemType = QING_LONG_SHI;
			gemNum = itemManager->getGemNum(QING_LONG_SHI);
			break;
		case SHANG_ZI:
		case JIAN:
			// 朱雀石
			gemType = ZHU_QUE_SHI;
			gemNum = itemManager->getGemNum(ZHU_QUE_SHI);
			break;
		case QIANG:
		case DAO:
		case GONG_JIAN:
			// 白虎石
			gemType = BAI_HU_SHI;
			gemNum = itemManager->getGemNum(BAI_HU_SHI);
			break;
		}
	}

	selectGemId = 0;

	pageNum = 0;
	maxPageNum = (gemNum-1) / 4 + 1;

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
					Gem* gem = (Gem*)item;

					if (gem->attribute.zhongLei == gemType)
					{
						WeponGem weponGem = {i, (Gem*)item};
						weponGemArray[j++] = weponGem;
					}
				}
			}
		}
	}
}

void WeponManager::fillEXT()
{
	WeponGem& weponGem1 = gemFillSprite.weponGem;
	WeponGem& weponGem2 = weponGemArray[selectGemId];
	
	if (weponGem1.gem != NULL)
	{
		WeponGem t = weponGem1;
		weponGem1 = weponGem2;
		weponGem2 = t;
	}
	else
	{
		weponGem1 = weponGem2;
		weponGem2.gem = NULL;
	}
}

void WeponManager::fill()
{
	if (equipment == NULL)
	{
		return;
	}

	WeponGem weponGem = gemFillSprite.weponGem;
	Gem* gem = equipment->gem;

	if (gem != NULL)
	{
		Gem* t = (Gem*)itemManager->itemArray[weponGem.id];
		itemManager->itemArray[weponGem.id] = equipment->gem;
		equipment->gem = t;
	}
	else
	{
		equipment->gem = weponGem.gem;
		itemManager->itemArray[weponGem.id] = NULL;

		equipment->attribute.chuShiDianShu += equipment->gem->getAttributeValue();
	}
}