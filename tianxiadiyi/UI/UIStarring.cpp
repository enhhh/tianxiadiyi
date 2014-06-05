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
	
	UIButton* operateCloseButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("OperateCloseButton"));
	operateCloseButton->addTouchEventListener(this, toucheventselector(UIStarring::operateCloseButtonClicked));

	UIButton* cultureButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("CultureButton"));
	cultureButton->addTouchEventListener(this, toucheventselector(UIStarring::cultureButtonClicked));

	UIButton* talentButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("TalentButton"));
	talentButton->addTouchEventListener(this, toucheventselector(UIStarring::telentButtonClicked));

	UIButton* soulButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("SoulButton"));
	soulButton->addTouchEventListener(this, toucheventselector(UIStarring::soulButtonClicked));

	// 主角
	starringAttributePanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("StarringAttributePanel"));	
	attributePanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("AttributePanel"));;
	UIPanel* spritePanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("SpritePanel"));
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("ui/HeroineSprite0.png", "ui/HeroineSprite0.plist", "ui/HeroineSprite.ExportJson");
	spriteAarmature = CCArmature::create("HeroineSprite");
	spriteAarmature->getAnimation()->play("Stand");
	spriteAarmature->setPosition(ccp(starringAttributePanel->getPositionX()+spritePanel->getPositionX(), starringAttributePanel->getPositionY()+spritePanel->getPositionY()));
	uiLayer->addChild(spriteAarmature);

	for (int i = 0; i < 4; i++)
	{
		const char* s = CCString::createWithFormat("AttributeValueLabel_%d", i+1)->getCString();
		attributeLabel[i] = dynamic_cast<UILabel*>(uiLayer->getWidgetByName(s));
	}

	// 培养
	cultureModePanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("CultureModePanel"));
	
	UIButton* cultureCloseButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("CultureCloseButton"));
	cultureCloseButton->addTouchEventListener(this, toucheventselector(UIStarring::cultureCloseButtonClicked));

	UIButton* cultureModeButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("CultureModeButton"));
	cultureModeButton->addTouchEventListener(this, toucheventselector(UIStarring::cultureModeButtonClicked));
	
	for (int i = 0; i < 3; i++)
	{
		const char* s = CCString::createWithFormat("CultureRadioButton_%d", i+1)->getCString();
		cultureRadioButtonArray[i] = dynamic_cast<UIButton*>(uiLayer->getWidgetByName(s));
		cultureRadioButtonArray[i]->addTouchEventListener(this, toucheventselector(UIStarring::cultureRadioButtonClicked));
	}

	cultureImageView = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("CultureImageView"));
	successRateLabel = dynamic_cast<UILabel*>(uiLayer->getWidgetByName("SuccessRateLabel"));;

	// 天赋
	telentModePanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("TelentModePanel"));

	UIButton* telentCloseButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("TelentCloseButton"));
	telentCloseButton->addTouchEventListener(this, toucheventselector(UIStarring::telentCloseButtonClicked));

	char* telentPanelName[5] = {"BaiHuPanel", "XuanWuPanel", "QingLongPanel", "ZhuQuePanel", "QiLinPanel"};

	for (int i = 0; i < 5; i++)
	{
		telentPanelArrary[i] = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName(telentPanelName[i]));
	}

	for (int i = 0; i < 5; i++)
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

	UIButton* pageLeftButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("PageLeftButton"));
	pageLeftButton->addTouchEventListener(this, toucheventselector(UIStarring::pageLeftButtonClicked));

	UIButton* pageRightButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("PageRightButton"));
	pageRightButton->addTouchEventListener(this, toucheventselector(UIStarring::pageRightButtonClicked));

	// 魂珠
	soulAttributePanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("SoulAttributePanel"));
	soulPanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("SoulPanel"));

	UIButton* soulCloseButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("SoulCloseButton"));
	soulCloseButton->addTouchEventListener(this, toucheventselector(UIStarring::soulCloseButtonClicked));

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

	UIButton* pageLeftSoulButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("PageLeftSoulButton"));
	pageLeftSoulButton->addTouchEventListener(this, toucheventselector(UIStarring::pageLeftSoulButtonClicked));

	UIButton* pageRightSoulButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("PageRightSoulButton"));
	pageRightSoulButton->addTouchEventListener(this, toucheventselector(UIStarring::pageRightSoulButtonClicked));

	soulBeadFeatureImageView = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("SoulFeatureImageView"));
	selectSoulFrameImageView = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("SoulSelectFrameImageView"));

	addChild(uiLayer);
	setVisible(false);
	refresh();
	return true;
}

