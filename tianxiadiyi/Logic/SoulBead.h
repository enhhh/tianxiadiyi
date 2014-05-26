#ifndef __SOUL_BEAD_H__
#define __SOUL_BEAD_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Item.h"

#include "tinytab\DataBase.h"
#include "tinytab\DBC_Struct.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

class SoulBead : public Item
{
public:
	// ªÍ÷È∂Øª≠
	CCArmature* armature;
	_DBC_SOUL_BEAD attribute;

	SoulBead(int id);
	~SoulBead();
};

#endif