#ifndef __NPC__
#define __NPC__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Sprite.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace gui;

class Npc : public Sprite
{
public:
	Npc(int type);
	~Npc();

	void updateEXT(float delta);
};

#endif