void UIStarring::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -2, false);
}

void UIStarring::refresh()
{
	// 武力
	const char* wuLi = CCString::createWithFormat("%d", starringManager->player->attribute.wuLi)->getCString();
	// 智力
	const char* zhiLi = CCString::createWithFormat("%d", starringManager->player->attribute.zhiLi)->getCString();
	// 体力
	const char* tiLi = CCString::createWithFormat("%d", starringManager->player->attribute.tiLi)->getCString();
	// 敏捷
	const char* minJie = CCString::createWithFormat("%d", starringManager->player->attribute.minJie)->getCString();

	const char* attribute[4] = {wuLi, zhiLi, tiLi, minJie};

	for (int i = 0; i < 4; i++)
	{
		attributeLabel[i]->setText(attribute[i]);
	}

	if (cultureModePanel->isVisible())
	{
		refreshCulture();
	}

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
	int rate = starringManager->cultureSuccessRate[starringManager->selectCultureId];
	const char* s = CCString::createWithFormat("%d%", rate)->getCString();
	successRateLabel->setText(s);
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

	for (int i = 0; i < 20; i++)
	{
		if (i < starringManager->telentLightPoint[starringManager->telentPageNum])
		{
			telentImageViewArray[starringManager->telentPageNum][i]->setVisible(true);
			telentButtonArray[starringManager->telentPageNum][i]->setVisible(false);
			telentButtonArray[starringManager->telentPageNum][i]->setEnabled(false);
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

	if (soulPanel->isVisible() == false)
	{
		return true;
	}

	CCPoint touchPosition = pTouch->getLocation();

	// 选择魂珠
	for (int i = 0; i < 12; i++)
	{
		CCPoint soulPanelPosition = soulPanel->getPosition();
		CCPoint soulBeadButtonPosition = soulBeadButton[i]->getPosition();

		CCPoint position = CCPoint(soulPanelPosition.x+soulBeadButtonPosition.x, soulPanelPosition.y+soulBeadButtonPosition.y);

		CCSize size = soulBeadButton[i]->getContentSize();
		CCRect rect = CCRect(position.x-size.width/2, position.y-size.height/2, size.width, size.height);

		if (rect.containsPoint(touchPosition))
		{
			starringManager->isSelectSoulBead = true;

			starringManager->selectSoulBeadId = starringManager->soulPageNum * 12 + i;
			selectSoulBeadSprite = starringManager->soulBeadSpriteArray[i];

			starringManager->soulBeadSpriteArray[i].armature = NULL;
			starringManager->soulBeadSpriteArray[i].soulBead = NULL;

			refreshSoulFeatureSprite();

			return true;
		}
	}

	// 选择魂圈
	for (int i = 0; i < 10; i++)
	{
		CCPoint soulAttributePanelPosition = soulAttributePanel->getPosition();
		CCPoint soulBeadCircleImageViewPosition = soulBeadCircleImageView[i]->getPosition();
		CCPoint position = CCPoint(soulAttributePanelPosition.x+soulBeadCircleImageViewPosition.x, soulAttributePanelPosition.y+soulBeadCircleImageViewPosition.y);

		CCSize size = soulBeadCircleImageView[i]->getContentSize();
		CCRect rect = CCRect(position.x-size.width/2, position.y-size.height/2, size.width, size.height);

		if (rect.containsPoint(touchPosition))
		{
			starringManager->isSelectSoulBead = false;

			starringManager->selectSoulBeadEquipId = i;
			selectSoulBeadSprite = starringManager->soulBeadEquipSpriteArray[i];

			starringManager->soulBeadEquipSpriteArray[i].armature = NULL;
			starringManager->soulBeadEquipSpriteArray[i].soulBead = NULL;

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
		if (starringManager->isSelectSoulBead)
		{
			int buttonId = starringManager->selectSoulBeadId - starringManager->soulPageNum*12;
			CCPoint soulPanelPosition = soulPanel->getPosition();
			CCPoint soulBeadButtonPosition = soulBeadButton[buttonId]->getPosition();
			CCPoint soulBeadPosition = CCPoint(soulPanelPosition.x+soulBeadButtonPosition.x, soulPanelPosition.y+soulBeadButtonPosition.y);

			// 选择魂珠
			for (int i = 0; i < 12; i++)
			{
				CCPoint soulPanelPosition = soulPanel->getPosition();
				CCPoint soulBeadButtonPosition = soulBeadButton[i]->getPosition();

				CCPoint position = CCPoint(soulPanelPosition.x+soulBeadButtonPosition.x, soulPanelPosition.y+soulBeadButtonPosition.y);

				CCSize size = soulBeadButton[i]->getContentSize();
				CCRect rect = CCRect(position.x-size.width/2, position.y-size.height/2, size.width, size.height);

				if (rect.containsPoint(touchPosition))
				{
					// 目的位置是否有魂珠
					if (starringManager->soulBeadSpriteArray[i].armature != NULL)
					{
						// 交换魂珠位置
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

					starringManager->swapSoulBead(1);
					int id = starringManager->soulPageNum * 12 + i;
					SoulBead* s = starringManager->soulBeadArray[starringManager->selectSoulBeadId];
					starringManager->soulBeadArray[starringManager->selectSoulBeadId] = starringManager->soulBeadArray[id];
					starringManager->soulBeadArray[id] = s;

					return;
				}
			}

			// 选择魂圈
			for (int i = 0; i < 10; i++)
			{
				CCPoint soulAttributePanelPosition = soulAttributePanel->getPosition();
				CCPoint soulBeadCircleImageViewPosition = soulBeadCircleImageView[i]->getPosition();

				CCPoint position = CCPoint(soulAttributePanelPosition.x+soulBeadCircleImageViewPosition.x, soulAttributePanelPosition.y+soulBeadCircleImageViewPosition.y);

				CCSize size = soulBeadCircleImageView[i]->getContentSize();
				CCRect rect = CCRect(position.x-size.width/2, position.y-size.height/2, size.width, size.height);

				if (rect.containsPoint(touchPosition))
				{
					starringManager->selectSoulBeadEquipId = i;

					// 目的位置是否有魂珠
					if (starringManager->soulBeadEquipSpriteArray[i].armature != NULL)
					{
						// 交换魂珠位置
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

					starringManager->putOnSoulBead();
					refresh();

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
		else
		{
			int circleId = starringManager->selectSoulBeadEquipId;
			CCPoint soulAttributePanelPosition = soulAttributePanel->getPosition();
			CCPoint soulBeadCircleImageViewPosition = soulBeadCircleImageView[circleId]->getPosition();
			CCPoint soulBeadCirclePosition = CCPoint(soulAttributePanelPosition.x+soulBeadCircleImageViewPosition.x, soulAttributePanelPosition.y+soulBeadCircleImageViewPosition.y);

			// 选择魂圈
			for (int i = 0; i < 10; i++)
			{
				CCPoint soulAttributePanelPosition = soulAttributePanel->getPosition();
				CCPoint soulBeadCircleImageViewPostion = soulBeadCircleImageView[i]->getPosition();

				CCPoint position = CCPoint(soulAttributePanelPosition.x+soulBeadCircleImageViewPostion.x, soulAttributePanelPosition.y+soulBeadCircleImageViewPostion.y);
				CCSize size = soulBeadCircleImageView[circleId]->getContentSize();
				CCRect rect = CCRect(position.x-size.width/2, position.y-size.height/2, size.width, size.height);

				if (rect.containsPoint(touchPosition))
				{
					// 目的位置是否有魂珠
					if (starringManager->soulBeadEquipSpriteArray[i].armature != NULL)
					{
						// 交换魂珠位置
						starringManager->soulBeadEquipSpriteArray[i].armature->setPosition(soulBeadCirclePosition);
						selectSoulBeadSprite.armature->setPosition(position);

						starringManager->soulBeadEquipSpriteArray[circleId] = starringManager->soulBeadEquipSpriteArray[i];
						starringManager->soulBeadEquipSpriteArray[i] = selectSoulBeadSprite;
					}
					else
					{
						selectSoulBeadSprite.armature->setPosition(position);
						starringManager->soulBeadEquipSpriteArray[i] = selectSoulBeadSprite;
					}

					starringManager->swapSoulBead(2);

					SoulBead* s = starringManager->soulBeadEquipArray[starringManager->selectSoulBeadEquipId];
					starringManager->soulBeadEquipArray[starringManager->selectSoulBeadEquipId] = starringManager->soulBeadEquipArray[i];
					starringManager->soulBeadEquipArray[i] = s;

					selectSoulBeadSprite.armature = NULL;
					selectSoulBeadSprite.soulBead = NULL;
					return;
				}
			}


			// 选择魂珠
			for (int i = 0; i < 12; i++)
			{
				CCPoint soulPanelPosition = soulPanel->getPosition();
				CCPoint soulBeadButtonPosition = soulBeadButton[i]->getPosition();
				CCPoint position = CCPoint(soulPanelPosition.x+soulBeadButtonPosition.x, soulPanelPosition.y+soulBeadButtonPosition.y);

				CCSize size = soulBeadButton[i]->getContentSize();
				CCRect rect = CCRect(position.x-size.width/2, position.y-size.height/2, size.width, size.height);

				if (rect.containsPoint(touchPosition))
				{
					// 目的位置是否有魂珠
					if (starringManager->soulBeadSpriteArray[i].armature != NULL)
					{
						// 交换魂珠位置
						starringManager->soulBeadSpriteArray[i].armature->setPosition(soulBeadCirclePosition);
						selectSoulBeadSprite.armature->setPosition(position);

						starringManager->soulBeadEquipSpriteArray[circleId] = starringManager->soulBeadSpriteArray[i];
						starringManager->soulBeadSpriteArray[i] = selectSoulBeadSprite;
					}
					else
					{
						selectSoulBeadSprite.armature->setPosition(position);
						starringManager->soulBeadSpriteArray[i] = selectSoulBeadSprite;
					}

					starringManager->selectSoulBeadId = starringManager->soulPageNum * 12 + i;
					starringManager->takeOffSoulBead();
					refresh();

					selectSoulBeadSprite.armature = NULL;
					selectSoulBeadSprite.soulBead = NULL;

					return;
				}
			}

			selectSoulBeadSprite.armature->setPosition(soulBeadCirclePosition);
			starringManager->soulBeadEquipSpriteArray[circleId] = selectSoulBeadSprite;
			selectSoulBeadSprite.armature = NULL;
			selectSoulBeadSprite.soulBead = NULL;
		}
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

	refresh();
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

	refresh();
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
	TianXiaDiYi::getTheOnlyInstance()->mainCityScene->player->attribute.wuLi += 0;
	TianXiaDiYi::getTheOnlyInstance()->mainCityScene->player->attribute.zhiLi += 0;
	TianXiaDiYi::getTheOnlyInstance()->mainCityScene->player->attribute.tiLi+= 0;
	TianXiaDiYi::getTheOnlyInstance()->mainCityScene->player->attribute.minJie += 0;
}

void UIStarring::cultureRadioButtonClicked( CCObject* sender, TouchEventType type )
{
	UIButton* button = (UIButton*)sender;

	for (int i = 0; i < 3; i++)
	{
		const char* s = CCString::createWithFormat("CultureRadioButton_%d", i+1)->getCString();

		if (strcmp(button->getName(), s) == 0)
		{
			cultureImageView->setVisible(true);
			cultureImageView->setPosition(button->getPosition());
			starringManager->selectCultureId = i;
			refresh();
			break;
		}
	}
}

void UIStarring::telentButtonEXTClicked( CCObject* sender, TouchEventType type )
{
	UIButton* button = (UIButton*)sender;

	for (int i = 0; i < 20; i++)
	{
		const char* s = CCString::createWithFormat("Telent%dButton_%d", starringManager->telentPageNum+1, i+1)->getCString();

		if (strcmp(button->getName(), s) == 0)
		{
			starringManager->selectTelentPointId = i;
			starringManager->lightUpTelentPoint();
			refresh();

			return;
		}
	}
}

void UIStarring::cultureModeButtonClicked( CCObject* sender, TouchEventType type )
{
	if (type == CCTOUCHBEGAN)
	{
		starringManager->culture();
		refresh();
	}
}