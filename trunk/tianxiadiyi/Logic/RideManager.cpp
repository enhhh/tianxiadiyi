#include "RideManager.h"

static RideManager* rideManager = NULL;

RideManager::RideManager()
{
	for (int i = 0; i < 12; i++)
	{
		Ride* ride = new Ride(i);
		rideVector.push_back(ride);
	}

	selectRideId = 0;

	pageNum = 0;
	maxPageNum = (rideVector.size()-1) / 8 + 1;

	if (rideVector.size() == 0)
	{
		maxPageNum = 0;
	}
}

RideManager::~RideManager()
{
}

RideManager* RideManager::getTheOnlyInstance()
{
	if (!rideManager)
	{
		rideManager = new RideManager();
	}

	return rideManager;
}
