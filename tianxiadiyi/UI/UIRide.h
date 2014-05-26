#ifndef __UIRIDE_H__
#define __UIRIDE_H__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace gui;
using namespace std;

class UIRide : public CCLayer
{
public:

	UILayer* uiLayer;

	UIRide();
	~UIRide();

	virtual bool init();
	virtual void onEnter();
	void refresh();

	void closeButtonClicked(CCObject* sender, TouchEventType type);

	CREATE_FUNC(UIRide);
};

#endif