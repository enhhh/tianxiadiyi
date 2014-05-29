#include "UIWeponTakeUp.h"
#include "UIGeneral.h"

#include "..\TianXiaDiYi.h"

UIWeponTakeUp::UIWeponTakeUp()
{
	generalManager = GeneralManager::getTheOnlyInstance();
	weponTakeUpManager = WeponTakeUpManager::getTheOnlyInstance();

	weponTakeUpManager->init();
}

UIWeponTakeUp::~UIWeponTakeUp()
{
}

bool UIWeponTakeUp::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	uiLayer = UILayer::create();

	UILayout* weponTakeupRoot = dynamic_cast<UILayout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/UIWeponTakeUp.ExportJson"));
	uiLayer->addWidget(weponTakeupRoot);

	UIButton* closeButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("CloseButton"));
	closeButton->addTouchEventListener(this, toucheventselector(UIWeponTakeUp::closeButtonClicked));

	UIButton* takeUpButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("TakeUpButton"));
	takeUpButton->addTouchEventListener(this, toucheventselector(UIWeponTakeUp::takeUpButtonClicked));

	UIButton* fillButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("FillButton"));
	fillButton->addTouchEventListener(this, toucheventselector(UIWeponTakeUp::fillButtonClicked));

	equipmentFeatureImageView = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("EquipmentFeatureImageView"));
	roundImageView = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("RoundImageView"));

	for (int i = 0; i < 3; i++)
	{
		const char* s = CCString::createWithFormat("EquipmentImageView_%d", i+1)->getCString();
		equipmentImageView[i] = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName(s));
	}

	for (int i = 0; i < 3; i++)
	{
		const char* s = CCString::createWithFormat("EquipmentButton_%d", i+1)->getCString();
		UIButton* equipmentButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName(s));
		equipmentButton->addTouchEventListener(this, toucheventselector(UIWeponTakeUp::equipmentButtonClicked));
	}

	UIButton* pageLeftButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("PageLeftButton"));
	pageLeftButton->addTouchEventListener(this, toucheventselector(UIWeponTakeUp::pageLeftButtonClicked));

	UIButton* pageRightButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("PageRightButton"));
	pageRightButton->addTouchEventListener(this, toucheventselector(UIWeponTakeUp::pageRightButtonClicked));

	addChild(uiLayer);
	refresh();

	return true;
}

void UIWeponTakeUp::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
}

void UIWeponTakeUp::clear()
{
	equipmentFeatureImageView->setVisible(false);
	roundImageView->setVisible(false);

	for (int i = 0; i < 3; i++)
	{
		equipmentImageView[i]->setVisible(false);
	}
}

void UIWeponTakeUp::refresh()
{
	clear();

	if (weponTakeUpManager->equipment != NULL)
	{
		const char* s = CCString::createWithFormat("png/equipment/%s.png", weponTakeUpManager->equipment->attribute.tuPian)->getCString();
		equipmentFeatureImageView->loadTexture(s);
		equipmentFeatureImageView->setVisible(true);

		if (weponTakeUpManager->equipment->gem != NULL)
		{
			const char* s = CCString::createWithFormat("png/gem/%s.png", weponTakeUpManager->equipment->gem->attribute.tuPian)->getCString();
			roundImageView->loadTexture(s);
			roundImageView->setVisible(true);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		int j = weponTakeUpManager->pageNum * 3 + i;

		if (j < weponTakeUpManager->equipmentVector.size())
		{
			const char* s = CCString::createWithFormat("png/equipment/%s.png", weponTakeUpManager->equipmentVector[j].equipment->attribute.tuPian)->getCString();
			equipmentImageView[i]->loadTexture(s);
			equipmentImageView[i]->setVisible(true);
		}
		else
		{
			equipmentImageView[i]->setVisible(false);
		}
	}
}

void UIWeponTakeUp::closeButtonClicked( CCObject* sender, TouchEventType type )
{
	TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiWeponTakeup, true);
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiWeponTakeup->release();
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiWeponTakeup = NULL;
}

void UIWeponTakeUp::takeUpButtonClicked( CCObject* sender, TouchEventType type )
{
	weponTakeUpManager->takeUp();

	TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiWeponTakeup, true);
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiWeponTakeup->release();
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiWeponTakeup = NULL;
	
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiGeneral->refresh();
}

void UIWeponTakeUp::fillButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiWepon = UIWepon::create();
		TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiWepon->retain();
		TianXiaDiYi::getTheOnlyInstance()->addChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiWepon);
	}
}

void UIWeponTakeUp::equipmentButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		UIButton* button = (UIButton*)sender;

		for (int i = 0; i < 3; i++)
		{
			const char* s = CCString::createWithFormat("EquipmentButton_%d", i+1)->getCString();

			if (strcmp(button->getName(), s) == 0)
			{
				weponTakeUpManager->selectEquipmentId = weponTakeUpManager->pageNum * 3 + i;

				// Ñ¡Ôñ×°±¸
				if (weponTakeUpManager->selectEquipmentId < weponTakeUpManager->equipmentVector.size())
				{
					weponTakeUpManager->equipment = weponTakeUpManager->equipmentVector[weponTakeUpManager->selectEquipmentId].equipment;
				}
				else
				{
					weponTakeUpManager->equipment = NULL;
				}

				refresh();

				break;
			}
		}
	}
}

void UIWeponTakeUp::pageLeftButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		weponTakeUpManager->pageNum--;

		if (weponTakeUpManager->pageNum < 0)
		{
			weponTakeUpManager->pageNum = 0;
			return;
		}

		CCLOG("weponTakeUpManager->pageNum: %d", weponTakeUpManager->pageNum);

		refresh();
	}
}

void UIWeponTakeUp::pageRightButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		weponTakeUpManager->pageNum++;

		if (weponTakeUpManager->pageNum > weponTakeUpManager->maxPageNum - 1)
		{
			weponTakeUpManager->pageNum = weponTakeUpManager->maxPageNum - 1;
			return;
		}

		CCLOG("weponTakeUpManager->pageNum: %d", weponTakeUpManager->pageNum);

		refresh();
	}
}