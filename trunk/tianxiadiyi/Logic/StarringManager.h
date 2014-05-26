#ifndef __STARRING_MANAGER_H__
#define __STARRING_MANAGER_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

#include "SoulBead.h"

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
	int selectSoulBeadCircleId;

	static StarringManager* getTheOnlyInstance();
};

#endif