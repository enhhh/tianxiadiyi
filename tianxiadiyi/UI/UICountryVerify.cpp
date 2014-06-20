#include "UICountryVerify.h"

#include "..\TianXiaDiYi.h"

UICountryVerify::UICountryVerify()
{
	countryManager = CountryManager::getTheOnlyInstance();
}

UICountryVerify::~UICountryVerify()
{
}

bool UICountryVerify::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	uiLayer = UILayer::create();

	UILayout* countryRankRoot = dynamic_cast<UILayout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/UICountryVerify.ExportJson"));
	uiLayer->addWidget(countryRankRoot);

	UIButton* closeButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("CloseButton"));
	closeButton->addTouchEventListener(this, toucheventselector(UICountryVerify::closeButtonClicked));

	verifyTestButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("VerifyTestButton"));
	memberPanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("MemberPanel"));
	
	// 审核成员列表
	UIPanel* tableViewPanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("TableViewPanel"));
	memberTableView = CCTableView::create(this, CCSizeMake(tableViewPanel->getContentSize().width, tableViewPanel->getContentSize().height));
	memberTableView->setDirection(kCCScrollViewDirectionVertical);
	memberTableView->setVerticalFillOrder(kCCTableViewFillTopDown);

	CCPoint testButtonPosition = verifyTestButton->getPosition();
	memberTableView->setPosition(ccp(testButtonPosition.x, testButtonPosition.y - tableViewPanel->getContentSize().height));
	memberTableView->setDelegate(this);
	memberTableView->reloadData();
	addChild(uiLayer);
	addChild(memberTableView);
	refresh();
	return true;
}

void UICountryVerify::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
}

void UICountryVerify::clear()
{
}

void UICountryVerify::refresh()
{
	clear();
}

void UICountryVerify::scrollViewDidScroll( CCScrollView* view )
{

}

void UICountryVerify::scrollViewDidZoom( CCScrollView* view )
{
}

void UICountryVerify::tableCellTouched( CCTableView* table, CCTableViewCell* cell )
{
	CCLOG("cell touched at index: %i", cell->getIdx());
	countryManager->selectVerifyId = cell->getIdx();
}

cocos2d::CCSize UICountryVerify::cellSizeForTable( CCTableView* table )
{
	return  CCSizeMake(memberPanel->getContentSize().width, memberPanel->getContentSize().height);
}

CCTableViewCell* UICountryVerify::tableCellAtIndex( CCTableView* table, unsigned int idx )
{
	CCTableViewCell* cell = table->cellAtIndex(idx);

	if (!cell)
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		UIPanel* panel = UIPanel::create();
		panel->setTag(8);
		panel->setContentSize(memberPanel->getContentSize());

		UIImageView* memberBGImageView = UIImageView::create();

		if (idx % 2 == 0)
		{
			memberBGImageView->loadTexture("png/MemberBG2.png");
		}
		else
		{
			memberBGImageView->loadTexture("png/MemberBG1.png");
		}

		UIImageView* memberBGImageViewEXT = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("MemberBGImageView"));
		memberBGImageView->setPosition(memberBGImageViewEXT->getPosition());
		panel->addChild(memberBGImageView);

		VerifyMember verifyMember = countryManager->verifyMemberVector[idx];

		// 等级
		const char* lv = CCString::createWithFormat("%d", verifyMember.lv)->getCString();
		// 玩家
		const char* name = TianXiaDiYi::getTheOnlyInstance()->ansi2utf8(verifyMember.name);
	
		const char* attribute[2] = {lv, name};

		for (int i = 0; i < 2; i++)
		{
			UILabel* memberLabel = UILabel::create();
			memberLabel->setZOrder(5);
			memberLabel->setColor(ccRED);
			memberLabel->setText(attribute[i]);

			const char* s = CCString::createWithFormat("MemberLabel_%d", i+1)->getCString();
			UILabel* memberLableEXT = dynamic_cast<UILabel*>(uiLayer->getWidgetByName(s));
			memberLabel->setPosition(memberLableEXT->getPosition());

			panel->addChild(memberLabel);
		}

		delete[] name;

		UIImageView* selectVerifyFrameImageView = UIImageView::create();
		selectVerifyFrameImageView->loadTexture("png/SelectVerifyFrame.png");
		selectVerifyFrameImageView->setVisible(false);
		selectVerifyFrameImageView->setTag(8);
		UIImageView* selectCoutryFrameImageViewEXT = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("SelectVerifyFrameImageView"));
		selectVerifyFrameImageView->setPosition(selectCoutryFrameImageViewEXT->getPosition());
		panel->addChild(selectVerifyFrameImageView);
		cell->addChild(panel);

		tableViewSpriteVector.push_back(selectVerifyFrameImageView);
	}

	return cell;
}

unsigned int UICountryVerify::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return countryManager->verifyMemberVector.size();
}

void UICountryVerify::tableCellHighlight( CCTableView* table, extension::CCTableViewCell* cell )
{
	countryManager->selectVerifyId = cell->getIdx();

	for (int i = 0; i < tableViewSpriteVector.size(); i++)
	{
		tableViewSpriteVector[i]->setVisible(false);
	}

	UIPanel* panel = (UIPanel*)cell->getChildByTag(8);
	UIImageView* selectCoutryFrameImageView = (UIImageView*)panel->getChildByTag(8);
	selectCoutryFrameImageView->setVisible(true);
}

void UICountryVerify::tableCellUnhighlight( CCTableView* table, extension::CCTableViewCell* cell )
{
}

void UICountryVerify::closeButtonClicked( CCObject* sender, TouchEventType type )
{
	TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiCountryVerify, true);
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiCountryVerify->release();
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiCountryVerify = NULL;
}