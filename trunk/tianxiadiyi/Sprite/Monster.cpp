#include "Monster.h"
#include "AI\States.h"
#include "AI\SpriteStates.h"
#include "AI\SteeringBehavious.h"

Monster::Monster(int type)
{
	monsterType = type;
	attackSprite = NULL;

	isFriend = false;
	isBack = true;

	direction = LEFT;
	face = LEFT;

	setAttribute();
	setType(MONSTER);
}

Monster::~Monster()
{
}

void Monster::updateEXT(float delta)
{
	Sprite::updateEXT(delta);
}

void Monster::setIsFriend(bool isFriend)
{
	this->isFriend = isFriend;
}

void Monster::setAttribute()
{
	agility = rand() % 100;
	anger = 0;
	hp = 100;
}
