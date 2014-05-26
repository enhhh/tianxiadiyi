#include "SpriteStates.h"
#include "States.h"
#include "AI\PathFind.h"
#include "UI\UINumber.h"
#include "..\TianXiaDiYi.h"

void Stand::enter( Sprite* sprite )
{
	if (sprite->action != STAND)
	{
		sprite->setAction(STAND);
	}
}

void Stand::execute( Sprite* sprite )
{
}

void Stand::exit( Sprite* sprite )
{
}

void Walk::enter( Sprite* sprite )
{
	sprite->speedX = 0;
	sprite->speedY = 0;

	if (sprite->type == PLAYER)
	{
		if (sprite->isTouchMove)
		{
			CCPoint dist = ccp(sprite->targetPosition.x-sprite->position.x, sprite->targetPosition.y-sprite->position.y);

			sprite->distX = dist.x;
			sprite->distY = dist.y;

			if ((sprite->distX == 0) && (sprite->distY == 0))
			{
				return;
			}

			float temp = sprite->speed / sqrt(sprite->distX * sprite->distX + sprite->distY * sprite->distY);
			sprite->speedX = sprite->distX * temp;
			sprite->speedY = sprite->distY * temp;

			float radians = ccpToAngle(ccpSub(sprite->targetPosition, sprite->position));
			float degrees = -1 * CC_RADIANS_TO_DEGREES(radians);

			if (degrees <= -75 && degrees >= -105)
			{
				sprite->touchNextDirectionX = DIRECTION_NONE;
				sprite->touchNextDirectionY = UP;
			}
			else if (degrees >=75 && degrees <=105)
			{
				sprite->touchNextDirectionX = DIRECTION_NONE;
				sprite->touchNextDirectionY = DOWN;
			}
			else if (degrees >=165 || degrees <= -165)
			{
				sprite->touchNextDirectionX = LEFT;
				sprite->touchNextDirectionY = DIRECTION_NONE;
			}
			else if (degrees <= 15 && degrees >= -15)
			{
				sprite->touchNextDirectionX = RIGHT;
				sprite->touchNextDirectionY = DIRECTION_NONE;
			}
			else if (degrees < -105 && degrees > -165)
			{
				sprite->touchNextDirectionX = LEFT;
				sprite->touchNextDirectionY = UP;
			}
			else if (degrees < -15 && degrees > -75)
			{
				sprite->touchNextDirectionX = RIGHT;
				sprite->touchNextDirectionY = UP;
			}
			else if (degrees > 105 && degrees < 165)
			{
				sprite->touchNextDirectionX = LEFT;
				sprite->touchNextDirectionY = DOWN;
			}
			else if (degrees > 15 && degrees < 75)
			{
				sprite->touchNextDirectionX = RIGHT;
				sprite->touchNextDirectionY = DOWN;
			}

			if (sprite->action != WALK)
			{
				sprite->setAction(WALK);
			}

			if ((sprite->touchNextDirectionX != sprite->directionX) || (sprite->touchNextDirectionY != sprite->directionY))
			{
				sprite->directionX = sprite->touchNextDirectionX;
				sprite->directionY = sprite->touchNextDirectionY;
				sprite->setAction(WALK);
			}
		}
		else
		{
			switch(sprite->nextDirectionY)
			{
			case UP:
				sprite->speedY = WALK_SPEED;
				break;
			case DOWN:
				sprite->speedY = -WALK_SPEED;
				break;
			}

			switch(sprite->nextDirectionX)
			{
			case LEFT:

				sprite->speedX = -WALK_SPEED;
				sprite->face = LEFT;
				break;
			case RIGHT:

				sprite->speedX = WALK_SPEED;
				sprite->face = RIGHT;
				break;
			}

			if (sprite->action != WALK)
			{
				sprite->setAction(WALK);
			}

			if ((sprite->nextDirectionX != sprite->directionX) || (sprite->nextDirectionY != sprite->directionY))
			{
				sprite->directionX = sprite->nextDirectionX;
				sprite->directionY = sprite->nextDirectionY;
				sprite->setAction(WALK);
			}
		}
	}

	if (sprite->type == MONSTER)
	{
		CCPoint dist = ccp(sprite->targetPosition.x-sprite->position.x, sprite->targetPosition.y-sprite->position.y);

		sprite->distX = dist.x;
		sprite->distY = dist.y;

		if ((sprite->distX == 0) && (sprite->distY == 0))
		{
			return;
		}

		float temp = (sprite->speed + 20) / sqrt(sprite->distX * sprite->distX + sprite->distY * sprite->distY);
		sprite->speedX = sprite->distX * temp;
		sprite->speedY = sprite->distY * temp;

		if(sprite->distX < 0)
		{
			sprite->face = LEFT;
			sprite->nextDirectionX = LEFT;
		} 
		else if(sprite->distX > 0)
		{
			sprite->face = RIGHT;
			sprite->nextDirectionX = RIGHT;
		}

		if(sprite->distY < 0)
		{
			sprite->nextDirectionY = DOWN;
		} 
		else if(sprite->distY > 0)
		{
			sprite->nextDirectionY = UP;
		}

		if (sprite->action != WALK)
		{
			sprite->setAction(WALK);
		}
	}
}

