#ifndef __STARRING_MANAGER_H__
#define __STARRING_MANAGER_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

#include "Sprite\Player.h"
#include "SoulBead.h"

enum TELENT_TYPE
{
	BAI_HU = 0,
	XUAN_WU = 1,
	QING_LONG = 2,
	ZHU_QUE = 3,
	QI_LIN = 4
};

enum SOUL_CONTAINER_TYPE
{
	SOUL_BEAD_BAG = 1,
	SOUL_BEAD_EQUIP = 2
};

struct SoulBeadSprite
{
	SoulBead* soulBead;
	CCArmature* armature;
};

class StarringManager
{
public:
	StarringManager();
	~StarringManager();

	Player* player;

	int cultureSuccessRate[3];
	int selectCultureId;

	// Ìì¸³µã
	int telentLightPoint[5];
	bool telentPoint[5][20];
	int selectTelentPointId;
	int telentPageNum;

	vector<SoulBead*>soulBeadVector;

	SoulBeadSprite soulBeadSpriteArray[12];
	SoulBeadSprite soulBeadEquipSpriteArray[10];

	bool isSelectSoulBead;
	int soulPageNum;
	int soulMaxPageNum;
	
	SoulBead** soulBeadArray;
	SoulBead* soulBeadEquipArray[10];

	int selectSoulBeadId;
	int selectSoulBeadEquipId;

	static StarringManager* getTheOnlyInstance();

	void culture();

	int getTelentPointValue(int telentId, int point);
	void lightUpTelentPoint();

	void addSoulBeadAtrribute(SoulBead* soulBead, int add);
	void putOnSoulBead();
	void takeOffSoulBead();

	void swapSoulBead(int type);
};

#endif