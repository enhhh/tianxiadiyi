#ifndef __Player__
#define __Player__

#include <vector>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Sprite.h"
#include "General.h"
#include "Network\UUPacketEXT.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace std;

class Player : public Sprite
{
public:
	Player();
	~Player();

	int guid;
	
	// �ȼ�
	int level;

	// ����
	int wuLi;

	// ����
	int zhiLi;

	// ����
	int tiLi;

	// ����
	int minJie;

	// ŭ��
	int nuQi;

	// ����
	int baoJi;

	// ����
	int shanBi;

	// ʶ��
	int shiPo;

	// ����
	int mingZhong;

	// ��
	int geDang;

	// �����˺�
	int baoJiShangHai;

	void updateEXT(float delta);
};

#endif
