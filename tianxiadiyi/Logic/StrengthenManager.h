#ifndef __STRENGTHEN_MANAGER_H__
#define __STRENGTHEN_MANAGER_H__

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

class StrengthenManager
{
public:
	
	FormationManager* formationManager;
	ItemManager* itemManager;

	// 选择的将领
	int selectGeneralId;

	// 选择的装备
	int selectEquipmentId;

	// 装备当前页
	int pageNum;

	StrengthenManager();
	~StrengthenManager();

	static StrengthenManager* getTheOnlyInstance();

	int getMaxPageNum();
};

#endif