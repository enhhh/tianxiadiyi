#include "ChapterManager.h"

static ChapterManager* chapterManager = NULL;

ChapterManager::ChapterManager()
{
	for (int i = 0; i < 5; i++)
	{
		Charpter chapter = {false};
		chapterVector.push_back(chapter);
	}

	selectChapterId = 0;
	selectRoundId = 0;
	selectLevelId = 0;
}

ChapterManager::~ChapterManager()
{
}

ChapterManager* ChapterManager::getTheOnlyInstance()
{
	if (!chapterManager)
	{
		chapterManager = new ChapterManager();
	}

	return chapterManager;
}

vector<string> ChapterManager::getArmyVector()
{
	const tDataBase* roundTab = CDataBaseSystem::GetMe()->GetDataBase(DBC_ROUND);
	const _DBC_ROUND* round = (_DBC_ROUND*)roundTab->Search_Index_EQU(selectChapterId*30+selectRoundId*6+selectLevelId+1);
	vector<string> armyVector = CDataBase::GetSplitData(round->army);

	return armyVector;
}

void ChapterManager::setArmyFormation()
{
	vector<string>armyVector = getArmyVector();

	bool isHasBoss = false;
	
	for (int i = 0; i < armyVector.size(); i++)
	{
		const tDataBase* soliderTab = CDataBaseSystem::GetMe()->GetDataBase(DBC_SOLIDER);
		const _DBC_SOLIDER* solider = (_DBC_SOLIDER*)soliderTab->Search_Index_EQU(atoi(armyVector[i].c_str()));

		if (solider->jieBie == 1)
		{
			isHasBoss = true;
			break;
		}
	}

	const tDataBase* soliderPositionTab = CDataBaseSystem::GetMe()->GetDataBase(DBC_SOLIDER_POSITION);
	const _DBC_SOLIDER_POSITION* soliderPosition = (_DBC_SOLIDER_POSITION*)soliderPositionTab->Search_Index_EQU(armyVector.size());
	
	vector<string> soliderPositionVector;

	if (isHasBoss)
	{
		soliderPositionVector = CDataBase::GetSplitData(soliderPosition->youBossZhanWei);
	}
	else
	{
		soliderPositionVector = CDataBase::GetSplitData(soliderPosition->wuBossZhanWei);
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			formationArmyArray[i][j] = false;
		}
	}

	int grid[9][2] = 
	{
		{0, 0},
		{1, 0},
		{2, 0},

		{0, 1},
		{1, 1},
		{2, 1},

		{0, 2},
		{1, 2},
		{2, 2}
	};

	for (int i = 0; i < soliderPositionVector.size(); i++)
	{
		 int p = atoi(soliderPositionVector[i].c_str());
		 formationArmyArray[grid[p-1][0]][grid[p-1][1]] = true;
	}
}
