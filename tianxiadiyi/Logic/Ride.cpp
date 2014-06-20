#include "Ride.h"

Ride::Ride(int id)
{
	const tDataBase* rideTab = CDataBaseSystem::GetMe()->GetDataBase(DBC_RIDE);
	const _DBC_RIDE* ride = (_DBC_RIDE*)rideTab->Search_LineNum_EQU(id);
	attribute = *ride;

	lv = 1;
	strengthenLv = 1;

	vector<string> strengthenAttribute = getStrengthenAttribute(strengthenLv);
	attribute.chuShiGongJi += atoi(strengthenAttribute[0].c_str());
	attribute.chuShiFangYu += atoi(strengthenAttribute[1].c_str());
	attribute.chuShiShengMing += atoi(strengthenAttribute[2].c_str());
}

Ride::~Ride()
{
}

vector<string> Ride::getStrengthenAttribute(int strengthenLv)
{
	const tDataBase* rideStrengthenTab = CDataBaseSystem::GetMe()->GetDataBase(DBC_RIDE_STRENGTHEN_MANAGER);
	const _DBC_RIDE_STRENGTHEN* rideStrengthen = (_DBC_RIDE_STRENGTHEN*)rideStrengthenTab->Search_Index_EQU(attribute.id);

	vector<string> strengthenAttributeVector;

	switch(lv)
	{
	case 1:
		return CDataBase::GetSplitData(rideStrengthen->yiJiShuZhi);
		break;
	case 2:
		return CDataBase::GetSplitData(rideStrengthen->erJiShuZhi);
		break;
	case 3:
		return CDataBase::GetSplitData(rideStrengthen->sanJiShuZhi);
		break;
	case 4:
		return CDataBase::GetSplitData(rideStrengthen->siJiShuZhi);
		break;
	case 5:
		return CDataBase::GetSplitData(rideStrengthen->wuJiShuZhi);
		break;
	case 6:
		return CDataBase::GetSplitData(rideStrengthen->liuJiShuZhi);
		break;
	case 7:
		return CDataBase::GetSplitData(rideStrengthen->qiJiShuZhi);
		break;
	case 8:
		return CDataBase::GetSplitData(rideStrengthen->baJiShuZhi);
		break;
	case 9:
		return CDataBase::GetSplitData(rideStrengthen->jiuJiShuZhi);
		break;
	case 10:
		return CDataBase::GetSplitData(rideStrengthen->shiJiShuZhi);
		break;
	}

	return strengthenAttributeVector;
}
