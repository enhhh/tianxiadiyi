#include "TianXiaDiYi.h"
#include "Packets\CGHeartBeat.h"
#include "Packets\Formation\CGFormationList.h"
#include "Packets\Formation\CGGeneralList.h"

#include "tinytab\DataBase.h"
#include "tinytab\DBC_Struct.h"

#include "tinyxml\tinystr.h"
#include "tinyxml\tinyxml.h"

static TianXiaDiYi* tianXiaDiYi = NULL;

TianXiaDiYi* TianXiaDiYi::getTheOnlyInstance()
{
	if (!tianXiaDiYi)
	{
		tianXiaDiYi = new TianXiaDiYi();
		tianXiaDiYi->init();
		tianXiaDiYi->autorelease();
	}

	return tianXiaDiYi;
}

CCScene* TianXiaDiYi::scene()
{
	CCScene* scene = CCScene::create();
	TianXiaDiYi* layer = TianXiaDiYi::getTheOnlyInstance();
	scene->addChild(layer);
	return scene;
}

bool TianXiaDiYi::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	CDataBaseSystem::GetMe()->Initial(NULL);

	// xml
	/*
	TiXmlDocument doc("xml/huLaoMap.xml");
	
	if (!doc.LoadFile())
	{
		return false;
	}

	TiXmlHandle hDoc(&doc);
	TiXmlElement* pElem;
	TiXmlHandle hRoot(0);
	pElem = hDoc.FirstChildElement().Element();

	// should always have a valid root but handle gracefully if it does
	if (!pElem) 
	{
		return false;
	}

	// save this for later
	hRoot = TiXmlHandle(pElem);
	pElem = hRoot.FirstChild( "name" ).Element();
	const char* name = pElem->GetText();

	pElem = hRoot.FirstChild( "xinFengBuDui" ).FirstChild().Element();

	for(pElem; pElem; pElem = pElem->NextSiblingElement())
	{
		int elem = 0;
		TiXmlElement* pSubElem = pElem->FirstChildElement()->FirstChildElement();

		for(pSubElem; pSubElem; pSubElem = pSubElem->NextSiblingElement())
		{
			const char* pKey = pSubElem->Value();
			const char* pText2 = pSubElem->GetText();
			elem++;
		}
	}
	*/

	socketWrap = UUCSocketWrap::getTheOnlyInstance();
	socketWrap->Init();
	socketWrap->CreateSocket();
	
	if (socketWrap->Connect("192.168.1.211", 1003))
	{
		socketWrap->SetStatusCode(UUCSocketWrap::WORK_NORMAL);
	}
	
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("audio\\TianXiaDiYi.mp3", true);
	playCgAction();

	mainCityScene = NULL;
	chapterScene = NULL;
	fightingScene = NULL;

	CGFormationList formationList;
	formationList.playerGuid = 4528;
	socketWrap->SendPacket(&formationList);

	CGGeneralList generalList;
	generalList.playerGuid = 4528;
	socketWrap->SendPacket(&generalList);

	setKeypadEnabled(true);
	scheduleUpdate();

	return true;
}

void TianXiaDiYi::draw()
{
}

void TianXiaDiYi::update( float delta )
{
	static long long lastTime = getCurrentTime();
	long long nowTime = getCurrentTime();
	int time = nowTime - lastTime;
	
	if (time >= 25 * 1000)
	{
		lastTime = getCurrentTime();
		CGHeartBeat heartBeat;
		heartBeat.heartBeat1 = 8;
		socketWrap->SendPacket(&heartBeat);
	}

	socketWrap->Tick();

	if (mainCityScene != NULL)
	{
		mainCityScene->updateEXT(delta);
	}

	if (chapterScene != NULL)
	{
		chapterScene->updateEXT(delta);
	}

	if (fightingScene != NULL)
	{
		fightingScene->updateEXT(delta);
	}
}

bool TianXiaDiYi::ccTouchBegan( CCTouch* pTouch, CCEvent* event )
{
	return true;
}

void TianXiaDiYi::ccTouchMoved( CCTouch* pTouch, CCEvent* event )
{

}

void TianXiaDiYi::ccTouchEnded( CCTouch* pTouch, CCEvent* event )
{

}

void TianXiaDiYi::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
}

void TianXiaDiYi::onEnter()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
	CCLayer::onEnter();
}

void TianXiaDiYi::onExit()
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
}

void TianXiaDiYi::setSceneType(int type)
{
	this->sceneType = sceneType;
}

