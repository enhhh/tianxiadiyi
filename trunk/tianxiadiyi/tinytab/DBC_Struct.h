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
	int gongJi;
	// ����
	int shengMing;
	// ����
	char* dongHua;
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
	int wuQiZhongLei;
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
	int name;
	// ͼƬ
	char* tuPian;
};

#define DBC_SOUL_BEAD 7
struct _DBC_SOUL_BEAD 
{
	// ���	
	int id;
	// ����	
	char* name;
	// ����ֵ	
	float shuXingZhi;
	// �ȼ�
	int dengJi;
	// �����ȼ�	
	int kaiQiJiShu;
	// ����
	char* dongHua;
};
