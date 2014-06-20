#include "UIBag.h"

#include "Logic\ItemManager.h"
#include "..\TianXiaDiYi.h"

UIBag::UIBag()
{
	itemManager = ItemManager::getTheOnlyInstance();
	multiStringPanelTemp = NULL;
}

UIBag::~UIBag()
{
}

bool UIBag::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	uiLayer = UILayer::create();

	UILayout* bagRoot = dynamic_cast<UILayout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/UIBag.ExportJson"));
	uiLayer->addWidget(bagRoot);

	UIButton* closeButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("CloseButton"));
	closeButton->addTouchEventListener(this, toucheventselector(UIBag::closeButtonClicked));

	for (int i = 0; i < 16; i++)
	{
		const char* s = CCString::createWithFormat("ItemButton_%d", i+1)->getCString();
		UIButton* itemButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName(s));
		itemButton->addTouchEventListener(this, toucheventselector(UIBag::itemButtonClicked));
	}

	UIButton* sortButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("SortButton"));
	sortButton->addTouchEventListener(this, toucheventselector(UIBag::sortButtonClicked));

	UIButton* sellButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("SellButton"));
	sellButton->addTouchEventListener(this, toucheventselector(UIBag::sellButtonClicked));

	UIButton* pageLeftButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("PageLeftButton"));
	pageLeftButton->addTouchEventListener(this, toucheventselector(UIBag::pageLeftButtonClicked));

	UIButton* pageRightButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("PageRightButton"));
	pageRightButton->addTouchEventListener(this, toucheventselector(UIBag::pageRightButtonClicked));

	for (int i = 0; i < 16; i++)
	{
		const char* s = CCString::createWithFormat("ItemImageView_%d", i+1)->getCString();
		itemImageView[i] = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName(s));
	}

	itemFeatureImageView = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("ItemFeatureImageView"));

	selectFrameImageView = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("SelectFrameImageView"));

	for (int i = 0; i < 3; i++)
	{
		const char* s = CCString::createWithFormat("AttributeValueLabel_%d", i+1)->getCString();
		attributeValueLabel[i] = dynamic_cast<UILabel*>(uiLayer->getWidgetByName(s));
	}

	multiStringPanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("MultiStringPanel"));

	addChild(uiLayer);

	setVisible(false);
	refresh();
	return true;
}

void UIBag::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
}

void UIBag::clear()
{
	for (int i = 0; i < 16; i++)
	{
		itemImageView[i]->setVisible(false);
	}

	itemFeatureImageView->setVisible(false);

	for (int i = 0; i < 3; i++)
	{
		attributeValueLabel[i]->setText(" ");
	}

	if (multiStringPanelTemp != NULL)
	{
		multiStringPanel->removeChild(multiStringPanelTemp, true);
	}
}

void UIBag::refresh()
{
	clear();

	for (int i = 0; i < 16; i++)
	{
		int j = itemManager->pageNum * 16 + i;

		Item* item = itemManager->itemArray[j];

		if (item != NULL)
		{
			const char* s;

			if (item->type == GEM)
			{
				Gem* gem = (Gem*)item;
				s = CCString::createWithFormat("png/gem/%s.png", gem->attribute.tuPian)->getCString();
			}

			if (item->type == EQUIPMENT)
			{
				Equipment* equipment = (Equipment*)item;
				s = CCString::createWithFormat("png/equipment/%s.png", equipment->attribute.tuPian)->getCString();
			}

			itemImageView[i]->loadTexture(s);
			itemImageView[i]->setVisible(true);
		}
	}

	Item* item = itemManager->itemArray[itemManager->selectItemId];

	if (item != NULL)
	{
		// 图片
		const char* tuPian;
		// 名称
		const char* mingCheng;
		// 描述
		const char* miaoShu;
		// 价格
		const char* jiaGe;

		if (item->type == GEM)
		{
			Gem* gem = (Gem*)item;
			tuPian = CCString::createWithFormat("png/gem/%s.png", gem->attribute.tuPian)->getCString();
			
			mingCheng = TianXiaDiYi::getTheOnlyInstance()->ansi2utf8(gem->attribute.name);
			miaoShu = gem->attribute.miaoShu;
			jiaGe = TianXiaDiYi::getTheOnlyInstance()->ansi2utf8(CCString::createWithFormat("%d金币", gem->attribute.maiChuJiaGe)->getCString());
		}

		if (item->type == EQUIPMENT)
		{
			Equipment* equipment = (Equipment*)item;
			tuPian = CCString::createWithFormat("png/equipment/%s.png", equipment->attribute.tuPian)->getCString();

			mingCheng = TianXiaDiYi::getTheOnlyInstance()->ansi2utf8(equipment->attribute.name);
			miaoShu = equipment->attribute.miaoShu;
			jiaGe = TianXiaDiYi::getTheOnlyInstance()->ansi2utf8(CCString::createWithFormat("%d金币", equipment->attribute.maiChuJiaGe)->getCString());
		}

		itemFeatureImageView->loadTexture(tuPian);
		itemFeatureImageView->setVisible(true);

		const char* attribute[3] = {mingCheng, miaoShu, jiaGe};

		for (int i = 0; i < 3; i++)
		{
			attributeValueLabel[i]->setText(attribute[i]);
		}

		if (miaoShu != NULL)
		{
			multiStringPanelTemp = TianXiaDiYi::getTheOnlyInstance()->getMultiString(miaoShu, multiStringPanel->getContentSize().width);
			multiStringPanel->addChild(multiStringPanelTemp);
		}

		delete[] mingCheng;
		delete[] jiaGe;
	}
}

void UIBag::closeButtonClicked( CCObject* sender, TouchEventType type )
{
	TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiBag, true);
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiBag->release();
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiBag = NULL;
}

void UIBag::itemButtonClicked( CCObject* sender, TouchEventType type )
{
	UIButton* button = (UIButton*)sender;

	for (int i = 0; i < 16; i++)
	{
		const char* s = CCString::createWithFormat("ItemButton_%d", i+1)->getCString();

		if (strcmp(button->getName(), s) == 0)
		{
			selectFrameImageView->setPosition(button->getPosition());
			itemManager->selectItemId = itemManager->pageNum * 16 + i;
			refresh();

			break;
		}
	}
}

void UIBag::sortButtonClicked( CCObject* sender, TouchEventType type )
{
	itemManager->sort();
	refresh();
}

void UIBag::sellButtonClicked( CCObject* sender, TouchEventType type )
{
	itemManager->sell();
	refresh();
}

void UIBag::pageLeftButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		itemManager->pageNum--;

		if (itemManager->pageNum < 0)
		{
			itemManager->pageNum = 0;
			return;
		}

		CCLOG("itemManager->pageNum: %d", itemManager->pageNum);
		itemManager->selectItemId = itemManager->pageNum * 16;
		UIButton* button = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("ItemButton_1"));
		selectFrameImageView->setPosition(button->getPosition());

		refresh();
	}
}

void UIBag::pageRightButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		itemManager->pageNum++;

		if (itemManager->pageNum > itemManager->maxPageNum - 1)
		{
			itemManager->pageNum = itemManager->maxPageNum - 1;
			return;
		}

		CCLOG("itemManager->pageNum: %d", itemManager->pageNum);
		itemManager->selectItemId = itemManager->pageNum * 16;
		UIButton* button = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("ItemButton_1"));
		selectFrameImageView->setPosition(button->getPosition());

		refresh();
	}
}
