#include "UIAdvanced.h"

#include "..\TianXiaDiYi.h"

UIAdvanced::UIAdvanced()
{
	advanceManager = AdvanceManager::getTheOnlyInstance();
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
	const char* imagePath = CCString::createWithFormat("ui/%sSprite0.png", advanceManager->general->attribute.tuPian)->getCString();;
	const char* plistPath = CCString::createWithFormat("ui/%sSprite0.plist", advanceManager->general->attribute.tuPian)->getCString();;
	const char* configFilePath = CCString::createWithFormat("ui/%sSprite.ExportJson", advanceManager->general->attribute.tuPian)->getCString();

	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(imagePath, plistPath, configFilePath);
	const char* armatureName1 = CCString::createWithFormat("%sSprite", advanceManager->general->attribute.tuPian)->getCString();
	spriteAarmature1 = CCArmature::create(armatureName1);
	spriteAarmature1->getAnimation()->play("Stand");
	spriteAarmature1->setPosition(spritePanel->getPosition());
	uiLayer->addChild(spriteAarmature1);

	UIPanel* spritePanel2 = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("GeneralSpritePanel_2"));
	const char* imagePath2 = CCString::createWithFormat("ui/%sSprite0.png", advanceManager->general->attribute.tuPian)->getCString();;
	const char* plistPath2 = CCString::createWithFormat("ui/%sSprite0.plist", advanceManager->general->attribute.tuPian)->getCString();;
	const char* configFilePath2 = CCString::createWithFormat("ui/%sSprite.ExportJson", advanceManager->general->attribute.tuPian)->getCString();

	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(imagePath2, plistPath2, configFilePath2);
	const char* armatureName2 = CCString::createWithFormat("%sSprite", advanceManager->general->attribute.tuPian)->getCString();
	spriteAarmature2 = CCArmature::create(armatureName2);
	spriteAarmature2->getAnimation()->play("Stand");
	spriteAarmature2->setPosition(spritePanel2->getPosition());
	uiLayer->addChild(spriteAarmature2);

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
	if (spriteAarmature1 != NULL)
	{
		uiLayer->removeChild(spriteAarmature1, true);
	}

	if (spriteAarmature2 != NULL)
	{
		uiLayer->removeChild(spriteAarmature2, true);
	}

	TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiAdvanced, true);
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiAdvanced->release();
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiAdvanced = NULL;
}