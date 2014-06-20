#ifndef __RIDE_STRENGTHEN_MANAGER_H__
#define __RIDE_STRENGTHEN_MANAGER_H__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Ride.h"
#include "RideManager.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace std;

class RideStrengthenManager
{
public:
	RideManager* rideManager;
	Ride* ride;

	RideStrengthenManager();
	~RideStrengthenManager();

	static RideStrengthenManager* getTheOnlyInstance();
	void init();
};

#endif