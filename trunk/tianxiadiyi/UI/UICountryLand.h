#ifndef __UICOUNTRY_LAND_H__
#define __UICOUNTRY_LAND_H__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace gui;
using namespace std;


class UICountryLand : public CCLayer
{
public:

	UILayer* uiLayer;

	UICountryLand();
	~UICountryLand();

	virtual bool init();
	virtual void onEnter();
	void clear();
	void refresh();

	void closeButtonClicked(CCObject* sender, TouchEventType type);
	CREATE_FUNC(UICountryLand);
};

#endif