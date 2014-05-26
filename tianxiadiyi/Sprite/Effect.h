#ifndef __EFFECT_H__
#define __EFFECT_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "Sprite.h"

enum EFFECT_TYPE
{
	EFFECT_NONE = 0,
	QIAN_JUN_PO,
	HE_JIE_ZHI_LI,
	LI_ZHAN,
	FEN_NU_YI_JI,
	SHI_MIAN_MAI_FU,
	FEN_LI_YI_JI,
	WU_JI_LIAN_SHA,
	GUI_KU_LANG_HAO
};

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

class Effect : public Sprite
{
public:
	int type;

	Effect();
	~Effect();

	void updateEXT(float delta);
};

#endif
