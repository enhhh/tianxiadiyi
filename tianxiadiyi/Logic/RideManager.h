#ifndef __RIDE_MANAGER_H__
#define __RIDE_MANAGER_H__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Ride.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace std;

class RideManager
{
public:
	RideManager();
	~RideManager();

	vector<Ride*>rideVector;

	int selectRideId;
	int pageNum;
	int maxPageNum;

	static RideManager* getTheOnlyInstance();
};

#endif