/*�ļ����ƣ�
**�����������׽������ݻ�����
**�ļ�˵����
**��    �ߣ�uutc
**����ʱ�䣺
**��    �ģ�2013-05-06
*/

#ifndef _UUSTREAMBUFFER_H_
#define _UUSTREAMBUFFER_H_

#include "UUCommonType.h"


#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

class UUCSocketWrap;

const int UNIT_LENGTH = 1024*4;				//��������Ԫ����
//extern "C" {
/************************************************************************/
// �������
/************************************************************************/
class UUCOutputStream
{
	enum
	{
		DEFAULT_BUFF_SIZE  = UNIT_LENGTH,		//Ĭ�ϻ�������С
		MAX_BUFF_SIZE	   = UNIT_LENGTH*32,	//��󻺳�����С
		BUFF_SIZE_INC_STEP = UNIT_LENGTH,		//��������С��������
	};
public:
	UUCOutputStream(UUCSocketWrap* pSocket, int iLen=DEFAULT_BUFF_SIZE, int iMaxLen=MAX_BUFF_SIZE);
	~UUCOutputStream();
public:
	// дBuff������д���������
	int				WriteBuff(const char* pBuf, int iLen);
	// ˢBuff���������ݣ�����ʵ�ʷ�����
	int				FlushBuff();
	// ����Buffֵ
	void			SetBuffSize(int iSize);
	// ����Buff���ֵ
	void			SetBuffMaxSize(int iSize);
	// ��ȡBuff���ֵ
	int				GetBuffMaxSize() const;
	// ��ȡBuffʹ�ô�С
	int				GetBuffUsedSize() const;
	// ����Ĭ�ϴ�С
	bool			SetBuffDefaultSize(int iSize);
	// ��λ
	void			Reset();
protected:
	// ������������С
	bool			__Resize(int iNeed);
	// ��ȡռ����Ŀ
	int				__GetUsedCount() const;
	// ��ȡ������Ŀ
	int				__GetFreeCount() const;
private:
	char*			m_pBuf;					//�������ݻ�����
	int				m_iLen;					//buff����
	int				m_iMaxLen;				//buff���������󳤶�
	int				m_iHead;				//ͷָ��
	int				m_iTail;				//βָ��
	UUCSocketWrap*	m_pSocket;				//�����׽��ְ�װ
};

// ��������
class UUCInputStream
{
	enum
	{
		DEFAULT_BUFF_SIZE  = UNIT_LENGTH,		//Ĭ�ϻ�������С
		MAX_BUFF_SIZE	   = UNIT_LENGTH*32,	//��󻺳�����С
		BUFF_SIZE_INC_STEP = UNIT_LENGTH,		//��������С��������
		SINGLE_RECV_LEN	   = 1024,				//���ν������ݳ���
	};
public:
	UUCInputStream(UUCSocketWrap* pSocket, int iLen=DEFAULT_BUFF_SIZE, int iMaxLen=MAX_BUFF_SIZE);
	~UUCInputStream();
public:
	// ��λ����
	void			Reset();
	// ��Buff�����ض�ȡ��������
	int				ReadBuff(char* pBuf, int iLen);
	// ���Buff����ȡ���ݣ�������ȡ��
	int				FillBuff();
	// ��Buff�������α�
	bool			Peek(char* pBuf, int iLen) const;
	// ���Buff
	bool			CheckSize(int iCheckSize) const;
	// �ƶ��α�
	void			Skip(int iOffset);
	// ����Buffֵ
	void			SetBuffSize(int iSize);
	// ����Buff���ֵ
	void			SetBuffMaxSize(int iSize);
	// ��ȡBuff���ֵ
	int				GetBuffMaxSize() const;
	// ��ȡBuffʹ��
	int				GetBuffUsedSize() const;
	// ����Ĭ�ϴ�С
	bool			SetBuffDefaultSize(int iSize);
protected:
	// ������������С
	bool			__Resize(int iNeed);
	// ��ȡռ����Ŀ
	int				__GetUsedCount() const;
	// ��ȡ������Ŀ
	int				__GetFreeCount() const;
private:
	char*			m_pBuf;					//�������ݻ�����
	int				m_iLen;					//Buff����
	int				m_iMaxLen;				//���Buffer����
	int				m_iHead;				//ͷָ��
	int				m_iTail;				//βָ��
	UUCSocketWrap*	m_pSocket;				//�����׽��ְ�װ
};
//}

#endif

