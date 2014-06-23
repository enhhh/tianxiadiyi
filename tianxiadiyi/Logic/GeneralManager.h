#ifndef __GENERAL_MANAGER_H__
#define __GENERAL_MANAGER_H__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Sprite\General.h"
#include "Logic\ItemManager.h"

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
	GENERAL_ZUO_JI
};

struct GeneralItem
{
	int id;
	Equipment* equipment;
};

struct ItemSprite
{
	GeneralItem generalItem;
	CCSprite* sprite;
};

class GeneralManager
{
public:

	ItemManager* itemManager;

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

	GeneralItem* generalItemArray;

	ItemSprite itemSpriteArray[9];

	// ѡ�����Ʒ
	int selectItemId;

	// ��Ʒ��ǰҳ��
	int itemPageNum;

	// ��Ʒ���ҳ��
	int itemMaxPageNum;

	GeneralManager();
	~GeneralManager();

	static GeneralManager* getTheOnlyInstance();
	void addAttribute(int type);
};

#endif