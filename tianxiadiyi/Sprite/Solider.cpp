#include "Solider.h"

Solider::Solider( int id ) : Monster(SOLDIER)
{
	const tDataBase* soliderTab = CDataBaseSystem::GetMe()->GetDataBase(DBC_SOLIDER);
	const _DBC_SOLIDER* solider = (_DBC_SOLIDER*)soliderTab->Search_Index_EQU(id);

	attribute = *solider;
}

Solider::~Solider()
{
}

void Solider::creatArmature()
{
	const char* imagePath = CCString::createWithFormat("%s0.png", attribute.dongHua)->getCString();;
	const char* plistPath = CCString::createWithFormat("%s0.plist", attribute.dongHua)->getCString();;
	const char* configFilePath = CCString::createWithFormat("%s.ExportJson", attribute.dongHua)->getCString();

	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(imagePath, plistPath, configFilePath);
	armature = CCArmature::create(attribute.dongHua);
}
