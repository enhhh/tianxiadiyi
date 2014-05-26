#include "UICountry.h"

#include "..\TianXiaDiYi.h"

UICountry::UICountry()
{
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