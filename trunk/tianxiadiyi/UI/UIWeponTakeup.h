#ifndef __UIWEPON_TAKEUP_H__
#define __UIWEPON_TAKEUP_H__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "Logic\GeneralManager.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace gui;
using namespace std;

class UIWeponTakeup : public CCLayer
{
public:
	GeneralManager* generalManager;
	UILayer* uiLayer;

	UIImageView* equipmentFeatureImageView;

	UIWeponTakeup();
	~UIWeponTakeup();

	virtual bool init();
	virtual void onEnter();
	void refresh();

	void closeButtonClicked(CCObject* sender, TouchEventType type);
	void fillButtonClicked(CCObject* sender, TouchEventType type);

	CREATE_FUNC(UIWeponTakeup);
};

#endif