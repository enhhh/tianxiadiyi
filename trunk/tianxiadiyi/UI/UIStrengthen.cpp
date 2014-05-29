#include "UIStrengthen.h"

#include "..\TianXiaDiYi.h"

UIStrengthen::UIStrengthen()
{
	itemManager = ItemManager::getTheOnlyInstance();
	formationManager = FormationManager::getTheOnlyInstance();
	strengthenManager = StrengthenManager::getTheOnlyInstance();
}

UIStrengthen::~UIStrengthen()
{
}

bool UIStrengthen::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	uiLayer = UILayer::create();

	UILayout* strengthenRoot = dynamic_cast<UILayout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/UIStrengthen.ExportJson"));
	uiLayer->addWidget(strengthenRoot);

	UIButton* closeButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("CloseButton"));
	closeButton->addTouchEventListener(this, toucheventselector(UIStrengthen::closeButtonClicked));

	UIButton* strengthenButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("StrengthenButton"));
	strengthenButton->addTouchEventListener(this, toucheventselector(UIStrengthen::strengthenButtonClicked));

	UIButton* pageLeftButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("PageLeftButton"));
	pageLeftButton->addTouchEventListener(this, toucheventselector(UIStrengthen::pageLeftButtonClicked));

	UIButton* pageRightButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("PageRightButton"));
	pageRightButton->addTouchEventListener(this, toucheventselector(UIStrengthen::pageRightButtonClicked));

	for (int i = 0; i < 4; i++)
	{
		const char* s = CCString::createWithFormat("EquipmentImageView_%d", i+1)->getCString();
		equipmentImageView[i] = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName(s));
	}

	for (int i = 0; i < 3; i++)
	{
		const char* s = CCString::createWithFormat("GemImageView_%d", i+1)->getCString();
		gemImageView[i] = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName(s));
	}

	for (int i = 0; i < 2; i++)
	{
		const char* s = CCString::createWithFormat("GemFrontImageView_%d", i+1)->getCString();
		gemFrontImageView[i] = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName(s));
	}

	featureImageView = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("FeatureImageView"));

	strengthenTestButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("StrengthenTestButton"));

	UIPanel* tableViewPanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("TableViewPanel"));

	CCTableView* strengthenTableView = CCTableView::create(this, CCSizeMake(strengthenTestButton->getContentSize().width, tableViewPanel->getContentSize().height));
	strengthenTableView->setDirection(kCCScrollViewDirectionVertical);
	strengthenTableView->setVerticalFillOrder(kCCTableViewFillTopDown);

	selectFrameImageView = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("SelectFrameImageView"));

	CCPoint strengthenTestPosition = strengthenTestButton->getPosition();
	strengthenTableView->setPosition(ccp(strengthenTestPosition.x, strengthenTestPosition.y - tableViewPanel->getContentSize().height));
	strengthenTableView->setDelegate(this);
	strengthenTableView->reloadData();

	for (int i = 0; i < 4; i++)
	{
		const char* s = CCString::createWithFormat("EquipmentButton_%d", i+1)->getCString();
		UIButton* equipmentButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName(s));
		equipmentButton->addTouchEventListener(this, toucheventselector(UIStrengthen::equipmentButtonClicked));
	}

	for (int i = 0; i < 2; i++)
	{
		const char* s = CCString::createWithFormat("GemButton_%d", i+1)->getCString();
		UIButton* gemButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName(s));
		gemButton->addTouchEventListener(this, toucheventselector(UIStrengthen::gemButtonClicked));
	}

	addChild(uiLayer);
	addChild(strengthenTableView);
	setVisible(false);

	refresh();
	return true;
}

void UIStrengthen::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
}

