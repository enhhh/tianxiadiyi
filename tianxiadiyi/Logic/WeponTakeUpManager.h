#ifndef __WEPON_TAKE_UP_MANAGER_H__
#define __WEPON_TAKE_UP_MANAGER_H__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Equipment.h"
#include "ItemManager.h"
#include "GeneralManager.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace std;

struct WeponTakeUpEquipment
{
	int id;
	Equipment* equipment;
};

class WeponTakeUpManager
{
public:

	ItemManager* itemManager;
	GeneralManager* generalManager;

	General* general;
	Equipment* equipment;
	vector<WeponTakeUpEquipment>equipmentVector;
	
	int selectEquipmentId;
	int pageNum;
	int maxPageNum;

	WeponTakeUpManager();
	~WeponTakeUpManager();

	static WeponTakeUpManager* getTheOnlyInstance();
	void init();
	void takeUp();
};

#endif