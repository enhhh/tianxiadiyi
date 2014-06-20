#include "UIRideStrengthen.h"

#include "..\TianXiaDiYi.h"

UIRideStrengthen::UIRideStrengthen()
{
	rideStrengthenManager = RideStrengthenManager::getTheOnlyInstance();
	rideStrengthenManager->init();
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

	featureImageView = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("RideFeatureImageView"));

	nameLabel = dynamic_cast<UILabel*>(uiLayer->getWidgetByName("RideNameLabel"));
	lvLabel = dynamic_cast<UILabel*>(uiLayer->getWidgetByName("LvNameLabel"));

	for (int i = 0; i < 5; i++)
	{
		const char* s = CCString::createWithFormat("Attribute1ValueLabel_%d", i+1)->getCString();
		attribute1ValueLabel[i] = dynamic_cast<UILabel*>(uiLayer->getWidgetByName(s));

		const char* t = CCString::createWithFormat("Attribute2ValueLabel_%d", i+1)->getCString();
		attribute2ValueLabel[i] = dynamic_cast<UILabel*>(uiLayer->getWidgetByName(t));
	}

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
	nameLabel->setText(" ");
	lvLabel->setText(" ");

	for (int i = 0; i < 5; i++)
	{
		attribute1ValueLabel[i]->setText(" ");
		attribute2ValueLabel[i]->setText(" ");
	}
}

void UIRideStrengthen::refresh()
{
	clear();

	Ride* ride = rideStrengthenManager->ride;

	const char* s = CCString::createWithFormat("png/rideFeature/%sFeature.png", ride->attribute.tuPian)->getCString();
	featureImageView->loadTexture(s);

	const char* name = TianXiaDiYi::getTheOnlyInstance()->ansi2utf8(ride->attribute.name);
	nameLabel->setText(name);

	const char* lv = CCString::createWithFormat("Lv%d", ride->lv)->getCString();
	lvLabel->setPositionX(nameLabel->getPositionX()+nameLabel->getContentSize().width);
	lvLabel->setText(lv);

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
		attribute1ValueLabel[i]->setText(attribute[i]);
	}

	vector<string> strengthenAttribute = ride->getStrengthenAttribute(ride->strengthenLv+1);
	int gongJi = atoi(strengthenAttribute[0].c_str());
	int fangYu = atoi(strengthenAttribute[1].c_str());
	int shengMingValue = atoi(strengthenAttribute[2].c_str());

	// 物理攻击
	wuLiGongJi = CCString::createWithFormat("%d", ride->attribute.chuShiGongJi+gongJi)->getCString();
	// 物理防御
	wuLifangYu = CCString::createWithFormat("%d", ride->attribute.chuShiFangYu+fangYu)->getCString();
	// 法术攻击
	faShuGongJi = CCString::createWithFormat("%d", ride->attribute.chuShiGongJi+gongJi)->getCString();
	// 法术防御
	faShuFangYu = CCString::createWithFormat("%d", ride->attribute.chuShiFangYu+fangYu)->getCString();
	// 生命
	shengMing = CCString::createWithFormat("%d", ride->attribute.chuShiShengMing+shengMingValue)->getCString();

	const char* attribute2[5] = {wuLiGongJi, wuLifangYu, faShuFangYu, faShuGongJi, shengMing};

	for (int i = 0; i < 5; i++)
	{
		attribute2ValueLabel[i]->setText(attribute2[i]);
	}
}

void UIRideStrengthen::closeButtonClicked( CCObject* sender, TouchEventType type )
{
	TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiRideStrengthen, true);
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiRideStrengthen->release();
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiRideStrengthen = NULL;
}
