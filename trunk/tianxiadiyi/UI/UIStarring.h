#ifndef __UISTARRING_H__
#define __UISTARRING_H__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Logic\StarringManager.h"
#include "Logic\SoulBead.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace gui;
using namespace std;

class UIStarring : public CCLayer
{
public:
	StarringManager* starringManager;
	UILayer* uiLayer;

	// 操作
	UIPanel* operatePanel;

	// 角色
	UIPanel* starringAttributePanel;
	UIPanel* attributePanel;
	CCArmature* spriteAarmature;
	UILabel* attributeLabel[4];

	// 培养
	UIPanel* cultureModePanel;
	UIButton* cultureRadioButtonArray[4];
	UIImageView* cultureImageView;
	UILabel* successRateLabel;

	// 天赋
	UIPanel* telentModePanel;
	UIPanel* telentPanelArrary[5];
	UIButton* telentButtonArray[5][20];
	UIImageView* telentImageViewArray[5][20];

	UIPanel* soulAttributePanel;
	UIPanel* soulPanel;

	// 魂珠动画
	UIImageView* soulBeadCircleImageView[10];
	UIButton* soulBeadButton[12];
	UIImageView* soulBeadFeatureImageView;
	UIImageView* selectSoulFrameImageView;

	SoulBeadSprite soulBeadFeatureSprite;
	SoulBeadSprite selectSoulBeadSprite;

	UIStarring();
	~UIStarring();

	virtual bool init();
	virtual void onEnter();
	void refresh();
	
	// 重写触屏回调函数
	virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* event);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	void refreshCulture();
	void refreshTelent();
	void refreshSoul();
	void refreshSoulFeatureSprite();

	void operateCloseButtonClicked(CCObject* sender, TouchEventType type);
	void cultureCloseButtonClicked(CCObject* sender, TouchEventType type);
	void telentCloseButtonClicked(CCObject* sender, TouchEventType type);
	void soulCloseButtonClicked(CCObject* sender, TouchEventType type);

	void cultureButtonClicked(CCObject* sender, TouchEventType type);
	void telentButtonClicked(CCObject* sender, TouchEventType type);
	void soulButtonClicked(CCObject* sender, TouchEventType type);

	void pageLeftButtonClicked(CCObject* sender, TouchEventType type);
	void pageRightButtonClicked(CCObject* sender, TouchEventType type);

	void pageLeftSoulButtonClicked(CCObject* sender, TouchEventType type);
	void pageRightSoulButtonClicked(CCObject* sender, TouchEventType type);

	void soulButtonEXTClicked(CCObject* sender, TouchEventType type);
	void cultureRadioButtonClicked(CCObject* sender, TouchEventType type);
	void telentButtonEXTClicked(CCObject* sender, TouchEventType type);

	void cultureModeButtonClicked(CCObject* sender, TouchEventType type);

	CREATE_FUNC(UIStarring);
};

#endif