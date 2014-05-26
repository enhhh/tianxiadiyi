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
	
	// 等级
	int level;

	// 武力
	int wuLi;

	// 智力
	int zhiLi;

	// 体力
	int tiLi;

	// 敏捷
	int minJie;

	// 怒气
	int nuQi;

	// 暴击
	int baoJi;

	// 闪避
	int shanBi;

	// 识破
	int shiPo;

	// 命中
	int mingZhong;

	// 格档
	int geDang;

	// 暴击伤害
	int baoJiShangHai;

	void updateEXT(float delta);
};

#endif