void Walk::execute( Sprite* sprite )
{
	if (sprite->type == PLAYER)
	{
		float offsetX = sprite->speedX;
		float offsetY = sprite->speedY;

		bool isMoveX = true;
		bool isMoveY = true;

		if (sprite->distX < 0)
		{
			if (sprite->position.x + offsetX <= sprite->targetPosition.x)
			{
				offsetX = sprite->targetPosition.x - sprite->position.x;
				sprite->distX = 0;
			}
		} 
		else if (sprite->distX > 0) 
		{
			if (sprite->position.x + offsetX >= sprite->targetPosition.x)
			{
				offsetX = sprite->targetPosition.x - sprite->position.x;
				sprite->distX = 0;
			}
		}

		if (sprite->distY < 0)
		{
			if (sprite->position.y + offsetY <= sprite->targetPosition.y)
			{
				offsetY = sprite->targetPosition.y - sprite->position.y;
				sprite->distY = 0;
			}
		}
		else if (sprite->distY > 0) 
		{
			if(sprite->position.y + offsetY >= sprite->targetPosition.y)
			{
				offsetY = sprite->targetPosition.y - sprite->position.y;
				sprite->distY = 0;
			}
		}

		if ((sprite->position.x + offsetX >= sprite->visibleSize.width / 2) && 
			(sprite->position.x + offsetX <= sprite->mainCity->tiledMap->getContentSize().width - sprite->visibleSize.width / 2))
		{
			float x = sprite->position.x + offsetX - sprite->visibleSize.width / 2;
			sprite->mainCity->position.x = -x;
			sprite->mainCity->tiledMap->setPositionX(-x);

			isMoveX = false;
		}

		if ((sprite->position.y + offsetY >= sprite->visibleSize.height / 2) && 
			(sprite->position.y + offsetY <= sprite->mainCity->tiledMap->getContentSize().height - sprite->visibleSize.height / 2))
		{
			float y = sprite->position.y + offsetY - sprite->visibleSize.height / 2;
			sprite->mainCity->position.y = -y;
			sprite->mainCity->tiledMap->setPositionY(-y);
			isMoveY = false;
		}

		sprite->position.x += offsetX;
		sprite->position.y += offsetY;

		if (((int)sprite->position.x == (int)sprite->targetPosition.x) && ((int)sprite->position.y == (int)sprite->targetPosition.y))
		{
			list<CCPoint>& astarPathList = PathFind::getTheOnlyInstance()->astarPathList;
			
			if (astarPathList.size() != 0)
			{
				sprite->isAstar = false;
			}
			else
			{
				sprite->stateMachine->changeState(STAND);
				sprite->isTouchMove = false;
			}
		}

		if (isMoveX)
		{
			
			sprite->armature->setPositionX(sprite->position.x+sprite->mainCity->position.x);
		}

		if (isMoveY)
		{
			sprite->armature->setPositionY(sprite->position.y+sprite->mainCity->position.y);
		}
	}

	if (sprite->type == MONSTER)
	{
		float offsetX = sprite->speedX;
		float offsetY = sprite->speedY;

		if (sprite->distX < 0)
		{
			if (sprite->position.x + offsetX <= sprite->targetPosition.x)
			{
				offsetX = sprite->targetPosition.x - sprite->position.x;
				sprite->distX = 0;
			}
		} 
		else if (sprite->distX > 0) 
		{
			if (sprite->position.x + offsetX >= sprite->targetPosition.x)
			{
				offsetX = sprite->targetPosition.x - sprite->position.x;
				sprite->distX = 0;
			}
		}

		if (sprite->distY < 0)
		{
			if (sprite->position.y + offsetY <= sprite->targetPosition.y)
			{
				offsetY = sprite->targetPosition.y - sprite->position.y;
				sprite->distY = 0;
			}
		}
		else if (sprite->distY > 0) 
		{
			if(sprite->position.y + offsetY >= sprite->targetPosition.y)
			{
				offsetY = sprite->targetPosition.y - sprite->position.y;
				sprite->distY = 0;
			}
		}

		sprite->position.x += offsetX;
		sprite->position.y += offsetY;

		if (((int)sprite->position.x == (int)sprite->targetPosition.x) && ((int)sprite->position.y == (int)sprite->targetPosition.y))
		{
			if (sprite->isBack == false)
			{
				sprite->stateMachine->changeState(ATTACK0);
				sprite->isBack = true;
			}
			else
			{
				sprite->stateMachine->changeState(STAND);
			}
		}
	}
}

