#include "Effect.h"
#include "AI\States.h"
#include "AI\SpriteStates.h"

Effect::Effect()
{
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("FenNuYiJiEffect0.png", "FenNuYiJiEffect0.plist", "FenNuYiJiEffect.ExportJson");;
	armature = CCArmature::create("FenNuYiJiEffect");
}

Effect::~Effect()
{
}

void Effect::updateEXT(float delta)
{
}
