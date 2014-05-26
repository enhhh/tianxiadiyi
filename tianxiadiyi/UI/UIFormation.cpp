#include "UIFormation.h"
#include "..\TianXiaDiYi.h"
#include "Packets\Formation\CGFormationList.h"
#include "Packets\Formation\CGGeneralList.h"

UIFormation::UIFormation()
{
	formationManager = FormationManager::getTheOnlyInstance();

	memset(headImage, 0, sizeof(UIImageView*)*8);

	selectGeneralSprite.general = NULL;
	selectGeneralSprite.sprite = NULL;
}

UIFormation::~UIFormation()
{
}

bool UIFormation::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	uiLayer = UILayer::create();

	UILayout* formationRoot = dynamic_cast<UILayout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/UIFormation.ExportJson"));
	uiLayer->addWidget(formationRoot);

	UIButton* closeButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("CloseButton"));
	closeButton->addTouchEventListener(this, toucheventselector(UIFormation::closeButtonClicked));

	UIButton* pageLeftButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("PreButton"));
	pageLeftButton->addTouchEventListener(this, toucheventselector(UIFormation::pageLeftButtonClicked));

	UIButton* pageRightButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("NextButton"));
	pageRightButton->addTouchEventListener(this, toucheventselector(UIFormation::pageRightButtonClicked));

	// 将领图片
	for (int i = 0; i < 8; i++)
	{
		if (i < formationManager->generalVector.size())
		{
			char headImageViewName[100] = {0};
			sprintf(headImageViewName, "HeadImageView%d", i+1);
			headImage[i] = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName(headImageViewName));
			headImage[i]->setVisible(false);
		}
	}

	// 阵型图片
	int k = 1;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			char headFormationImageViewName[100] = {0};
			sprintf(headFormationImageViewName, "HeadFormationImageView%d", k++);
			headFormationImage[i][j] = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName(headFormationImageViewName));
		}
	}

	formationTestButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("FormationTestButton"));

	// 阵法列表
	UIPanel* tableViewPanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("TableViewPanel"));

	CCTableView* formationTableView = CCTableView::create(this, CCSizeMake(formationTestButton->getContentSize().width, tableViewPanel->getContentSize().height));
	formationTableView->setDirection(kCCScrollViewDirectionVertical);
	formationTableView->setVerticalFillOrder(kCCTableViewFillTopDown);

	CCPoint formationTestPosition = formationTestButton->getPosition();
	formationTableView->setPosition(ccp(formationTestPosition.x, formationTestPosition.y - tableViewPanel->getContentSize().height));
	formationTableView->setDelegate(this);
	formationTableView->reloadData();

	addChild(uiLayer);
	addChild(formationTableView);

	// 阵型图片
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			GeneralSprite gs = formationManager->generalSpriteArray[i][j];

			if (gs.general != NULL)
			{
				if (gs.general->isFormation)
				{
					const char* s = CCString::createWithFormat("png/general/%s.png", gs.general->attribute.tuPian)->getCString();
					CCSprite* sprite = CCSprite::create(s);
					CCPoint position = headFormationImage[i][j]->getPosition();
					sprite->setPosition(position);
					addChild(sprite);
					formationManager->generalSpriteArray[i][j].sprite = sprite;
				}
			}
		}
	}

	setVisible(false);

	CGFormationList formationList;
	formationList.playerGuid = 4528;
	TianXiaDiYi::getTheOnlyInstance()->socketWrap->SendPacket(&formationList);

	CGGeneralList generalList;
	generalList.playerGuid = 4528;
	TianXiaDiYi::getTheOnlyInstance()->socketWrap->SendPacket(&generalList);

	refresh();

	return true;
}

void UIFormation::onEnter()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1, false);
	CCLayer::onEnter();
}

