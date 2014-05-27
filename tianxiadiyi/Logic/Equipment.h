#ifndef __EQUIPMENT_H__
#define __EQUIPMENT_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "Item.h"

#include "tinytab\DataBase.h"
#include "tinytab\DBC_Struct.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

enum EQUIPMENT_TYPE
{
	BING_FU = 1,
	KAI_JIA,
	PI_FENG,
	SHANG_ZI,
	JIAN,
	QIANG,
	DAO,
	GONG_JIAN,
	BING_SHU
};

class Equipment : public Item
{
public:

	_DBC_EQUIPMENT attribute;

	Equipment(int id);
	~Equipment();
};

#endif