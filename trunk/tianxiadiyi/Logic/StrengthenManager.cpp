#include "StrengthenManager.h"

static StrengthenManager* strengthenManager = NULL;

StrengthenManager::StrengthenManager()
{
	formationManager = FormationManager::getTheOnlyInstance();
	itemManager = ItemManager::getTheOnlyInstance();

	// ѡ��Ľ���
	selectGeneralId = 0;

	// ѡ���װ��
	selectEquipmentId = 0;

	// װ����ǰҳ
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