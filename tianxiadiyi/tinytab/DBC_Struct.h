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
	// 武器种类
	int wuQiZhongLei;
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
	// 属性值	
	float shuXingZhi;
	// 等级
	int dengJi;
	// 开启等级	
	int kaiQiJiShu;
	// 动画
	char* dongHua;
};
