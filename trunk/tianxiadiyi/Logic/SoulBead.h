#ifndef __SOUL_BEAD_H__
#define __SOUL_BEAD_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "Item.h"

#include "tinytab\DataBase.h"
#include "tinytab\DBC_Struct.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

enum SOUL_BEAD_TYPE
{
	WU_LI_SOUL_BEAD = 1,
	ZHI_LI_SOUL_BEAD = 2,
	TI_LI_SOUL_BEAD = 3,
	NU_QI_SOUL_BEAD = 4,
	BAO_JI_SOUL_BEAD = 5,
	SHAN_BI_SOUL_BEAD = 6,
	SHI_PO_SOUL_BEAD = 7,
	MING_ZHONG_SOUL_BEAD = 8,
	GE_DANG_SOUL_BEAD = 9,
	BAO_JI_SHANG_HAI_SOUL_BEAD = 10,
};

class SoulBead : public Item
{
public:
	// ªÍ÷È∂Øª≠
	CCArmature* armature;
	_DBC_SOUL_BEAD attribute;

	SoulBead(int id);
	~SoulBead();
};

#endif