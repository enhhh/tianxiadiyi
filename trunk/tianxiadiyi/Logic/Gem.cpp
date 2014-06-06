#include "Gem.h"

Gem::Gem(int id)
{
	const tDataBase* gemTab = CDataBaseSystem::GetMe()->GetDataBase(DBC_GEM);
	const _DBC_GEM* gem = (_DBC_GEM*)gemTab->Search_LineNum_EQU(id);
	attribute = *gem;

	lv = 1;

	type = GEM;
}

Gem::~Gem()
{
}

int Gem::getAttributeValue()
{
	const tDataBase* gemStrengthenTab = CDataBaseSystem::GetMe()->GetDataBase(DBC_GEM_STRENGTHEN);
	const _DBC_GEM_STRENGTHEN* gemStrengthen = (_DBC_GEM_STRENGTHEN*)gemStrengthenTab->Search_Index_EQU(attribute.id);

	switch(lv)
	{
	case 1: 
		return gemStrengthen->yiJiShuXingZhi;
		break;
	case 2: 
		return gemStrengthen->erJiShuXingZhi;
		break;
	case 3:
		return gemStrengthen->sanJiShuXingZhi;
		break;
	case 4:
		return gemStrengthen->siJiShuXingZhi;
		break;
	case 5:
		return gemStrengthen->wuJiShuXingZhi;
		break;
	case 6:
		return gemStrengthen->liuJiShuXingZhi;
		break;
	case 7:
		return gemStrengthen->qiJiShuXingZhi;
		break;
	case 8:
		return gemStrengthen->baJiShuXingZhi;
		break;
	case 9:
		return gemStrengthen->jiuJiShuXingZhi;
		break;
	case 10:
		return gemStrengthen->shiJiShuXingZhi;
		break;
	}
}