void UIFormation::refresh()
{
	// 将领图片
	int num;

	if (formationManager->pageNum < (formationManager->maxPageNum-1))
	{
		num = 8;
	}
	else
	{
		num = formationManager->generalVector.size() - formationManager->pageNum * 8;
	}

	for (int i = 0; i < 8; i++)
	{

		if (i < num)
		{
			int j = formationManager->pageNum * 8 + i;
			const char* s = CCString::createWithFormat("png/general/%s.png", formationManager->generalVector[j]->attribute.tuPian)->getCString();
			headImage[i]->loadTexture(s);
			headImage[i]->setVisible(true);
		}
		else
		{
			headImage[i]->setVisible(false);
		}
	}

	// 阵型图片
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (formationArrary[formationManager->selectId][i][j])
			{
				headFormationImage[i][j]->setVisible(true);
			}
			else
			{
				headFormationImage[i][j]->setVisible(false);
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// 清除阵型图片
			CCSprite* sprite = formationManager->generalSpriteArray[i][j].sprite;

			if (sprite != NULL)
			{
				if (formationManager->selectPreId != formationManager->selectId)
				{
					formationManager->generalSpriteArray[i][j].general->isFormation = false;
					formationManager->generalSpriteArray[i][j].general = NULL;
					formationManager->generalSpriteArray[i][j].sprite = NULL;
					removeChild(sprite, true);
				}
			}

			// 显示阵型图片
			sprite = formationManager->generalSpriteArray[i][j].sprite;

			if (sprite != NULL)
			{
				sprite->setVisible(true);
			}
		}
	}
}

bool UIFormation::ccTouchBegan( CCTouch* pTouch, CCEvent* event )
{
	CCLOG("ccTouchBegan");
	CCPoint touchPosition = pTouch->getLocation();

	// 选择将领
	for (int i = 0; i < 8; i++)
	{
		if (headImage[i] == NULL)
		{
			continue;
		}

		CCPoint position = headImage[i]->getPosition();
		CCSize size = headImage[i]->getContentSize();
		CCRect rect = CCRect(position.x-size.width/2, position.y-size.height/2, size.width, size.height);

		if (rect.containsPoint(touchPosition))
		{
			i = formationManager->pageNum * 8 + i;

			selectGeneralSprite.general = formationManager->generalVector[i];

			if (selectGeneralSprite.general->isFormation)
			{
				return true;
			}

			const char* s = CCString::createWithFormat("png/general/%s.png", formationManager->generalVector[i]->attribute.tuPian)->getCString();
			selectGeneralSprite.sprite = CCSprite::create(s);
			addChild(selectGeneralSprite.sprite);
			return true;
		}
	}

	// 选择阵型
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (formationArrary[formationManager->selectId][i][j])
			{
				CCPoint position = headFormationImage[i][j]->getPosition();
				CCSize size = headFormationImage[i][j]->getContentSize();
				CCRect rect = CCRect(position.x-size.width/2, position.y-size.height/2, size.width, size.height);

				if (rect.containsPoint(touchPosition))
				{
					selectGeneralSprite = formationManager->generalSpriteArray[i][j];
					
					formationManager->generalSpriteArray[i][j].general = NULL;
					formationManager->generalSpriteArray[i][j].sprite = NULL;
				}
			}
		}
	}

	return true;
}

void UIFormation::ccTouchMoved( CCTouch* pTouch, CCEvent* event )
{
	CCLOG("ccTouchMoved");
	CCPoint touchPosition = pTouch->getLocation();
	
	if (selectGeneralSprite.sprite != NULL)
	{
		selectGeneralSprite.sprite->setPosition(touchPosition);
	}
}

void UIFormation::ccTouchEnded( CCTouch* pTouch, CCEvent* event )
{
	CCLOG("ccTouchEnded");
	CCPoint touchPosition = pTouch->getLocation();

	// 取消选择将领
	if (selectGeneralSprite.sprite != NULL)
	{
		// 选择阵型
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (formationArrary[formationManager->selectId][i][j])
				{
					CCPoint position = headFormationImage[i][j]->getPosition();
					CCSize size = headFormationImage[i][j]->getContentSize();
					CCRect rect = CCRect(position.x-size.width/2, position.y-size.height/2, size.width, size.height);

					if (rect.containsPoint(touchPosition))
					{
						GeneralSprite& gs = formationManager->generalSpriteArray[i][j];

						if (gs.sprite != NULL)
						{
							removeChild(gs.sprite, true);
							gs.general->isFormation = false;
							gs.general = NULL;
							gs.sprite = NULL;
						}

						selectGeneralSprite.general->isFormation = true;
						selectGeneralSprite.sprite->setPosition(position);
						formationManager->generalSpriteArray[i][j] = selectGeneralSprite;
						selectGeneralSprite.general = NULL;
						selectGeneralSprite.sprite = NULL;
						return;
					}
				}
			}
		}

		removeChild(selectGeneralSprite.sprite, true);
		selectGeneralSprite.general->isFormation = false;
		selectGeneralSprite.general = NULL;
		selectGeneralSprite.sprite = NULL;
	}
}

