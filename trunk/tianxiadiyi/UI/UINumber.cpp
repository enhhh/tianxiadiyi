#include "UINumber.h"
#include "..\TianXiaDiYi.h"

static UINumber* uiNumber = NULL;

UINumber::UINumber()
{
}

UINumber::~UINumber()
{
}

UINumber* UINumber::getTheOnlyInstance()
{
	if (!uiNumber)
	{
		uiNumber = UINumber::create();
		uiNumber->setVisible(false);
	}

	return uiNumber;
}

CCSprite* UINumber::getNumber(int num)
{
	char mumber[100] = {0};
	
	sprintf(mumber,"%d", num);
	CCString* numberCCString = CCString::create(mumber);
	string numberString = numberCCString->getCString();

	CCSprite* numberImage = CCSprite::create("ui/number.png");
	float numberImageWidth = numberImage->getContentSize().width;
	float numberImageHeight = numberImage->getContentSize().height;

	float wight = numberImageWidth / 11;
	float height = numberImageHeight;

	CCRect negativeRect = CCRect(0, 0, wight, height);
	CCSprite* numbersSprite = CCSprite::create("ui/number.png", negativeRect);

	for (int i = 0; i < numberCCString->length(); i++)
	{
		string singleNumber =  numberString.substr(0+i, 1);
		CCString* CCSingleNumber = CCString::create(singleNumber);
		CCRect numberRect = CCRect(wight*CCSingleNumber->intValue()+wight,0, wight, height);
		CCSprite* numberSprite = CCSprite::create("ui/number.png", numberRect);
		numberSprite->setPosition(ccp(numbersSprite->getContentSize().width+numbersSprite->getContentSize().width*i, numbersSprite->getContentSize().height/2));
		numbersSprite->addChild(numberSprite, 1, i);
	}

	return numbersSprite;
}

CCSprite* UINumber::floatNumber(int num, float x, float y, float w, float h)
{
	char mumber[100] = {0};

	sprintf(mumber, "%d", num);
	CCString* numberCCString = CCString::create(mumber);
	CCSprite* numbersSprite = getNumber(num);

	numbersSprite->setPosition(ccp(x, y));

	CCActionInterval* scaleBy = CCScaleBy::create(1.0f, 1.5f);
	numbersSprite->runAction(CCSequence::create(scaleBy, scaleBy->reverse(), NULL));

	CCActionInterval* fadeOut = CCFadeOut::create(1.0f);

	numbersSprite->runAction(fadeOut);

	CCActionInterval* fadeIn = CCFadeIn::create(1.0f);

	for (int i = 0; i < numberCCString->length(); i++)
	{
		CCActionInterval* actionInterval = fadeIn->reverse();
		numbersSprite->getChildByTag(i)->runAction(actionInterval);    
	}

	ccBezierConfig bezier;
	bezier.controlPoint_1 = CCPointMake(x+50, y+h*1.5);
	bezier.controlPoint_2 = CCPointMake(x+60, y+h);

	CCActionInterval* bezierTo = CCBezierTo::create(2.5f, bezier);
	CCFiniteTimeAction* floatNumberAction = CCCallFuncO::create(NULL, callfuncO_selector(UINumber::floatNumberCallback), NULL);
	numbersSprite->runAction(CCSequence::create(bezierTo, floatNumberAction,NULL));

	return numbersSprite;
}

void UINumber::floatNumberCallback(CCObject* object)
{
}