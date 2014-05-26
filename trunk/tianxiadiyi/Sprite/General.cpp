#include "General.h"
#include "Monster.h"

General::General( int id ) : Monster(GENERAL)
{
	const tDataBase* generalTab = CDataBaseSystem::GetMe()->GetDataBase(DBC_GENERAL);
	const _DBC_GENERAL* general = (_DBC_GENERAL*)generalTab->Search_Index_EQU(id);
	attribute = *general;

	wuLiGongJi = 6 * attribute.wuLi;
	wuLiFangYu = 5 * attribute.wuLi;
	faShuGongJi = 0 * attribute.zhiLi;
	faShuFangYu = 6 * attribute.zhiLi;
	hp = 10 * attribute.tiLi;



	isFormation = false;
}

General::~General()
{
}

void General::creatArmature()
{
	const char* imagePath = CCString::createWithFormat("%s0.png", attribute.dongHua)->getCString();;
	const char* plistPath = CCString::createWithFormat("%s0.plist", attribute.dongHua)->getCString();;
	const char* configFilePath = CCString::createWithFormat("%s.ExportJson", attribute.dongHua)->getCString();

	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(imagePath, plistPath, configFilePath);
	armature = CCArmature::create(attribute.dongHua);
}