void Walk::exit( Sprite* sprite )
{

}

void ForwardWalk::enter( Sprite* sprite )
{

}

void ForwardWalk::execute( Sprite* sprite )
{

}

void ForwardWalk::exit( Sprite* sprite )
{

}

void BackwardWalk::enter( Sprite* sprite )
{

}

void BackwardWalk::execute( Sprite* sprite )
{

}

void BackwardWalk::exit( Sprite* sprite )
{

}

void FastForwardRun::enter( Sprite* sprite )
{

}

void FastForwardRun::execute( Sprite* sprite )
{

}

void FastForwardRun::exit( Sprite* sprite )
{

}

void FastBackwardRun::enter( Sprite* sprite )
{

}

void FastBackwardRun::execute( Sprite* sprite )
{

}

void FastBackwardRun::exit( Sprite* sprite )
{

}

void JumpUp::enter( Sprite* sprite )
{

}

void JumpUp::execute( Sprite* sprite )
{

}

void JumpUp::exit( Sprite* sprite )
{

}

void JumpDown::enter( Sprite* sprite )
{

}

void JumpDown::execute( Sprite* sprite )
{

}

void JumpDown::exit( Sprite* sprite )
{

}

void GoDown::enter( Sprite* sprite )
{

}

void GoDown::execute( Sprite* sprite )
{

}

void GoDown::exit( Sprite* sprite )
{

}

void GoUp::enter( Sprite* sprite )
{

}

void GoUp::execute( Sprite* sprite )
{

}

void GoUp::exit( Sprite* sprite )
{

}

