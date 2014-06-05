#pragma once

#include "BaseType.h"

#define DBC_GENERAL 1
struct _DBC_GENERAL
{
	// 编号	
	int id;
	// 姓名
	char* name;
	// 职业
	int zhiYe;
	// 职业名称
	char* zhiYeMingCheng;
	// 攻击属性
	int gongJiShuXing;
	// 姓别
	int xingBie;
	// 武力
	int	wuLi;
	// 智力
	int	zhiLi;
	// 体力
	int	tiLi;
	// 速度
	int	minJie;
	// 星级
	float xingJi;
	// 暴击率
	float BaoJiLv;
	// 格挡率
	float geDangLv;
	// 闪避率
	float shanBiLv;
	// 命中率
	float mingZhongLv;
	// 识破率
	float shiPoLv;
	// 暴击伤害
	int baoJiShangHai;
	// 天赋
	char* tianFu;
	// 技能
	char* JiNeng;
	// 头像
	char* tuPian;
	// 动画
	char* dongHua;
};

#define DBC_SOLIDER 2
struct _DBC_SOLIDER
{
	// 编号
	int id;
	// 姓名
	char* name;
	// 攻击
	int gongJi;
	// 生命
	int shengMing;
	// 动画
	char* dongHua;
};

#define DBC_FORMATION 3
struct _DBC_FORMATION
{
	// 编号
	int id;
	// 姓名
	char* name;
	// 图片
	char* tuPian;
};

#define DBC_EQUIPMENT 4
struct _DBC_EQUIPMENT
{
	// 编号
	int id;
	// 名字
	char* name;
	// 种类名称
	char* zhongLeiMingCheng;
	// 种类
	int zhongLei;
	// 开启级数
	int kaiQiJiShu;
	// 强化等级
	int qiangHuaDengJi;
	// 职业需求
	char* zhiYeXuQiu;
	// 性别
	int xingBie;
	// 初始点数 
	int chuShiDianShu;
	// 图片
	char* tuPian;
	// 描述
	char* miaoShu;
};

#define DBC_SKILL 5
struct _DBC_SKILL
{
	// 编号
	int id;
	// 名字
	char* name;
};

#define DBC_GEM 6
struct _DBC_GEM
{
	// 编号
	int id;
	// 名称
	int name;
	// 种类
	int zhongLei;
	// 图片
	char* tuPian;
};

#define DBC_SOUL_BEAD 7
struct _DBC_SOUL_BEAD 
{
	// 编号	
	int id;
	// 名称	
	char* name;
	// 种类
	int zhongLei;
	// 属性值	
	float shuXingZhi;
	// 等级
	int dengJi;
	// 开启等级	
	int kaiQiJiShu;
	// 动画
	char* dongHua;
};

#define DBC_RIDE 8
struct _DBC_RIDE
{
	// 编号	
	int id;
	// 名字
	const char* name;
	// 图片
	const char* tuPian;
	// 星级	
	int xingJi;
	// 初始攻击
	int chuShiGongJi;
	// 初始防御
	int chuShiFangYu;
	// 初始生命
	int chuShiShengMing;
};

#define DBC_TELENT 9

struct _DBC_TELENT
{
	// 编号	
	int id;
	// 名称	
	char* name;
	// 加成属性	
	char* jiaChengShuXing;
	// 第一个点
	int diYiGeDian;
	// 第二个点
	int diErGeDian;
	// 第三个点
	int diSanGeDian;
	// 第四个点
	int diSiGeDian;
	// 第五个点
	int diWuGeDian;
	// 第六个点
	int diLiuGeDian;
	// 第七个点
	int diQiGeDian;
	// 第八个点
	int diBaGeDian;
	// 第九个点
	int diJiuGeDian;
	// 第十个点
	int diShiGeDian;
	// 第十一个点
	int diShiYiGeDian;
	// 第十二个点
	int diShiErGeDian;
	// 第十三个点
	int diShiSanGeDian;
	// 第十四个点
	int diShiSiGeDian;
	// 第十五个点
	int diShiWuGeDian;
	// 第十六个点
	int diShiLiuGeDian;
	// 第十七个点
	int diShiQiGeDian;
	// 第十八个点
	int diShiBaGeDian;
	// 第十九个点
	int diShiJiuGeDian;
	// 第二十个点
	int	diErShiGeDian;
};