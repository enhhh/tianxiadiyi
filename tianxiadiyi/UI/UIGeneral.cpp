#include "UIGeneral.h"
#include "UIWepon.h"
#include "UIAdvanced.h"
#include "UIGeneral.h"

#include "..\TianXiaDiYi.h"

UIGeneral::UIGeneral()
{
	generalManager = GeneralManager::getTheOnlyInstance();
	spriteAarmature = NULL;

	itemFeatureSprite.sprite = NULL;
	selectItemSprite.sprite = NULL;
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

	spritePanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("SpritePanel"));

	UIButton* pageLeftButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("PageLeftButton"));
	pageLeftButton->addTouchEventListener(this, toucheventselector(UIGeneral::pageLeftButtonClicked));

	UIButton* pageRightButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("PageRightButton"));
	pageRightButton->addTouchEventListener(this, toucheventselector(UIGeneral::pageRightButtonClicked));

	for (int i = 0; i < 3; i++)
	{
		const char* s = CCString::createWithFormat("HeadButton_%d", i+1)->getCString();
		UIButton* headButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName(s));
		headButton->addTouchEventListener(this, toucheventselector(UIGeneral::headButtonClicked));
	}

	selectFrameImageView = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("SelectFrameImageView"));

	/*for (int i = 0; i < 4; i++)
	{
		const char* s = CCString::createWithFormat("AddButton_%d", i+1)->getCString();
		UIButton* addButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName(s));
		addButton->addTouchEventListener(this, toucheventselector(UIGeneral::addButtonClicked));
	}*/

	for (int i = 0; i < 3; i++)
	{
		const char* s = CCString::createWithFormat("HeadImageView_%d", i+1)->getCString();
		headImageView[i] = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName(s));
	}

	for (int i = 0; i < 6; i++)
	{
		const char* s = CCString::createWithFormat("EquipmentFrameImageView_%d", i+1)->getCString();
		equipmentImageView[i] = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName(s));
	}

	headFeatureImageView = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("HeadFeatureImageView"));

	for (int i = 0; i < 15; i++)
	{
		const char* s = CCString::createWithFormat("AttributeValueLabel_%d", i+1)->getCString();
		attributeValueLabel[i] = dynamic_cast<UILabel*>(uiLayer->getWidgetByName(s));
	}

	for (int i = 0; i < 10; i++)
	{
		const char* s = CCString::createWithFormat("StarImageView_%d", i+1)->getCString();
		starImageView[i] = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName(s));;
	}

	itemPanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("ItemPanel"));

	itemFeatureImageView = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("ItemFeatureFrameImageView"));

	for (int i = 0; i < 9; i++)
	{
		const char* s = CCString::createWithFormat("ItemFrameImageView_%d", i+1)->getCString();
		itemImageView[i] = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName(s));
	}

	UIButton* pageUpButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("PageUpButton"));
	pageUpButton->addTouchEventListener(this, toucheventselector(UIGeneral::pageUpButtonClicked));

	UIButton* pageDownButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("PageDownButton"));
	pageDownButton->addTouchEventListener(this, toucheventselector(UIGeneral::pageDownButtonClicked));

	addChild(uiLayer);
	setVisible(false);
	refresh();
	return true;
}

void UIGeneral::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1, false);
}

bool UIGeneral::ccTouchBegan( CCTouch* pTouch, CCEvent* event )
{
	CCPoint touchPosition = pTouch->getLocation();
	
	// 选择魂珠
	for (int i = 0; i < 9; i++)
	{
		CCPoint itemPanelPosition = itemPanel->getPosition();
		CCPoint itemImageViewPosition = itemImageView[i]->getPosition();
		CCPoint position = CCPoint(itemPanelPosition.x+itemImageViewPosition.x, itemPanelPosition.y+itemImageViewPosition.y);

		CCSize size = itemImageView[i]->getContentSize();
		CCRect rect = CCRect(position.x-size.width/2, position.y-size.height/2, size.width, size.height);

		if (rect.containsPoint(touchPosition))
		{
			generalManager->selectItemId = generalManager->itemPageNum * 9 + i;
			selectItemSprite = generalManager->itemSpriteArray[i];

			generalManager->itemSpriteArray[i].generalItem.equipment= NULL;
			generalManager->itemSpriteArray[i].sprite = NULL;

			refreshItemFeatureSprite();

			return true;
		}
	}

	CCLOG("ccTouchBegan");
	return true;
}

