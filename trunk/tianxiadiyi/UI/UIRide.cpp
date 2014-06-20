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

	selectFrameImageView = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("SelectFrameImageView"));

	for (int i = 0; i < 8; i++)
	{
		const char* s = CCString::createWithFormat("RideImageView_%d", i+1)->getCString();
		rideImageView[i] = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName(s));
	}

	for (int i = 0; i < 8; i++)
	{
		const char* s = CCString::createWithFormat("RideNameLabel_%d", i+1)->getCString();
		rideNameLabel[i] = dynamic_cast<UILabel*>(uiLayer->getWidgetByName(s));
	}

	for (int i = 0; i < 8; i++)
	{
		const char* s = CCString::createWithFormat("RideLvLabel_%d", i+1)->getCString();
		rideLvLabel[i] = dynamic_cast<UILabel*>(uiLayer->getWidgetByName(s));
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

	for (int i = 0; i < 5; i++)
	{
		attributeValueLabel[i]->setText(" ");
	}

	for (int i = 0; i < 8; i++)
	{
		rideNameLabel[i]->setText(" ");
	}

	for (int i = 0; i < 8; i++)
	{
		rideLvLabel[i]->setText(" ");
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
			Ride* ride = rideManager->rideVector[j];

			const char* s = CCString::createWithFormat("png/ride/%s.png", ride->attribute.tuPian)->getCString();
			rideImageView[i]->loadTexture(s);
			rideImageView[i]->setVisible(true);

			const char* name = TianXiaDiYi::getTheOnlyInstance()->ansi2utf8(ride->attribute.name);
			rideNameLabel[i]->setText(name);
			delete[] name;

			const char* lv = CCString::createWithFormat("Lv%d", ride->lv)->getCString();
			rideLvLabel[i]->setText(lv);
		}
	}

	if (rideManager->selectRideId >= rideManager->rideVector.size())
	{
		return;
	}

	Ride* ride = rideManager->rideVector[rideManager->selectRideId];

	// 物理攻击
	const char* wuLiGongJi = CCString::createWithFormat("%d", ride->attribute.chuShiGongJi)->getCString();
	// 物理防御
	const char* wuLifangYu = CCString::createWithFormat("%d", ride->attribute.chuShiFangYu)->getCString();
	// 法术攻击
	const char* faShuGongJi = CCString::createWithFormat("%d", ride->attribute.chuShiGongJi)->getCString();
	// 法术防御
	const char* faShuFangYu = CCString::createWithFormat("%d", ride->attribute.chuShiFangYu)->getCString();
	// 生命
	const char* shengMing = CCString::createWithFormat("%d", ride->attribute.chuShiShengMing)->getCString();

	const char* attribute[5] = {wuLiGongJi, wuLifangYu, faShuFangYu, faShuGongJi, shengMing};

	for (int i = 0; i < 5; i++)
	{
		attributeValueLabel[i]->setText(attribute[i]);
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
	UIButton* button = (UIButton*)sender;

	for (int i = 0; i < 8; i++)
	{
		const char* s = CCString::createWithFormat("RideButton_%d", i+1)->getCString();

		if (strcmp(button->getName(), s) == 0)
		{
			selectFrameImageView->setPosition(button->getPosition());
			rideManager->selectRideId = rideManager->pageNum * 8 + i;
			refresh();

			break;
		}
	}
}

void UIRide::ridingButtonClicked( CCObject* sender, TouchEventType type )
{
}

void UIRide::strengthenButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiRideStrengthen = UIRideStrengthen::create();
		TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiRideStrengthen->retain();
		TianXiaDiYi::getTheOnlyInstance()->addChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiRideStrengthen);
	}
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
		rideManager->selectRideId = rideManager->pageNum * 8;
		UIButton* button = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("RideButton_1"));;
		selectFrameImageView->setPosition(button->getPosition());

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
		rideManager->selectRideId = rideManager->pageNum * 8;
		UIButton* button = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("RideButton_1"));;
		selectFrameImageView->setPosition(button->getPosition());

		refresh();
	}
}