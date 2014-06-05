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
	// 玩家id
	int id;
	// 玩家名称
	char* name;
	// 职务
	int job;
	// 贡献度
	int contribute;
	// 在线小时
	int hour;
	// 在线分钟
	int minute;
};

class CountryManager
{
public:
	// 国号
	string* name;
	// 在线人数
	int onlineNum;
	// 总人数
	int totalNum;
	// 公告
	string* notice;

	// 成员
	vector<CountryMember>countryMemberVector;

	// 选中当前项
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