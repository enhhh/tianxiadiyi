#ifndef __GENERAL_MANAGER_H__
#define __GENERAL_MANAGER_H__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Sprite\General.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace std;

// 武器、兵符、兵书、铠甲、披风、坐骑

class GeneralManager
{
public:

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

	GeneralManager();
	~GeneralManager();

	static GeneralManager* getTheOnlyInstance();
};

#endif