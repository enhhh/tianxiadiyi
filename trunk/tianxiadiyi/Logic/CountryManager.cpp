#include "CountryManager.h"

#include "tinytab\DataBase.h"
#include "tinytab\DBC_Struct.h"

static CountryManager* countryManager = NULL;

CountryManager::CountryManager()
{
	// 国号
	name = "天下第一";
	// 在线人数
	onlineNum = 1;
	// 总人数
	totalNum = 1;
	// 等级
	lv = 1;
	// 经验
	exp = 1;
	// 公告
	notice = "《天下第一》是由 天一网络科技有限公司 自主研发的古装武侠横版动作格斗网游。游戏类型立足于格斗，但又不局限于格斗，是以格斗游戏（动作）为核心，集休闲、社交于一体的综合性网游。游戏题材取自于王晶监制，邓衍成导演，程小东担任武术指导的武侠巨制《天下第一》。游戏目标致力于弘扬民族文化，振兴中国娱乐产业，全力打造 \"天下第一\" 格斗网游。";

	// 国家成员
	for (int i = 0; i < 20; i++)
	{
		CountryMember countryMember = {10086, "袁林", 0, 1, 10086, 3, 7};
		countryMemberVector.push_back(countryMember);
	}

	// 国家成员
	for (int i = 0; i < 20; i++)
	{
		VerifyMember rerifyMember = {10086, "袁林", 27};
		verifyMemberVector.push_back(rerifyMember);
	}

	// 国家排名成员
	for (int i = 0; i < 20; i++)
	{
		CountryRankMember countryRankMember = {1, "天下第一", "袁林", 1, 1};
		countryRankMemberVector.push_back(countryRankMember);
	}

	selectId = 0;
	selectVerifyId = 0;
}

CountryManager::~CountryManager()
{
}

CountryManager* CountryManager::getTheOnlyInstance()
{
	if (!countryManager)
	{
		countryManager = new CountryManager();
	}

	return countryManager;
}


char* CountryManager::getJobName( int job )
{
	const tDataBase* officialTab = CDataBaseSystem::GetMe()->GetDataBase(DBC_OFFICIAL);
	const _DBC_OFFICIAL* official = (_DBC_OFFICIAL*)officialTab->Search_LineNum_EQU(job);

	return official->name;
}

void CountryManager::verify()
{
}

void CountryManager::modify()
{

}

void CountryManager::appointment()
{

}

void CountryManager::quit()
{

}

void CountryManager::kick()
{
	if (countryMemberVector.size() == 0)
	{
		return;
	}
	
	countryMemberVector.erase(countryMemberVector.begin()+selectId);
	selectId -= 1;

	if (selectId < 0)
	{
		selectId = 0;
	}
}