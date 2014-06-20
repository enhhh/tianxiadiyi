#ifndef __UIRIDE_STRENGTHEN_H__
#define __UIRIDE_STRENGTHEN_H__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Logic\RideStrengthenManager.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace gui;
using namespace std;

class UIRideStrengthen : public CCLayer
{
public:

	RideStrengthenManager* rideStrengthenManager;
	
	UILayer* uiLayer;

	UIImageView* featureImageView;
	UILabel* nameLabel;
	UILabel* lvLabel;
	UILabel* attribute1ValueLabel[5];
	UILabel* attribute2ValueLabel[5];

	UIRideStrengthen();
	~UIRideStrengthen();

	virtual bool init();
	virtual void onEnter();

	void clear();
	void refresh();

	void closeButtonClicked(CCObject* sender, TouchEventType type);

	CREATE_FUNC(UIRideStrengthen);
};

#endif