#ifndef __ITEM_MANAGER_H__
#define __ITEM_MANAGER_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Item.h"
#include "Equipment.h"
#include "Gem.h"
#include "SoulBead.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

class ItemManager
{
public:
	ItemManager();
	~ItemManager();

	vector<Item*>itemVector;
	vector<Gem*>gemVector;
	vector<Equipment*>equipmentVector;

	// ±³°ü
	Item** itemArray;

	int pageNum;
	int maxPageNum;

	int selectItemId;

	static ItemManager* getTheOnlyInstance();

	int getGemNum();
};

#endif