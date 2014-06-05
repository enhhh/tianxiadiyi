#include "StarringManager.h"
#include "..\TianXiaDiYi.h"

#include "tinytab\DataBase.h"
#include "tinytab\DBC_Struct.h"

#include "Packets\Starring\CGCulture.h"
#include "Packets\Starring\CGLightUpTelent.h"
#include "Packets\Starring\CGPutOnSoulBead.h"
#include "Packets\Starring\CGTakeOffSoulBead.h"
#include "Packets\Starring\CGSwapSoulBead.h"

static StarringManager* starringManager = NULL;

StarringManager::StarringManager()
{
	player = TianXiaDiYi::getTheOnlyInstance()->mainCityScene->player;

	cultureSuccessRate[0] = 50;
	cultureSuccessRate[1] = 70;
	cultureSuccessRate[2] = 90;

	selectCultureId = 0;

	for (int i = 0; i < 5; i++)
	{
		telentLightPoint[i] = 0;
	}

	for (int i = 0; i < 5 ; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			telentPoint[i][j] = false;
		}
	}

	selectTelentPointId = 0;
	telentPageNum = 0;

	for (int i = 0; i < 12; i++)
	{
		soulBeadSpriteArray[i].armature = NULL;
	}

	for (int i = 0; i < 10; i++)
	{
		soulBeadEquipSpriteArray[i].armature = NULL;
	}

	for (int i = 0; i < 22; i++)
	{
		int id = rand() % 10;
		soulBeadVector.push_back(new SoulBead(id));
	}

	isSelectSoulBead = true;

	soulPageNum = 0;
	soulMaxPageNum = (soulBeadVector.size()-1) / 12 + 1;

	if (soulBeadVector.size() == 0)
	{
		soulMaxPageNum = 0;
	}

	if (soulMaxPageNum > 0)
	{
		soulBeadArray = new SoulBead*[soulMaxPageNum*12];

		for (int i = 0; i < soulMaxPageNum*12; i++)
		{
			soulBeadArray[i] = NULL;
		}

		for (int i = 0; i < 22; i++)
		{
			soulBeadArray[i] = soulBeadVector[i];
		}
	}

	for (int i = 0; i < 10; i++)
	{
		soulBeadEquipArray[i] = NULL;
	}

	selectSoulBeadId = 0;
	selectSoulBeadEquipId = 0;
}

StarringManager::~StarringManager()
{
}

StarringManager* StarringManager::getTheOnlyInstance()
{
	if (!starringManager)
	{
		starringManager = new StarringManager();
	}

	return starringManager;
}

void StarringManager::culture()
{
	if (player->attribute.wuLi == player->lv)
	{
		return;
	}

	CGCulture culture;
	culture.playerGuid = 1;
	culture.type = 0;
	TianXiaDiYi::getTheOnlyInstance()->socketWrap->SendPacket(&culture);

	/*int randRate = rand() % 100;

	if (randRate < cultureSuccessRate[selectCultureId])
	{
		player->attribute.wuLi += 1;
		player->attribute.zhiLi += 1;
		player->attribute.tiLi += 1;
		player->attribute.minJie += 1;
	}*/
}

int StarringManager::getTelentPointValue( int telentID, int point )
{
	const tDataBase* telentTab = CDataBaseSystem::GetMe()->GetDataBase(DBC_TELENT);
	const _DBC_TELENT* telent = (_DBC_TELENT*)telentTab->Search_LineNum_EQU(telentID);

	switch(point)
	{
	case 0:
		return telent->diYiGeDian;
		break;
	case 1:
		return telent->diErGeDian;
		break;
	case 2:
		return telent->diYiGeDian;
		break;
	case 3:
		return telent->diSanGeDian;
		break;
	case 4:
		return telent->diSiGeDian;
		break;
	case 5:
		return telent->diWuGeDian;
		break;
	case 6:
		return telent->diLiuGeDian;
		break;
	case 7:
		return telent->diQiGeDian;
		break;
	case 8:
		return telent->diBaGeDian;
		break;
	case 9:
		return telent->diJiuGeDian;
		break;
	case 10:
		return telent->diShiGeDian;
		break;
	case 11:
		return telent->diShiGeDian;
		break;
	case 12:
		return telent->diShiErGeDian;
		break;
	case 13:
		return telent->diShiSanGeDian;
		break;
	case 14:
		return telent->diShiSiGeDian;
	case 15:
		return telent->diShiWuGeDian;
	case 16:
		return telent->diShiLiuGeDian;
	case 17:
		return telent->diShiQiGeDian;
	case 18:
		return telent->diShiJiuGeDian;
	case 19:
		return telent->diErShiGeDian;
		break;
	}

	return 0;
}

