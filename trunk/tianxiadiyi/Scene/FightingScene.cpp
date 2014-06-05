#include "FightingScene.h"
#include "Input\Input.h"
#include "AI\StateMachine.h"
#include "AI\PathFind.h"
#include "..\TianXiaDiYi.h"

FightingScene::FightingScene()
{
	monsterAgilityVector.clear();
	monsterEnemyVector.clear();
	monsterFriendVector.clear();

	formationManager = FormationManager::getTheOnlyInstance();
	
	round = 0;
	roundDuration = 0;

	memset(monsterEnemyArray, 0, sizeof(Monster*)*3*3);
	memset(monsterFriendArray, 0, sizeof(Monster*)*3*3);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			formationGeneral[i][j] = formationArrary[formationManager->selectId][i][j];
			formationSoldier[i][j] = formationArrary[formationManager->selectId][i][j];
		}
	}

	isFighting = true;
}

FightingScene::~FightingScene()
{
}

bool FightingScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	fightingMap = new FightingMap();
	fightingMap->tiledMap->setPosition(ccp(0, 0));
	addChild(fightingMap->tiledMap);

	// 将领
	CCPoint formationGeneralPositions[3][3] = 
	{
		{ccp(417, 426), ccp(288, 426), ccp(156, 426)},
		{ccp(417, 296), ccp(288, 296), ccp(156, 296)},
		{ccp(417, 164), ccp(288, 164), ccp(156, 164)}
	};

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (formationGeneral[j][i] == false)
			{
				continue;
			}

			GeneralSprite gs = formationManager->generalSpriteArray[j][i];

			if (gs.general == NULL)
			{
				continue;
			}

			if (gs.general->isFormation == false)
			{
				continue;
			}

			Monster* monster = gs.general;
			gs.general->creatArmature();
			monster->setAttribute();
			monster->setPosition(ccp(formationGeneralPositions[j][i].x, formationGeneralPositions[j][i].y));
			monster->setOriginalPosition(monster->position);
			monster->armature->setPosition(monster->position);
			monster->setDirectionEXT(RIGHT, DIRECTION_NONE);
			monster->setAction(STAND);
			addChild(monster->armature);

			// 血量条
			monster->uiBloodLayer = UILayer::create();
			UILayout* bloodRoot = dynamic_cast<UILayout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/UIBlood.ExportJson"));
			monster->uiBloodLayer->addWidget(bloodRoot);

			UILoadingBar* bloodLoadingBar = dynamic_cast<UILoadingBar*>(monster->uiBloodLayer->getWidgetByName("BloodLoadingBar"));
			UILoadingBar* angerLoadingBar = dynamic_cast<UILoadingBar*>(monster->uiBloodLayer->getWidgetByName("AngerLoadingBar"));

			angerLoadingBar->setPercent(0);
			monster->uiBloodLayer->setPosition(ccp(-50, 80));
			monster->armature->addChild(monster->uiBloodLayer);

			monster->setFightingMap(fightingMap);
			monster->setIsAi(true);
			monster->setIsFriend(true);

			monsterFriendVector.push_back(monster);
			monsterFriendArray[j][i] = monster;

			StateMachine* stateMachine = new StateMachine(monster);
			monster->setStateMachine(stateMachine);
		}
	}

	// 小兵
	CCPoint formationSoldierPositions[3][3] = 
	{
		{ccp(742, 426), ccp(874, 426), ccp(1003, 426)},
		{ccp(742, 296), ccp(874, 296), ccp(1003, 296)},
		{ccp(742, 164), ccp(874, 164), ccp(1003, 164)}
	};

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (formationSoldier[j][i] == false)
			{
				continue;
			}

			Solider* solider = new Solider(1);
			solider->creatArmature();
			Monster* monster = solider;
			monster->setAttribute();
			monster->setPosition(ccp(formationSoldierPositions[j][i].x, formationSoldierPositions[j][i].y));
			monster->armature->setPosition(monster->position);
			monster->setOriginalPosition(monster->position);
			monster->setDirectionEXT(RIGHT, DIRECTION_NONE);
			monster->setAction(STAND);
			monster->armature->setScaleX(-1);
			addChild(monster->armature);

			// 血量条
			monster->uiBloodLayer = UILayer::create();
			UILayout* bloodRoot = dynamic_cast<UILayout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/UIBlood.ExportJson"));
			monster->uiBloodLayer->addWidget(bloodRoot);

			UILoadingBar* bloodLoadingBar = dynamic_cast<UILoadingBar*>(monster->uiBloodLayer->getWidgetByName("BloodLoadingBar"));
			UILoadingBar* angerLoadingBar = dynamic_cast<UILoadingBar*>(monster->uiBloodLayer->getWidgetByName("AngerLoadingBar"));
			bloodLoadingBar->setDirection(LoadingBarTypeRight);
			angerLoadingBar->setDirection(LoadingBarTypeRight);

			angerLoadingBar->setPercent(0);
			monster->uiBloodLayer->setPosition(ccp(-50, 80));
			monster->armature->addChild(monster->uiBloodLayer);

			monster->setFightingMap(fightingMap);
			monster->setIsAi(true);
			monster->setIsFriend(false);

			monsterEnemyVector.push_back(monster);
			monsterEnemyArray[j][i] = monster;

			StateMachine* stateMachine = new StateMachine(monster);
			monster->setStateMachine(stateMachine);
		}
	}

	fenNuYiJiEffect = new Effect();
	fenNuYiJiEffect->armature->setVisible(false);
	addChild(fenNuYiJiEffect->armature);

	// 敏捷值排序
	for (int i = 0; i < monsterEnemyVector.size(); i++)
	{
		monsterAgilityVector.push_back(monsterEnemyVector[i]);
	}

	for (int i = 0; i < monsterFriendVector.size(); i++)
	{
		monsterAgilityVector.push_back(monsterFriendVector[i]);
	}

	for (int i = 0; i < monsterAgilityVector.size(); i++)
	{
		for (int j = 0; j < monsterAgilityVector.size(); j++)
		{
			if (monsterAgilityVector[i]->agility > monsterAgilityVector[j]->agility)
			{
				Monster* sprite = monsterAgilityVector[i];
				monsterAgilityVector[i] = monsterAgilityVector[j];
				monsterAgilityVector[j] = sprite;
			}
		}
	}

	setKeypadEnabled(true);

	return true;
}

