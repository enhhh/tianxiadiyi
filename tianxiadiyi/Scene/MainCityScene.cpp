#include "MainCityScene.h"
#include "AI\StateMachine.h"
#include "Input\Input.h"
#include "AI\PathFind.h"

MainCityScene::MainCityScene()
{
}

MainCityScene::~MainCityScene()
{
	removeChild(mainCity->tiledMap, true);
	removeChild(player->armature, true);
}

bool MainCityScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	mainCity = new MainCity();
	mainCity->tiledMap->setPosition(ccp(0, 0));
	addChild(mainCity->tiledMap);

	player = new Player();
	player->setPosition(ccp(450, 360));
	player->armature->setPosition(ccp(450, 360));
	addChild(player->armature);

	player->setMainCity(mainCity);
	StateMachine* stateMachine = new StateMachine(player);
	player->setStateMachine(stateMachine);

	setKeypadEnabled(true);

	return true;
}

void MainCityScene::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
}

void MainCityScene::onExit()
{
	CCLayer::onExit();
}

void MainCityScene::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
}

bool MainCityScene::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CCPoint touchPoint = touch->getLocation();

	touchPoint.x = (touchPoint.x - mainCity->position.x);
	touchPoint.y = (touchPoint.y - mainCity->position.y);

	int startX = player->position.x / mainCity->tiledMap->getTileSize().width;
    int startY = (mainCity->tiledMap->getContentSize().height - player->position.y) / mainCity->tiledMap->getTileSize().height;

	int endX = touchPoint.x / mainCity->tiledMap->getTileSize().width;
    int endY = (mainCity->tiledMap->getContentSize().height - touchPoint.y) / mainCity->tiledMap->getTileSize().height;

	// 搜索路径
	if (PathFind::getTheOnlyInstance()->AStarSearch(mainCity->tiledMap, startX, startY, endX, endY))
	{
		list<CCPoint>& astarPathList = PathFind::getTheOnlyInstance()->astarPathList;
		list<CCPoint>::iterator it = astarPathList.begin();
		CCTMXLayer* mapLayer = mainCity->tiledMap->layerNamed("mainCityLayer");
		
		CCPoint targetPosition;
		targetPosition.x = (*it).x * mainCity->tiledMap->getTileSize().width + mainCity->tiledMap->getTileSize().width / 2;
		targetPosition.y = mainCity->tiledMap->getContentSize().height - (*it).y * mainCity->tiledMap->getTileSize().height - mainCity->tiledMap->getTileSize().height / 2;
		astarPathList.pop_front();

		player->isAstar = true;
		player->setTargetPosition(targetPosition);
		player->setTouchMove(true);
		player->stateMachine->changeState(WALK);
	}
	
	return true;
}

void MainCityScene::ccTouchEnded(CCTouch* touch, CCEvent* event)
{

}

void MainCityScene::ccTouchCancelled(CCTouch* touch, CCEvent* event)
{

}

void MainCityScene::ccTouchMoved(CCTouch* touch, CCEvent* event)
{

}

void MainCityScene::draw()
{
	// 绘制怪物位置
	/*CCRect rect = player->armature->boundingBox();
	char playerPosition[100] = {0};
	sprintf(playerPosition, "(playerX = %0.1f, playerY = %0.1f)\n(playerW = %0.1f, playerH = %0.1f)", player->position.x, player->position.y,
		rect.getMaxX() - rect.origin.x, rect.getMaxY() - rect.origin.y);
	
	player->positionLabel->setString(playerPosition);

	for (int i = 0; i < monsterVector.size(); i++)
	{
		CCRect rect = monsterVector[i]->armature->boundingBox();
		char monsterPosition[100] = {0};
		sprintf(monsterPosition, "(monsterX = %0.1f, monsterY = %0.1f)\n(monsterW = %0.1f, monsterH = %0.1f)", monsterVector[i]->position.x, monsterVector[i]->position.y,
			rect.getMaxX() - rect.origin.x, rect.getMaxY() - rect.origin.y);

		monsterVector[i]->positionLabel->setString(monsterPosition);
	}*/
}

void MainCityScene::updateEXT(float delta)
{
	Input::update();

	vector<Sprite*> spriteVector;
	spriteVector.push_back(player);

	for (int i = 0; i < monsterVector.size(); i++)
	{
		spriteVector.push_back(monsterVector[i]);
	}

	for (int i = 0; i < spriteVector.size(); i++)
	{
		for (int j = 0; j < spriteVector.size(); j++)
		{
			if (spriteVector[i]->position.y > spriteVector[j]->position.y)
			{
				Sprite* sprite = spriteVector[i];
				spriteVector[i] = spriteVector[j];
				spriteVector[j] = sprite;
			}
		}
	}

	for (int i = 0; i < spriteVector.size(); i++)
	{
		spriteVector[i]->armature->setZOrder(i);
	}

	mainCity->updateEXT(delta);
	player->updateEXT(delta);
	
	for (int i = 0; i < monsterVector.size(); i++)
	{
		monsterVector[i]->updateEXT(delta);
	}
}