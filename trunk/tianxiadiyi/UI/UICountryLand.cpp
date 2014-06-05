#include "UICountryLand.h"

#include "..\TianXiaDiYi.h"

UICountryLand::UICountryLand()
{
}

UICountryLand::~UICountryLand()
{
}

bool UICountryLand::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	uiLayer = UILayer::create();

	UILayout* countryLandRoot = dynamic_cast<UILayout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/UICountryLand.ExportJson"));
	uiLayer->addWidget(countryLandRoot);

	UIButton* closeButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("CloseButton"));
	closeButton->addTouchEventListener(this, toucheventselector(UICountryLand::closeButtonClicked));

	string spritePlist[3][4] = 
	{
		{"ui/SacrificeSprite0.png", "ui/SacrificeSprite0.plist", "ui/SacrificeSprite.ExportJson", "SacrificeSprite"},
		{"ui/GrandCouncilSprite0.png", "ui/GrandCouncilSprite0.plist", "ui/GrandCouncilSprite.ExportJson", "GrandCouncilSprite"},
		{"ui/ShopSprite0.png", "ui/ShopSprite0.plist", "ui/ShopSprite.ExportJson", "ShopSprite"}
	};

	for (int i = 0; i < 3; i++)
	{
		const char* s = CCString::createWithFormat("SpritePanel_%d", i+1)->getCString();
		UIPanel* spritePanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName(s));

		CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(spritePlist[i][0].c_str(), spritePlist[i][1].c_str(), spritePlist[i][2].c_str());
		CCArmature* spriteAarmature = CCArmature::create(spritePlist[i][3].c_str());
		spriteAarmature->getAnimation()->play("Stand");
		spriteAarmature->setPosition(spritePanel->getPosition());
		uiLayer->addChild(spriteAarmature);
	}

	addChild(uiLayer);
	refresh();
	return true;
}

void UICountryLand::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
}

void UICountryLand::clear()
{
}

void UICountryLand::refresh()
{
	clear();
}

void UICountryLand::closeButtonClicked( CCObject* sender, TouchEventType type )
{
	TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiCountryLand, true);
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiCountryLand->release();
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiCountryLand = NULL;
}