#ifndef __UIWEPON_TAKEUP_H__
#define __UIWEPON_TAKEUP_H__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "Logic\GeneralManager.h"
#include "Logic\WeponTakeUpManager.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace gui;
using namespace std;

class UIWeponTakeUp : public CCLayer
{
public:
	GeneralManager* generalManager;
	WeponTakeUpManager* weponTakeUpManager;

	UILayer* uiLayer;

	UIImageView* equipmentFeatureImageView;
	UIImageView* roundImageView;
	UIImageView* equipmentImageView[3];

	UIWeponTakeUp();
	~UIWeponTakeUp();

	virtual bool init();
	virtual void onEnter();
	void clear();
	void refresh();

	void closeButtonClicked(CCObject* sender, TouchEventType type);
	void takeUpButtonClicked(CCObject* sender, TouchEventType type);
	void fillButtonClicked(CCObject* sender, TouchEventType type);
	void equipmentButtonClicked(CCObject* sender, TouchEventType type);

	void pageLeftButtonClicked(CCObject* sender, TouchEventType type);
	void pageRightButtonClicked(CCObject* sender, TouchEventType type);

	CREATE_FUNC(UIWeponTakeUp);
};

#endif