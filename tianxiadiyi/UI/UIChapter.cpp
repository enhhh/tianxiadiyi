#include "UIChapter.h"

#include "..\TianXiaDiYi.h"

UIChapter::UIChapter()
{
	chapterManager = ChapterManager::getTheOnlyInstance();
}

UIChapter::~UIChapter()
{
}

bool UIChapter::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	uiLayer = UILayer::create();

	UILayout* rideRoot = dynamic_cast<UILayout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/UIRound1.ExportJson"));
	uiLayer->addWidget(rideRoot);

	UIButton* closeButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("ReturnButton"));
	closeButton->addTouchEventListener(this, toucheventselector(UIChapter::closeButtonClicked));

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			const char* s = CCString::createWithFormat("Round%dLevel%dImageView", i+1, j+1)->getCString();
			round[i][j] = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName(s));
		}
	}

	addChild(uiLayer);
	setVisible(false);
	refresh();
	return true;
}

void UIChapter::onEnter()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1, false);
	CCLayer::onEnter();
}

void UIChapter::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

void UIChapter::clear()
{
}

void UIChapter::refresh()
{
	clear();
}

bool UIChapter::ccTouchBegan( CCTouch* pTouch, CCEvent* event )
{
	CCLOG("ccTouchBegan");
	CCPoint touchPosition = pTouch->getLocation();

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			CCPoint position = round[i][j]->getPosition();
			CCSize size = round[i][j]->getContentSize();
			CCRect rect = CCRect(position.x-size.width/2, position.y-size.height/2, size.width, size.height);

			if (rect.containsPoint(touchPosition))
			{
				chapterManager->selectRoundId = i;
				chapterManager->selectLevelId = j;

				chapterManager->setArmyFormation();

				TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiChapter, true);
				TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiChapter->release();
				TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiChapter = NULL;

				TianXiaDiYi::getTheOnlyInstance()->fightingScene = FightingScene::create();
				TianXiaDiYi::getTheOnlyInstance()->fightingScene->retain();
				TianXiaDiYi::getTheOnlyInstance()->addChild(TianXiaDiYi::getTheOnlyInstance()->fightingScene);

				return true;
			}
		}
	}

	return true;
}

void UIChapter::ccTouchMoved( CCTouch* pTouch, CCEvent* event )
{
	CCLOG("ccTouchMoved");
	CCPoint touchPosition = pTouch->getLocation();
}

void UIChapter::ccTouchEnded( CCTouch* pTouch, CCEvent* event )
{
	CCLOG("ccTouchEnded");
	CCPoint touchPosition = pTouch->getLocation();
}

void UIChapter::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	CCLOG("ccTouchCancelled");
}

void UIChapter::closeButtonClicked( CCObject* sender, TouchEventType type )
{
	TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiChapter, true);
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiChapter->release();
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiChapter = NULL;

	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiFighting = UIFighting::create();
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiFighting->retain();
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiFighting->setVisible(true);
	TianXiaDiYi::getTheOnlyInstance()->addChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiFighting);
}