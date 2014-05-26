#include "UIRide.h"

#include "..\TianXiaDiYi.h"

UIRide::UIRide()
{
}

UIRide::~UIRide()
{
}

bool UIRide::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	uiLayer = UILayer::create();

	UILayout* rideRoot = dynamic_cast<UILayout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/UIRide.ExportJson"));
	uiLayer->addWidget(rideRoot);

	UIButton* closeButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("CloseButton"));
	closeButton->addTouchEventListener(this, toucheventselector(UIRide::closeButtonClicked));

	addChild(uiLayer);
	setVisible(false);

	refresh();
	return true;
}

void UIRide::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
}

void UIRide::refresh()
{
}

void UIRide::closeButtonClicked( CCObject* sender, TouchEventType type )
{
	TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiRide, true);
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiRide->release();
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiRide = NULL;
}