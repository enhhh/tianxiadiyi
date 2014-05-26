#include "UIFighting.h"
#include "UIMainCity.h"
#include "Scene\ChapterScene.h"

#include "..\TianXiaDiYi.h"

UIFighting::UIFighting()
{
}

UIFighting::~UIFighting()
{
}

bool UIFighting::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	uiLayer = UILayer::create();

	UILayout* fightingRoot = dynamic_cast<UILayout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/UIFighting.ExportJson"));
	uiLayer->addWidget(fightingRoot);

	UIButton* closeButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("CloseButton"));
	closeButton->addTouchEventListener(this, toucheventselector(UIFighting::closeButtonClicked));

	UIButton* enterButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("EnterButton"));
	enterButton->addTouchEventListener(this, toucheventselector(UIFighting::enterButtonClicked));

	fightingTestButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("FightingTestButton"));

	chapterPanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("ChapterPanel"));

	// уб╫зап╠М
	UIPanel* tableViewPanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("TableViewPanel"));

	CCTableView* chapterTableView = CCTableView::create(this, CCSizeMake(tableViewPanel->getContentSize().width, tableViewPanel->getContentSize().height));
	chapterTableView->setDirection(kCCScrollViewDirectionVertical);
	chapterTableView->setVerticalFillOrder(kCCTableViewFillTopDown);

	CCPoint formationTestPosition = fightingTestButton->getPosition();
	chapterTableView->setPosition(ccp(formationTestPosition.x, formationTestPosition.y - tableViewPanel->getContentSize().height));
	chapterTableView->setDelegate(this);
	chapterTableView->reloadData();

	addChild(uiLayer);
	addChild(chapterTableView);

	setVisible(false);
	return true;
}

void UIFighting::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
}

void UIFighting::scrollViewDidScroll( CCScrollView* view )
{

}

void UIFighting::scrollViewDidZoom( CCScrollView* view )
{
}

void UIFighting::tableCellTouched( CCTableView* table, CCTableViewCell* cell )
{
	CCLOG("cell touched at index: %i", cell->getIdx());
}

cocos2d::CCSize UIFighting::cellSizeForTable( CCTableView* table )
{
	CCSize size = chapterPanel->getContentSize();
	return  CCSizeMake(chapterPanel->getContentSize().width-60, chapterPanel->getContentSize().height);
}

CCTableViewCell* UIFighting::tableCellAtIndex( CCTableView* table, unsigned int idx )
{
	CCTableViewCell* cell = table->cellAtIndex(idx);

	if (!cell)
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		UIPanel* panel = UIPanel::create();
		panel->setContentSize(chapterPanel->getContentSize());

		UIImageView* chapterFrameImageView = UIImageView::create();
		chapterFrameImageView->loadTexture("png/SelectFrame.png");
		UIButton* chapterFrameImageViewEXT = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("ChapterButton"));
		chapterFrameImageView->setPosition(chapterFrameImageViewEXT->getPosition());
		chapterFrameImageView->setZOrder(2);
		panel->addChild(chapterFrameImageView);

		UIImageView* completeBGImageView = UIImageView::create();
		completeBGImageView->loadTexture("png/CompleteBG.png");
		UIImageView* completeBGImageViewEXT = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("CompleteBGImageView"));
		completeBGImageView->setPosition(completeBGImageViewEXT->getPosition());
		panel->addChild(completeBGImageView);

		UIImageView* completeImageView = UIImageView::create();
		completeImageView->loadTexture("png/Complete.png");
		UIImageView* completeImageViewEXT = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("CompleteImageView"));
		completeImageView->setPosition(completeImageViewEXT->getPosition());
		panel->addChild(completeImageView);

		UIImageView* chapterImageView = UIImageView::create();
		const char* s = CCString::createWithFormat("png/chapter/Chapter%d.png", idx+1)->getCString();
		chapterImageView->loadTexture(s);

		UIImageView* chapterImageViewEXT = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("ChapterImageView"));
		chapterImageView->setPosition(chapterFrameImageViewEXT->getPosition());
		panel->addChild(chapterImageView);

		cell->addChild(panel);

		CCSprite* chapterSelectSprite = CCSprite::create("png/ChapterSelect.png");
		chapterSelectSprite->setPosition(ccp(-4,-2));
		chapterSelectSprite->setAnchorPoint(CCPointZero);
		chapterSelectSprite->setTag(8);
		chapterSelectSprite->setVisible(false);
		cell->addChild(chapterSelectSprite);

		chapterSelectSpriteVector.push_back(chapterSelectSprite);
	}

	return cell;
}

unsigned int UIFighting::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 5;
}

void UIFighting::tableCellHighlight( CCTableView* table, extension::CCTableViewCell* cell )
{
	CCLOG("cell tableCellHighlight at index: %i", cell->getIdx());

	for (int i = 0; i < chapterSelectSpriteVector.size(); i++)
	{
		chapterSelectSpriteVector[i]->setVisible(false);
	}

	UIImageView* chapterSelectImageView = (UIImageView*)cell->getChildByTag(8);
	chapterSelectImageView->setVisible(true);
}

void UIFighting::tableCellUnhighlight( CCTableView* table, extension::CCTableViewCell* cell )
{
}

void UIFighting::closeButtonClicked(CCObject* sender, TouchEventType type)
{
	TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiFighting, true);
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiFighting->release();
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiFighting = NULL;
}

void UIFighting::enterButtonClicked( CCObject* sender, TouchEventType type )
{
	TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiFighting, true);
	TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity, true);

	TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->mainCityScene, true);
	TianXiaDiYi::getTheOnlyInstance()->mainCityScene->release();
	TianXiaDiYi::getTheOnlyInstance()->mainCityScene= NULL;

	TianXiaDiYi::getTheOnlyInstance()->chapterScene = ChapterScene::create();
	TianXiaDiYi::getTheOnlyInstance()->chapterScene->retain();
	TianXiaDiYi::getTheOnlyInstance()->addChild(TianXiaDiYi::getTheOnlyInstance()->chapterScene);
}