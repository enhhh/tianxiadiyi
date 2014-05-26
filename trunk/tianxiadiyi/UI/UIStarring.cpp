#include "UIStarring.h"

#include "..\TianXiaDiYi.h"

UIStarring::UIStarring()
{
	starringManager = StarringManager::getTheOnlyInstance();

	soulBeadFeatureSprite.armature = NULL;
	soulBeadFeatureSprite.soulBead = NULL;

	selectSoulBeadSprite.armature = NULL;
	selectSoulBeadSprite.soulBead = NULL;
}

UIStarring::~UIStarring()
{
}

bool UIStarring::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	uiLayer = UILayer::create();

	UILayout* starringRoot = dynamic_cast<UILayout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/UIStarring.ExportJson"));
	uiLayer->addWidget(starringRoot);

	operatePanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("OperatePanel"));

	starringAttributePanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("StarringAttributePanel"));	
	attributePanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("AttributePanel"));;
	UIPanel* spritePanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("SpritePanel"));
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("ui/HeroineSprite0.png", "ui/HeroineSprite0.plist", "ui/HeroineSprite.ExportJson");
	spriteAarmature = CCArmature::create("HeroineSprite");
	spriteAarmature->getAnimation()->play("Stand");
	spriteAarmature->setPosition(ccp(starringAttributePanel->getPositionX()+spritePanel->getPositionX(), starringAttributePanel->getPositionY()+spritePanel->getPositionY()));
	uiLayer->addChild(spriteAarmature);

	cultureModePanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("CultureModePanel"));
	cultureImageView = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("CultureImageView"));

	for (int i = 0; i < 3; i++)
	{
		const char* s = CCString::createWithFormat("CultureRadioButton_%d", i+1)->getCString();
		cultureButtonArray[i] = dynamic_cast<UIButton*>(uiLayer->getWidgetByName(s));
		cultureButtonArray[i]->addTouchEventListener(this, toucheventselector(UIStarring::cultureButtonEXTClicked));
	}

	telentModePanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("TelentModePanel"));

	char* telentPanelName[5] = {"BaiHuPanel", "XuanWuPanel", "QingLongPanel", "ZhuQuePanel", "QiLinPanel"};

	for (int i = 0; i < 5; i++)
	{
		telentPanelArrary[i] = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName(telentPanelName[i]));
	}
	
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			const char* s = CCString::createWithFormat("Telent%dButton_%d", i+1, j+1)->getCString();
			telentButtonArray[i][j] = dynamic_cast<UIButton*>(uiLayer->getWidgetByName(s));
			telentButtonArray[i][j]->addTouchEventListener(this, toucheventselector(UIStarring::telentButtonEXTClicked));

			const char* t = CCString::createWithFormat("Telent%dImageView_%d", i+1, j+1)->getCString();
			telentImageViewArray[i][j] = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName(t));
		}
	}

	soulAttributePanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("SoulAttributePanel"));
	soulPanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("SoulPanel"));

	for (int i = 0; i < 12; i++)
	{
		const char* s = CCString::createWithFormat("SoulBeadButton_%d", i+1)->getCString();
		soulBeadButton[i] = dynamic_cast<UIButton*>(uiLayer->getWidgetByName(s));
	}

	for (int i = 0; i < 10; i++)
	{
		const char* s = CCString::createWithFormat("SoulCircleImageView_%d", i+1)->getCString();
		soulBeadCircleImageView[i] = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName(s));
	}

	soulBeadFeatureImageView = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("SoulFeatureImageView"));
	selectSoulFrameImageView = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("SoulSelectFrameImageView"));

	UIButton* operateCloseButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("OperateCloseButton"));
	operateCloseButton->addTouchEventListener(this, toucheventselector(UIStarring::operateCloseButtonClicked));

	UIButton* cultureCloseButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("CultureCloseButton"));
	cultureCloseButton->addTouchEventListener(this, toucheventselector(UIStarring::cultureCloseButtonClicked));

	UIButton* telentCloseButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("TelentCloseButton"));
	telentCloseButton->addTouchEventListener(this, toucheventselector(UIStarring::telentCloseButtonClicked));

	UIButton* soulCloseButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("SoulCloseButton"));
	soulCloseButton->addTouchEventListener(this, toucheventselector(UIStarring::soulCloseButtonClicked));

	UIButton* cultureButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("CultureButton"));
	cultureButton->addTouchEventListener(this, toucheventselector(UIStarring::cultureButtonClicked));

	UIButton* talentButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("TalentButton"));
	talentButton->addTouchEventListener(this, toucheventselector(UIStarring::telentButtonClicked));

	UIButton* soulButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("SoulButton"));
	soulButton->addTouchEventListener(this, toucheventselector(UIStarring::soulButtonClicked));

	UIButton* pageLeftButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("PageLeftButton"));
	pageLeftButton->addTouchEventListener(this, toucheventselector(UIStarring::pageLeftButtonClicked));

	UIButton* pageRightButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("PageRightButton"));
	pageRightButton->addTouchEventListener(this, toucheventselector(UIStarring::pageRightButtonClicked));

	UIButton* pageLeftSoulButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("PageLeftSoulButton"));
	pageLeftSoulButton->addTouchEventListener(this, toucheventselector(UIStarring::pageLeftSoulButtonClicked));

	UIButton* pageRightSoulButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("PageRightSoulButton"));
	pageRightSoulButton->addTouchEventListener(this, toucheventselector(UIStarring::pageRightSoulButtonClicked));

	addChild(uiLayer);
	setVisible(false);
	return true;
}

