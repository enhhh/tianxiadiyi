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
	// 国家等级
	int lv;
	// 国家名称
	char* name;
	// 国家君主
	char* zhenMingTianZi;
	// 人数
	int num;
	// 排名
	int rank;
};

struct VerifyMember
{
	// 玩家id
	int id;
	// 玩家名称
	char* name;
	// 等级
	int lv;
};

struct CountryMember
{
	// 玩家id
	int id;
	// 玩家名称
	char* name;
	// 职务
	int job;
	// 等级
	int lv;
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
	char* name;
	// 在线人数
	int onlineNum;
	// 总人数
	int totalNum;
	// 等级
	int lv;
	// 经验
	int exp;
	// 公告
	char* notice;

	// 国家成员
	vector<CountryMember>countryMemberVector;
	// 审核成员
	vector<VerifyMember>verifyMemberVector;
	// 国家排名成员
	vector<CountryRankMember>countryRankMemberVector;

	// 选中当前项
	int selectId;
	// 选中审核成员
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