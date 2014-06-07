#ifndef __GENERAL__
#define __GENERAL__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Monster.h"
#include "Logic\Equipment.h"

#include "tinytab\DataBase.h"
#include "tinytab\DBC_Struct.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace gui;

enum GENERAL_TYPE
{
	// 猛将
	MENG_JIANG = 1,
	// 术士
	MOU_SHI
};

class General : public Monster
{
public:

	_DBC_GENERAL attribute;

	// 物理攻击
	int wuLiGongJi;

	// 物理防御
	int wuLiFangYu;

	// 法术攻击
	int faShuGongJi;

	// 法术防御
	int faShuFangYu;

	// 生命
	int hp;

	// 属性点
	int attributePoint;

	// 是否上阵
	bool isFormation;

	// 将领装备数组
	Equipment* equipmentArray[6];

	General(int id);
	~General();

	void creatArmature();
};

#endif
