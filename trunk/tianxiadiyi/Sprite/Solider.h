#ifndef __SOLIDER__
#define __SOLIDER__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "Monster.h"

#include "tinytab\DataBase.h"
#include "tinytab\DBC_Struct.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace gui;

class Solider : public Monster
{
public:

	_DBC_SOLIDER attribute;

	Solider(int id);
	~Solider();

	void creatArmature();
};
#endif
