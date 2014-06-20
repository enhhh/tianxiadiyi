#ifndef __UICOUNTRY_RANK_H__
#define __UICOUNTRY_RANK_H__

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


class UICountryRank : public CCLayer, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	CountryManager* countryManager;
	UILayer* uiLayer;

	UIButton* rankTestButton;
	UIPanel* memberPanel;
	CCTableView* memberTableView;
	vector<UIImageView*> tableViewSpriteVector;

	UICountryRank();
	~UICountryRank();

	virtual bool init();
	virtual void onEnter();
	void clear();
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
	CREATE_FUNC(UICountryRank);
};

#endif