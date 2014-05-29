#ifndef __RIDE_H__
#define __RIDE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "tinytab\DataBase.h"
#include "tinytab\DBC_Struct.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

class Ride
{
public:
	_DBC_RIDE attribute;

	Ride(int id);
	~Ride();
};

#endif