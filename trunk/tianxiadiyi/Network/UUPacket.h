/*
**文件名称：UUCPacket.h
**功能描述：网络包模块
**文件说明：
**作    者：uutc
**创建时间：
**修    改：2013-05-06
*/

#ifndef __UUPACKET_H__
#define __UUPACKET_H__

#include "UUCommonType.h"
#include "UUSocketAPI.h"
/* 网络包结构
|------------------------------------------------------------------------|
| 包类型编号（2Byte）| 包数据长度（2Byte）|	内容数据 |
|------------------------------------------------------------------------|

包头：		PacketHeader = PacketId+DataLen
包头长度：	PacketHeaderLen = 4 Byte
*/

/************************************************************************/
// 网络包抽象基类
/************************************************************************/

//extern "C" {

class UUCPacket
{	
public:
	UUCPacket()
	{
		m_pNext = NULL;
		m_nType = 0;
		m_nLength = 0;
		skip = 0;
	}
	UUCPacket(unsigned nType,unsigned nLen,char* pContent)
	{
		m_pNext = NULL;
		m_nType = nType;
		m_nLength = nLen;
		m_pData = new char[nLen+1];
		memset(m_pData,0,nLen+1);
		m_pData[nLen]='\0';
		memcpy(m_pData,pContent,nLen);

		skip = 0;
	}
	~UUCPacket()
	{
		CleanUp();	
	}

	// 获取类型编号
	unsigned GetID(){return m_nType; };
	// 获取数据大小
	unsigned GetSize(){return m_nLength; };
	// 清理
	void CleanUp()
	{
		m_pNext = NULL;

		if(m_nLength>0)
		{
			SAFE_DELETE(m_pData);
		}

		m_nType = 0;
		m_nLength = 0;
	}
	// 读取内容
	char* GetContent(){return m_pData;};

public:
	//类型
	unsigned m_nType;
	//内容长度
	unsigned m_nLength;
	//内容数据
	char* m_pData;	

	int skip;

public:
	void SetType(unsigned nType){m_nType =nType; }
	void SetLength(unsigned nLen){m_nLength =nLen; }
	void SetContent(const char* buf, unsigned int len){};

	void Read(char* buf, unsigned int len);
	void Write(const char* buf, unsigned int len);

	//Next指引
	UUCPacket* m_pNext;
};

//};//extern "C"
#endif
