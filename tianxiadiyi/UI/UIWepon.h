#ifndef __UIWEPON_H__
#define __UIWEPON_H__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Logic\WeponManager.h"
#include "Logic\Equipment.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace gui;
using namespace std;

class UIWepon : public CCLayer
{
public:
	WeponManager* weponManager;
	bool isPage;
	GemSprite selectGemSprite;

	UILayer* uiLayer;
	UIImageView* equipmentFeatureImageView;
	UIImageView* roundImageView;
	UIImageView* gemImageView[4];
	UILabel* equipmentAttributeValueLable[4];

	UIWepon();
	~UIWepon();

	virtual bool init();
	virtual void onEnter();
	void clear();
	void refresh();

	// 重写触屏回调函数
	virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* event);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	void closeButtonClicked(CCObject* sender, TouchEventType type);
	void pageLeftButtonClicked(CCObject* sender, TouchEventType type);
	void pageRightButtonClicked(CCObject* sender, TouchEventType type);

	CREATE_FUNC(UIWepon);
};

#endif