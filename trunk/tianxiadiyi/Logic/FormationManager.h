#ifndef _FORMATION_MANAGER_H__
#define _FORMATION_MANAGER_H__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Formation.h"
#include "Sprite\General.h"
#include "GeneralManager.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace std;

struct GeneralSprite
{
	General* general;
	CCSprite* sprite;
	bool isFormation;
	int i;
	int j;
};

class FormationManager
{
public:
	// 阵型列表
	vector<Formation*> formationVector;

	// 将领列表
	vector<General*>generalVector;

	// 阵型将领数组
	GeneralSprite generalSpriteArray[3][3];

	// 前一个选择的阵型
	int selectPreId;

	// 选择的阵型
	int selectId;

	// 将领当前页数
	int pageNum;

	// 将领最大页数
	int maxPageNum;

	FormationManager();
	~FormationManager();
	static FormationManager* getTheOnlyInstance();
};

extern bool formationArrary[11][3][3];

#endif