#include "RideStrengthenManager.h"

static RideStrengthenManager* rideStrengthenManager = NULL;

RideStrengthenManager::RideStrengthenManager()
{
	rideManager = RideManager::getTheOnlyInstance();
	
}

RideStrengthenManager::~RideStrengthenManager()
{
}

RideStrengthenManager* RideStrengthenManager::getTheOnlyInstance()
{
	if (!rideStrengthenManager)
	{
		rideStrengthenManager = new RideStrengthenManager();
	}

	return rideStrengthenManager;
}

void RideStrengthenManager::init()
{
	ride = rideManager->rideVector[rideManager->selectRideId];
}
