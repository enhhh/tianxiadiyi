#include "Monster.h"
#include "AI\States.h"
#include "AI\SpriteStates.h"
#include "AI\SteeringBehavious.h"

Monster::Monster(int type)
{
	attackSprite = NULL;

	isFriend = false;
	isBack = true;

	direction = LEFT;
	face = LEFT;
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