void UIStarring::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -2, false);
}

void UIStarring::refresh()
{
	if (telentModePanel->isVisible())
	{
		refreshTelent();
	}

	if (soulPanel->isVisible())
	{
		refreshSoul();
	}
}

void UIStarring::refreshCulture()
{
}

void UIStarring::refreshTelent()
{
	for (int i = 0; i < 5; i++)
	{
		if (i == starringManager->telentPageNum)
		{
			telentPanelArrary[i]->setVisible(true);
		}
		else
		{
			telentPanelArrary[i]->setVisible(false);
		}
	}
}

void UIStarring::refreshSoul()
{
	if (starringManager->soulMaxPageNum <= 0)
	{
		return;
	}

	for (int i = 0; i < 12; i++)
	{
		if (starringManager->soulBeadSpriteArray[i].armature != NULL)
		{
			uiLayer->removeChild(starringManager->soulBeadSpriteArray[i].armature, true);
			starringManager->soulBeadSpriteArray[i].armature = NULL;
		}

		int j = starringManager->soulPageNum * 12 + i;

		if (starringManager->soulBeadArray[j] != NULL)
		{
			const char* imagePath = CCString::createWithFormat("ui/%s0.png", starringManager->soulBeadArray[j]->attribute.dongHua)->getCString();;
			const char* plistPath = CCString::createWithFormat("ui/%s0.plist", starringManager->soulBeadArray[j]->attribute.dongHua)->getCString();;
			const char* configFilePath = CCString::createWithFormat("ui/%s.ExportJson", starringManager->soulBeadArray[j]->attribute.dongHua)->getCString();

			CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(imagePath, plistPath, configFilePath);
			starringManager->soulBeadSpriteArray[i].armature = CCArmature::create(starringManager->soulBeadArray[j]->attribute.dongHua);
			starringManager->soulBeadSpriteArray[i].armature->getAnimation()->play(starringManager->soulBeadArray[j]->attribute.dongHua);

			CCPoint soulPanelPosition = soulPanel->getPosition();
			CCPoint soulBeadButtonPosition = soulBeadButton[i]->getPosition();
			CCPoint position = CCPoint(soulPanelPosition.x+soulBeadButtonPosition.x, soulPanelPosition.y+soulBeadButtonPosition.y);
			
			starringManager->soulBeadSpriteArray[i].armature->setPosition(position);
			uiLayer->addChild(starringManager->soulBeadSpriteArray[i].armature);

			starringManager->soulBeadSpriteArray[i].soulBead = starringManager->soulBeadArray[j];
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (starringManager->soulBeadEquipSpriteArray[i].armature != NULL)
		{
			uiLayer->removeChild(starringManager->soulBeadEquipSpriteArray[i].armature, true);
			starringManager->soulBeadEquipSpriteArray[i].armature = NULL;
		}

		if (starringManager->soulBeadEquipArray[i] != NULL)
		{
			const char* imagePath = CCString::createWithFormat("ui/%s0.png", starringManager->soulBeadEquipArray[i]->attribute.dongHua)->getCString();;
			const char* plistPath = CCString::createWithFormat("ui/%s0.plist", starringManager->soulBeadEquipArray[i]->attribute.dongHua)->getCString();;
			const char* configFilePath = CCString::createWithFormat("ui/%s.ExportJson", starringManager->soulBeadEquipArray[i]->attribute.dongHua)->getCString();

			CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(imagePath, plistPath, configFilePath);
			starringManager->soulBeadEquipSpriteArray[i].armature = CCArmature::create(starringManager->soulBeadEquipArray[i]->attribute.dongHua);
			starringManager->soulBeadEquipSpriteArray[i].armature->getAnimation()->play(starringManager->soulBeadEquipArray[i]->attribute.dongHua);

			CCPoint soulAttributePanelPosition = soulAttributePanel->getPosition();
			CCPoint soulBeadCircleImageViewPosition = soulBeadCircleImageView[i]->getPosition();
			CCPoint position = CCPoint(soulAttributePanelPosition.x+soulBeadCircleImageViewPosition.x, soulAttributePanelPosition.y+soulBeadCircleImageViewPosition.y);

			starringManager->soulBeadEquipSpriteArray[i].armature->setPosition(position);
			uiLayer->addChild(starringManager->soulBeadEquipSpriteArray[i].armature);
			starringManager->soulBeadEquipSpriteArray[i].soulBead = starringManager->soulBeadEquipArray[i];
		}
	}
}

void UIStarring::refreshSoulFeatureSprite()
{
	if (soulBeadFeatureSprite.armature != NULL)
	{
		uiLayer->removeChild(soulBeadFeatureSprite.armature, true);
		soulBeadFeatureSprite.armature = NULL;
	}

	if (starringManager->soulBeadArray[starringManager->selectSoulBeadId] != NULL)
	{
		const char* imagePath = CCString::createWithFormat("ui/%s0.png", starringManager->soulBeadArray[starringManager->selectSoulBeadId]->attribute.dongHua)->getCString();;
		const char* plistPath = CCString::createWithFormat("ui/%s0.plist", starringManager->soulBeadArray[starringManager->selectSoulBeadId]->attribute.dongHua)->getCString();;
		const char* configFilePath = CCString::createWithFormat("ui/%s.ExportJson", starringManager->soulBeadArray[starringManager->selectSoulBeadId]->attribute.dongHua)->getCString();

		CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(imagePath, plistPath, configFilePath);
		soulBeadFeatureSprite.armature = CCArmature::create(starringManager->soulBeadArray[starringManager->selectSoulBeadId]->attribute.dongHua);
		soulBeadFeatureSprite.armature->getAnimation()->play(starringManager->soulBeadArray[starringManager->selectSoulBeadId]->attribute.dongHua);

		soulBeadFeatureSprite.armature->setPosition(ccp(soulPanel->getPositionX()+soulBeadFeatureImageView->getPositionX(), soulPanel->getPositionY()+soulBeadFeatureImageView->getPositionY()));
		uiLayer->addChild(soulBeadFeatureSprite.armature);
		soulBeadFeatureSprite.soulBead = starringManager->soulBeadArray[starringManager->selectSoulBeadId];
	}
}

bool UIStarring::ccTouchBegan( CCTouch* pTouch, CCEvent* event )
{
	CCLOG("ccTouchBegan");
	CCPoint touchPosition = pTouch->getLocation();

	// —°‘ÒªÍ÷È
	for (int i = 0; i < 12; i++)
	{
		CCPoint soulPanelPosition = soulPanel->getPosition();
		CCPoint soulBeadButtonPosition = soulBeadButton[i]->getPosition();

		CCPoint position = CCPoint(soulPanelPosition.x+soulBeadButtonPosition.x, soulPanelPosition.y+soulBeadButtonPosition.y);

		CCSize size = soulBeadButton[i]->getContentSize();
		CCRect rect = CCRect(position.x-size.width/2, position.y-size.height/2, size.width, size.height);

		if (rect.containsPoint(touchPosition))
		{
			starringManager->selectSoulBeadId = starringManager->soulPageNum * 12 + i;
			selectSoulBeadSprite = starringManager->soulBeadSpriteArray[i];

			starringManager->soulBeadSpriteArray[i].armature = NULL;
			starringManager->soulBeadSpriteArray[i].soulBead = NULL;

			starringManager->selectSoulBeadId = starringManager->soulPageNum * 12 + i;
			refreshSoulFeatureSprite();

			return true;
		}
	}

	// —°‘ÒªÍ»¶
	for (int i = 0; i < 10; i++)
	{
		CCPoint soulAttributePanelPosition = soulAttributePanel->getPosition();
		CCPoint soulBeadCircleImageViewPosition = soulBeadCircleImageView[i]->getPosition();

		CCPoint position = CCPoint(soulAttributePanelPosition.x+soulBeadCircleImageViewPosition.x, soulAttributePanelPosition.y+soulBeadCircleImageViewPosition.y);

		CCSize size = soulBeadCircleImageView[i]->getContentSize();
		CCRect rect = CCRect(position.x-size.width/2, position.y-size.height/2, size.width, size.height);

		if (rect.containsPoint(touchPosition))
		{
			return true;
		}
	}

	return true;
}

void UIStarring::ccTouchMoved( CCTouch* pTouch, CCEvent* event )
{
	CCLOG("ccTouchMoved");
	CCPoint touchPosition = pTouch->getLocation();

	if (selectSoulBeadSprite.armature != NULL)
	{
		selectSoulBeadSprite.armature->setPosition(touchPosition);
	}
}

void UIStarring::ccTouchEnded( CCTouch* pTouch, CCEvent* event )
{
	CCLOG("ccTouchEnded");
	CCPoint touchPosition = pTouch->getLocation();

	if (selectSoulBeadSprite.armature != NULL)
	{
		int buttonId = starringManager->selectSoulBeadId - starringManager->soulPageNum*12;
		CCPoint soulPanelPosition = soulPanel->getPosition();
		CCPoint soulBeadButtonPosition = soulBeadButton[buttonId]->getPosition();
		CCPoint soulBeadPosition = CCPoint(soulPanelPosition.x+soulBeadButtonPosition.x, soulPanelPosition.y+soulBeadButtonPosition.y);

		// —°‘ÒªÍ÷È
		for (int i = 0; i < 12; i++)
		{
			CCPoint soulPanelPosition = soulPanel->getPosition();
			CCPoint soulBeadButtonPosition = soulBeadButton[i]->getPosition();

			CCPoint position = CCPoint(soulPanelPosition.x+soulBeadButtonPosition.x, soulPanelPosition.y+soulBeadButtonPosition.y);

			CCSize size = soulBeadButton[i]->getContentSize();
			CCRect rect = CCRect(position.x-size.width/2, position.y-size.height/2, size.width, size.height);

			if (rect.containsPoint(touchPosition))
			{
				// ƒøµƒŒª÷√ «∑Ò”–ªÍ÷È
				if (starringManager->soulBeadSpriteArray[i].armature != NULL)
				{
					// ΩªªªªÍ÷ÈŒª÷√
					starringManager->soulBeadSpriteArray[i].armature->setPosition(soulBeadPosition);
					selectSoulBeadSprite.armature->setPosition(position);

					starringManager->soulBeadSpriteArray[buttonId] = starringManager->soulBeadSpriteArray[i];
					starringManager->soulBeadSpriteArray[i] = selectSoulBeadSprite;
				}
				else
				{
					selectSoulBeadSprite.armature->setPosition(position);
					starringManager->soulBeadSpriteArray[i] = selectSoulBeadSprite;
				}

				selectSoulBeadSprite.armature = NULL;
				selectSoulBeadSprite.soulBead = NULL;

				int id = starringManager->soulPageNum * 12 + i;
				SoulBead* s = starringManager->soulBeadArray[starringManager->selectSoulBeadId];
				starringManager->soulBeadArray[starringManager->selectSoulBeadId] = starringManager->soulBeadArray[id];
				starringManager->soulBeadArray[id] = s;

				return;
			}
		}

		// —°‘ÒªÍ»¶
		for (int i = 0; i < 10; i++)
		{
			CCPoint soulAttributePanelPosition = soulAttributePanel->getPosition();
			CCPoint soulBeadCircleImageViewPosition = soulBeadCircleImageView[i]->getPosition();

			CCPoint position = CCPoint(soulAttributePanelPosition.x+soulBeadCircleImageViewPosition.x, soulAttributePanelPosition.y+soulBeadCircleImageViewPosition.y);

			CCSize size = soulBeadCircleImageView[i]->getContentSize();
			CCRect rect = CCRect(position.x-size.width/2, position.y-size.height/2, size.width, size.height);

			if (rect.containsPoint(touchPosition))
			{
				// ƒøµƒŒª÷√ «∑Ò”–ªÍ÷È
				if (starringManager->soulBeadEquipSpriteArray[i].armature != NULL)
				{
					// ΩªªªªÍ÷ÈŒª÷√
					starringManager->soulBeadEquipSpriteArray[i].armature->setPosition(soulBeadPosition);
					selectSoulBeadSprite.armature->setPosition(position);

					starringManager->soulBeadSpriteArray[buttonId] = starringManager->soulBeadEquipSpriteArray[i];
					starringManager->soulBeadEquipSpriteArray[i] = selectSoulBeadSprite;
				}
				else
				{
					selectSoulBeadSprite.armature->setPosition(position);
					starringManager->soulBeadEquipSpriteArray[i] = selectSoulBeadSprite;
				}

				SoulBead* s = starringManager->soulBeadArray[starringManager->selectSoulBeadId];
				starringManager->soulBeadArray[starringManager->selectSoulBeadId] = starringManager->soulBeadEquipArray[i];
				starringManager->soulBeadEquipArray[i] = s;

				selectSoulBeadSprite.armature = NULL;
				selectSoulBeadSprite.soulBead = NULL;

				return;
			}
		}

		selectSoulBeadSprite.armature->setPosition(soulBeadPosition);
		starringManager->soulBeadSpriteArray[buttonId] = selectSoulBeadSprite;
		selectSoulBeadSprite.armature = NULL;
		selectSoulBeadSprite.soulBead = NULL;
	}
}

void UIStarring::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	CCLOG("ccTouchCancelled");
}