void FightingScene::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
}

void FightingScene::onExit()
{
	CCLayer::onExit();
}

void FightingScene::registerWithTouchDispatcher()
{
	setTouchEnabled(true);
}

bool FightingScene::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	return true;
}

void FightingScene::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
}

void FightingScene::ccTouchCancelled(CCTouch* touch, CCEvent* event)
{
}

void FightingScene::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
}

void FightingScene::draw()
{
}

void FightingScene::updateEXT(float delta)
{
	if (isFighting == false)
	{
		return;
	}

	roundDuration++;

	if (roundDuration > 100)
	{
		// 战斗结束
		int i = 0;
		int j = 0;

		for (int k = 0; k < monsterAgilityVector.size(); k++)
		{
			if (monsterAgilityVector[k]->action == DEAD)
			{
				if (monsterAgilityVector[k]->isFriend)
				{
					i++;
				}
				else
				{
					j++;
				}
			}
		}

		if ((i == monsterFriendVector.size()) || (j == monsterEnemyVector.size()))
		{
			if (i == monsterFriendVector.size())
			{
				uiFightingWin = UIFightingWin::create();

				uiFightingWin->winImageView->setVisible(false);
				uiFightingWin->awardImageView->setVisible(false);
				uiFightingWin->loseImageView->setVisible(true);

				TianXiaDiYi::getTheOnlyInstance()->addChild(uiFightingWin);
			}
			
			if (j == monsterEnemyVector.size())
			{
				uiFightingWin = UIFightingWin::create();
				TianXiaDiYi::getTheOnlyInstance()->addChild(uiFightingWin);
			}

			isFighting = false;
			return;
		}

		// 先手
		Monster* fightingMonster = NULL;

		while(true)
		{
			round = round % (monsterAgilityVector.size());
			fightingMonster = monsterAgilityVector[round++];
			
			if (fightingMonster->action != DEAD)
			{
				break;
			}
		}

		if (fightingMonster->isFriend == true)
		{
			// 选择攻击对像
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (formationSoldier[j][i] == true)
					{
						if ((monsterEnemyArray[j][i] == NULL) || (monsterEnemyArray[j][i]->action == DEAD))
						{
							continue;
						}

						fightingMonster->attackSprite = monsterEnemyArray[j][i];
						goto END1;
					}
				}
			}
END1:
			fightingMonster->isBack = false;
			fightingMonster->setTargetPosition(ccp(fightingMonster->attackSprite->position.x - 50, fightingMonster->attackSprite->position.y));
			fightingMonster->stateMachine->changeState(WALK);
		}
		else
		{
			// 选择攻击对像
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (formationSoldier[j][i] == true)
					{
						if ((monsterFriendArray[j][i] == NULL) || (monsterFriendArray[j][i]->action == DEAD))
						{
							continue;
						}

						fightingMonster->attackSprite = monsterFriendArray[j][i];
						goto END2;
					}
				}
			}
END2:
			fightingMonster->isBack = false;
			fightingMonster->setTargetPosition(ccp(fightingMonster->attackSprite->position.x + 50, fightingMonster->attackSprite->position.y));
			fightingMonster->stateMachine->changeState(WALK);
		}

		roundDuration = 0;
	}
	
	for (int i = 0; i < monsterAgilityVector.size(); i++)
	{
		monsterAgilityVector[i]->updateEXT(delta);
	}
}
