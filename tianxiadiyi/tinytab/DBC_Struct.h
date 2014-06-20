#pragma once

#include "BaseType.h"

#define DBC_GENERAL 1
struct _DBC_GENERAL
{
	// ���	
	int id;
	// ����
	char* name;
	// ְҵ
	int zhiYe;
	// ְҵ����
	char* zhiYeMingCheng;
	// ��������
	int gongJiShuXing;
	// �ձ�
	int xingBie;
	// ����
	int	wuLi;
	// ����
	int	zhiLi;
	// ����
	int	tiLi;
	// �ٶ�
	int	minJie;
	// �Ǽ�
	float xingJi;
	// ������
	float BaoJiLv;
	// ����
	float geDangLv;
	// ������
	float shanBiLv;
	// ������
	float mingZhongLv;
	// ʶ����
	float shiPoLv;
	// �����˺�
	int baoJiShangHai;
	// �츳
	char* tianFu;
	// ����
	char* JiNeng;
	// ������Ч 
	char* jiNengTeXiao;
	// ͷ��
	char* tuPian;
	// ����
	char* dongHua;
};

#define DBC_SOLIDER 2
struct _DBC_SOLIDER
{
	// ���
	int id;
	// ����
	char* name;
	// ����
	char* dongHua;
	// ����
	int gongJi;
	// ����
	int shengMing;
	// ����
	int jieBie;
};

#define DBC_FORMATION 3
struct _DBC_FORMATION
{
	// ���
	int id;
	// ����
	char* name;
	// ͼƬ
	char* tuPian;
};

#define DBC_EQUIPMENT 4
struct _DBC_EQUIPMENT
{
	// ���
	int id;
	// ����
	char* name;
	// ��������
	char* zhongLeiMingCheng;
	// ����
	int zhongLei;
	// ��������
	int kaiQiJiShu;
	// ǿ���ȼ�
	int qiangHuaDengJi;
	// ְҵ����
	char* zhiYeXuQiu;
	// �Ա�
	int xingBie;
	// ��ʼ���� 
	int chuShiDianShu;
	// ͼƬ
	char* tuPian;
	// ����
	char* miaoShu;
	// �����۸�
	int maiChuJiaGe;
};

#define DBC_SKILL 5
struct _DBC_SKILL
{
	// ���
	int id;
	// ����
	char* name;
};

#define DBC_GEM 6
struct _DBC_GEM
{
	// ���
	int id;
	// ����
	char* name;
	// ����
	int zhongLei;
	// ͼƬ
	char* tuPian;
	// ����
	char* miaoShu;
	// �����۸�
	int maiChuJiaGe;
};

#define DBC_SOUL_BEAD 7
struct _DBC_SOUL_BEAD 
{
	// ���	
	int id;
	// ����	
	char* name;
	// ����
	int zhongLei;
	// ����ֵ	
	float shuXingZhi;
	// �ȼ�
	int dengJi;
	// �����ȼ�	
	int kaiQiJiShu;
	// ����
	char* dongHua;
};

#define DBC_RIDE 8
struct _DBC_RIDE
{
	// ���	
	int id;
	// ����
	const char* name;
	// ͼƬ
	const char* tuPian;
	// �Ǽ�	
	int xingJi;
	// ��ʼ����
	int chuShiGongJi;
	// ��ʼ����
	int chuShiFangYu;
	// ��ʼ����
	int chuShiShengMing;
};

#define DBC_TELENT 9

struct _DBC_TELENT
{
	// ���	
	int id;
	// ����	
	char* name;
	// �ӳ�����	
	char* jiaChengShuXing;
	// ��һ����
	int diYiGeDian;
	// �ڶ�����
	int diErGeDian;
	// ��������
	int diSanGeDian;
	// ���ĸ���
	int diSiGeDian;
	// �������
	int diWuGeDian;
	// ��������
	int diLiuGeDian;
	// ���߸���
	int diQiGeDian;
	// �ڰ˸���
	int diBaGeDian;
	// �ھŸ���
	int diJiuGeDian;
	// ��ʮ����
	int diShiGeDian;
	// ��ʮһ����
	int diShiYiGeDian;
	// ��ʮ������
	int diShiErGeDian;
	// ��ʮ������
	int diShiSanGeDian;
	// ��ʮ�ĸ���
	int diShiSiGeDian;
	// ��ʮ�����
	int diShiWuGeDian;
	// ��ʮ������
	int diShiLiuGeDian;
	// ��ʮ�߸���
	int diShiQiGeDian;
	// ��ʮ�˸���
	int diShiBaGeDian;
	// ��ʮ�Ÿ���
	int diShiJiuGeDian;
	// �ڶ�ʮ����
	int	diErShiGeDian;
};

#define DBC_GEM_STRENGTHEN 10
struct _DBC_GEM_STRENGTHEN
{
	// ���
	int id;
	// ����
	char* name;
	// �ӳ�����
	char* jiaChengShuXing;
	// һ������ֵ
	int yiJiShuXingZhi;
	// ��������ֵ
	int erJiShuXingZhi;
	// ��������ֵ
	int sanJiShuXingZhi;
	// �ļ�����ֵ
	int siJiShuXingZhi;
	// �弶����ֵ
	int wuJiShuXingZhi;
	// ��������ֵ
	int liuJiShuXingZhi;
	// �߼�����ֵ
	int qiJiShuXingZhi;
	// �˼�����ֵ
	int baJiShuXingZhi;
	// �ż�����ֵ
	int jiuJiShuXingZhi;
	// ʮ������ֵ
	int shiJiShuXingZhi;
};

#define DBC_ADVANCED 11
struct _DBC_ADVANCED
{
	// ���
	int id;
	// ����
	char* name;
	// �ȼ�
	int dengJi;
	// �ӳɵ���
	int jiaChengDianShu;
	// ����Ʒ
	char* xiaoHaoPin;
};

#define DBC_RIDE_STRENGTHEN_MANAGER 12
struct _DBC_RIDE_STRENGTHEN
{
	// ���
	int id;
	// ����
	char* name;
	// һ����ֵ
	char* yiJiShuZhi;
	// ������ֵ
	char* erJiShuZhi;
	// ������ֵ
	char* sanJiShuZhi;
	// �ļ���ֵ
	char* siJiShuZhi;
	// �弶��ֵ
	char* wuJiShuZhi;
	// ������ֵ
	char* liuJiShuZhi;
	// �߼���ֵ
	char* qiJiShuZhi;
	// �˼���ֵ
	char* baJiShuZhi;
	// �ż���ֵ
	char* jiuJiShuZhi;
	// ʮ����ֵ
	char* shiJiShuZhi;
};

#define DBC_OFFICIAL 13
struct _DBC_OFFICIAL
{
	// ���
	int id;
	// ����
	char* name;
	// ��������
	int gongXianXuQiu;
};

#define DBC_ROUND 14
struct _DBC_ROUND
{
	// ���
	int id;
	// ����
	char* name;
	// ����
	int fengMianGeneral;
	// ����
	char* army;
	// ��ͼ
	char* diTu;
};

#define DBC_SOLIDER_POSITION 15
struct _DBC_SOLIDER_POSITION
{
	// ���
	int id;
	// ��BOOSռλ
	char* wuBossZhanWei;
	// ��BOSSռλ
	char* youBossZhanWei;
};