#include "UICountry.h"

#include "..\TianXiaDiYi.h"

UICountry::UICountry()
{
	countryManager = CountryManager::getTheOnlyInstance();
}

UICountry::~UICountry()
{
}

bool UICountry::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	uiLayer = UILayer::create();

	UILayout* countryRoot = dynamic_cast<UILayout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/UICountry.ExportJson"));
	uiLayer->addWidget(countryRoot);

	UIButton* closeButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("CloseButton"));
	closeButton->addTouchEventListener(this, toucheventselector(UICountry::closeButtonClicked));

	UIButton* verifyButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("VerifyButton"));
	verifyButton->addTouchEventListener(this, toucheventselector(UICountry::verifyButtonClicked));

	UIButton* modifyButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("ModifyButton"));
	modifyButton->addTouchEventListener(this, toucheventselector(UICountry::modifyButtonClicked));

	UIButton* appointmentButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("AppointmentButton"));
	appointmentButton->addTouchEventListener(this, toucheventselector(UICountry::appointmentButtonClicked));

	UIButton* quitButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("QuitButton"));
	quitButton->addTouchEventListener(this, toucheventselector(UICountry::quitButtonClicked));

	UIButton* kickButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("KickButton"));
	kickButton->addTouchEventListener(this, toucheventselector(UICountry::kickButtonClicked));

	UIButton* countryRankButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("CountryRankButton"));
	countryRankButton->addTouchEventListener(this, toucheventselector(UICountry::countryRankButtonClicked));

	UIButton* countryLand = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("CountryLandButton"));
	countryLand->addTouchEventListener(this, toucheventselector(UICountry::countryLandButtonClicked));

	addChild(uiLayer);
	setVisible(false);

	refresh();
	return true;
}

void UICountry::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
}

void UICountry::refresh()
{
}

void UICountry::closeButtonClicked( CCObject* sender, TouchEventType type )
{
	TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiCountry, true);
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiCountry->release();
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiCountry = NULL;
}

void UICountry::verifyButtonClicked( CCObject* sender, TouchEventType type )
{
	countryManager->verify();
}

void UICountry::modifyButtonClicked( CCObject* sender, TouchEventType type )
{
	countryManager->modify();
}

void UICountry::appointmentButtonClicked( CCObject* sender, TouchEventType type )
{
	countryManager->appointment();
}

void UICountry::quitButtonClicked( CCObject* sender, TouchEventType type )
{
	countryManager->quit();
}

void UICountry::kickButtonClicked( CCObject* sender, TouchEventType type )
{
	countryManager->kick();
}

void UICountry::countryRankButtonClicked( CCObject* sender, TouchEventType type )
{
}

void UICountry::countryLandButtonClicked( CCObject* sender, TouchEventType type )
{
}