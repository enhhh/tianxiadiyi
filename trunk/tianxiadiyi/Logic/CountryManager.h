#ifndef __COUNTRY_MANAGER_H__
#define __COUNTRY_MANAGER_H__

#include <vector>
#include <string>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace std;

struct CountryRankMember
{
	// ���ҵȼ�
	int lv;
	// ��������
	char* name;
	// ���Ҿ���
	char* zhenMingTianZi;
	// ����
	int num;
	// ����
	int rank;
};

struct VerifyMember
{
	// ���id
	int id;
	// �������
	char* name;
	// �ȼ�
	int lv;
};

struct CountryMember
{
	// ���id
	int id;
	// �������
	char* name;
	// ְ��
	int job;
	// �ȼ�
	int lv;
	// ���׶�
	int contribute;
	// ����Сʱ
	int hour;
	// ���߷���
	int minute;
};

class CountryManager
{
public:
	// ����
	char* name;
	// ��������
	int onlineNum;
	// ������
	int totalNum;
	// �ȼ�
	int lv;
	// ����
	int exp;
	// ����
	char* notice;

	// ���ҳ�Ա
	vector<CountryMember>countryMemberVector;
	// ��˳�Ա
	vector<VerifyMember>verifyMemberVector;
	// ����������Ա
	vector<CountryRankMember>countryRankMemberVector;

	// ѡ�е�ǰ��
	int selectId;
	// ѡ����˳�Ա
	int selectVerifyId;

	CountryManager();
	~CountryManager();

	static CountryManager* getTheOnlyInstance();
	char* getJobName(int job);

	void verify();
	void modify();
	void appointment();
	void quit();
	void kick();
};

#endif