#ifndef __UIMAIN_CITY__
#define __UIMAIN_CITY__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "UIFighting.h"
#include "UIFormation.h"
#include "UIStarring.h"

#include "UIGeneral.h"
#include "UIWepon.h"
#include "UIWeponTakeup.h"
#include "UIAdvanced.h"

#include "UIBag.h"
#include "UIStrengthen.h"
#include "UIRide.h"
#include "UIRideStrengthen.h"
#include "UICountry.h"
#include "UICountryLand.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace gui;

class UIMainCity : public CCLayer
{
public:

	UILayer* uiLayer;

	UIFighting* uiFighting;
	UIFormation* uiFormation;
	UIStarring* uiStarring;

	UIGeneral* uiGeneral;
	UIWepon* uiWepon;
	UIWeponTakeUp* uiWeponTakeup;
	UIAdvanced* uiAdvanced;

	UIBag* uiBag;
	UIStrengthen* uiStrengthen;
	UIRide* uiRide;
	UIRideStrengthen* uiRideStrengthen;
	UICountry* uiCountry;
	UICountryLand* uiCountryLand;

	UIMainCity();
	~UIMainCity();

	virtual bool init();
	virtual void onEnter();

	void fightingButtonClicked(CCObject* sender, TouchEventType type);
	void formationButtonClicked(CCObject* sender, TouchEventType type);
	void starringButtonClicked(CCObject* sender, TouchEventType type);
	void generalButtonClicked(CCObject* sender, TouchEventType type);
	void bagButtonClicked(CCObject* sender, TouchEventType type);
	void strengthenButtonClicked(CCObject* sender, TouchEventType type);
	void rideButtonClicked(CCObject* sender, TouchEventType type);
	void countryButtonClicked(CCObject* sender, TouchEventType type);

	CREATE_FUNC(UIMainCity);
};

#endif