#ifndef __UIFORMATION__
#define __UIFORMATION__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Logic\FormationManager.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace gui;

using namespace std;

class UIFormation : public CCLayer, public CCTableViewDataSource, public CCTableViewDelegate
{
public:

	FormationManager* formationManager;

	UILayer* uiLayer;

	// 将领图片
	UIImageView* headImage[8];

	// 阵型图片
	UIImageView* headFormationImage[3][3];

	// 选中将领
	GeneralSprite selectGeneralSprite;

	UIButton* formationTestButton;
	vector<CCSprite*> tableViewSpriteVector;

	UIFormation();
	~UIFormation();

	virtual bool init();
	virtual void onEnter();
	void clear();
	void refresh();

	// 重写触屏回调函数
	virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* event);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	virtual void scrollViewDidScroll(CCScrollView* view);
	virtual void scrollViewDidZoom(CCScrollView* view);
	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
	virtual CCSize cellSizeForTable(CCTableView* table);
	virtual CCTableViewCell* tableCellAtIndex(CCTableView* table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
	void tableCellHighlight(CCTableView* table, extension::CCTableViewCell* cell);
	void tableCellUnhighlight(CCTableView* table, extension::CCTableViewCell* cell);

	void closeButtonClicked(CCObject* sender, TouchEventType type);
	void pageLeftButtonClicked(CCObject* sender, TouchEventType type);
	void pageRightButtonClicked(CCObject* sender, TouchEventType type);

	CREATE_FUNC(UIFormation);
};

#endif