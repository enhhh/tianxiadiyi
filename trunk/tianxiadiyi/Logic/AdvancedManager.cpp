#include "AdvancedManager.h"

#include "tinytab\DataBase.h"
#include "tinytab\DBC_Struct.h"

static AdvancedManager* advancedManager = NULL;

AdvancedManager::AdvancedManager()
{
	generalManager = GeneralManager::getTheOnlyInstance();
}

AdvancedManager::~AdvancedManager()
{
}

void AdvancedManager::init()
{
	general = generalManager->generalVector[generalManager->selectGeneralId];
}

AdvancedManager* AdvancedManager::getTheOnlyInstance()
{
	if (!advancedManager)
	{
		advancedManager = new AdvancedManager();
	}

	return advancedManager;
}

int AdvancedManager::getAdvancedAddAttribute()
{
	const tDataBase* advancedTab = CDataBaseSystem::GetMe()->GetDataBase(DBC_ADVANCED);
	const _DBC_ADVANCED* advanced = (_DBC_ADVANCED*)advancedTab->Search_LineNum_EQU(general->advanced);
	return advanced->jiaChengDianShu;
}

vector<string> AdvancedManager::getAdvancedConsume()
{
	const tDataBase* advancedTab = CDataBaseSystem::GetMe()->GetDataBase(DBC_ADVANCED);
	const _DBC_ADVANCED* advanced = (_DBC_ADVANCED*)advancedTab->Search_LineNum_EQU(general->advanced);

	vector<string>splitVector = CDataBase::GetSplitData(advanced->xiaoHaoPin);
	return splitVector;
}

void AdvancedManager::advanced()
{
	int add = advancedManager->getAdvancedAddAttribute();

	general->attribute.wuLi += add;
	general->attribute.zhiLi += add;
	general->attribute.tiLi += add;
	general->attribute.minJie += add;
}
