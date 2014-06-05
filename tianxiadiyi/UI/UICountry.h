#ifndef __UICOUNTRY_H__
#define __UICOUNTRY_H__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Logic\CountryManager.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace gui;
using namespace std;


class UICountry : public CCLayer, public CCTableViewDataSource, public CCTableViewDelegate
{
public:

	CountryManager* countryManager;

	UILayer* uiLayer;

	UIButton* coutryTestButton;
	UIPanel* memberPanel;

	CCTableView* memberTableView;
	vector<UIImageView*> tableViewSpriteVector;

	UICountry();
	~UICountry();

	virtual bool init();
	virtual void onEnter();
	void refresh();

	virtual void scrollViewDidScroll(CCScrollView* view);
	virtual void scrollViewDidZoom(CCScrollView* view);
	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
	virtual CCSize cellSizeForTable(CCTableView* table);
	virtual CCTableViewCell* tableCellAtIndex(CCTableView* table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
	void tableCellHighlight(CCTableView* table, extension::CCTableViewCell* cell);
	void tableCellUnhighlight(CCTableView* table, extension::CCTableViewCell* cell);

	void closeButtonClicked(CCObject* sender, TouchEventType type);
	void verifyButtonClicked(CCObject* sender, TouchEventType type);
	void modifyButtonClicked(CCObject* sender, TouchEventType type);
	void appointmentButtonClicked(CCObject* sender, TouchEventType type);
	void quitButtonClicked(CCObject* sender, TouchEventType type);
	void kickButtonClicked(CCObject* sender, TouchEventType type);
	void countryRankButtonClicked(CCObject* sender, TouchEventType type);
	void countryLandButtonClicked(CCObject* sender, TouchEventType type);

	CREATE_FUNC(UICountry);
};

#endif