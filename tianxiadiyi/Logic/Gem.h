#ifndef __GEM_H__
#define __GEM_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Item.h"

#include "tinytab\DataBase.h"
#include "tinytab\DBC_Struct.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

enum GEM_TYPE
{
	BAI_HU_SHI = 1,
	XUAN_WU_SHI,
	ZHU_QUE_SHI,
	QING_LONG_SHI,
	XUE_SHI,
	QIANG_HUA_SHI,
	XING_YUN_SHI,
	BAO_HU_SHI
};

class Gem : public Item
{
public:

	_DBC_GEM attribute;
	int lv;

	Gem(int id);
	~Gem();

	int getAttributeValue();
};

#endif