void UIStarring::operateCloseButtonClicked( CCObject* sender, TouchEventType type )
{
	TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiStarring, true);
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiStarring = NULL;
}

void UIStarring::cultureCloseButtonClicked( CCObject* sender, TouchEventType type )
{
	operatePanel->setEnabled(true);
	cultureModePanel->setVisible(false);
}

void UIStarring::telentCloseButtonClicked( CCObject* sender, TouchEventType type )
{
	operatePanel->setEnabled(true);
	telentModePanel->setVisible(false);
}

void UIStarring::soulCloseButtonClicked( CCObject* sender, TouchEventType type )
{
	operatePanel->setEnabled(true);
	soulPanel->setVisible(false);
	soulAttributePanel->setVisible(false);
	
	for (int i = 0; i < 12; i++)
	{
		soulBeadButton[i]->setTouchEnabled(false);
	}

	attributePanel->setVisible(true);

	if (soulBeadFeatureSprite.armature != NULL)
	{
		uiLayer->removeChild(soulBeadFeatureSprite.armature, true);
		soulBeadFeatureSprite.armature = NULL;
	}

	for (int i = 0; i < 12; i++)
	{
		if (starringManager->soulBeadSpriteArray[i].armature != NULL)
		{
			uiLayer->removeChild(starringManager->soulBeadSpriteArray[i].armature, true);
			starringManager->soulBeadSpriteArray[i].armature = NULL;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (starringManager->soulBeadEquipSpriteArray[i].armature != NULL)
		{
			uiLayer->removeChild(starringManager->soulBeadEquipSpriteArray[i].armature, true);
			starringManager->soulBeadEquipSpriteArray[i].armature = NULL;
		}
	}
}

void UIStarring::cultureButtonClicked( CCObject* sender, TouchEventType type )
{
	operatePanel->setEnabled(false);

	cultureModePanel->setVisible(true);
	cultureModePanel->setEnabled(true);

	telentModePanel->setVisible(false);
	telentModePanel->setEnabled(false);
	
	soulPanel->setVisible(false);
	soulPanel->setEnabled(false);

	cultureModePanel->setZOrder(4);
	telentModePanel->setZOrder(3);
	soulPanel->setZOrder(2);
}

void UIStarring::telentButtonClicked( CCObject* sender, TouchEventType type )
{
	operatePanel->setEnabled(false);

	cultureModePanel->setVisible(false);
	cultureModePanel->setEnabled(false);

	telentModePanel->setVisible(true);
	telentModePanel->setEnabled(true);

	soulPanel->setVisible(false);
	soulPanel->setEnabled(false);

	cultureModePanel->setZOrder(2);
	telentModePanel->setZOrder(4);
	soulPanel->setZOrder(3);
}

void UIStarring::soulButtonClicked( CCObject* sender, TouchEventType type )
{
	operatePanel->setEnabled(false);

	cultureModePanel->setVisible(false);
	cultureModePanel->setEnabled(false);

	telentModePanel->setVisible(false);
	telentModePanel->setEnabled(false);

	soulPanel->setVisible(true);
	soulPanel->setEnabled(true);

	cultureModePanel->setZOrder(2);
	telentModePanel->setZOrder(3);
	soulPanel->setZOrder(4);

	attributePanel->setVisible(false);
	soulAttributePanel->setVisible(true);
	
	for (int i = 0; i < 12; i++)
	{
		soulBeadButton[i]->setTouchEnabled(true);
	}

	refresh();
}

void UIStarring::pageLeftButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		starringManager->telentPageNum--;

		if (starringManager->telentPageNum < 0)
		{
			starringManager->telentPageNum = 0;
		}

		refresh();
	}
}

