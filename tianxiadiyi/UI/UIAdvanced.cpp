#include "UIAdvanced.h"

#include "..\TianXiaDiYi.h"

UIAdvanced::UIAdvanced()
{
	advancedManager = AdvancedManager::getTheOnlyInstance();
	advancedManager->init();
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

	UIButton* advancedButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("AdvancedButton"));
	advancedButton->addTouchEventListener(this, toucheventselector(UIAdvanced::advancedButtonClicked));

	UIPanel* spritePanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("GeneralSpritePanel_1"));
	const char* imagePath = CCString::createWithFormat("ui/%sSprite0.png", advancedManager->general->attribute.tuPian)->getCString();;
	const char* plistPath = CCString::createWithFormat("ui/%sSprite0.plist", advancedManager->general->attribute.tuPian)->getCString();;
	const char* configFilePath = CCString::createWithFormat("ui/%sSprite.ExportJson", advancedManager->general->attribute.tuPian)->getCString();

	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(imagePath, plistPath, configFilePath);
	const char* armatureName1 = CCString::createWithFormat("%sSprite", advancedManager->general->attribute.tuPian)->getCString();
	spriteAarmature1 = CCArmature::create(armatureName1);
	spriteAarmature1->getAnimation()->play("Stand");
	spriteAarmature1->setPosition(spritePanel->getPosition());
	uiLayer->addChild(spriteAarmature1);

	UIPanel* spritePanel2 = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("GeneralSpritePanel_2"));
	const char* imagePath2 = CCString::createWithFormat("ui/%sSprite0.png", advancedManager->general->attribute.tuPian)->getCString();;
	const char* plistPath2 = CCString::createWithFormat("ui/%sSprite0.plist", advancedManager->general->attribute.tuPian)->getCString();;
	const char* configFilePath2 = CCString::createWithFormat("ui/%sSprite.ExportJson", advancedManager->general->attribute.tuPian)->getCString();

	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(imagePath2, plistPath2, configFilePath2);
	const char* armatureName2 = CCString::createWithFormat("%sSprite", advancedManager->general->attribute.tuPian)->getCString();
	spriteAarmature2 = CCArmature::create(armatureName2);
	spriteAarmature2->getAnimation()->play("Stand");
	spriteAarmature2->setPosition(spritePanel2->getPosition());
	uiLayer->addChild(spriteAarmature2);

	for (int i = 0; i < 5; i++)
	{
		const char* s = CCString::createWithFormat("Attribute1ValueLabel_%d", i+1)->getCString();
		attribute1ValueLabel[i] = dynamic_cast<UILabel*>(uiLayer->getWidgetByName(s));
	}

	for (int i = 0; i < 5; i++)
	{
		const char* s = CCString::createWithFormat("Attribute2ValueLabel_%d", i+1)->getCString();
		attribute2ValueLabel[i] = dynamic_cast<UILabel*>(uiLayer->getWidgetByName(s));
	}

	for (int i = 0; i < 3; i++)
	{
		const char* s = CCString::createWithFormat("ConsumeValueLabel_%d", i+1)->getCString();
		consumeValueLabel[i] = dynamic_cast<UILabel*>(uiLayer->getWidgetByName(s));
	}

	addChild(uiLayer);
	refresh();
	return true;
}

void UIAdvanced::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
}

void UIAdvanced::clear()
{
	for (int i = 0; i < 5; i++)
	{
		attribute1ValueLabel[i]->setText(" ");
	}

	for (int i = 0; i < 5; i++)
	{
		attribute2ValueLabel[i]->setText(" ");
	}

	for (int i = 0; i < 3; i++)
	{
		consumeValueLabel[i]->setText(" ");
	}
}

void UIAdvanced::refresh()
{
	clear();

	// 武力
	const char* wuLi = CCString::createWithFormat("%d", advancedManager->general->attribute.wuLi)->getCString();
	// 智力
	const char* zhiLi = CCString::createWithFormat("%d", advancedManager->general->attribute.zhiLi)->getCString();
	// 体力
	const char* tiLi = CCString::createWithFormat("%d", advancedManager->general->attribute.tiLi)->getCString();
	// 敏捷
	const char* minJie = CCString::createWithFormat("%d", advancedManager->general->attribute.minJie)->getCString();
	// 技能伤害
	const char* jiNengShangHai = "N/A";

	const char* attribute[5] = {wuLi, zhiLi, tiLi, minJie, jiNengShangHai};

	for (int i = 0; i < 5; i++)
	{
		attribute1ValueLabel[i]->setText(attribute[i]);
	}

	int add = advancedManager->getAdvancedAddAttribute();

	// 武力
	const char* wuLi2 = CCString::createWithFormat("%d", advancedManager->general->attribute.wuLi+add)->getCString();
	// 智力
	const char* zhiLi2 = CCString::createWithFormat("%d", advancedManager->general->attribute.zhiLi+add)->getCString();
	// 体力
	const char* tiLi2 = CCString::createWithFormat("%d", advancedManager->general->attribute.tiLi+add)->getCString();
	// 敏捷
	const char* minJie2 = CCString::createWithFormat("%d", advancedManager->general->attribute.minJie+add)->getCString();
	// 技能伤害
	const char* jiNengShangHai2 = "N/A";
	const char* attribute2[5] = {wuLi2, zhiLi2, tiLi2, minJie2, jiNengShangHai2};

	for (int i = 0; i < 5; i++)
	{
		attribute2ValueLabel[i]->setText(attribute2[i]);
	}

	vector<string>consume = advancedManager->getAdvancedConsume();

	for (int i = 0; i < 3; i++)
	{
		consumeValueLabel[i]->setText(consume[i].c_str());
	}
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

	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiGeneral->refresh();
}

void UIAdvanced::advancedButtonClicked( CCObject* sender, TouchEventType type )
{
	advancedManager->advanced();
}
