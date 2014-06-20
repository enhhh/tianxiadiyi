#include "UIFightingWin.h"
#include "..\TianXiaDiYi.h"

UIFightingWin::UIFightingWin()
{
}

UIFightingWin::~UIFightingWin()
{
}

bool UIFightingWin::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	uiLayer = UILayer::create();

	UILayout* fightingWinRoot = dynamic_cast<UILayout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/UIFightingWin.ExportJson"));
	uiLayer->addWidget(fightingWinRoot);

	winImageView = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("WinImageView"));
	awardImageView = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("AwardImageView"));
	loseImageView = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("LoseImageView"));

	UIButton* okButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("OkButton"));
	okButton->addTouchEventListener(this, toucheventselector(UIFightingWin::okButtonClicked));

	CCSize visibleSize = TianXiaDiYi::getTheOnlyInstance()->visibleSize;
	CCSize size = fightingWinRoot->getContentSize();

	setPosition(ccp((visibleSize.width-size.width) / 2, (visibleSize.height-size.height) / 2));
	addChild(uiLayer);

	return true;
}

void UIFightingWin::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
}

void UIFightingWin::okButtonClicked(CCObject* sender, TouchEventType type)
{
	TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->fightingScene->uiFightingWin, true);
	TianXiaDiYi::getTheOnlyInstance()->fightingScene->uiFightingWin = NULL;

	TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->fightingScene, true);
	TianXiaDiYi::getTheOnlyInstance()->fightingScene->release();
	TianXiaDiYi::getTheOnlyInstance()->fightingScene = NULL;
}