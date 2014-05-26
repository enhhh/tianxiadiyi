#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

enum ITEM_TYPE
{
	EQUIPMENT = 0,
	GEM = 1
};

class Item
{
public:

	int type;

	Item();
	~Item();
};

#endif