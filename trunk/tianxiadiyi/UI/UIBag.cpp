#include "UIBag.h"

#include "Logic\ItemManager.h"
#include "..\TianXiaDiYi.h"

UIBag::UIBag()
{
	itemManager = ItemManager::getTheOnlyInstance();
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

		itemFeatureImageView->loadTexture(s);
		itemFeatureImageView->setVisible(true);
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

		refresh();
	}
}
