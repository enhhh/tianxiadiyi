/*
**�ļ����ƣ�
**�����������׽���API������ʵ��
**�ļ�˵�����������ƽ̨�޹ص��׽���API
**��    �ߣ�uutc
**����ʱ�䣺
**��    ��1��
**��    �ģ�
*/
#ifndef _UUSocketAPI_H_
#define _UUSocketAPI_H_

#include "UUSocketDef.h"
#include "UUCommonType.h"

/************************************************************************/
// �����׽���API
/************************************************************************/
//extern "C" {
class UUCSocketAPI
{
public:
	UUCSocketAPI();
	~UUCSocketAPI();
public:
	// �����׽���
	static UUSOCKET	Create();
	// �ر��׽���
	static int		Close(UUSOCKET s);
	// ��ֹ�׽���
	static int		Shutdown(UUSOCKET s, int iHow); 
	// ����
	static int		Connect(UUSOCKET s, const char* pIP, const unsigned& rPort);
	// ɸѡ

	static int 		Select (int iFds, UUFDSET* pReadFds, UUFDSET* pWriteFds, UUFDSET* pErrorFds, UUTIMEVAL &rTimeout);
	// ��������
	static int		Send(UUSOCKET s, const char* pBuf, int iLen, int iFlag);
	// ��������
	static int		Recv(UUSOCKET s, char* pBuf, int iLen, int iFlag);
public:
	// ����I/Oģʽ��������(1) ������0��
	static int		SetIOMode(UUSOCKET s, int bNonBlock);
	// ��ȡsocket�����뻺�����ȡ��������
	static unsigned int		GetInBuffReadableData(UUSOCKET s);
	// �����׽���ѡ��
	static int		SetSockOpt(UUSOCKET s, int iLevel, int iOptName, const int* pOptVal, int iOptLen);
	// ��ȡ�׽���ѡ��
	static int		GetSockOpt(UUSOCKET s, int iLevel, int iOptName, int* pOptVal, int& iOptLen);
	// �����׽��ּ���
	static void		FdZero(UUFDSET& rfdSet);
	// �Ӽ���ɾ���׽���
	static void		FdClear(UUSOCKET fd, UUFDSET& rfdSet);
	// ����׽��ֵ�����
	static void		FdSet(UUSOCKET fd, UUFDSET& rfdSet);
	// ����׻����Ƿ��ڼ�����
	static bool		FdCheck(UUSOCKET fd, const UUFDSET& rfdSet);
};

//}
#endif


