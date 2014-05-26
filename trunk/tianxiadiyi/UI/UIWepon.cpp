#include "UIWepon.h"

#include "..\TianXiaDiYi.h"

UIWepon::UIWepon()
{
}

UIWepon::~UIWepon()
{
}

bool UIWepon::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	uiLayer = UILayer::create();

	UILayout* weponRoot = dynamic_cast<UILayout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/UIWepon.ExportJson"));
	uiLayer->addWidget(weponRoot);

	UIButton* closeButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("CloseButton"));
	closeButton->addTouchEventListener(this, toucheventselector(UIWepon::closeButtonClicked));

	addChild(uiLayer);
	return true;
}

void UIWepon::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
}

void UIWepon::closeButtonClicked( CCObject* sender, TouchEventType type )
{
	TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiWepon, true);
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiWepon->release();
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiWepon = NULL;
}