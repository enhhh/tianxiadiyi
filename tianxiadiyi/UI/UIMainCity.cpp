#include "UIMainCity.h"
#include "..\TianXiaDiYi.h"

UIMainCity::UIMainCity()
{
	uiFighting = NULL;
	uiFormation = NULL;
	uiStarring = NULL;

	uiGeneral = NULL;
	uiWepon = NULL;
	uiWeponTakeup = NULL;
	uiAdvanced = NULL;

	uiBag = NULL;
	uiStrengthen = NULL;
	uiRide = NULL;
	uiCountry = NULL;
}

UIMainCity::~UIMainCity()
{
}

bool UIMainCity::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	uiLayer = UILayer::create();

	UILayout* mainCityRoot = dynamic_cast<UILayout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/UIMainCity.ExportJson"));
	uiLayer->addWidget(mainCityRoot);

	UIButton* fightingButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("FightingButton"));
	fightingButton->addTouchEventListener(this, toucheventselector(UIMainCity::fightingButtonClicked));

	UIButton* formationButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("FormationButton"));
	formationButton->addTouchEventListener(this, toucheventselector(UIMainCity::formationButtonClicked));
	
	UIButton* starringButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("StarringButton"));
	starringButton->addTouchEventListener(this, toucheventselector(UIMainCity::starringButtonClicked));

	UIButton* generalButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("GeneralButton"));
	generalButton->addTouchEventListener(this, toucheventselector(UIMainCity::generalButtonClicked));

	UIButton* bagButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("BagButton"));
	bagButton->addTouchEventListener(this, toucheventselector(UIMainCity::bagButtonClicked));

	UIButton* strengthenButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("StrengthenButton"));
	strengthenButton->addTouchEventListener(this, toucheventselector(UIMainCity::strengthenButtonClicked));

	UIButton* rideButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("RideButton"));
	rideButton->addTouchEventListener(this, toucheventselector(UIMainCity::rideButtonClicked));

	UIButton* countryButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("NationButton"));
	countryButton->addTouchEventListener(this, toucheventselector(UIMainCity::countryButtonClicked));

	setVisible(false);
	addChild(uiLayer);

	return true;
}

void UIMainCity::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
}

void UIMainCity::fightingButtonClicked(CCObject* sender, TouchEventType type)
{
	if (type != TOUCH_EVENT_BEGAN)
	{
		return;
	}

	if (uiFighting == NULL)
	{
		uiFighting = UIFighting::create();
		uiFighting->retain();
		TianXiaDiYi::getTheOnlyInstance()->addChild(uiFighting);
	}

	if (uiFighting->isVisible())
	{
		uiFighting->setVisible(false);
	}
	else
	{
		uiFighting->setVisible(true);
	}
}

void UIMainCity::formationButtonClicked(CCObject* sender, TouchEventType type)
{
	if (type != TOUCH_EVENT_BEGAN)
	{
		return;
	}

	if (uiFormation == NULL)
	{
		uiFormation = UIFormation::create();
		uiFormation->retain();
		TianXiaDiYi::getTheOnlyInstance()->addChild(uiFormation);
	}

	if (uiFormation->isVisible())
	{
		uiFormation->setVisible(false);
	}
	else
	{
		uiFormation->setVisible(true);
	}
}

void UIMainCity::starringButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type != TOUCH_EVENT_BEGAN)
	{
		return;
	}

	if (uiStarring == NULL)
	{
		uiStarring = UIStarring::create();
		uiStarring->retain();
		TianXiaDiYi::getTheOnlyInstance()->addChild(uiStarring);
	}

	if (uiStarring->isVisible())
	{
		uiStarring->setVisible(false);
	}
	else
	{
		uiStarring->setVisible(true);
	}
}

void UIMainCity::generalButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type != TOUCH_EVENT_BEGAN)
	{
		return;
	}

	if (uiGeneral == NULL)
	{
		uiGeneral = UIGeneral::create();
		uiGeneral->retain();
		TianXiaDiYi::getTheOnlyInstance()->addChild(uiGeneral);
	}

	if (uiGeneral->isVisible())
	{
		uiGeneral->setVisible(false);
	}
	else
	{
		uiGeneral->setVisible(true);
	}
}

void UIMainCity::bagButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type != TOUCH_EVENT_BEGAN)
	{
		return;
	}

	if (uiBag == NULL)
	{
		uiBag = UIBag::create();
		uiBag->retain();
		TianXiaDiYi::getTheOnlyInstance()->addChild(uiBag);
	}

	if (uiBag->isVisible())
	{
		uiBag->setVisible(false);
	}
	else
	{
		uiBag->setVisible(true);
	}
}

void UIMainCity::strengthenButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type != TOUCH_EVENT_BEGAN)
	{
		return;
	}

	if (uiStrengthen == NULL)
	{
		uiStrengthen = UIStrengthen::create();
		uiStrengthen->retain();
		TianXiaDiYi::getTheOnlyInstance()->addChild(uiStrengthen);
	}

	if (uiStrengthen->isVisible())
	{
		uiStrengthen->setVisible(false);
	}
	else
	{
		uiStrengthen->setVisible(true);
	}
}

void UIMainCity::rideButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type != TOUCH_EVENT_BEGAN)
	{
		return;
	}

	if (uiRide == NULL)
	{
		uiRide = UIRide::create();
		uiRide->retain();
		TianXiaDiYi::getTheOnlyInstance()->addChild(uiRide);
	}

	if (uiRide->isVisible())
	{
		uiRide->setVisible(false);
	}
	else
	{
		uiRide->setVisible(true);
	}
}

void UIMainCity::countryButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type != TOUCH_EVENT_BEGAN)
	{
		return;
	}

	if (uiCountry == NULL)
	{
		uiCountry = UICountry::create();
		uiCountry->retain();
		TianXiaDiYi::getTheOnlyInstance()->addChild(uiCountry);
	}

	if (uiCountry->isVisible())
	{
		uiCountry->setVisible(false);
	}
	else
	{
		uiCountry->setVisible(true);
	}
}
