#ifndef __FIGHTING_SCENE_H__
#define __FIGHTING_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include <vector>

#include "TileMap\FightingMap.h"
#include "Sprite\Player.h"
#include "Sprite\Monster.h"
#include "Sprite\Effect.h"
#include "AI\States.h"
#include "Logic\FormationManager.h"
#include "UI\UIFightingWin.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

using namespace std;

class FightingScene : public CCLayer
{
public:
	FightingScene();
	~FightingScene();
public:

	CCSize visibleSize;

	FightingMap* fightingMap;

	vector<Monster*> monsterAgilityVector;
	vector<Monster*>monsterEnemyVector;
	vector<Monster*>monsterFriendVector;

	Monster* monsterEnemyArray[3][3];
	Monster* monsterFriendArray[3][3];

	Effect* fenNuYiJiEffect;

	int round;
	int roundMax;
	int roundDuration;

	FormationManager* formationManager;
	bool formationGeneral[3][3];
	bool formationSoldier[3][3];

	bool isFighting;

	UIFightingWin* uiFightingWin;

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void ccTouchCancelled(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);

	CREATE_FUNC(FightingScene);

	void draw();

	void updateEXT(float delta);
};

#endif