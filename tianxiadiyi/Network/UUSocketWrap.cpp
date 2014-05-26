/*
**文件名称：
**功能描述：套接字封装类
**文件说明：供应用程序使用
**作    者：uutc
**创建时间：
**修    改：2013-05-06
*/
#include "UUSocketWrap.h"
#include "UUSocketAPI.h"
#include "UUCommonType.h"
static UUCSocketWrap* socketWrap = NULL;
/************************************************************************/
// 1.套接字封装的函数定义
/************************************************************************/
UUCSocketWrap::UUCSocketWrap()
{
	m_Socket = UUINVALID_SOCKET;
	//m_Socket = -1;
	m_pInput = new UUCInputStream(this);
	m_pOutput = new UUCOutputStream(this);	
	m_PackTemp = new char[RECV_MAX_SIZE];
	m_PackHead = new char[PACKET_HEADER_LEN];
	//初始，无数据
	m_pCache	 = NULL; 
	m_pCacheTail = NULL;
	m_PacketCount	= 0;

	m_LogicCode = WAIT_CONNECT;
	memset(&m_SockAddr, 0, sizeof(m_SockAddr));
	memset(m_IP, 0, sizeof(m_IP));
	m_Port = 0;
	m_pSocketWrap = NULL; 
	//CONNECTING
	SetStatusCode(WAIT_CONNECT);
	m_MaxHandle = UUINVALID_SOCKET ;//linux 下使用
}

UUCSocketWrap::~UUCSocketWrap()
{
	#if defined(Debug)
		printf("Kill Client,Release Resource \n");
	#endif

	//缓存流
	SAFE_DELETE(m_pInput);
	SAFE_DELETE(m_pOutput);
	SAFE_DELETE(m_PackTemp);
	SAFE_DELETE(m_PackHead);
	if (m_Socket != UUINVALID_SOCKET)
	{//释放socket资源
		Shutdown();
		Close();
	}

	//缓存包释放
	while(NULL!=m_pCache)
	{
		UUCPacket* pCache = m_pCache;//->m_pNext;
		m_pCache= pCache->m_pNext;
		SAFE_DELETE(pCache);
	}
	m_PacketCount=0;
	m_pSocketWrap=NULL;

#if defined (_WIN32_)
#else 
	m_MaxHandle = UUINVALID_SOCKET;	
#endif


}

UUCSocketWrap* UUCSocketWrap::getTheOnlyInstance()
{	
	if (!socketWrap)
	{
		socketWrap = new UUCSocketWrap();
	}

	return socketWrap;
}

UUSOCKET UUCSocketWrap::GetSocket() const
{
	return m_Socket;
}

int UUCSocketWrap::SendMsg(const char* pMsg, int iLen)
{
	if (NULL == pMsg) 
    {
        return -1;
    }
	return m_pOutput->WriteBuff(pMsg, iLen);
}

int UUCSocketWrap::RecvMsg(char* pMsg, int iLen)
{
	if (NULL == pMsg )
	{
		return -1;
	}
	return m_pInput->ReadBuff(pMsg, iLen);
}

bool UUCSocketWrap::Peek(char* pBuf, int iLen) const
{
	if (pBuf == NULL)
	{
		return false;
	}
	return m_pInput->Peek(pBuf, iLen);
}

bool UUCSocketWrap::CheckSize(int iLen) const
{
	if (iLen < 0)
	{
		return false;
	}

	return m_pInput->CheckSize(iLen);
}

void UUCSocketWrap::Skip(int iOffset)
{
	m_pInput->Skip(iOffset);
}

bool UUCSocketWrap::Connect(const char* pIP, const unsigned& rPort)
{
	strncpy(m_IP, pIP, UUIP_SIZE-1);
	m_Port = rPort;
	m_SockAddr.sin_addr.s_addr = inet_addr(m_IP);
	m_SockAddr.sin_port = htons(m_Port);

	int bRet = UUCSocketAPI::Connect(m_Socket, pIP, rPort);

	if (bRet == UUSOCKET_ERROR) 
	{
		SetStatusCode(CONNECT_FAIL);
		return false;
	}
	return true;
}

bool UUCSocketWrap::Shutdown()
{
	int bRet = 0;
	// 套接字已连接，终止套接字
	if ( WORK_NORMAL == GetStatusCode())
	{
		bRet = UUCSocketAPI::Shutdown(m_Socket, UUSHUTDOWN_BOTH);	
		if (bRet == UUSOCKET_ERROR)
		{
			SetStatusCode(SHUTDOWN_FAIL);
			return false;
		}
	}
	return true;
}

