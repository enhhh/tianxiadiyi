#include "Effect.h"
#include "AI\States.h"
#include "AI\SpriteStates.h"

Effect::Effect(int type)
{
	switch (type)
	{
	case QIAN_JUN_PO:
		CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("QianJunPoEffect0.png", "QianJunPoEffect0.plist", "QianJunPoEffect.ExportJson");;
		armature = CCArmature::create("QianJunPoEffect");
		break;
	case LI_ZHAN:
		CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("LiZhanEffect0.png", "LiZhanEffect0.plist", "LiZhanEffect.ExportJson");;
		armature = CCArmature::create("LiZhanEffect");
		break;
	case FEN_NU_YI_JI:
		CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("FenNuYiJiEffect0.png", "FenNuYiJiEffect0.plist", "FenNuYiJiEffect.ExportJson");;
		armature = CCArmature::create("FenNuYiJiEffect");
		break;
	}
}

Effect::~Effect()
{
}

void Effect::updateEXT(float delta)
{
}
