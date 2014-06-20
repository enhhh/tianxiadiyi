#ifndef __UIFIGHTING__
#define __UIFIGHTING__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "Logic\ChapterManager.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace gui;
using namespace std;

class UIFighting : public CCLayer, public CCTableViewDataSource, public CCTableViewDelegate
{
public:

	ChapterManager* chapterManager;
	UILayer* uiLayer;

	UIButton* fightingTestButton;
	UIPanel* chapterPanel;
	vector<CCSprite*> tableViewSpriteVector;

	UIFighting();
	~UIFighting();

	virtual bool init();
	virtual void onEnter();

	void closeButtonClicked(CCObject* sender, TouchEventType type);
	void enterButtonClicked(CCObject* sender, TouchEventType type);

	virtual void scrollViewDidScroll(CCScrollView* view);
	virtual void scrollViewDidZoom(CCScrollView* view);
	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
	virtual CCSize cellSizeForTable(CCTableView* table);
	virtual CCTableViewCell* tableCellAtIndex(CCTableView* table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
	void tableCellHighlight(CCTableView* table, extension::CCTableViewCell* cell);
	void tableCellUnhighlight(CCTableView* table, extension::CCTableViewCell* cell);

	CREATE_FUNC(UIFighting);
};

#endif