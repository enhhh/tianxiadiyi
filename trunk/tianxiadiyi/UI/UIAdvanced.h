#ifndef __UIADVANCED_H__
#define __UIADVANCED_H__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Logic\AdvancedManager.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace gui;
using namespace std;

class UIAdvanced : public CCLayer
{
public:
	AdvancedManager* advancedManager;
	UILayer* uiLayer;

	CCArmature* spriteAarmature1;
	CCArmature* spriteAarmature2;

	UILabel* attribute1ValueLabel[5];
	UILabel* attribute2ValueLabel[5];
	UILabel* consumeValueLabel[3];

	UIAdvanced();
	~UIAdvanced();

	virtual bool init();
	virtual void onEnter();
	void clear();
	void refresh();

	void closeButtonClicked(CCObject* sender, TouchEventType type);
	void advancedButtonClicked(CCObject* sender, TouchEventType type);

	CREATE_FUNC(UIAdvanced);
};

#endif