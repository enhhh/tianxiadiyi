#include "Npc.h"
#include "AI\States.h"
#include "AI\SpriteStates.h"
#include "AI\SteeringBehavious.h"

Npc::Npc(int type)
{
}

Npc::~Npc()
{
}

void Npc::updateEXT(float delta)
{
	Sprite::updateEXT(delta);
}