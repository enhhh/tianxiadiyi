#include "Ride.h"

Ride::Ride(int id)
{
	const tDataBase* rideTab = CDataBaseSystem::GetMe()->GetDataBase(DBC_RIDE);
	const _DBC_RIDE* ride = (_DBC_RIDE*)rideTab->Search_LineNum_EQU(id);
	attribute = *ride;
}

Ride::~Ride()
{
}