long long TianXiaDiYi::getCurrentTime()
{
	struct cc_timeval now;
	CCTime::gettimeofdayCocos2d(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

CCAnimation* animation;
CCAnimate* animate;
CCSequence* sequence;
CCRepeat* repeat;

void TianXiaDiYi::playCgAction()
{
	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("TianXiaDiYiCg.png");
	CCSpriteFrame* frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(0, 0, texture->getPixelsWide(), texture->getPixelsHigh()));
	cgAction = CCSprite::createWithSpriteFrame(frame);
	cgAction->retain();
	cgAction->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
	addChild(cgAction);
	CCActionInterval* actionBy = CCSkewBy::create(2, 0.0f, -180.0f);
	CCSequence*  sequence = CCSequence::create(actionBy, NULL);
	cgAction->runAction(CCSequence::create(sequence, CCCallFuncN::create(this, callfuncN_selector(TianXiaDiYi::playCgActionCallback)), NULL));
}

void TianXiaDiYi::playCgActionCallback( CCNode* pSender )
{
	CCTexture2D* tianTexture = CCTextureCache::sharedTextureCache()->addImage("Tian.png");
	CCSpriteFrame* tianFrame = CCSpriteFrame::createWithTexture(tianTexture, CCRectMake(0, 0, tianTexture->getPixelsWide(), tianTexture->getPixelsHigh()));
	tianAction = CCSprite::createWithSpriteFrame(tianFrame);
	tianAction->retain();
	tianAction->setPosition(ccp(visibleSize.width/2, visibleSize.height));
	tianAction->setFlipX(true);
	CCActionInterval* tianActionTo = CCMoveTo::create(0.5, ccp(visibleSize.width/2, visibleSize.height/2 + 1.5 * tianTexture->getPixelsHigh()));
	CCActionInterval* tianActionRotate = CCRotateTo::create(0.25, 0, 180);
	CCSequence*  sequence = CCSequence::create(tianActionTo, tianActionRotate, NULL);
	tianAction->runAction(CCSequence::create(sequence, CCCallFuncN::create(this, callfuncN_selector(TianXiaDiYi::tianActionCallback)), NULL));
	addChild(tianAction);
}

void TianXiaDiYi::tianActionCallback( CCNode* pSender )
{
	CCTexture2D* xiaTexture = CCTextureCache::sharedTextureCache()->addImage("Xia.png");
	CCSpriteFrame* xiaFrame = CCSpriteFrame::createWithTexture(xiaTexture, CCRectMake(0, 0, xiaTexture->getPixelsWide(), xiaTexture->getPixelsHigh()));
	xiaAction = CCSprite::createWithSpriteFrame(xiaFrame);
	xiaAction->retain();
	xiaAction->setPosition(ccp(visibleSize.width/2 - visibleSize.width/3, visibleSize.height/2 + xiaTexture->getPixelsHigh()));
	CCActionInterval* xiaActionTo = CCMoveTo::create(0.5, ccp(visibleSize.width/2, visibleSize.height/2 + 0.5 * xiaTexture->getPixelsHigh()));
	CCSequence* sequence = CCSequence::create(xiaActionTo, NULL);
	xiaAction->runAction(CCSequence::create(sequence, CCCallFuncN::create(this, callfuncN_selector(TianXiaDiYi::xiaActionCallback)), NULL));
	addChild(xiaAction);
}

void TianXiaDiYi::xiaActionCallback( CCNode* pSender )
{
	CCTexture2D* diTexture = CCTextureCache::sharedTextureCache()->addImage("Di.png");
	CCSpriteFrame* diFrame = CCSpriteFrame::createWithTexture(diTexture, CCRectMake(0, 0, diTexture->getPixelsWide(), diTexture->getPixelsHigh()));
	diAction = CCSprite::createWithSpriteFrame(diFrame);
	diAction->retain();
	diAction->setPosition(ccp(visibleSize.width/2 + visibleSize.width/3,  visibleSize.height/2 - diTexture->getPixelsHigh()));
	CCActionInterval* diActionTo = CCMoveTo::create(0.5, ccp(visibleSize.width/2, visibleSize.height/2 - 0.5 * diTexture->getPixelsHigh()));
	CCSequence* sequence = CCSequence::create(diActionTo, NULL);
	diAction->runAction(CCSequence::create(sequence, CCCallFuncN::create(this, callfuncN_selector(TianXiaDiYi::diActionCallback)), NULL));
	addChild(diAction);
}

void TianXiaDiYi::diActionCallback( CCNode* pSender )
{
	CCTexture2D* yiTexture = CCTextureCache::sharedTextureCache()->addImage("Yi.png");
	CCSpriteFrame* yiFrame = CCSpriteFrame::createWithTexture(yiTexture, CCRectMake(0, 0, yiTexture->getPixelsWide(), yiTexture->getPixelsHigh()));
	yiAction = CCSprite::createWithSpriteFrame(yiFrame);
	yiAction->retain();
	yiAction->setPosition(ccp(visibleSize.width/2, 0));
	yiAction->setFlipX(true);
	CCActionInterval* yiActionRotate = CCRotateBy::create(0.25, 0, 180);
	CCActionInterval* yiActionTo = CCMoveTo::create(0.5, ccp(visibleSize.width/2,  visibleSize.height/2 - 1.5 * yiTexture->getPixelsHigh()));
	CCActionInterval* yiActionRotate2 = CCRotateTo::create(1, 0, 180);
	CCSequence* sequence = CCSequence::create(yiActionRotate, yiActionTo, yiActionRotate2, NULL);
	yiAction->runAction(CCSequence::create(sequence, CCCallFuncN::create(this, callfuncN_selector(TianXiaDiYi::yiActionCallback)), NULL));
	addChild(yiAction);
}

void TianXiaDiYi::yiActionCallback( CCNode* pSender )
{
	cgAction->setVisible(false);
	tianAction->setVisible(false);
	xiaAction->setVisible(false);
	diAction->setVisible(false);
	yiAction->setVisible(false);

	mainCityScene = MainCityScene::create();
	mainCityScene->retain();
	addChild(mainCityScene);

	uiMainCity = UIMainCity::create();
	addChild(uiMainCity);

	uiMainCity->setVisible(true);
}
