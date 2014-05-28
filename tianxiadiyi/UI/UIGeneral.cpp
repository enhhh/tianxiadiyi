#include "UIGeneral.h"
#include "UIWepon.h"
#include "UIAdvanced.h"
#include "UIGeneral.h"

#include "..\TianXiaDiYi.h"

UIGeneral::UIGeneral()
{
	generalManager = GeneralManager::getTheOnlyInstance();
}

UIGeneral::~UIGeneral()
{
}

bool UIGeneral::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	uiLayer = UILayer::create();

	UILayout* generalRoot = dynamic_cast<UILayout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/UIGeneral.ExportJson"));
	uiLayer->addWidget(generalRoot);

	UIButton* advancedButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("AdvancedButton"));
	advancedButton->addTouchEventListener(this, toucheventselector(UIGeneral::advancedButtonClicked));

	UIButton* closeButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("CloseButton"));
	closeButton->addTouchEventListener(this, toucheventselector(UIGeneral::closeButtonClicked));

	UIButton* pageLeftButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("PageLeftButton"));
	pageLeftButton->addTouchEventListener(this, toucheventselector(UIGeneral::pageLeftButtonClicked));

	UIButton* pageRightButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("PageRightButton"));
	pageRightButton->addTouchEventListener(this, toucheventselector(UIGeneral::pageRightButtonClicked));

	for (int i = 0; i < 3; i++)
	{
		const char* s = CCString::createWithFormat("HeadImageView_%d", i+1)->getCString();
		headImageView[i] = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName(s));
	}

	selectFrameImageView = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("SelectFrameImageView"));

	for (int i = 0; i < 6; i++)
	{
		const char* s = CCString::createWithFormat("EquipmentImageView_%d", i+1)->getCString();
		equipmentImageView[i] = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName(s));
	}

	headFeatureImageView = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("HeadFeatureImageView"));

	for (int i = 0; i < 3; i++)
	{
		const char* s = CCString::createWithFormat("HeadButton_%d", i+1)->getCString();
		UIButton* headButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName(s));
		headButton->addTouchEventListener(this, toucheventselector(UIGeneral::headButtonClicked));
	}

	for (int i = 0; i < 6; i++)
	{
		const char* s = CCString::createWithFormat("EquipmentButton_%d", i+1)->getCString();
		UIButton* headButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName(s));
		headButton->addTouchEventListener(this, toucheventselector(UIGeneral::equipmentButtonClicked));
	}

	UIPanel* spritePanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("SpritePanel"));
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("ui/StarringSprite0.png", "ui/StarringSprite0.plist", "ui/StarringSprite.ExportJson");
	CCArmature* spriteAarmature = CCArmature::create("StarringSprite");
	spriteAarmature->getAnimation()->play("StandDown");
	spriteAarmature->setPosition(spritePanel->getPosition());

	uiLayer->addChild(spriteAarmature);

	addChild(uiLayer);
	setVisible(false);

	refresh();
	return true;
}

void UIGeneral::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
}

void UIGeneral::refresh()
{
	headFeatureImageView->setVisible(false);

	if (generalManager->selectGeneralId < generalManager->generalVector.size())
	{
		const char* s = CCString::createWithFormat("png/general/%s.png", generalManager->generalVector[generalManager->selectGeneralId]->attribute.tuPian)->getCString();
		headFeatureImageView->loadTexture(s);
		headFeatureImageView->setVisible(true);
	}

	// ½«ÁìÍ¼Æ¬
	int num;

	if (generalManager->pageNum < (generalManager->maxPageNum-1))
	{
		num = 3;
	}
	else
	{
		num = generalManager->generalVector.size() - generalManager->pageNum * 3;
	}

	for (int i = 0; i < 3; i++)
	{
		if (i < num)
		{
			int j = generalManager->pageNum * 3 + i;
			const char* s = CCString::createWithFormat("png/general/%s.png", generalManager->generalVector[j]->attribute.tuPian)->getCString();
			headImageView[i]->loadTexture(s);
			headImageView[i]->setVisible(true);
		}
		else
		{
			headImageView[i]->setVisible(false);
		}
	}

	for (int i = 0; i < 6; i++)
	{
		equipmentImageView[i]->setVisible(false);

		if (generalManager->selectGeneralId < generalManager->generalVector.size())
		{
			Equipment* equipment = generalManager->generalVector[generalManager->selectGeneralId]->equipmentArray[i];

			if (equipment != NULL)
			{
				const char* s = CCString::createWithFormat("png/equipment/%s.png", equipment->attribute.tuPian)->getCString();
				equipmentImageView[i]->loadTexture(s);
				equipmentImageView[i]->setVisible(true);
			}	
		}
	}
}

void UIGeneral::closeButtonClicked( CCObject* sender, TouchEventType type )
{
	TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiGeneral, true);
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiGeneral->release();
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiGeneral = NULL;
}

void UIGeneral::headButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		UIButton* button = (UIButton*)sender;

		for (int i = 0; i < 3; i++)
		{
			const char* s = CCString::createWithFormat("HeadButton_%d", i+1)->getCString();

			if (strcmp(button->getName(), s) == 0)
			{
				selectFrameImageView->setPosition(button->getPosition());
				generalManager->selectGeneralId = generalManager->pageNum * 3 + i;
				refresh();

				break;
			}
		}
	}	
}

void UIGeneral::equipmentButtonClicked( CCObject* sender, TouchEventType type )
{
	if (generalManager->selectGeneralId >= generalManager->generalVector.size())
	{
		return;
	}

	UIButton* button = (UIButton*)sender;

	if (type == CCTOUCHBEGAN)
	{
		for (int i = 0; i < 6; i++)
		{
			const char* s = CCString::createWithFormat("EquipmentButton_%d", i+1)->getCString();

			if (strcmp(button->getName(), s) == 0)
			{
				generalManager->selectEquipmentId = i;

				TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiWeponTakeup = UIWeponTakeUp::create();
				TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiWeponTakeup->retain();
				TianXiaDiYi::getTheOnlyInstance()->addChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiWeponTakeup);
			}
		}
	}
}

void UIGeneral::advancedButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiAdvanced = UIAdvanced::create();
		TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiAdvanced->retain();
		TianXiaDiYi::getTheOnlyInstance()->addChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiAdvanced);
	}
}

void UIGeneral::pageLeftButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		generalManager->pageNum--;

		if (generalManager->pageNum < 0)
		{
			generalManager->pageNum = 0;
			return;
		}

		CCLOG("generalManager->pageNum: %d", generalManager->pageNum);
		generalManager->selectGeneralId = generalManager->pageNum * 3;
		UIButton* button = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("HeadButton_1"));;
		selectFrameImageView->setPosition(button->getPosition());

		refresh();
	}
}

void UIGeneral::pageRightButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		generalManager->pageNum++;

		if (generalManager->pageNum > generalManager->maxPageNum - 1)
		{
			generalManager->pageNum = generalManager->maxPageNum - 1;
			return;
		}

		CCLOG("generalManager->pageNum: %d", generalManager->pageNum);

		generalManager->selectGeneralId = generalManager->pageNum * 3;
		UIButton* button = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("HeadButton_1"));;
		selectFrameImageView->setPosition(button->getPosition());

		refresh();
	}
}
