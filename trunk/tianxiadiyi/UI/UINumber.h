#ifndef __UINUMBER__
#define __UINUMBER__

#include <vector>
#include <string>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace gui;
using namespace std;

class UINumber : public CCSprite
{
public:
	UINumber();
	~UINumber();
	
	static UINumber* getTheOnlyInstance();

	CCSprite* getNumber(int num);
	CCSprite* floatNumber(int num, float x, float y, float w, float h);
	void floatNumberCallback(CCObject* object);

	CREATE_FUNC(UINumber);
};

#endif