void UIGeneral::ccTouchMoved( CCTouch* pTouch, CCEvent* event )
{
	CCLOG("ccTouchMoved");
	CCPoint touchPosition = pTouch->getLocation();

	if (selectItemSprite.sprite != NULL)
	{
		selectItemSprite.sprite->setPosition(touchPosition);
	}
}

void UIGeneral::ccTouchEnded( CCTouch* pTouch, CCEvent* event )
{
	CCLOG("ccTouchEnded");
	CCPoint touchPosition = pTouch->getLocation();

	// 取消选择物品
	if (selectItemSprite.sprite != NULL)
	{
		int imageViewId = generalManager->selectItemId - generalManager->itemPageNum*9;
		
		CCPoint itemPanelPosition = itemPanel->getPosition();
		CCPoint itemImageViewPosition = itemImageView[imageViewId]->getPosition();
		CCPoint itemPosition = CCPoint(itemPanelPosition.x+itemImageViewPosition.x, itemPanelPosition.y+itemImageViewPosition.y);
		
		// 选择物品栏
		for (int i = 0; i < 9; i++)
		{
			CCPoint itemPanelPosition = itemPanel->getPosition();
			CCPoint itemImageViewPosition = itemImageView[i]->getPosition();
			CCPoint position = CCPoint(itemPanelPosition.x+itemImageViewPosition.x, itemPanelPosition.y+itemImageViewPosition.y);

			CCSize size = itemImageView[i]->getContentSize();
			CCRect rect = CCRect(position.x-size.width/2, position.y-size.height/2, size.width, size.height);

			if (rect.containsPoint(touchPosition))
			{
				if (generalManager->itemSpriteArray[i].sprite != NULL)
				{
					// 交换物品位置
					generalManager->itemSpriteArray[i].sprite->setPosition(itemPosition);
					selectItemSprite.sprite->setPosition(position);

					generalManager->itemSpriteArray[imageViewId] = generalManager->itemSpriteArray[i];
					generalManager->itemSpriteArray[i] = selectItemSprite;
				}
				else
				{
					selectItemSprite.sprite->setPosition(position);
					generalManager->itemSpriteArray[i] = selectItemSprite;
				}

				selectItemSprite.generalItem.equipment = NULL;
				selectItemSprite.sprite = NULL;

				return;
			}
		}

		// 选择装备栏
		for (int i = 0; i < 6; i++)
		{
			CCPoint equipmentImageViewPosition = equipmentImageView[i]->getPosition();

			CCSize size = equipmentImageView[i]->getContentSize();
			CCRect rect = CCRect(equipmentImageViewPosition.x-size.width/2, equipmentImageViewPosition.y-size.height/2, size.width, size.height);

			if (rect.containsPoint(touchPosition))
			{
			}
		}

		selectItemSprite.sprite->setPosition(itemPosition);
		generalManager->itemSpriteArray[imageViewId] = selectItemSprite;

		selectItemSprite.generalItem.equipment = NULL;
		selectItemSprite.sprite = NULL;
	}
}

void UIGeneral::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	CCLOG("ccTouchCancelled");
	CCPoint touchPosition = pTouch->getLocation();
}

void UIGeneral::clear()
{
	for (int i = 0; i < 3; i++)
	{
		headImageView[i]->setVisible(false);
	}

	if (spriteAarmature != NULL)
	{
		uiLayer->removeChild(spriteAarmature, true);
	}
}

