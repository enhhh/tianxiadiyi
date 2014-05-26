#ifndef __CHAPTER_SCENE_H__
#define __CHAPTER_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include <vector>

#include "TileMap\ChapterMap.h"
#include "Sprite\Player.h"
#include "Sprite\Monster.h"
#include "Sprite\General.h"
#include "Sprite\Solider.h"
#include "AI\States.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

using namespace std;

class ChapterScene : public CCLayer
{
public:
	ChapterScene();
	~ChapterScene();
public:

	CCSize visibleSize;

	ChapterMap* chapterMap;
	vector<Monster*>monsterVector;

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void ccTouchCancelled(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);

	CREATE_FUNC(ChapterScene);

	void draw();

	void updateEXT(float delta);
};

#endif __CHAPTER_SCENE_H__