#include "StarringManager.h"

static StarringManager* starringManager = NULL;

StarringManager::StarringManager()
{
	telentPageNum = 0;

	for (int i = 0; i < 12; i++)
	{
		soulBeadSpriteArray[i].armature = NULL;
	}

	for (int i = 0; i < 10; i++)
	{
		soulBeadEquipSpriteArray[i].armature = NULL;
	}

	for (int i = 0; i < 22; i++)
	{
		int id = rand() % 10;
		soulBeadVector.push_back(new SoulBead(id));
	}

	isSelectSoulBead = true;

	soulPageNum = 0;
	soulMaxPageNum = (soulBeadVector.size()-1) / 12 + 1;

	if (soulBeadVector.size() == 0)
	{
		soulMaxPageNum = 0;
	}

	if (soulMaxPageNum > 0)
	{
		soulBeadArray = new SoulBead*[soulMaxPageNum*12];

		for (int i = 0; i < soulMaxPageNum*12; i++)
		{
			soulBeadArray[i] = NULL;
		}

		for (int i = 0; i < 22; i++)
		{
			soulBeadArray[i] = soulBeadVector[i];
		}
	}

	for (int i = 0; i < 10; i++)
	{
		soulBeadEquipArray[i] = NULL;
	}

	selectSoulBeadId = 0;
	selectSoulBeadCircleId = 0;
}

StarringManager::~StarringManager()
{
}

StarringManager* StarringManager::getTheOnlyInstance()
{
	if (!starringManager)
	{
		starringManager = new StarringManager();
	}

	return starringManager;
}