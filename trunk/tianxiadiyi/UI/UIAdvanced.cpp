#include "UIAdvanced.h"

#include "..\TianXiaDiYi.h"

UIAdvanced::UIAdvanced()
{
}

UIAdvanced::~UIAdvanced()
{
}

bool UIAdvanced::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	uiLayer = UILayer::create();

	UILayout* advancedRoot = dynamic_cast<UILayout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/UIAdvanced.ExportJson"));
	uiLayer->addWidget(advancedRoot);

	UIButton* closeButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("AdvancedCloseButton"));
	closeButton->addTouchEventListener(this, toucheventselector(UIAdvanced::closeButtonClicked));

	UIPanel* spritePanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("GeneralSpritePanel_1"));
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("ui/StarringSprite0.png", "ui/StarringSprite0.plist", "ui/StarringSprite.ExportJson");
	CCArmature* spriteAarmature = CCArmature::create("StarringSprite");
	spriteAarmature->getAnimation()->play("StandDown");
	spriteAarmature->setPosition(spritePanel->getPosition());
	uiLayer->addChild(spriteAarmature);

	spritePanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("GeneralSpritePanel_2"));
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("ui/StarringSprite0.png", "ui/StarringSprite0.plist", "ui/StarringSprite.ExportJson");
	spriteAarmature = CCArmature::create("StarringSprite");
	spriteAarmature->getAnimation()->play("StandDown");
	spriteAarmature->setPosition(spritePanel->getPosition());
	uiLayer->addChild(spriteAarmature);

	addChild(uiLayer);
	return true;
}

void UIAdvanced::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
}

void UIAdvanced::closeButtonClicked( CCObject* sender, TouchEventType type )
{
	TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiAdvanced, true);
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiAdvanced->release();
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiAdvanced = NULL;
}