#ifndef __UICHAPTER_H__
#define __UICHAPTER_H__

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

class UIChapter : public CCLayer
{
public:

	ChapterManager* chapterManager;

	UILayer* uiLayer;
	UIImageView* round[2][6];

	UIChapter();
	~UIChapter();

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	// 重写触屏回调函数
	virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* event);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	void clear();
	void refresh();
	void closeButtonClicked(CCObject* sender, TouchEventType type);
	CREATE_FUNC(UIChapter);
};

#endif