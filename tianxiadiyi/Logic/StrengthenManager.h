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

struct StrengthenEquipment
{
	int id;
	Equipment* equipment;
};

class StrengthenManager
{
public:
	
	FormationManager* formationManager;
	ItemManager* itemManager;

	vector<StrengthenEquipment>equipmentVector;

	// ѡ��Ľ���
	int selectGeneralId;

	// ѡ���װ��
	int selectEquipmentId;

	// װ����ǰҳ
	int pageNum;
	int maxPageNum;

	StrengthenManager();
	~StrengthenManager();

	static StrengthenManager* getTheOnlyInstance();

	void init();
};

#endif