void StarringManager::lightUpTelentPoint()
{
	int telentLv[5] = {10, 30, 50, 70, 90};

	if (player->lv < telentLv[telentPageNum])
	{
		return;
	}

	CGLightUpTelent lightUpTelent;
	lightUpTelent.playerGuid = 1;
	lightUpTelent.type = 1;
	TianXiaDiYi::getTheOnlyInstance()->socketWrap->SendPacket(&lightUpTelent);

	if (selectTelentPointId == telentLightPoint[telentPageNum])
	{
		telentLightPoint[telentPageNum]++;

		int v = getTelentPointValue(telentPageNum, selectTelentPointId);

		switch(telentPageNum)
		{
		case BAI_HU:
			player->attribute.wuLiFangYu += v;
			player->attribute.faShuFangYu += v;
			break;
		case XUAN_WU:
			player->attribute.shengMing += v;
			break;
		case QING_LONG:
			player->attribute.wuLiGongJi += v;
			player->attribute.wuLiFangYu += v;
			break;
		case ZHU_QUE:
			player->attribute.faShuGongJi += v;
			player->attribute.faShuFangYu += v;
			break;
		case QI_LIN:
			player->attribute.wuLiGongJi += v;
			player->attribute.wuLiFangYu += v;
			player->attribute.faShuGongJi += v;
			player->attribute.faShuFangYu += v;
			player->attribute.shengMing += v;
			break;
		}
	}
}

void StarringManager::addSoulBeadAtrribute( SoulBead* soulBead, int add )
{
	switch(soulBead->attribute.zhongLei)
	{
	case WU_LI_SOUL_BEAD:
		player->attribute.wuLi += soulBead->attribute.shuXingZhi * add;
		break;
	case ZHI_LI_SOUL_BEAD:
		player->attribute.zhiLi += soulBead->attribute.shuXingZhi * add;
		break;
	case TI_LI_SOUL_BEAD:
		player->attribute.tiLi += soulBead->attribute.shuXingZhi * add;
		break;
	case NU_QI_SOUL_BEAD:
		player->attribute.nuQi += soulBead->attribute.shuXingZhi * add;
		break;
	case BAO_JI_SOUL_BEAD:
		player->attribute.baoJi += soulBead->attribute.shuXingZhi * add;
		break;
	case SHAN_BI_SOUL_BEAD:
		player->attribute.shanBi += soulBead->attribute.shuXingZhi * add;
		break;
	case SHI_PO_SOUL_BEAD:
		player->attribute.shiPo += soulBead->attribute.shuXingZhi * add;
		break;
	case MING_ZHONG_SOUL_BEAD:
		player->attribute.mingZhong += soulBead->attribute.shuXingZhi * add;
		break;
	case GE_DANG_SOUL_BEAD:
		player->attribute.geDang += soulBead->attribute.shuXingZhi * add;
		break;
	case BAO_JI_SHANG_HAI_SOUL_BEAD:
		player->attribute.baoJiShangHai += soulBead->attribute.shuXingZhi * add;
		break;
	}
}

void StarringManager::putOnSoulBead()
{
	CGPutOnSoulBead cgPutOnSoulBead;
	cgPutOnSoulBead.playerGuid = 1;
	cgPutOnSoulBead.srcPosition = 1;
	cgPutOnSoulBead.destPosition = 1;

	TianXiaDiYi::getTheOnlyInstance()->socketWrap->SendPacket(&cgPutOnSoulBead);

	SoulBead* t = starringManager->soulBeadEquipArray[starringManager->selectSoulBeadEquipId];

	if (t != NULL)
	{
		addSoulBeadAtrribute(t, -1);
	}

	SoulBead* s = starringManager->soulBeadArray[starringManager->selectSoulBeadId];
	starringManager->soulBeadArray[starringManager->selectSoulBeadId] = starringManager->soulBeadEquipArray[starringManager->selectSoulBeadEquipId];
	starringManager->soulBeadEquipArray[starringManager->selectSoulBeadEquipId] = s;

	if (s != NULL)
	{
		addSoulBeadAtrribute(s, 1);
	}
}

void StarringManager::takeOffSoulBead()
{
	CGTakeOffSoulBead cgTakeOffSoulBead;
	cgTakeOffSoulBead.playerGuid = 1;
	cgTakeOffSoulBead.srcPosition = 1;
	cgTakeOffSoulBead.destPosition = 1;

	TianXiaDiYi::getTheOnlyInstance()->socketWrap->SendPacket(&cgTakeOffSoulBead);

	SoulBead* s = starringManager->soulBeadEquipArray[starringManager->selectSoulBeadEquipId];
	starringManager->soulBeadEquipArray[starringManager->selectSoulBeadEquipId] = starringManager->soulBeadArray[starringManager->selectSoulBeadId];
	starringManager->soulBeadArray[selectSoulBeadId] = s;

	if (s != NULL)
	{
		addSoulBeadAtrribute(s, -1);
	}
}

void StarringManager::swapSoulBead( int type )
{
	CGSwapSoulBead sgSwapSoulBead;
	sgSwapSoulBead.playerGuid = 1;
	sgSwapSoulBead.type = SOUL_BEAD_BAG;
	sgSwapSoulBead.srcPosition = 1;
	sgSwapSoulBead.destPosition = 1;

	TianXiaDiYi::getTheOnlyInstance()->socketWrap->SendPacket(&sgSwapSoulBead);
}
