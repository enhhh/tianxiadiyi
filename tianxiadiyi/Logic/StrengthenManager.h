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

	// ѡ��Ľ���
	int selectGeneralId;

	// ѡ���װ��
	int selectEquipmentId;

	// װ����ǰҳ
	int pageNum;

	StrengthenManager();
	~StrengthenManager();

	static StrengthenManager* getTheOnlyInstance();

	int getMaxPageNum();
};

#endif