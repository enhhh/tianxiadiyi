#ifndef __UIADVANCED_H__
#define __UIADVANCED_H__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace gui;
using namespace std;

class UIAdvanced : public CCLayer
{
public:

	UILayer* uiLayer;

	UIAdvanced();
	~UIAdvanced();

	virtual bool init();
	virtual void onEnter();

	void closeButtonClicked(CCObject* sender, TouchEventType type);
	CREATE_FUNC(UIAdvanced);
};

#endif