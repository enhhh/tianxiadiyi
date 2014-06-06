#ifndef __TIANXIADIYI__
#define __TIANXIADIYI__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "platform\third_party\win32\iconv\iconv.h"

#include "Scene\MainCityScene.h"
#include "Scene\FightingScene.h"
#include "Scene\ChapterScene.h"
#include "UI\UIMainCity.h"
#include "Network\UUSocketWrap.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

enum SceneType
{
	MAIN_CITY = 0,
	CHAPTER_SCENE,
	FIGHTING_SCENE
};

class TianXiaDiYi : public cocos2d::CCLayer
{
public:

	// 屏幕尺寸
	CCSize visibleSize;

	int sceneType;

	// CG 动画
	CCSprite* cgAction;
	CCSprite* tianAction;
	CCSprite* xiaAction;
	CCSprite* diAction;
	CCSprite* yiAction;

	UUCSocketWrap* socketWrap;

	MainCityScene* mainCityScene;
	ChapterScene* chapterScene;
	FightingScene* fightingScene;

	UIMainCity* uiMainCity;

	static TianXiaDiYi* getTheOnlyInstance();

    static cocos2d::CCScene* scene();

    virtual bool init();

	virtual void draw();

	void update(float delta);

	// 重写触屏回调函数
	virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* event);

	virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* event);

	virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* event);

	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	// 重写生命周期函数
	virtual void onEnter();

	virtual void onExit();

	void setSceneType(int sceneType);

	long long getCurrentTime();

	char* ansi2utf8(const char* inbuf);
	
	void playCgAction();

	void playCgActionCallback(CCNode* pSender);

	void tianActionCallback(CCNode* pSender);

	void xiaActionCallback(CCNode* pSender);

	void diActionCallback(CCNode* pSender);

	void yiActionCallback(CCNode* pSender);

    CREATE_FUNC(TianXiaDiYi);
};

#endif // __HELLOWORLD_SCENE_H__
