#include "ChapterScene.h"
#include "AI\StateMachine.h"
#include "Input\Input.h"
#include "AI\PathFind.h"
#include "..\TianXiaDiYi.h"

ChapterScene::ChapterScene()
{
}

ChapterScene::~ChapterScene()
{
	removeChild(chapterMap->tiledMap, true);
	
	for (int i = 0; i < monsterVector.size(); i++)
	{
		removeChild(monsterVector[i]->armature, true);
	}
}

bool ChapterScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	chapterMap = new ChapterMap();
	chapterMap->tiledMap->setPosition(ccp(0, 0));
	addChild(chapterMap->tiledMap);

	for (int i = 0; i < 1; i++)
	{
		General* general = new General(i+1);
		general->creatArmature();

		Monster* monster = general;
		monster->setPosition(ccp(742, 164));
		monster->setDirectionEXT(DIRECTION_NONE, DOWN);
		monster->setAction(STAND);
		monster->armature->setPosition(monster->position);
		addChild(monster->armature);

		monster->setChapterMap(chapterMap);
		monsterVector.push_back(monster);
		StateMachine* stateMachine = new StateMachine(monster);
		monster->setStateMachine(stateMachine);
	}

	for (int i = 0; i < 1; i++)
	{
		Solider* solider = new Solider(i+1);
		solider->creatArmature();

		Monster* monster = solider;
		monster->setPosition(ccp(417, 164));
		monster->armature->setPosition(monster->position);
		monster->setDirectionEXT(DIRECTION_NONE, DOWN);
		monster->setAction(STAND);
		addChild(monster->armature);

		monster->setChapterMap(chapterMap);
		monsterVector.push_back(monster);
		StateMachine* stateMachine = new StateMachine(monster);
		monster->setStateMachine(stateMachine);
	}

	setKeypadEnabled(true);

	return true;
}

void ChapterScene::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
}

void ChapterScene::onExit()
{
	CCLayer::onExit();
}

void ChapterScene::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 2, true);
}

bool ChapterScene::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CCPoint touchPoint = touch->getLocation();

	for (int i = 0; i < monsterVector.size(); i++)
	{
		CCRect rect = monsterVector[i]->armature->boundingBox();

		if (rect.containsPoint(touchPoint))
		{
			switch (monsterVector[i]->monsterType)
			{
			case GENERAL:
			case SOLDIER:	
				TianXiaDiYi::getTheOnlyInstance()->removeChild(TianXiaDiYi::getTheOnlyInstance()->chapterScene, true);
				TianXiaDiYi::getTheOnlyInstance()->chapterScene->release();
				TianXiaDiYi::getTheOnlyInstance()->chapterScene = NULL;

				TianXiaDiYi::getTheOnlyInstance()->fightingScene = FightingScene::create();
				TianXiaDiYi::getTheOnlyInstance()->fightingScene->retain();
				TianXiaDiYi::getTheOnlyInstance()->addChild(TianXiaDiYi::getTheOnlyInstance()->fightingScene);
				return true;

				break;
			}
		}
	}

	return true;
}

void ChapterScene::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
}

void ChapterScene::ccTouchCancelled(CCTouch* touch, CCEvent* event)
{
}

void ChapterScene::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
}

void ChapterScene::draw()
{
}

void ChapterScene::updateEXT(float delta)
{
}