void UIGeneral::refresh()
{
	clear();

	// 将领图片
	for (int i = 0; i < 3; i++)
	{
		int j = generalManager->pageNum * 3 + i;

		if (j < generalManager->generalVector.size())
		{
			const char* s = CCString::createWithFormat("png/general/%s.png", generalManager->generalVector[j]->attribute.tuPian)->getCString();
			headImageView[i]->loadTexture(s);
			headImageView[i]->setVisible(true);
		}
	}

	/*for (int i = 0; i < 6; i++)
	{
		Equipment* equipment = generalManager->generalVector[generalManager->selectGeneralId]->equipmentArray[i];

		if (equipment != NULL)
		{
			const char* s = CCString::createWithFormat("png/equipment/%s.png", equipment->attribute.tuPian)->getCString();
			equipmentImageView[i]->loadTexture(s);
			equipmentImageView[i]->setVisible(true);
		}
	}*/

	General* general = generalManager->generalVector[generalManager->selectGeneralId];

	const char* imagePath = CCString::createWithFormat("ui/%sSprite0.png", general->attribute.tuPian)->getCString();;
	const char* plistPath = CCString::createWithFormat("ui/%sSprite0.plist", general->attribute.tuPian)->getCString();;
	const char* configFilePath = CCString::createWithFormat("ui/%sSprite.ExportJson", general->attribute.tuPian)->getCString();

	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(imagePath, plistPath, configFilePath);
	const char* armatureName = CCString::createWithFormat("%sSprite", general->attribute.tuPian)->getCString();
	spriteAarmature = CCArmature::create(armatureName);
	spriteAarmature->getAnimation()->play("Stand");
	spriteAarmature->setPosition(spritePanel->getPosition());
	uiLayer->addChild(spriteAarmature);

	if (itemPanel->isVisible())
	{
		refreshItem();
	}
}

void UIGeneral::clearItem()
{
	for (int i = 0; i < 9; i++)
	{
		if (generalManager->itemSpriteArray[i].sprite != NULL)
		{
			uiLayer->removeChild(generalManager->itemSpriteArray[i].sprite, true);
			generalManager->itemSpriteArray[i].sprite = NULL;
		}
	}
}

void UIGeneral::refreshItem()
{
	clearItem();

	refreshItemFeatureSprite();

	if (generalManager->itemMaxPageNum <= 0)
	{
		return;
	}

	for (int i = 0; i < 9; i++)
	{
		int j = generalManager->itemPageNum * 9 + i;

		// 背包栏是否有装备
		if (generalManager->generalItemArray[j].equipment != NULL)
		{
			const char* s = CCString::createWithFormat("png/equipment/%s.png", generalManager->generalItemArray[j].equipment->attribute.tuPian)->getCString();
			generalManager->itemSpriteArray[i].sprite = CCSprite::create(s);

			CCPoint itemPanelPosition = itemPanel->getPosition();
			CCPoint itemImageViewPosition = itemImageView[i]->getPosition();
			CCPoint position = CCPoint(itemPanelPosition.x+itemImageViewPosition.x, itemPanelPosition.y+itemImageViewPosition.y);

			generalManager->itemSpriteArray[i].sprite->setPosition(position);
			uiLayer->addChild(generalManager->itemSpriteArray[i].sprite);
			generalManager->itemSpriteArray[i].generalItem = generalManager->generalItemArray[i];
		}
	}
}

void UIGeneral::clearAttribute()
{
	headFeatureImageView->setVisible(false);

	for (int i = 0; i < 15; i++)
	{
		attributeValueLabel[i]->setText(" ");
	}

	for (int i = 0; i < 10; i++)
	{
		starImageView[i]->setVisible(false);
	}
}