bool UUCSocketWrap::Close()
{
	int bRet = UUCSocketAPI::Close(m_Socket);
	if (bRet == UUSOCKET_ERROR)
	{
		SetStatusCode(CLOSE_FAIL);
	}

	m_Socket = UUINVALID_SOCKET;
	memset(&m_SockAddr, 0, sizeof(m_SockAddr));
	memset(m_IP, 0, sizeof(m_IP));
	m_Port = 0;
	return CleanSocket();
}

int UUCSocketWrap::SetIOMode(int bNonBlock)
{
	return UUCSocketAPI::SetIOMode(m_Socket, bNonBlock);
}

bool UUCSocketWrap::Recv()
{
	if (!IsValid())
	{
		return false;
	}

	int iRet = m_pInput->FillBuff();

	#if defined(Debug)
		printf(" data len = %d \n ",iRet);
	#endif

	return iRet > 0;
}

bool UUCSocketWrap::Send()
{
	if (!IsValid())
	{
		return false;
	}
	
	int iRet = m_pOutput->FlushBuff();
	return iRet >= 0;
}

UUCSocketWrap::STATUS_CODE UUCSocketWrap::GetStatusCode() const
{
	return m_LogicCode;
}

void UUCSocketWrap::SetStatusCode(STATUS_CODE code)
{
	m_LogicCode = code;
}

bool UUCSocketWrap::IsValid() const
{
	if (m_Socket == UUINVALID_SOCKET)
	{
		return false;
	}

	return GetStatusCode()==WORK_NORMAL ? true: false;
}

void UUCSocketWrap::SetBuffDefaultSize(int iSize,bool bInOrOut)
{
	if (bInOrOut)
	{
		m_pInput->SetBuffDefaultSize(iSize);
	}
	else
	{
		m_pOutput->SetBuffDefaultSize(iSize);
	}
}


/*****************************************************************************
* 	函数功能：设置输入输出缓存最大长度
* 	参数说明：iMaxSize最大值，bInOrOut设置输入（true），设置输出（false）
* 	返回值：	  无
******************************************************************************/
void UUCSocketWrap::SetBuffMaxSize(int iMaxSize, bool bInOrOut)
{
	if (bInOrOut)
	{
		m_pInput->SetBuffMaxSize(iMaxSize);
	}
	else
	{
		m_pOutput->SetBuffMaxSize(iMaxSize);
	}
}

/*****************************************************************************
* 	函数功能：获取输入输出缓存最大长度
* 	参数说明：bInOrOut 输入（true），输出（false）
* 	返回值：	 缓存最大长度
******************************************************************************/
int UUCSocketWrap::GetBuffMaxSize(bool bInOrOut) const
{
	if (bInOrOut)
	{
		return m_pInput->GetBuffMaxSize();
	}
	else
	{
		return m_pOutput->GetBuffMaxSize();
	}
}

/*****************************************************************************
* 	函数功能：获取输入输出缓存使用长度
* 	参数说明：bInOrOut 输入（true），输出（false）
* 	返回值：	 缓存最大长度
******************************************************************************/
int	UUCSocketWrap::GetBuffUsedSize(bool bInOrOut) const
{
	if (bInOrOut)
	{
		return m_pInput->GetBuffUsedSize();
	}
	else
	{
		return m_pOutput->GetBuffUsedSize();
	}
}

//Select模型部分
bool UUCSocketWrap::Init()
{
	_Zero();
	UUCSocketAPI::FdZero(m_SelReadSet);
	UUCSocketAPI::FdZero(m_SelWriteSet);
	UUCSocketAPI::FdZero(m_SelErrorSet);
	memset(&m_TimeOut, 0, sizeof(m_TimeOut));
	SetTimeOut(500,0);	
	m_InitSocket = false;

	if(!m_InitSocket)
	{
		if(!InitSocket())
		{
			return false;
		}
	}

#if defined (_WIN32_)
#else 
	m_MaxHandle = UUINVALID_SOCKET;	
#endif
	
	return true;
}

bool UUCSocketWrap::InitSocket()
{
#if defined (_WIN32_)
	//初始化网络环境
	WSADATA wsaDATA;
	WORD version = MAKEWORD(2, 0);
	int ret = WSAStartup(version, &wsaDATA);
	if(ret != 0)
	{
		return false; 
	}

#else 
	
#endif

	m_InitSocket = true;
	
	m_PacketFactoryManager.Init();
	return true;
}

bool UUCSocketWrap::CleanSocket()
{
	m_InitSocket = false;

#if defined (_WIN32_)	 
	if(0 != WSACleanup() )
	{
		return false; 
	}

#else 
	
#endif	

	return true;
}

void UUCSocketWrap::_Zero()
{
	UUCSocketAPI::FdZero(m_RawSet);
}

void UUCSocketWrap::_Clear(UUCSocketWrap& rWrap)
{
#if defined (_WIN32_)
#else	
	m_MaxHandle= UUINVALID_SOCKET;
#endif

	UUCSocketAPI::FdClear(rWrap.GetSocket(), m_RawSet);
}

