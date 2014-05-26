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

	// 装备当前页
	pageNum = 0;
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

int StrengthenManager::getMaxPageNum()
{
	int size = 0;

	if (selectGeneralId == 0)
	{
		size = itemManager->equipmentVector.size() ;
	}
	else
	{
		size = formationManager->generalVector[selectGeneralId-1]->equipmentVector.size();
	}

	int maxPageNum = (size-1) / 4 + 1;

	if (size == 0)
	{
		maxPageNum = 0;
	}

	return maxPageNum;
}