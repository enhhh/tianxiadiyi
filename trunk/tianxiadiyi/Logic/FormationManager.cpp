#include "FormationManager.h"

static FormationManager* formationManager = NULL;

// 阵型
bool formationArrary[11][3][3] = 
{
	    // 基础阵法
	{
		{false, false, false},
		{true, false, false},
		{false, false, false}
	},
	    // 一字长蛇阵
	{
		{true, true, false},
		{true, false, false},
		{true, true, false}
	},
		// 二龙出水阵
	{
		{true, true, false},
		{false, true, false},
		{true, true, false}
	},
		// 天地三才阵
	{
		{false, false, true},
		{true, true, true},
		{false, false, true}
	},
		// 四门兜底阵
	{
		{false, true, false},
		{false, true, true},
		{true, true, true}
	},
		// 五虎群羊阵
	{
		{true, true, true},
		{true, false, false},
		{true, false, false}
	},
		// 六丁六甲阵
	{
		{false, true, false},
		{false, true, false},
		{true, true, true}
	},
		// 北斗七星阵
	{
		{false, true, true},
		{false, true, false},
		{true, true, false}
	},
		// 八门金锁阵
	{
		{false, true, true},
		{true, false, false},
		{false, true, true}
	},
		// 九字连环阵
	{
		{true, false, true},
		{false, true, false},
		{true, false, true}
	},
		// 十面埋伏阵
	{
		{true, true, true},
		{true, true, true},
		{true, true, true}
	},
};

FormationManager::FormationManager()
{
	for (int i = 0; i < 11; i++)
	{
		formationVector.push_back(new Formation(i));
	}

	generalVector = GeneralManager::getTheOnlyInstance()->generalVector;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			generalSpriteArray[i][j].general = NULL;
			generalSpriteArray[i][j].sprite = NULL;
		}
	}

	selectPreId = 0; 
	selectId = 0;

	pageNum = 0;
	maxPageNum = (generalVector.size()-1) / 8 + 1;

	if (generalVector.size() == 0)
	{
		maxPageNum = 0;
	}
}

FormationManager::~FormationManager()
{
}

FormationManager* FormationManager::getTheOnlyInstance()
{
	if (!formationManager)
	{
		formationManager = new FormationManager();
	}

	return formationManager;
}
