#ifndef __UISTRENGTHEN_H__
#define __UISTRENGTHEN_H__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Logic\FormationManager.h"
#include "Logic\ItemManager.h"
#include "Logic\StrengthenManager.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace gui;
using namespace std;

class UIStrengthen : public CCLayer, public CCTableViewDataSource, public CCTableViewDelegate
{
public:

	ItemManager* itemManager;
	FormationManager* formationManager;
	StrengthenManager* strengthenManager;


	UILayer* uiLayer;
	UIButton* strengthenTestButton;
	vector<CCSprite*> generalSelectSpriteVector;

	UIImageView* equipmentImageView[4];

	UIImageView* gemImageView[3];

	UIImageView* featureImageView;

	UIImageView* selectFrameImageView;

	UIStrengthen();
	~UIStrengthen();

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
	void equipmentButtonClicked(CCObject* sender, TouchEventType type);

	void pageLeftButtonClicked(CCObject* sender, TouchEventType type);
	void pageRightButtonClicked(CCObject* sender, TouchEventType type);

	CREATE_FUNC(UIStrengthen);
};

#endif