void UIGeneral::refreshAttribute()
{
	clearAttribute();

	if (generalManager->selectGeneralId >= generalManager->generalVector.size())
	{
		return;
	}

	const char* s = CCString::createWithFormat("png/general/%s.png", generalManager->generalVector[generalManager->selectGeneralId]->attribute.tuPian)->getCString();
	headFeatureImageView->loadTexture(s);
	headFeatureImageView->setVisible(true);

	General* general = generalManager->generalVector[generalManager->selectGeneralId];

	// 武力
	const char* wuLi = CCString::createWithFormat("%d", general->attribute.wuLi)->getCString();
	// 智力
	const char* zhiLi = CCString::createWithFormat("%d", general->attribute.zhiLi)->getCString();
	// 体力
	const char* tiLi = CCString::createWithFormat("%d", general->attribute.tiLi)->getCString();
	// 敏捷
	const char* minJie = CCString::createWithFormat("%d", general->attribute.minJie)->getCString();
	// 天赋
	const char* tianFu = TianXiaDiYi::getTheOnlyInstance()->ansi2utf8(general->attribute.tianFu);
	// 生命 = 体力*5
	const char* shengMing = CCString::createWithFormat("%d", general->attribute.tiLi*5)->getCString();
	// 暴击
	const char* baoJi = CCString::createWithFormat("%.f%%", general->attribute.BaoJiLv*100)->getCString();
	// 格挡
	const char* geDang = CCString::createWithFormat("%.f%%", general->attribute.geDangLv*100)->getCString();
	// 命中
	const char* mingZhong = CCString::createWithFormat("%.f%%", general->attribute.mingZhongLv*100)->getCString();
	// 闪避
	const char* shanBi = CCString::createWithFormat("%.f%%", general->attribute.shanBiLv*100)->getCString();
	// 暴击伤害
	const char* baoJiShangHai = CCString::createWithFormat("%d", general->attribute.baoJiShangHai)->getCString();
	// 识破
	const char* shiPo = CCString::createWithFormat("%.f%%", general->attribute.shiPoLv*100)->getCString();
	// 名称
	const char* mingCheng = TianXiaDiYi::getTheOnlyInstance()->ansi2utf8(general->attribute.name);
	// 职业
	const char* zhiYe = TianXiaDiYi::getTheOnlyInstance()->ansi2utf8(general->attribute.zhiYeMingCheng);
	// 技能
	const char* jiNeng = TianXiaDiYi::getTheOnlyInstance()->ansi2utf8(general->attribute.JiNeng);

	const char* attribute[15] = {wuLi, zhiLi, tiLi, minJie, tianFu, shengMing, baoJi, geDang, mingZhong, shanBi, baoJiShangHai, shiPo, mingCheng, zhiYe, jiNeng};

	for (int i = 0; i < 15; i++)
	{
		attributeValueLabel[i]->setText(attribute[i]);
	}

	delete[] mingCheng;
	delete[] zhiYe;
	delete[] jiNeng;

	for (int i = 0; i < 10; i++)
	{
		if (i < general->attribute.xingJi*2)
		{
			starImageView[i]->setVisible(true);
		}	
	}
}

void UIGeneral::clearItemFeatureSprite()
{
	if (itemFeatureSprite.sprite != NULL)
	{
		uiLayer->removeChild(itemFeatureSprite.sprite, true);
		itemFeatureSprite.sprite = NULL;
	}
}

void UIGeneral::refreshItemFeatureSprite()
{
	clearItemFeatureSprite();

	GeneralItem generalItem = generalManager->generalItemArray[generalManager->selectItemId];

	if (generalItem.equipment != NULL)
	{
		const char* s = CCString::createWithFormat("png/equipment/%s.png", generalItem.equipment->attribute.tuPian)->getCString();
		itemFeatureSprite.sprite = CCSprite::create(s);

		CCPoint itemPanelPosition = itemPanel->getPosition();
		CCPoint itemFeatureImageViewPosition = itemFeatureImageView->getPosition();
		CCPoint position = CCPoint(itemPanelPosition.x+itemFeatureImageViewPosition.x, itemPanelPosition.y+itemFeatureImageViewPosition.y);

		itemFeatureSprite.sprite->setPosition(position);
		uiLayer->addChild(itemFeatureSprite.sprite);
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

void UIGeneral::addButtonClicked( CCObject* sender, TouchEventType type )
{
	UIButton* button = (UIButton*)sender;

	if (type == CCTOUCHBEGAN)
	{
		for (int i = 0; i < 4; i++)
		{
			const char* s = CCString::createWithFormat("AddButton_%d", i+1)->getCString();

			if (strcmp(button->getName(), s) == 0)
			{
				generalManager->addAttribute(i);
				refresh();
			}
		}
	}
}

void UIGeneral::advancedButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		if (generalManager->selectGeneralId >= generalManager->generalVector.size())
		{
			return;
		}

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

void UIGeneral::pageUpButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		generalManager->itemPageNum--;

		if (generalManager->itemPageNum < 0)
		{
			generalManager->itemPageNum = 0;
			return;
		}

		CCLOG("generalManager->pageNum: %d", generalManager->itemPageNum);
		generalManager->selectItemId = generalManager->itemPageNum * 9;

		refresh();
	}
}

void UIGeneral::pageDownButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		generalManager->itemPageNum++;

		if (generalManager->itemPageNum > generalManager->itemMaxPageNum - 1)
		{
			generalManager->itemPageNum = generalManager->itemMaxPageNum - 1;
			return;
		}

		CCLOG("generalManager->pageNum: %d", generalManager->itemPageNum);

		generalManager->selectItemId = generalManager->itemPageNum * 9;

		refresh();
	}
}