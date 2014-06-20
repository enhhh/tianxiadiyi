#include "UICountryRank.h"

#include "..\TianXiaDiYi.h"

UICountryRank::UICountryRank()
{
	countryManager = CountryManager::getTheOnlyInstance();
}

UICountryRank::~UICountryRank()
{
}

bool UICountryRank::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	uiLayer = UILayer::create();

	UILayout* countryRankRoot = dynamic_cast<UILayout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/UICountryRank.ExportJson"));
	uiLayer->addWidget(countryRankRoot);

	UIButton* closeButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("CloseButton"));
	closeButton->addTouchEventListener(this, toucheventselector(UICountryRank::closeButtonClicked));

	rankTestButton = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("RankTestButton"));
	memberPanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("MemberPanel"));

	// 审核成员列表
	UIPanel* tableViewPanel = dynamic_cast<UIPanel*>(uiLayer->getWidgetByName("TableViewPanel"));
	memberTableView = CCTableView::create(this, CCSizeMake(tableViewPanel->getContentSize().width, tableViewPanel->getContentSize().height));
	memberTableView->setDirection(kCCScrollViewDirectionVertical);
	memberTableView->setVerticalFillOrder(kCCTableViewFillTopDown);

	CCPoint testButtonPosition = rankTestButton->getPosition();
	memberTableView->setPosition(ccp(testButtonPosition.x, testButtonPosition.y - tableViewPanel->getContentSize().height));
	memberTableView->setDelegate(this);
	memberTableView->reloadData();
	addChild(uiLayer);
	addChild(memberTableView);
	refresh();

	return true;
}

void UICountryRank::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
}

void UICountryRank::clear()
{
}

void UICountryRank::refresh()
{
	clear();
}

void UICountryRank::scrollViewDidScroll( CCScrollView* view )
{

}

void UICountryRank::scrollViewDidZoom( CCScrollView* view )
{
}

void UICountryRank::tableCellTouched( CCTableView* table, CCTableViewCell* cell )
{
	CCLOG("cell touched at index: %i", cell->getIdx());
}

cocos2d::CCSize UICountryRank::cellSizeForTable( CCTableView* table )
{
	return  CCSizeMake(memberPanel->getContentSize().width, memberPanel->getContentSize().height);
}

CCTableViewCell* UICountryRank::tableCellAtIndex( CCTableView* table, unsigned int idx )
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
			memberBGImageView->loadTexture("png/RankMemberBG2.png");
		}
		else
		{
			memberBGImageView->loadTexture("png/RankMemberBG1.png");
		}

		UIImageView* memberBGImageViewEXT = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("MemberBGImageView"));
		memberBGImageView->setPosition(memberBGImageViewEXT->getPosition());
		panel->addChild(memberBGImageView);

		CountryRankMember rankMember = countryManager->countryRankMemberVector[idx];

		// 等级
		const char* lv = CCString::createWithFormat("%d级国家", rankMember.lv)->getCString();
		lv = TianXiaDiYi::getTheOnlyInstance()->ansi2utf8(lv);
		// 国家
		const char* name = TianXiaDiYi::getTheOnlyInstance()->ansi2utf8(rankMember.name);
		// 君主
		const char* zhenMingTianZi = TianXiaDiYi::getTheOnlyInstance()->ansi2utf8(rankMember.zhenMingTianZi);
		// 人数
		const char* num = CCString::createWithFormat("%d", rankMember.num)->getCString();
		// 排名
		const char* rank = CCString::createWithFormat("%d", rankMember.rank)->getCString();

		const char* attribute[5] = {lv, name, zhenMingTianZi, num, rank};

		for (int i = 0; i < 5; i++)
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

		delete[] lv;
		delete[] name;
		delete[] zhenMingTianZi;

		UIImageView* selectRankFrameImageView = UIImageView::create();
		selectRankFrameImageView->loadTexture("png/SelectRankFrame.png");
		selectRankFrameImageView->setVisible(false);
		selectRankFrameImageView->setTag(8);
		UIImageView* selectRankFrameImageViewEXT = dynamic_cast<UIImageView*>(uiLayer->getWidgetByName("SelectRankFrameImageView"));
		selectRankFrameImageView->setPosition(selectRankFrameImageViewEXT->getPosition());
		panel->addChild(selectRankFrameImageView);
		cell->addChild(panel);

		tableViewSpriteVector.push_back(selectRankFrameImageView);
	}

	return cell;
}

unsigned int UICountryRank::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return countryManager->countryRankMemberVector.size();
}

void UICountryRank::tableCellHighlight( CCTableView* table, extension::CCTableViewCell* cell )
{
	for (int i = 0; i < tableViewSpriteVector.size(); i++)
	{
		tableViewSpriteVector[i]->setVisible(false);
	}

	UIPanel* panel = (UIPanel*)cell->getChildByTag(8);
	UIImageView* selectRankFrameImageView = (UIImageView*)panel->getChildByTag(8);
	selectRankFrameImageView->setVisible(true);
}

void UICountryRank::tableCellUnhighlight( CCTableView* table, extension::CCTableViewCell* cell )
{
}

void UICountryRank::closeButtonClicked( CCObject* sender, TouchEventType type )
{
	TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiCountryRank, true);
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiCountryRank->release();
	TianXiaDiYi::getTheOnlyInstance()->uiMainCity->uiCountryRank = NULL;

	CCEditBox* editBox =  NULL;
}