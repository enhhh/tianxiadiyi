#ifndef __UICOUNTRY_H__
#define __UICOUNTRY_H__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace gui;
using namespace std;

class UICountry : public CCLayer
{
public:

	UILayer* uiLayer;

	UICountry();
	~UICountry();

	virtual bool init();
	virtual void onEnter();
	void refresh();

	void closeButtonClicked(CCObject* sender, TouchEventType type);

	CREATE_FUNC(UICountry);
};

#endif