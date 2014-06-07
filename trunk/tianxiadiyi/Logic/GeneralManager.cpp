#include "GeneralManager.h"

static GeneralManager* generalManager = NULL;

GeneralManager::GeneralManager()
{
	for (int i = 0; i < 8; i++)
	{
		General* general = new General(i+1);

		int equipmentId[6] = {36, 1, 1, 15, 35, 35};

		// 将领数组
		for (int i = 0; i < 6; i++)
		{
			// general->equipmentArray[i] = new Equipment(equipmentId[i]);
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