#include "UIWeponTakeup.h"

#include "..\TianXiaDiYi.h"

UIWeponTakeup::UIWeponTakeup()
{
	generalManager = GeneralManager::getTheOnlyInstance();
}

UIWeponTakeup::~UIWeponTakeup()
{
}

bool UIWeponTakeup::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	uiLayer = UILayer::create();

	UILayout* weponTakeupRoot = dynamic_cast<UILayout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/UIWeponTakeup.ExportJson"));
	uiLayer->addWidget(weponTakeupRoot);

	UIButton* closeButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("CloseButton"));
	closeButton->addTouchEventListener(this, toucheventselector(UIWeponTakeup::closeButtonClicked));

	UIButton* fillButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("FillButton"));
	fillButton->addTouchEventListener(this, toucheventselector(UIWeponTakeup::fillButtonClicked));

	equipmentFeatureImageView = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("EquipmentFeatureImageView"));

	addChild(uiLayer);
	refresh();

	return true;
}

void UIWeponTakeup::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
}

void UIWeponTakeup::refresh()
{
	Equipment* equipment = generalManager->generalVector[generalManager->selectGeneralId]->equipmentArray[generalManager->selectEquipmentId];

	if (equipment != NULL)
	{
		if (equipment != NULL)
		{
			const char* s = CCString::createWithFormat("png/equipment/%s.png", equipment->attribute.tuPian)->getCString();
			equipmentFeatureImageView->loadTexture(s);
			equipmentFeatureImageView->setVisible(true);
		}
		else
		{
			equipmentFeatureImageView->setVisible(false);
		}	
	}
}

void UIWeponTakeup::closeButtonClicked( CCObject* sender, TouchEventType type )
{
	TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiWeponTakeup, true);
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiWeponTakeup->release();
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiWeponTakeup = NULL;
}

void UIWeponTakeup::fillButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiWepon = UIWepon::create();
		TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiWepon->retain();
		TianXiaDiYi::getTheOnlyInstance()->addChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiWepon);
	}
}