void UUCSocketWrap::_Add(UUCSocketWrap& rWrap)
{
#if defined (_WIN32_)
#else 
	
	m_MaxHandle = rWrap.GetSocket();
	
#endif

	UUCSocketAPI::FdSet(rWrap.GetSocket(), m_RawSet);
}

bool UUCSocketWrap::DoSelect()
{
#if defined (_WIN32_)
#else 
	if (UUINVALID_SOCKET == m_MaxHandle )
	{
		return false;
	}
#endif
	m_SelReadSet = m_RawSet;
	m_SelWriteSet = m_RawSet;
	m_SelErrorSet = m_RawSet;

#if defined (_WIN32_)
	return UUCSocketAPI::Select(0, &m_SelReadSet, &m_SelWriteSet, &m_SelErrorSet, m_TimeOut) >=0 ;
#else // Linux64环境下select的第一个参数是最大句柄值加1，Win32环境忽略该值。
	return UUCSocketAPI::Select(m_MaxHandle+1, &m_SelReadSet, &m_SelWriteSet, &m_SelErrorSet, m_TimeOut) >= 0;
#endif

}

bool UUCSocketWrap::Tick()
{
	if(false==DoSelect())
	{
		return false;
	}

	if(false==ProcessError())
	{
		return false;
	}

	if(false==ProcessOutput())
	{
		return false;
	}
	if(false==ProcessInput())
	{
		return false;
	}

	// 流转包
	ProcessPakcet();

	// 执行包
	ExcutePacket();
	return true;
}

bool UUCSocketWrap::ProcessOutput()
{
	//检查可写
	UUCSocketWrap* pSockWrap = m_pSocketWrap;
	if (NULL == pSockWrap)
	{
		return false;
	}

	if(!pSockWrap->IsValid())
	{
		return false;
	}

	if (UUCSocketAPI::FdCheck(pSockWrap->GetSocket(), m_SelWriteSet))
	{
		pSockWrap->Send() ;
	}
	return true;
}

bool UUCSocketWrap::ProcessInput()
{
	UUCSocketWrap* pSockWrap = m_pSocketWrap;
	if (NULL == pSockWrap )
	{
		return false;
	}

	if(!pSockWrap->IsValid())
	{
		return false;
	}

	//检查可读
	if (UUCSocketAPI::FdCheck(pSockWrap->GetSocket(), m_SelReadSet))
	{
		pSockWrap->Recv();
	}

	return true;
}

bool UUCSocketWrap::ProcessError()
{
	UUCSocketWrap* pSockWrap = m_pSocketWrap;
	if (NULL == pSockWrap )
	{
		return false;
	}

	if(!pSockWrap->IsValid())
	{
		return false;
	}

	//检查异常
	if (UUCSocketAPI::FdCheck(pSockWrap->GetSocket(), m_SelErrorSet))
	{
		//置错误状态
		#if defined (_WIN32_)
			if(errno != WSAEINTR && errno != WSAEWOULDBLOCK )
			{
				pSockWrap->SetStatusCode(UUCSocketWrap::UNKNOWN_ERROR);
			}
		#else
			if(errno != EAGAIN  && errno != EINTR &&  errno != EWOULDBLOCK )
			{
				pSockWrap->SetStatusCode(UUCSocketWrap::UNKNOWN_ERROR);
			}
		#endif		
	}

	return true;
}

//递归解包
bool UUCSocketWrap::ProcessPakcet()
{
	UUCSocketWrap* pSockWrap = m_pSocketWrap;

	if (NULL == pSockWrap )
	{
		return false;
	}

	if (!pSockWrap->IsValid())
		return false;

	memset(m_PackHead,0,PACKET_HEADER_LEN);

	if (false==pSockWrap->Peek(m_PackHead,PACKET_HEADER_LEN))
	{
		return false; //包不完整
	}
	else
	{
		unsigned nType=0;
		unsigned nLen=0;

		memcpy(&nType,m_PackHead,2);
		memcpy(&nLen,m_PackHead+2,2);

#if defined(Debug)
		printf("char * to packet,ntype:%d,nLen:%d \n ",nType,nLen);
#endif
		// 包序号不存在
		if( RECV_MAX_SIZE < nLen )//内容包最大长度限制
		{
			//设置网络出错
			SetStatusCode(PAKCET_ERROR);
			return false;
		}

		if(pSockWrap->CheckSize(nLen))
		{
			//有完整包			
			memset(m_PackTemp,0,nLen+PACKET_HEADER_LEN+1);
			m_PackTemp[nLen+PACKET_HEADER_LEN]='\0';
			if((nLen+PACKET_HEADER_LEN)==pSockWrap->RecvMsg(m_PackTemp,nLen+PACKET_HEADER_LEN))
			{//加包			
				UUCPacket* mPacket = new UUCPacket(nType,nLen,m_PackTemp+PACKET_HEADER_LEN);

				if(0==m_PacketCount)
				{
					m_pCache = mPacket;
					m_pCacheTail = mPacket;
				}
				else
				{
					m_pCacheTail->m_pNext = mPacket;
					m_pCacheTail = mPacket;
				}

				m_PacketCount++;
			}
			//释放nei的内存
		}	
		//假设还有数据可以被解成包
		return ProcessPakcet();
	}	
	return true;
}

