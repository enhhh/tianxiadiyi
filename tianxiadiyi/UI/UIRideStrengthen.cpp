#include "UIRideStrengthen.h"

#include "..\TianXiaDiYi.h"

UIRideStrengthen::UIRideStrengthen()
{
}

UIRideStrengthen::~UIRideStrengthen()
{
}

bool UIRideStrengthen::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	uiLayer = UILayer::create();

	UILayout* rideRoot = dynamic_cast<UILayout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/UIRideStrengthen.ExportJson"));
	uiLayer->addWidget(rideRoot);

	UIButton* closeButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("CloseButton"));
	closeButton->addTouchEventListener(this, toucheventselector(UIRideStrengthen::closeButtonClicked));

	addChild(uiLayer);
	refresh();
	return true;
}

void UIRideStrengthen::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
}

void UIRideStrengthen::clear()
{

}

void UIRideStrengthen::refresh()
{
	clear();
}

void UIRideStrengthen::closeButtonClicked( CCObject* sender, TouchEventType type )
{
	TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiRideStrengthen, true);
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiRideStrengthen->release();
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiRideStrengthen = NULL;
}
