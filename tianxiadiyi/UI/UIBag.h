#ifndef __UIBAG_H__
#define __UIBAG_H__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Logic\ItemManager.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace gui;
using namespace std;

class UIBag : public CCLayer
{
public:

	UILayer* uiLayer;
	ItemManager* itemManager;

	UIImageView* itemImageView[16];
	UIImageView* itemFeatureImageView;

	UIBag();
	~UIBag();

	virtual bool init();
	virtual void onEnter();
	void refresh();

	void closeButtonClicked(CCObject* sender, TouchEventType type);
	void itemButtonClicked(CCObject* sender, TouchEventType type);
	void pageLeftButtonClicked(CCObject* sender, TouchEventType type);
	void pageRightButtonClicked(CCObject* sender, TouchEventType type);

	CREATE_FUNC(UIBag);
};

#endif