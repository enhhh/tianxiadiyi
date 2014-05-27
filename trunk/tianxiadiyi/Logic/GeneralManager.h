#ifndef __GENERAL_MANAGER_H__
#define __GENERAL_MANAGER_H__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Sprite\General.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace std;

// ���������������顢���ס����硢����
enum General_EQUIPMENT_TYPE
{
	GENERAL_WU_QI = 0,
	GENERAL_BING_FU,
	GENERAL_BING_SHU,
	GENERAL_KAI_JIA,
	GENERAL_PI_FENG,
	ZUO_JI
};

class GeneralManager
{
public:

	// �����б�
	vector<General*>generalVector;
	
	// ѡ��Ľ���
	int selectGeneralId;

	// ѡ���װ��
	int selectEquipmentId;

	// ���쵱ǰҳ��
	int pageNum;

	// �������ҳ��
	int maxPageNum;

	GeneralManager();
	~GeneralManager();

	static GeneralManager* getTheOnlyInstance();
};

#endif