#ifndef __UIGENERAL_H__
#define __UIGENERAL_H__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Logic\Equipment.h"
#include "Logic\GeneralManager.h"
#include "Logic\WeponManager.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace gui;
using namespace std;

class UIGeneral : public CCLayer
{
public:

	GeneralManager* generalManager;

	UILayer* uiLayer;
	
	UIImageView* headImageView[3];
	UIImageView* equipmentImageView[6];
	UILabel* attributeValueLabel[15];
	UIImageView* selectFrameImageView;
	UIImageView* headFeatureImageView;
	UIImageView* starImageView[10];

	UIGeneral();
	~UIGeneral();

	virtual bool init();
	virtual void onEnter();
	void clear();
	void refresh();

	void closeButtonClicked(CCObject* sender, TouchEventType type);
	void headButtonClicked(CCObject* sender, TouchEventType type);
	void equipmentButtonClicked(CCObject* sender, TouchEventType type);
	void addButtonClicked(CCObject* sender, TouchEventType type);
	void advancedButtonClicked(CCObject* sender, TouchEventType type);

	void pageLeftButtonClicked(CCObject* sender, TouchEventType type);
	void pageRightButtonClicked(CCObject* sender, TouchEventType type);

	CREATE_FUNC(UIGeneral);
};

#endif