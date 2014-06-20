#ifndef __UIRIDE_H__
#define __UIRIDE_H__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Logic\RideManager.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace gui;
using namespace std;

class UIRide : public CCLayer
{
public:

	RideManager* rideManager;

	UILayer* uiLayer;

	UIImageView* rideImageView[8];
	UILabel* rideNameLabel[8];
	UILabel* rideLvLabel[8];

	UILabel* attributeValueLabel[5];
	UIImageView* selectFrameImageView;

	UIRide();
	~UIRide();

	virtual bool init();
	virtual void onEnter();

	void clear();
	void refresh();

	void closeButtonClicked(CCObject* sender, TouchEventType type);
	void rideButtonClicked(CCObject* sender, TouchEventType type);
	void ridingButtonClicked(CCObject* sender, TouchEventType type);
	void strengthenButtonClicked(CCObject* sender, TouchEventType type);
	
	void pageLeftButtonClicked(CCObject* sender, TouchEventType type);
	void pageRightButtonClicked(CCObject* sender, TouchEventType type);

	CREATE_FUNC(UIRide);
};

#endif