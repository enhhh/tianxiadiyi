#include "UIWepon.h"

#include "..\TianXiaDiYi.h"

UIWepon::UIWepon()
{
	weponManager = WeponManager::getTheOnlyInstance();
	weponManager->init();

	selectGemSprite.sprite = NULL;
	selectGemSprite.weponGem.gem = NULL;

	isPage = false;
}

UIWepon::~UIWepon()
{
}

bool UIWepon::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	uiLayer = UILayer::create();

	UILayout* weponRoot = dynamic_cast<UILayout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/UIWepon.ExportJson"));
	uiLayer->addWidget(weponRoot);

	UIButton* closeButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("CloseButton"));
	closeButton->addTouchEventListener(this, toucheventselector(UIWepon::closeButtonClicked));

	equipmentFeatureImageView = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("EquipmentFeatureImageView"));
	roundImageView = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("RoundImageView"));

	for (int i = 0; i < 4; i++)
	{
		const char* s = CCString::createWithFormat("GemImageView_%d", i+1)->getCString();
		gemImageView[i] = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName(s));
	}

	UIButton* pageLeftButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("PageLeftButton"));
	pageLeftButton->addTouchEventListener(this, toucheventselector(UIWepon::pageLeftButtonClicked));

	UIButton* pageRightButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("PageRightButton"));
	pageRightButton->addTouchEventListener(this, toucheventselector(UIWepon::pageRightButtonClicked));

	addChild(uiLayer);
	refresh();
	return true;
}

void UIWepon::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -3, false);
}

void UIWepon::refresh()
{
	if (weponManager->equipment != NULL)
	{
		const char* s = CCString::createWithFormat("png/equipment/%s.png", weponManager->equipment->attribute.tuPian)->getCString();
		equipmentFeatureImageView->loadTexture(s);
		equipmentFeatureImageView->setVisible(true);

		if (weponManager->equipment->gem != NULL)
		{
			if (weponManager->gemFillSprite.sprite != NULL)
			{
				uiLayer->removeChild(weponManager->gemFillSprite.sprite, true);
				weponManager->gemFillSprite.sprite = NULL;
			}

			const char* s = CCString::createWithFormat("png/gem/%s.png", weponManager->equipment->gem->attribute.tuPian)->getCString();
			weponManager->gemFillSprite.sprite = CCSprite::create(s);
			weponManager->gemFillSprite.sprite->setPosition(roundImageView->getPosition());
			uiLayer->addChild(weponManager->gemFillSprite.sprite);

			weponManager->gemFillSprite.weponGem.gem = weponManager->equipment->gem;
		}
	}


	if (weponManager->maxPageNum <= 0)
	{
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		if (weponManager->gemSpriteArray[i].sprite != NULL)
		{
			uiLayer->removeChild(weponManager->gemSpriteArray[i].sprite, true);
			weponManager->gemSpriteArray[i].sprite = NULL;
		}

		int j = weponManager->pageNum * 4 + i;

		if (weponManager->weponGemArray[j].gem != NULL)
		{
			const char* s = CCString::createWithFormat("png/gem/%s.png", weponManager->weponGemArray[j].gem->attribute.tuPian)->getCString();
			weponManager->gemSpriteArray[i].sprite = CCSprite::create(s);
			weponManager->gemSpriteArray[i].sprite->setPosition(gemImageView[i]->getPosition());
			uiLayer->addChild(weponManager->gemSpriteArray[i].sprite);
			weponManager->gemSpriteArray[i].weponGem = weponManager->weponGemArray[i];
		}
	}
}

bool UIWepon::ccTouchBegan( CCTouch* pTouch, CCEvent* event )
{
	CCPoint touchPosition = pTouch->getLocation();
	
	// 选择宝石
	for (int i = 0; i < 4; i++)
	{
		CCPoint position = gemImageView[i]->getPosition();
		CCSize size = gemImageView[i]->getContentSize();
		CCRect rect = CCRect(position.x-size.width/2, position.y-size.height/2, size.width, size.height);

		if (rect.containsPoint(touchPosition))
		{
			weponManager->selectGemId = weponManager->pageNum * 4 + i;
			selectGemSprite = weponManager->gemSpriteArray[i];

			weponManager->gemSpriteArray[i].sprite = NULL;
			weponManager->gemSpriteArray[i].weponGem.gem = NULL;

			return true;
		}
	}

	CCLOG("ccTouchBegan");
	return true;
}

void UIWepon::ccTouchMoved( CCTouch* pTouch, CCEvent* event )
{
	CCLOG("ccTouchMoved");
	CCPoint touchPosition = pTouch->getLocation();

	if (selectGemSprite.sprite != NULL)
	{
		selectGemSprite.sprite->setPosition(touchPosition);
	}
}

void UIWepon::ccTouchEnded( CCTouch* pTouch, CCEvent* event )
{
	CCLOG("ccTouchEnded");
	CCPoint touchPosition = pTouch->getLocation();

	if (isPage)
	{
		isPage = false;
		return;
	}

	if (selectGemSprite.sprite != NULL)
	{
		int imageViewId = weponManager->selectGemId - weponManager->pageNum*4;
		CCPoint gemPosition = gemImageView[imageViewId]->getPosition();
	
		CCPoint position = roundImageView->getPosition();
		CCSize size = roundImageView->getContentSize();
		CCRect rect = CCRect(position.x-size.width/2, position.y-size.height/2, size.width, size.height);

		if (rect.containsPoint(touchPosition))
		{
			// 目的位置是否有宝石
			if (weponManager->gemFillSprite.weponGem.gem != NULL)
			{
				// 交换宝石位置
				weponManager->gemFillSprite.sprite->setPosition(gemPosition);
				selectGemSprite.sprite->setPosition(position);

				weponManager->gemSpriteArray[imageViewId] = weponManager->gemFillSprite;
				weponManager->gemFillSprite = selectGemSprite;
			}
			else
			{
				selectGemSprite.sprite->setPosition(position);
				weponManager->gemFillSprite = selectGemSprite;
			}

			// 交换宝石数据
			weponManager->fill();

			selectGemSprite.sprite = NULL;
			selectGemSprite.weponGem.gem = NULL;

			TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiWepon, true);
			TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiWepon->release();
			TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiWepon = NULL;

			TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiWeponTakeup->refresh();
			return;
		}

		selectGemSprite.sprite->setPosition(gemPosition);
		weponManager->gemSpriteArray[imageViewId] = selectGemSprite;
		selectGemSprite.sprite = NULL;
		selectGemSprite.weponGem.gem = NULL;
	}
}

void UIWepon::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	CCLOG("ccTouchCancelled");
}

void UIWepon::closeButtonClicked( CCObject* sender, TouchEventType type )
{
	TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiWepon, true);
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiWepon->release();
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiWepon = NULL;
}

void UIWepon::pageLeftButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		isPage = true;

		weponManager->pageNum--;

		if (weponManager->pageNum < 0)
		{
			weponManager->pageNum = 0;
			return;
		}

		CCLOG("weponManager->pageNum: %d", weponManager->pageNum);

		refresh();
	}
}

void UIWepon::pageRightButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		isPage = true;

		weponManager->pageNum++;

		if (weponManager->pageNum > weponManager->maxPageNum - 1)
		{
			weponManager->pageNum = weponManager->maxPageNum - 1;
			return;
		}

		CCLOG("weponManager->pageNum: %d", weponManager->pageNum);

		refresh();
	}
}
