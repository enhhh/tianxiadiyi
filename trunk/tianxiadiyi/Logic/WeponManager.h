#ifndef __WEPON_MANAGER_H__
#define __WEPON_MANAGER_H__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Gem.h"
#include "Equipment.h"
#include "ItemManager.h"
#include "WeponTakeUpManager.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace std;

struct WeponGem
{
	int id;
	Gem* gem;
};

struct GemSprite
{
	WeponGem weponGem;
	CCSprite* sprite;
};

class WeponManager
{
public:
	ItemManager* itemManager;
	WeponTakeUpManager* weponTakeUpManager;

	vector<WeponGem> gemVector;

	int pageNum;
	int maxPageNum;

	GemSprite gemSpriteArray[4];
	GemSprite gemFillSprite;

	Equipment* equipment;
	WeponGem* weponGemArray;

	int selectGemId;

	WeponManager();
	~WeponManager();

	static WeponManager* getTheOnlyInstance();
	void init();
	void fillEXT();
	void fill();
};

#endif