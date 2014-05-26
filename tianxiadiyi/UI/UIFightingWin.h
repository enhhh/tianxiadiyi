#ifndef __UIFIGHTING_WIN_H__
#define __UIFIGHTING_WIN_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace gui;

class UIFightingWin : public CCLayer
{
public:

	UILayer* uiLayer;

	UIImageView* winImageView;
	UIImageView* awardImageView;
	UIImageView* loseImageView;

	UIFightingWin();
	~UIFightingWin();

	virtual bool init();
	virtual void onEnter();

	void okButtonClicked(CCObject* sender, TouchEventType type);
	CREATE_FUNC(UIFightingWin);
};

#endif