void Attack::enter( Sprite* sprite )
{
	if (sprite->action != ATTACK0 &&
		sprite->action != ATTACK1 &&
		sprite->action != ATTACK2 &&
		sprite->action != ATTACK3 &&
		sprite->action != ATTACK4 
		)
	{
		Monster* monster = (Monster*)sprite;
		
		if (monster->anger == 100)
		{
			monster->anger = 0;
			TianXiaDiYi::getTheOnlyInstance()->fightingScene->fenNuYiJiEffect->armature->getAnimation()->play("FenNuYiJi");
			TianXiaDiYi::getTheOnlyInstance()->fightingScene->fenNuYiJiEffect->armature->setVisible(true);

			if (sprite->isFriend == false)
			{
				TianXiaDiYi::getTheOnlyInstance()->fightingScene->fenNuYiJiEffect->armature->setScale(-1);
				TianXiaDiYi::getTheOnlyInstance()->fightingScene->fenNuYiJiEffect->armature->setPosition(ccp(sprite->attackSprite->armature->getPositionX()-50, sprite->attackSprite->armature->getPositionY()));
			}
			else
			{
				TianXiaDiYi::getTheOnlyInstance()->fightingScene->fenNuYiJiEffect->armature->setScale(1);
				TianXiaDiYi::getTheOnlyInstance()->fightingScene->fenNuYiJiEffect->armature->setPosition(ccp(sprite->attackSprite->armature->getPositionX()+50, sprite->attackSprite->armature->getPositionY()));
			}
		}

		sprite->setAction(ATTACK0);
	}
}

void Attack::execute( Sprite* sprite )
{
	if (sprite->armature->getAnimation()->getIsPlaying() == false)
	{
		Monster* monster = (Monster*)sprite;
		monster->anger += 25;
		UILoadingBar* angerLoadingBar = dynamic_cast<UILoadingBar*>(sprite->uiBloodLayer->getWidgetByName("AngerLoadingBar"));
		angerLoadingBar->setPercent(monster->anger);

		sprite->setTargetPosition(sprite->originalPosition);
		sprite->stateMachine->changeState(WALK);

		Monster* attackMonster = (Monster*)sprite->attackSprite;
		attackMonster->hp -= 5;
		UILoadingBar* bloodLoadingBar = dynamic_cast<UILoadingBar*>(attackMonster->uiBloodLayer->getWidgetByName("BloodLoadingBar"));
		bloodLoadingBar->setPercent(attackMonster->hp);

		if (attackMonster->hp > 0)
		{
			sprite->attackSprite->stateMachine->changeState(HURT);
		}
		else
		{
			sprite->attackSprite->stateMachine->changeState(DEAD);
		}

		CCSprite* numberSprite = UINumber::getTheOnlyInstance()->floatNumber(100, sprite->attackSprite->armature->getPositionX()-50, sprite->attackSprite->armature->getPositionY()+80, sprite->armature->getContentSize().width, sprite->armature->getContentSize().height);
		TianXiaDiYi::getTheOnlyInstance()->fightingScene->addChild(numberSprite);
	}
}

void Attack::exit( Sprite* sprite )
{
}

void Hurt::enter( Sprite* sprite )
{
	sprite->setAction(HURT);
}

void Hurt::execute( Sprite* sprite )
{
	if (sprite->armature->getAnimation()->getIsPlaying() == false)
	{
		sprite->stateMachine->changeState(STAND);
	}
}

void Hurt::exit( Sprite* sprite )
{

}

void Dead::enter( Sprite* sprite )
{
	sprite->setAction(DEAD);
}

void Dead::execute( Sprite* sprite )
{
	if (sprite->type == MONSTER)
	{
		if (sprite->armature->getAnimation()->getIsPlaying() == false)
		{
			/*vector<Monster*>& monsterVector = TianXiaDiYi::getTheOnlyInstance()->mainCityScene->monsterVector;

			for (int i = 0; i < monsterVector.size(); i++)
			{
				if (sprite == (Sprite*)monsterVector[i])
				{
					TianXiaDiYi::getTheOnlyInstance()->mainCityScene->removeChild(monsterVector[i]->armature, true);
					TianXiaDiYi::getTheOnlyInstance()->mainCityScene->removeChild(monsterVector[i]->positionLabel, true);
					monsterVector.erase(monsterVector.begin()+i);
				}
			}*/
		}
	}
}

void Dead::exit( Sprite* sprite )
{
}