void UIStarring::pageRightButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		starringManager->telentPageNum++;

		if (starringManager->telentPageNum > 4)
		{
			starringManager->telentPageNum = 4;
		}

		refresh();
	}
}

void UIStarring::pageLeftSoulButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		starringManager->soulPageNum--;

		if (starringManager->soulPageNum < 0)
		{
			starringManager->soulPageNum = 0;
			return;
		}

		CCLOG("starringManager->soulPageNum: %d", starringManager->soulPageNum);

		refresh();
	}
}

void UIStarring::pageRightSoulButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		starringManager->soulPageNum++;

		if (starringManager->soulPageNum > starringManager->soulMaxPageNum - 1)
		{
			starringManager->soulPageNum = starringManager->soulMaxPageNum - 1;
			return;
		}

		CCLOG("starringManager->soulPageNum: %d", starringManager->soulPageNum);

		refresh();
	}
}

void UIStarring::soulButtonEXTClicked( CCObject* sender, TouchEventType type )
{
	TianXiaDiYi::getTheOnlyInstance()->mainCityScene->player->wuLi += 0;
	TianXiaDiYi::getTheOnlyInstance()->mainCityScene->player->zhiLi += 0;
	TianXiaDiYi::getTheOnlyInstance()->mainCityScene->player->tiLi+= 0;
	TianXiaDiYi::getTheOnlyInstance()->mainCityScene->player->minJie += 0;
}

void UIStarring::cultureButtonEXTClicked( CCObject* sender, TouchEventType type )
{
	UIButton* button = (UIButton*)sender;

	for (int i = 0; i < 3; i++)
	{
		const char* s = CCString::createWithFormat("CultureRadioButton_%d", i+1)->getCString();
		
		if (strcmp(button->getName(), s) == 0)
		{
			cultureImageView->setVisible(true);
			cultureImageView->setPosition(button->getPosition());

			break;
		}
	}
}

void UIStarring::telentButtonEXTClicked( CCObject* sender, TouchEventType type )
{
	UIButton* button = (UIButton*)sender;

	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			const char* s = CCString::createWithFormat("Telent%dButton_%d", i+1, j+1)->getCString();

			if (strcmp(button->getName(), s) == 0)
			{
				telentImageViewArray[i][j]->setVisible(true);
				button->setEnabled(false);
				button->setVisible(false);
				return;
			}
		}
	}
}