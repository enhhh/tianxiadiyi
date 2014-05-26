#ifndef _FORMATION_H__
#define _FORMATION_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "tinytab\DataBase.h"
#include "tinytab\DBC_Struct.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

class Formation
{
public:

	_DBC_FORMATION attribute;

	Formation(int id);
	~Formation();
};

#endif