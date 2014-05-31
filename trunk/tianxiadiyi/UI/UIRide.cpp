#include "UIRide.h"

#include "..\TianXiaDiYi.h"

UIRide::UIRide()
{
	rideManager = RideManager::getTheOnlyInstance();
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

	for (int i = 0; i < 8; i++)
	{
		const char* s = CCString::createWithFormat("RideButton_%d", i+1)->getCString();
		UIButton* rideButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName(s));
		rideButton->addTouchEventListener(this, toucheventselector(UIRide::rideButtonClicked));
	}

	UIButton* ridingButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("RidingButton"));
	ridingButton->addTouchEventListener(this, toucheventselector(UIRide::ridingButtonClicked));

	UIButton* strengthenButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("StrengthenButton"));
	strengthenButton->addTouchEventListener(this, toucheventselector(UIRide::strengthenButtonClicked));

	UIButton* pageLeftButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("PageLeftButton"));
	pageLeftButton->addTouchEventListener(this, toucheventselector(UIRide::pageLeftButtonClicked));

	UIButton* pageRightButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("PageRightButton"));
	pageRightButton->addTouchEventListener(this, toucheventselector(UIRide::pageRightButtonClicked));

	for (int i = 0; i < 8; i++)
	{
		const char* s = CCString::createWithFormat("RideImageView_%d", i+1)->getCString();
		rideImageView[i] = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName(s));
	}

	for (int i = 0; i < 5; i++)
	{
		const char* s = CCString::createWithFormat("AttributeValueLabel_%d", i+1)->getCString();
		attributeValueLabel[i] = dynamic_cast<UILabel*>(uiLayer->getWidgetByName(s));
	}

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

void UIRide::clear()
{
	for (int i = 0; i < 8; i++)
	{
		rideImageView[i]->setVisible(false);
	}
}

void UIRide::refresh()
{
	clear();

	for (int i = 0; i < 8; i++)
	{
		int j = rideManager->pageNum * 8 + i;

		if (j < rideManager->rideVector.size())
		{
			const char* s = CCString::createWithFormat("png/ride/%s.png", rideManager->rideVector[j]->attribute.tuPian)->getCString();
			rideImageView[i]->loadTexture(s);
			rideImageView[i]->setVisible(true);
		}
	}
}

void UIRide::closeButtonClicked( CCObject* sender, TouchEventType type )
{
	TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiRide, true);
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiRide->release();
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiRide = NULL;
}

void UIRide::rideButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiRideStrengthen = UIRideStrengthen::create();
		TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiRideStrengthen->retain();
		TianXiaDiYi::getTheOnlyInstance()->addChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiRideStrengthen);
	}
}

void UIRide::ridingButtonClicked( CCObject* sender, TouchEventType type )
{

}

void UIRide::strengthenButtonClicked( CCObject* sender, TouchEventType type )
{

}

void UIRide::pageLeftButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		rideManager->pageNum--;

		if (rideManager->pageNum < 0)
		{
			rideManager->pageNum = 0;
			return;
		}

		CCLOG("rideManager->pageNum: %d", rideManager->pageNum);

		refresh();
	}
}

void UIRide::pageRightButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		rideManager->pageNum++;

		if (rideManager->pageNum > rideManager->maxPageNum - 1)
		{
			rideManager->pageNum = rideManager->maxPageNum - 1;
			return;
		}

		CCLOG("rideManager->pageNum: %d", rideManager->pageNum);

		refresh();
	}
}
