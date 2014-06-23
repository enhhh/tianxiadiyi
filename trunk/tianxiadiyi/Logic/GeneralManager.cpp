#include "GeneralManager.h"

static GeneralManager* generalManager = NULL;

GeneralManager::GeneralManager()
{
	itemManager = ItemManager::getTheOnlyInstance();

	for (int i = 0; i < 8; i++)
	{
		General* general = new General(i+1);

		int equipmentId[6] = {36, 1, 1, 15, 35, 35};

		// 将领数组
		for (int i = 0; i < 6; i++)
		{
			general->equipmentArray[i] = NULL;
		}

		generalVector.push_back(general);
	}

	selectGeneralId = 0;

	pageNum = 0;
	maxPageNum = (generalVector.size()-1) / 3 + 1;

	if (generalVector.size() == 0)
	{
		maxPageNum = 0;
	}

	for (int i = 0; i < 9; i++)
	{
		itemSpriteArray[i].generalItem.equipment = NULL;
		itemSpriteArray[i].sprite = NULL;
	}

	selectItemId = 0;
	itemPageNum = 0;
	itemMaxPageNum = (itemManager->getEquipmentNum()-1) / 9 + 1;

	if (itemManager->getEquipmentNum() == 0)
	{
		itemMaxPageNum = 0;
	}

	if (itemMaxPageNum > 0)
	{
		generalItemArray = new GeneralItem[itemMaxPageNum*9];

		for (int i = 0; i < itemMaxPageNum*9; i++)
		{
			generalItemArray[i].id = -1;
			generalItemArray[i].equipment = NULL;
		}

		int j = 0;

		for (int i = 0; i < itemManager->maxPageNum*16; i++)
		{
			Item* item = itemManager->itemArray[i];

			if (item != NULL)
			{
				if (item->type == EQUIPMENT)
				{
					GeneralItem generalItem = {i, (Equipment*)item};
					generalItemArray[j++] = generalItem;
				}
			}
		}
	}
}

GeneralManager::~GeneralManager()
{
}

GeneralManager* GeneralManager::getTheOnlyInstance()
{
	if (!generalManager)
	{
		generalManager = new GeneralManager();
	}

	return generalManager;
}

void GeneralManager::addAttribute( int type )
{
	if (generalVector.size() == 0)
	{
		return;
	}

	if (selectGeneralId >= generalVector.size())
	{
		return;
	}

	General* general = generalManager->generalVector[generalManager->selectGeneralId];

	if (general->attributePoint <= 0)
	{
		return;
	}

	general->attributePoint--;

	switch(type)
	{
	case 0:
		general->attribute.wuLi += 1;
		// 武力
		break;
	case 1:
		// 智力
		general->attribute.zhiLi += 1;
		break;
	case 2:
		// 体力
		general->attribute.tiLi += 1;
		break;
	case 3:
		// 敏捷
		general->attribute.minJie += 1;
		break;
	}
}