#include "GeneralManager.h"

static GeneralManager* generalManager = NULL;

GeneralManager::GeneralManager()
{
	for (int i = 0; i < 8; i++)
	{
		General* general = new General(i+1);

		// 将领数组
		for (int i = 0; i < 6; i++)
		{
			if (i % 2 == 0)
			{
				int id = rand() % 70 + 1;
				general->equipmentArray[i] = new Equipment(id);
			}
			else
			{
				general->equipmentArray[i] = NULL;
			}
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