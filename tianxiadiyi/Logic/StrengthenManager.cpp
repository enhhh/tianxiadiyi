#include "StrengthenManager.h"

static StrengthenManager* strengthenManager = NULL;

StrengthenManager::StrengthenManager()
{
	formationManager = FormationManager::getTheOnlyInstance();
	itemManager = ItemManager::getTheOnlyInstance();

	// 选择的将领
	selectGeneralId = 0;

	// 选择的装备
	selectEquipmentId = 0;

	init();
}

StrengthenManager::~StrengthenManager()
{
}

StrengthenManager* StrengthenManager::getTheOnlyInstance()
{
	if (!strengthenManager)
	{
		strengthenManager = new StrengthenManager();
	}

	return strengthenManager;
}

void StrengthenManager::init()
{
	strengthenGemVector.clear();
	protectGemVector.clear();
	luckyGemVector.clear();

	for (int i = 0; i < itemManager->maxPageNum*16; i++)
	{
		Item* item = itemManager->itemArray[i];

		if (item != NULL)
		{
			if (item->type == GEM)
			{
				Gem* gem = (Gem*)item;

				StrengthenGem strengthenGem = {i, gem};
				
				switch (gem->attribute.zhongLei)
				{
				case QIANG_HUA_SHI:
					strengthenGemVector.push_back(strengthenGem);
					break;
				case XING_YUN_SHI:
					luckyGemVector.push_back(strengthenGem);
					break;
				case BAO_HU_SHI:
					protectGemVector.push_back(strengthenGem);
					break;
				}
			}
		}
	}

	equipmentVector.clear();

	if (selectGeneralId == 0)
	{
		for (int i = 0; i < itemManager->maxPageNum*16; i++)
		{
			Item* item = itemManager->itemArray[i];

			if (item != NULL)
			{
				if (item->type == EQUIPMENT)
				{
					StrengthenEquipment strengthenEquipment = {i, (Equipment*)item};
					equipmentVector.push_back(strengthenEquipment);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 6; i++)
		{
			if (formationManager->generalVector[selectGeneralId-1]->equipmentArray[i] != NULL)
			{
				Equipment* equipment = formationManager->generalVector[selectGeneralId-1]->equipmentArray[i];
				StrengthenEquipment strengthenEquipment = {i, equipment};
				equipmentVector.push_back(strengthenEquipment);
			}
		}
	}

	// 装备当前页
	pageNum = 0;

	maxPageNum = (equipmentVector.size()-1) / 4 + 1;

	if (equipmentVector.size() == 0)
	{
		maxPageNum = 0;
	}
}