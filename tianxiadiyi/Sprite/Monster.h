#ifndef __Monster__
#define __Monster__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Sprite.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace gui;

enum MonsterType
{
	GENERAL = 0,
	SOLDIER
};

class Monster : public Sprite
{
public:
	int monsterType;

	// Ãô½Ý
	int agility;

	// Å­Æø
	int anger;

	// ÑªÁ¿
	int hp;

	Monster(int type);
	~Monster();

	void updateEXT(float delta);

	void setIsFriend(bool isFriend);

	void setAttribute();
};

#endif
