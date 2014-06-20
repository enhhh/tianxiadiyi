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
	// �����б�
	vector<Formation*> formationVector;

	// �����б�
	vector<General*>generalVector;

	// ���ͽ�������
	GeneralSprite generalSpriteArray[3][3];

	// ǰһ��ѡ�������
	int selectPreId;

	// ѡ�������
	int selectId;

	// ���쵱ǰҳ��
	int pageNum;

	// �������ҳ��
	int maxPageNum;

	FormationManager();
	~FormationManager();
	static FormationManager* getTheOnlyInstance();
};

extern bool formationArrary[11][3][3];

#endif