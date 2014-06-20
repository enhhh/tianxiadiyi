#include "CountryManager.h"

#include "tinytab\DataBase.h"
#include "tinytab\DBC_Struct.h"

static CountryManager* countryManager = NULL;

CountryManager::CountryManager()
{
	// ����
	name = "���µ�һ";
	// ��������
	onlineNum = 1;
	// ������
	totalNum = 1;
	// �ȼ�
	lv = 1;
	// ����
	exp = 1;
	// ����
	notice = "�����µ�һ������ ��һ����Ƽ����޹�˾ �����з��Ĺ�װ������涯�������Ρ���Ϸ���������ڸ񶷣����ֲ������ڸ񶷣����Ը���Ϸ��������Ϊ���ģ������С��罻��һ����ۺ������Ρ���Ϸ���ȡ�����������ƣ����ܳɵ��ݣ���С����������ָ�����������ơ����µ�һ������ϷĿ�������ں��������Ļ��������й����ֲ�ҵ��ȫ������ \"���µ�һ\" �����Ρ�";

	// ���ҳ�Ա
	for (int i = 0; i < 20; i++)
	{
		CountryMember countryMember = {10086, "Ԭ��", 0, 1, 10086, 3, 7};
		countryMemberVector.push_back(countryMember);
	}

	// ���ҳ�Ա
	for (int i = 0; i < 20; i++)
	{
		VerifyMember rerifyMember = {10086, "Ԭ��", 27};
		verifyMemberVector.push_back(rerifyMember);
	}

	// ����������Ա
	for (int i = 0; i < 20; i++)
	{
		CountryRankMember countryRankMember = {1, "���µ�һ", "Ԭ��", 1, 1};
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