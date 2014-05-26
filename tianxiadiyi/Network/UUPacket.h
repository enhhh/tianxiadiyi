/*
**�ļ����ƣ�UUCPacket.h
**���������������ģ��
**�ļ�˵����
**��    �ߣ�uutc
**����ʱ�䣺
**��    �ģ�2013-05-06
*/

#ifndef __UUPACKET_H__
#define __UUPACKET_H__

#include "UUCommonType.h"
#include "UUSocketAPI.h"
/* ������ṹ
|------------------------------------------------------------------------|
| �����ͱ�ţ�2Byte��| �����ݳ��ȣ�2Byte��|	�������� |
|------------------------------------------------------------------------|

��ͷ��		PacketHeader = PacketId+DataLen
��ͷ���ȣ�	PacketHeaderLen = 4 Byte
*/

/************************************************************************/
// ������������
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

	// ��ȡ���ͱ��
	unsigned GetID(){return m_nType; };
	// ��ȡ���ݴ�С
	unsigned GetSize(){return m_nLength; };
	// ����
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
	// ��ȡ����
	char* GetContent(){return m_pData;};

public:
	//����
	unsigned m_nType;
	//���ݳ���
	unsigned m_nLength;
	//��������
	char* m_pData;	

	int skip;

public:
	void SetType(unsigned nType){m_nType =nType; }
	void SetLength(unsigned nLen){m_nLength =nLen; }
	void SetContent(const char* buf, unsigned int len){};

	void Read(char* buf, unsigned int len);
	void Write(const char* buf, unsigned int len);

	//Nextָ��
	UUCPacket* m_pNext;
};

//};//extern "C"
#endif
