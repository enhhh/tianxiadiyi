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

struct CountryMember
{
	// ���id
	int id;
	// �������
	char* name;
	// ְ��
	int job;
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
	string* name;
	// ��������
	int onlineNum;
	// ������
	int totalNum;
	// ����
	string* notice;

	// ��Ա
	vector<CountryMember>countryMemberVector;

	// ѡ�е�ǰ��
	int selectId;

	CountryManager();
	~CountryManager();

	static CountryManager* getTheOnlyInstance();

	void verify();
	void modify();
	void appointment();
	void quit();
	void kick();
};

#endif