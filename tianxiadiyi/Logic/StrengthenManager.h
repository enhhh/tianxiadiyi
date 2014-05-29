#ifndef __STRENGTHEN_MANAGER_H__
#define __STRENGTHEN_MANAGER_H__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Equipment.h"
#include "Gem.h"

#include "FormationManager.h"
#include "ItemManager.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace std;

enum STRENGTHEN_GEM_TYPE
{
	STRENGTHEN_GEM_PROTECT = 0,
	STRENGTHEN_GEM_LUCKY
};

struct StrengthenEquipment
{
	int id;
	Equipment* equipment;
};

struct StrengthenGem
{
	int id;
	Gem* gem;
};

class StrengthenManager
{
public:
	
	FormationManager* formationManager;
	ItemManager* itemManager;

	vector<StrengthenGem>strengthenGemVector;
	vector<StrengthenGem>protectGemVector;
	vector<StrengthenGem>luckyGemVector;

	vector<StrengthenEquipment>equipmentVector;

	// 选择的将领
	int selectGeneralId;

	// 选择的装备
	int selectEquipmentId;

	// 选择的宝石
	int selectGemId;

	// 装备当前页
	int pageNum;
	int maxPageNum;

	StrengthenManager();
	~StrengthenManager();

	static StrengthenManager* getTheOnlyInstance();

	void init();
	void strengthen();
};

#endif