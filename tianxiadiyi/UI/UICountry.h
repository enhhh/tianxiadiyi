#ifndef __UICOUNTRY_H__
#define __UICOUNTRY_H__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Logic\CountryManager.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace gui;
using namespace std;


class UICountry : public CCLayer
{
public:

	CountryManager* countryManager;

	UILayer* uiLayer;

	UICountry();
	~UICountry();

	virtual bool init();
	virtual void onEnter();
	void refresh();

	void closeButtonClicked(CCObject* sender, TouchEventType type);
	void verifyButtonClicked(CCObject* sender, TouchEventType type);
	void modifyButtonClicked(CCObject* sender, TouchEventType type);
	void appointmentButtonClicked(CCObject* sender, TouchEventType type);
	void quitButtonClicked(CCObject* sender, TouchEventType type);
	void kickButtonClicked(CCObject* sender, TouchEventType type);
	void countryRankButtonClicked(CCObject* sender, TouchEventType type);
	void countryLandButtonClicked(CCObject* sender, TouchEventType type);

	CREATE_FUNC(UICountry);
};

#endif