void UIStrengthen::refresh()
{
	int num;

	if (strengthenManager->pageNum < (strengthenManager->maxPageNum-1))
	{
		num = 4;
	}
	else
	{
		num = strengthenManager->equipmentVector.size() - strengthenManager->pageNum * 4;
	}

	for (int i = 0; i < 4; i++)
	{
		if (i < num)
		{
			int j = strengthenManager->pageNum * 4 + i;
			const char* s = CCString::createWithFormat("png/equipment/%s.png", strengthenManager->equipmentVector[j].equipment->attribute.tuPian)->getCString();

			equipmentImageView[i]->loadTexture(s);
			equipmentImageView[i]->setVisible(true);
		}
		else
		{
			equipmentImageView[i]->setVisible(false);
		}
	}

	featureImageView->setVisible(false);

	if (strengthenManager->selectEquipmentId < strengthenManager->equipmentVector.size())
	{
		const char* s = CCString::createWithFormat("png/equipment/%s.png", strengthenManager->equipmentVector[strengthenManager->selectEquipmentId].equipment->attribute.tuPian)->getCString();
		featureImageView->loadTexture(s);
		featureImageView->setVisible(true);
	}

	for (int i = 0; i < 2; i++)
	{
		gemFrontImageView[i]->setVisible(false);

		if (strengthenManager->selectGemId == i)
		{
			gemFrontImageView[i]->setVisible(true);
		}
	}

	gemImageView[0]->setVisible(false);

	if (strengthenManager->strengthenGemVector.size() != 0)
	{
		const char* s = CCString::createWithFormat("png/gem/%s.png", strengthenManager->strengthenGemVector[0].gem->attribute.tuPian)->getCString();
		gemImageView[0]->loadTexture(s);
		gemImageView[0]->setVisible(true);
	}

	gemImageView[1]->setVisible(false);

	if (strengthenManager->protectGemVector.size() != 0)
	{
		const char* s = CCString::createWithFormat("png/gem/%s.png", strengthenManager->protectGemVector[0].gem->attribute.tuPian)->getCString();
		gemImageView[1]->loadTexture(s);
		gemImageView[1]->setVisible(true);
	}

	gemImageView[2]->setVisible(false);

	if (strengthenManager->luckyGemVector.size() != 0)
	{
		const char* s = CCString::createWithFormat("png/gem/%s.png", strengthenManager->luckyGemVector[0].gem->attribute.tuPian)->getCString();
		gemImageView[2]->loadTexture(s);
		gemImageView[2]->setVisible(true);
	}
}

void UIStrengthen::scrollViewDidScroll( CCScrollView* view )
{
}

void UIStrengthen::scrollViewDidZoom( CCScrollView* view )
{
}

void UIStrengthen::tableCellTouched( CCTableView* table, CCTableViewCell* cell )
{
	CCLOG("cell touched at index: %i", cell->getIdx());

	strengthenManager->selectGeneralId = cell->getIdx();
	strengthenManager->pageNum = 0;
	strengthenManager->selectEquipmentId = 0;

	UIButton* button = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("EquipmentButton_1"));;
	selectFrameImageView->setPosition(button->getPosition());

	strengthenManager->init();

	refresh();
}

cocos2d::CCSize UIStrengthen::cellSizeForTable( CCTableView* table )
{
	return  CCSizeMake(strengthenTestButton->getContentSize().width, strengthenTestButton->getContentSize().height);
}