void UUCSocketWrap::ExcutePacket()
{
	UUCPacket readPacket;
	UUCPacket* packetReturn = socketWrap->GetPacket(&readPacket);

	if (packetReturn != NULL)
	{
		UUPacketEXT* pPacket = m_PacketFactoryManager.CreatePacket( packetReturn->GetID() ) ;
		pPacket->m_pData = packetReturn->m_pData;
		pPacket->Read();

		pPacket->Execute();

		m_PacketFactoryManager.RemovePacket( pPacket ) ;
	}
}

UUCPacket* UUCSocketWrap::GetPacket(UUCPacket* pData)
{
	if(m_PacketCount<1)
	{
		return NULL;
	}

	pData=new UUCPacket(m_pCache->GetID(),m_pCache->GetSize(),m_pCache->GetContent());

	//pData=m_pCache;
	DeleteHead();

	return pData;
}
bool UUCSocketWrap::DeleteHead()
{
	UUCPacket* pHead = m_pCache;
	
	if(NULL==pHead)
	{
		return true;
	}

	m_pCache = pHead->m_pNext;
	m_PacketCount--;

	SAFE_DELETE(pHead);
	//delete pHead;

	return true;
}

UUCSocketWrap* UUCSocketWrap::CreateSocket()
{
	m_pSocketWrap = this;//new UUCSocketWrap();
	if (m_pSocketWrap == NULL)
	{
		return NULL;
	}
	UUSOCKET s = UUCSocketAPI::Create();	

	if (s == UUINVALID_SOCKET)
	{
		SetStatusCode(CREATE_FAILED);
		return NULL;
	}

	/*const int bNodelay = 1; 
	UUCSocketAPI::SetSockOpt(s, IPPROTO_TCP, TCP_NODELAY, &bNodelay, sizeof(int));*/

	SetIOMode(1);//默认为非阻塞

	//挂接
	m_pSocketWrap->AttachSocket(s);
	//添加到集合 fd_set
	_Add(*m_pSocketWrap);
	return m_pSocketWrap;
}
bool UUCSocketWrap::AttachSocket(UUSOCKET s)
{
	if (s != UUINVALID_SOCKET)
	{
		m_Socket = s;
		SetStatusCode(WORK_NORMAL);
		return true;
	}
	return false;
}
void UUCSocketWrap::DetachSocket()
{
	m_Socket = UUINVALID_SOCKET;
	SetStatusCode(WAIT_CONNECT);
}
bool UUCSocketWrap::DeleteSocket(UUCSocketWrap& rWrap)
{
	if (!(UUCSocketAPI::FdCheck(rWrap.GetSocket(), m_RawSet)))
	{
		return false;
	}

	//从集合删除
	_Clear(rWrap);
	//终止套接字
	rWrap.Shutdown();
	//关闭套接字
	rWrap.Close();
	//扯卸
	rWrap.DetachSocket();

	return true;
}


void UUCSocketWrap::SetTimeOut(int iSec, int iUsec)
{
	m_TimeOut.tv_sec = iSec;
	m_TimeOut.tv_usec = iUsec;
}

bool UUCSocketWrap::SendPacket( UUPacketEXT* packet )
{
	packet->Write();
	bool ret = WritePacket(packet->GetPacketID(), packet->GetPacketSize(), packet->GetContent());
	
	Tick();
	
	return ret;
}

bool UUCSocketWrap::WritePacket(unsigned nType,unsigned nLen,char* pContent)
{
	UUCSocketWrap* pSockWrap = m_pSocketWrap;
	if (pSockWrap == NULL)
	{
		return false;
	}

	if(!pSockWrap->IsValid())
	{
		return false;
	}

	if (pSockWrap->SendMsg((char*)"XXXX", 4) != 4)
	{
		return false;
	}

	if (pSockWrap->SendMsg((char*)&nType, 2) != 2)
	{
		return false;
	}

	if (pSockWrap->SendMsg((char*)&nLen, 2) != 2)
	{
		return false;
	}

	if( (pSockWrap->SendMsg(pContent, nLen) == nLen) )
	{
		return true;
	}

	return false;
}