/*
**�ļ����ƣ�
**�����������׽��ַ�װ��
**�ļ�˵����
**��    �ߣ�uutc
**����ʱ�䣺
**��    �ģ�2013-05-06����ΰ��-���ӳ�ʼ����������,�������ݰ�������
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _UUCSocketWrap_H_
#define _UUCSocketWrap_H_

#include "UUCommonType.h"
#include "UUSocketDef.h"
#include "UUStreamBuffer.h"
#include "UUPacket.h"
#include "UUPacketEXT.h"
#include "UUPacketFactoryManager.h"

const int UUIP_SIZE = 24;	//IP����
const int RECV_MAX_SIZE = 1024;//��ѯ�հ���󳤶�
//const int TICK_TIME = 500; //Tick ʱ��

/************************************************************************/
// �׽��ְ�װ�� 
/************************************************************************/
extern "C" 
{
class UUCSocketWrap
{	
public:
	// ״̬����
	enum STATUS_CODE
	{
		NETWORK_INVALD		= -1,	//δ��ʼ
		WORK_NORMAL			= 0,	//��������
		WAIT_CONNECT		= 1,	//�ȴ���������	
		INIT_ERROR			= 2,	//��ʼ��ʧ��
		CREATE_FAILED		= 3,	//���Ӵ���ʧ��		
		CONNECTING			= 4,	//��������
		CONNECT_FAILED		= 5,	//����ʧ��
		UNKNOWN_ERROR		= 6,	//δ֪�쳣
		INPUT_OVERFLOW		= 7,	//���뻺�泬��
		OUTPUT_OVERFLOW		= 8,	//������泬��
		CONNECT_FAIL		= 9,	//Connectʧ��
		CLOSE_FAIL			= 10,	//Closeʧ��
		SEND_FAIL			= 11,	//Sendʧ��
		RECV_FAIL			= 12,	//Recvʧ��
		SHUTDOWN_FAIL		= 13,	//shutdownʧ��
		LOST_SERVER			= 14,   //���ж�����
		THREAD_ERROR		= 15,	//���紴���̳߳���
		PAKCET_ERROR		= 16,   //�⿪����,�����ݳ�����󳤶� (1024-4)

	};

	UUCSocketWrap();
	~UUCSocketWrap();

	static UUCSocketWrap* getTheOnlyInstance();

	// ���� ����ʼ����createsocket��
	//bool			Run();
	// ������Ϣ���ṩ��Ӧ�ó���ʹ�õķ������ݽӿڣ�,д�����������
	int				SendMsg(const char* pMsg, int iLen);
	// ������Ϣ���ṩ��Ӧ�ó���ʹ�õĽ������ݽӿڣ�,�ӻ�������ȡ
	int				RecvMsg(char* pMsg, int iLen);
	// ��ȡ��Ϣ�������α꣨���ڰ�ͷ�ļ����
	bool			Peek(char* pBuf, int iLen) const;
	// ���������С�������α�
	bool			CheckSize(int iLen) const;
	// �ƶ��α�
	void			Skip(int iOffset);
	// ���ӷ�����
	bool			Connect(const char* pIP, const unsigned& rPort);
	// ��ֹ Socket
	bool			Shutdown();
	// �ر� Socket
	bool			Close();
	// ��������
	bool			Recv();
	// ��������
	bool			Send();
	// ����I/Oģʽ��������(1) ������0��
	int				SetIOMode(int bNonBlock);
	// ��ȡ�׽���
	UUSOCKET			GetSocket() const;
	// ��ȡ״̬����
	STATUS_CODE			GetStatusCode() const;
	// ����״̬����
	void			SetStatusCode(STATUS_CODE code);
	// ��Ч���ж� (socket,״̬)
	bool			IsValid() const;
	// ���û�������ǰ��С
	void			SetBuffDefaultSize(int iSize,bool bInOrOut);
	// ��������������������ֵ
	void			SetBuffMaxSize(int iMaxSize, bool bInOrOut);
	// ��ȡ������������������ֵ
	int				GetBuffMaxSize(bool bInOrOut) const;
	// ��ȡ�������������ʹ��ֵ
	int				GetBuffUsedSize(bool bInOrOut) const;
	// ��ȡ����,����FALSEʱ,û�а��ɷ���
	UUCPacket*	    GetPacket(UUCPacket* pData);
	// ȥ��һ��ͷ
	bool			DeleteHead();

	// ����һ��
	bool			SendPacket(UUPacketEXT* packet);

	// д��һ��
	bool			WritePacket(unsigned nType,unsigned nLen,char* pContent);
	// �����׽��ֹ���,m_Socket
	bool			AttachSocket(UUSOCKET s);
	// ȡ���׽��ֹ���,m_Socket
	void			DetachSocket();

	//�õ���Ϣ����
	UUPacketFactoryManager&	GetPacketFactory(void) { return m_PacketFactoryManager; }

private:
	UUSOCKET			m_Socket;			// �׽���
	UUCOutputStream*	m_pOutput;			// ���buf
	UUCInputStream*	    m_pInput;			// ����buf
	UUCPacket*		    m_pCache;			// �������հ��������
	UUCPacket*		    m_pCacheTail;		// ������βԪ��
	int					m_PacketCount;		// ��ǰ����
	STATUS_CODE			m_LogicCode;		// �߼�״̬
	SOCKADDR_IN			m_SockAddr;			// �׽��ֵ�ַ�ṹ��
	char				m_IP[UUIP_SIZE];		// IP��ַ
	unsigned			m_Port;				// �˿ں�
	bool				m_InitSocket;		// �����ʼ��	
	char*				m_PackTemp;			// ������
	char*				m_PackHead;		    // ��ͷ

//==========================================================Select ����
public:
	// ��ʼ�� 
	bool				Init();
	// ��ʼ������
	bool				InitSocket();
	// �ͷ�����
	bool				CleanSocket();
public:
	// �����׽��� , ��ʼ��������
	UUCSocketWrap*	CreateSocket();
	// ɾ���׽���
	bool				DeleteSocket(UUCSocketWrap& rWrap);
	// ����ɸѡʱ��Ƭ
	void				SetTimeOut(int iSec, int iUsec);
	// ����ɸѡ
	bool				DoSelect();
	//�����հ�
	bool				ProcessInput();
	// �������
	bool				ProcessOutput();
	// �����쳣
	bool				ProcessError();
	// ������ת��
	bool				ProcessPakcet();

	// ִ����ת��       
	void                ExcutePacket();

	// Tick
	bool				Tick();


public:
	// ����ԭʼ�׽��ּ���
	void				_Zero();
	// ��ԭʼ������ɾ���׽���
	void				_Clear(UUCSocketWrap& rWrap);
	// ����׽��ֵ�ԭʼ����
	void				_Add(UUCSocketWrap& rWrap);
private:
	// Select���׽��ּ���
	UUFDSET				m_SelReadSet;
	// Selectд�׽��ּ���
	UUFDSET				m_SelWriteSet;
	// Select�����׽��ּ���
	UUFDSET				m_SelErrorSet;	
	// ԭʼ�׽��ּ���
	UUFDSET				m_RawSet;
	// Selectʱ��Ƭ
	UUTIMEVAL				m_TimeOut;
	// ԭʼ�׽��ּ��������ֵ	, ��ǰsocket id�ţ�-1ʱΪδ���ӻ��߶Ͽ���
	UUSOCKET				m_MaxHandle;		
	//���������,ָ���Լ�
	UUCSocketWrap*		m_pSocketWrap;

	//SOCKET��������
	UUPacketFactoryManager	m_PacketFactoryManager;

};
}
#endif




