#ifndef __GENERAL_MANAGER_H__
#define __GENERAL_MANAGER_H__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Sprite\General.h"
#include "Logic\ItemManager.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace std;

// 武器、兵符、兵书、铠甲、披风、坐骑
enum General_EQUIPMENT_TYPE
{
	GENERAL_WU_QI = 0,
	GENERAL_BING_FU,
	GENERAL_BING_SHU,
	GENERAL_KAI_JIA,
	GENERAL_PI_FENG,
	GENERAL_ZUO_JI
};

struct GeneralItem
{
	int id;
	Equipment* equipment;
};

struct ItemSprite
{
	GeneralItem generalItem;
	CCSprite* sprite;
};

class GeneralManager
{
public:

	ItemManager* itemManager;

	// 将领列表
	vector<General*>generalVector;

	// 选择的将领
	int selectGeneralId;

	// 选择的装备
	int selectEquipmentId;

	// 将领当前页数
	int pageNum;

	// 将领最大页数
	int maxPageNum;

	GeneralItem* generalItemArray;

	ItemSprite itemSpriteArray[9];

	// 选择的物品
	int selectItemId;

	// 物品当前页数
	int itemPageNum;

	// 物品最大页数
	int itemMaxPageNum;

	GeneralManager();
	~GeneralManager();

	static GeneralManager* getTheOnlyInstance();
	void addAttribute(int type);
};

#endif