void UIFormation::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	CCLOG("ccTouchCancelled");
}

void UIFormation::scrollViewDidScroll( CCScrollView* view )
{
}

void UIFormation::scrollViewDidZoom( CCScrollView* view )
{
}

void UIFormation::tableCellTouched( CCTableView* table, CCTableViewCell* cell )
{
	CCLOG("cell touched at index: %i", cell->getIdx());

	formationManager->selectPreId = formationManager->selectId;
	formationManager->selectId = cell->getIdx();
	refresh();
}

cocos2d::CCSize UIFormation::cellSizeForTable( CCTableView* table )
{
	return  CCSizeMake(formationTestButton->getContentSize().width, formationTestButton->getContentSize().height);
}

CCTableViewCell* UIFormation::tableCellAtIndex( CCTableView* table, unsigned int idx )
{
	CCTableViewCell* cell = table->cellAtIndex(idx);
	
	if (!cell)
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		const char* s = CCString::createWithFormat("png/formation/%s.png", formationManager->formationVector[idx]->attribute.tuPian)->getCString();
		CCSprite* formationSprite = CCSprite::create(s);
		formationSprite->setAnchorPoint(CCPointZero);
		formationSprite->setPosition(CCPointZero);
		cell->addChild(formationSprite);

		CCSprite* formationEnabledSprite = CCSprite::create("png/FormationEnabled.png");
		formationEnabledSprite->setPosition(ccp(-4,-2));
		formationEnabledSprite->setAnchorPoint(CCPointZero);
		formationEnabledSprite->setTag(8);
		formationEnabledSprite->setVisible(false);
		cell->addChild(formationEnabledSprite);

		selectFormationSpriteVector.push_back(formationEnabledSprite);

		if (idx == formationManager->selectId)
		{
			tableCellHighlight(table, cell);
		}
	}

	return cell;
}

unsigned int UIFormation::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return formationManager->formationVector.size();
}

void UIFormation::tableCellHighlight( CCTableView* table, extension::CCTableViewCell* cell )
{
	CCLOG("cell tableCellHighlight at index: %i", cell->getIdx());

	for (int i = 0; i < selectFormationSpriteVector.size(); i++)
	{
		selectFormationSpriteVector[i]->setVisible(false);
	}

	CCSprite* formationEnabledSprite =(CCSprite*)cell->getChildByTag(8);
	formationEnabledSprite->setVisible(true);
}

void UIFormation::tableCellUnhighlight( CCTableView* table, extension::CCTableViewCell* cell )
{
}

void UIFormation::closeButtonClicked(CCObject* sender, TouchEventType type)
{
	TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiFormation, true);
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiFormation->release();
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiFormation = NULL;

	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// 清除阵型图片
			CCSprite* sprite = formationManager->generalSpriteArray[i][j].sprite;

			if (sprite != NULL)
			{
				formationManager->generalSpriteArray[i][j].sprite = NULL;
				removeChild(sprite, true);
			}
		}
	}
}

void UIFormation::pageLeftButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		formationManager->pageNum--;

		if (formationManager->pageNum < 0)
		{
			formationManager->pageNum = 0;
		}

		CCLOG("formationManager->pageNum: %d", formationManager->pageNum);
		refresh();
	}
}

void UIFormation::pageRightButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		formationManager->pageNum++;

		if (formationManager->pageNum > formationManager->maxPageNum - 1)
		{
			formationManager->pageNum = formationManager->maxPageNum - 1;
		}

		CCLOG("formationManager->pageNum: %d", formationManager->pageNum);
		refresh();
	}
}

