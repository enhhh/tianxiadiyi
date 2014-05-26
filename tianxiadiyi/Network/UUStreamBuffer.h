/*文件名称：
**功能描述：套接字数据缓冲类
**文件说明：
**作    者：uutc
**创建时间：
**修    改：2013-05-06
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

const int UNIT_LENGTH = 1024*4;				//缓冲区单元长度
//extern "C" {
/************************************************************************/
// 输出流类
/************************************************************************/
class UUCOutputStream
{
	enum
	{
		DEFAULT_BUFF_SIZE  = UNIT_LENGTH,		//默认缓冲区大小
		MAX_BUFF_SIZE	   = UNIT_LENGTH*32,	//最大缓冲区大小
		BUFF_SIZE_INC_STEP = UNIT_LENGTH,		//缓冲区大小调整步长
	};
public:
	UUCOutputStream(UUCSocketWrap* pSocket, int iLen=DEFAULT_BUFF_SIZE, int iMaxLen=MAX_BUFF_SIZE);
	~UUCOutputStream();
public:
	// 写Buff，返回写入的数据量
	int				WriteBuff(const char* pBuf, int iLen);
	// 刷Buff，发送数据，返回实际发生量
	int				FlushBuff();
	// 设置Buff值
	void			SetBuffSize(int iSize);
	// 设置Buff最大值
	void			SetBuffMaxSize(int iSize);
	// 获取Buff最大值
	int				GetBuffMaxSize() const;
	// 获取Buff使用大小
	int				GetBuffUsedSize() const;
	// 设置默认大小
	bool			SetBuffDefaultSize(int iSize);
	// 复位
	void			Reset();
protected:
	// 调整缓冲区大小
	bool			__Resize(int iNeed);
	// 获取占用数目
	int				__GetUsedCount() const;
	// 获取空闲数目
	int				__GetFreeCount() const;
private:
	char*			m_pBuf;					//环形数据缓冲区
	int				m_iLen;					//buff长度
	int				m_iMaxLen;				//buff可扩充的最大长度
	int				m_iHead;				//头指引
	int				m_iTail;				//尾指引
	UUCSocketWrap*	m_pSocket;				//持有套接字包装
};

// 输入流类
class UUCInputStream
{
	enum
	{
		DEFAULT_BUFF_SIZE  = UNIT_LENGTH,		//默认缓冲区大小
		MAX_BUFF_SIZE	   = UNIT_LENGTH*32,	//最大缓冲区大小
		BUFF_SIZE_INC_STEP = UNIT_LENGTH,		//缓冲区大小调整步长
		SINGLE_RECV_LEN	   = 1024,				//单次接收数据长度
	};
public:
	UUCInputStream(UUCSocketWrap* pSocket, int iLen=DEFAULT_BUFF_SIZE, int iMaxLen=MAX_BUFF_SIZE);
	~UUCInputStream();
public:
	// 复位重置
	void			Reset();
	// 读Buff，返回读取的数据量
	int				ReadBuff(char* pBuf, int iLen);
	// 填充Buff，收取数据，返回收取量
	int				FillBuff();
	// 读Buff，不移游标
	bool			Peek(char* pBuf, int iLen) const;
	// 检查Buff
	bool			CheckSize(int iCheckSize) const;
	// 移动游标
	void			Skip(int iOffset);
	// 设置Buff值
	void			SetBuffSize(int iSize);
	// 设置Buff最大值
	void			SetBuffMaxSize(int iSize);
	// 获取Buff最大值
	int				GetBuffMaxSize() const;
	// 获取Buff使用
	int				GetBuffUsedSize() const;
	// 设置默认大小
	bool			SetBuffDefaultSize(int iSize);
protected:
	// 调整缓冲区大小
	bool			__Resize(int iNeed);
	// 获取占用数目
	int				__GetUsedCount() const;
	// 获取空闲数目
	int				__GetFreeCount() const;
private:
	char*			m_pBuf;					//环形数据缓冲区
	int				m_iLen;					//Buff长度
	int				m_iMaxLen;				//最大Buffer长度
	int				m_iHead;				//头指引
	int				m_iTail;				//尾指引
	UUCSocketWrap*	m_pSocket;				//持有套接字包装
};
//}

#endif