CCTableViewCell* UIStrengthen::tableCellAtIndex( CCTableView* table, unsigned int idx )
{
	CCTableViewCell* cell = table->cellAtIndex(idx);

	if (!cell)
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		CCSprite* generalNameBGSprite;

		if (idx == 0)
		{
			generalNameBGSprite = CCSprite::create("png/IdleEquipment.png");
		}
		else
		{
			generalNameBGSprite = CCSprite::create("png/GeneralNameBG.png");
		}

		generalNameBGSprite->setAnchorPoint(CCPointZero);
		generalNameBGSprite->setPosition(CCPointZero);
		cell->addChild(generalNameBGSprite);

		if (idx != 0)
		{
			CCLabelTTF* generalNameLabel = CCLabelTTF::create();
			generalNameLabel->setPosition(ccp(generalNameBGSprite->getContentSize().width/2, generalNameBGSprite->getContentSize().height/2));
			generalNameLabel->setString(formationManager->generalVector[idx-1]->attribute.tuPian);
			cell->addChild(generalNameLabel);
		}

		CCSprite* generalSelectSprite = CCSprite::create("png/GeneralNameSelect.png");
		generalSelectSprite->setPosition(CCPointZero);
		generalSelectSprite->setAnchorPoint(CCPointZero);
		generalSelectSprite->setTag(8);
		generalSelectSprite->setVisible(false);
		cell->addChild(generalSelectSprite);

		generalSelectSpriteVector.push_back(generalSelectSprite);

		if (idx == formationManager->selectId)
		{
			tableCellHighlight(table, cell);
		}
	}

	return cell;
}

unsigned int UIStrengthen::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return formationManager->generalVector.size() + 1;
}

void UIStrengthen::tableCellHighlight( CCTableView* table, extension::CCTableViewCell* cell )
{
	for (int i = 0; i < generalSelectSpriteVector.size(); i++)
	{
		generalSelectSpriteVector[i]->setVisible(false);
	}

	CCSprite* generalSelectSprite =(CCSprite*)cell->getChildByTag(8);
	generalSelectSprite->setVisible(true);
}

void UIStrengthen::tableCellUnhighlight( CCTableView* table, extension::CCTableViewCell* cell )
{
}

void UIStrengthen::closeButtonClicked( CCObject* sender, TouchEventType type )
{
	TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiStrengthen, true);
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiStrengthen->release();
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiStrengthen = NULL;
}

void UIStrengthen::equipmentButtonClicked( CCObject* sender, TouchEventType type )
{
	UIButton* button = (UIButton*)sender;

	for (int i = 0; i < 4; i++)
	{
		const char* s = CCString::createWithFormat("EquipmentButton_%d", i+1)->getCString();

		if (strcmp(button->getName(), s) == 0)
		{
			selectFrameImageView->setPosition(button->getPosition());
			strengthenManager->selectEquipmentId = strengthenManager->pageNum * 4 + i;
			refresh();
			break;
		}
	}
}

void UIStrengthen::gemButtonClicked( CCObject* sender, TouchEventType type )
{
	UIButton* button = (UIButton*)sender;

	for (int i = 0; i < 2; i++)
	{
		const char* s = CCString::createWithFormat("GemButton_%d", i+1)->getCString();

		if (strcmp(button->getName(), s) == 0)
		{
			strengthenManager->selectGemId = i;
			refresh();
			break;
		}
	}
}

void UIStrengthen::strengthenButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		strengthenManager->strengthen();
		refresh();
	}	
}


void UIStrengthen::pageLeftButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		strengthenManager->pageNum--;

		if (strengthenManager->pageNum < 0)
		{
			strengthenManager->pageNum = 0;
			return;
		}

		CCLOG("formationManager->pageNum: %d", strengthenManager->pageNum);

		strengthenManager->selectEquipmentId = strengthenManager->pageNum * 4;
		UIButton* button = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("EquipmentButton_1"));;
		selectFrameImageView->setPosition(button->getPosition());

		refresh();
	}
}

void UIStrengthen::pageRightButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		strengthenManager->pageNum++;

		if (strengthenManager->pageNum > strengthenManager->maxPageNum - 1)
		{
			strengthenManager->pageNum = strengthenManager->maxPageNum - 1;
			return;
		}

		CCLOG("formationManager->pageNum: %d", strengthenManager->pageNum);

		strengthenManager->selectEquipmentId = strengthenManager->pageNum * 4;
		UIButton* button = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("EquipmentButton_1"));;
		selectFrameImageView->setPosition(button->getPosition());

		refresh();
	}
}