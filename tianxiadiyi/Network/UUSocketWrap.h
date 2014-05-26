/*
**文件名称：
**功能描述：套接字封装类
**文件说明：
**作    者：uutc
**创建时间：
**修    改：2013-05-06，罗伟新-增加初始化网络内容,增加数据包流操作
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

const int UUIP_SIZE = 24;	//IP长度
const int RECV_MAX_SIZE = 1024;//轮询收包最大长度
//const int TICK_TIME = 500; //Tick 时间

/************************************************************************/
// 套接字包装类 
/************************************************************************/
extern "C" 
{
class UUCSocketWrap
{	
public:
	// 状态编码
	enum STATUS_CODE
	{
		NETWORK_INVALD		= -1,	//未初始
		WORK_NORMAL			= 0,	//运行正常
		WAIT_CONNECT		= 1,	//等待连接命令	
		INIT_ERROR			= 2,	//初始化失败
		CREATE_FAILED		= 3,	//连接创建失败		
		CONNECTING			= 4,	//正在连接
		CONNECT_FAILED		= 5,	//连接失败
		UNKNOWN_ERROR		= 6,	//未知异常
		INPUT_OVERFLOW		= 7,	//输入缓存超大
		OUTPUT_OVERFLOW		= 8,	//输出缓存超大
		CONNECT_FAIL		= 9,	//Connect失败
		CLOSE_FAIL			= 10,	//Close失败
		SEND_FAIL			= 11,	//Send失败
		RECV_FAIL			= 12,	//Recv失败
		SHUTDOWN_FAIL		= 13,	//shutdown失败
		LOST_SERVER			= 14,   //被中断连接
		THREAD_ERROR		= 15,	//网络创建线程出错
		PAKCET_ERROR		= 16,   //解开出错,包内容超出最大长度 (1024-4)

	};

	UUCSocketWrap();
	~UUCSocketWrap();

	static UUCSocketWrap* getTheOnlyInstance();

	// 运行 ，初始化后，createsocket后
	//bool			Run();
	// 发送消息（提供给应用程序使用的发送数据接口）,写入代发缓存中
	int				SendMsg(const char* pMsg, int iLen);
	// 接收消息（提供给应用程序使用的接收数据接口）,从缓存流读取
	int				RecvMsg(char* pMsg, int iLen);
	// 读取消息，不移游标（用于包头的检读）
	bool			Peek(char* pBuf, int iLen) const;
	// 检测入流大小，不移游标
	bool			CheckSize(int iLen) const;
	// 移动游标
	void			Skip(int iOffset);
	// 连接服务器
	bool			Connect(const char* pIP, const unsigned& rPort);
	// 终止 Socket
	bool			Shutdown();
	// 关闭 Socket
	bool			Close();
	// 接收数据
	bool			Recv();
	// 发送数据
	bool			Send();
	// 设置I/O模式；非阻塞(1) 阻塞（0）
	int				SetIOMode(int bNonBlock);
	// 获取套接字
	UUSOCKET			GetSocket() const;
	// 获取状态编码
	STATUS_CODE			GetStatusCode() const;
	// 设置状态编码
	void			SetStatusCode(STATUS_CODE code);
	// 有效性判断 (socket,状态)
	bool			IsValid() const;
	// 设置缓冲区当前大小
	void			SetBuffDefaultSize(int iSize,bool bInOrOut);
	// 设置输入输出缓存区最大值
	void			SetBuffMaxSize(int iMaxSize, bool bInOrOut);
	// 获取输入输出缓冲区的最大值
	int				GetBuffMaxSize(bool bInOrOut) const;
	// 获取输入输出缓冲区使用值
	int				GetBuffUsedSize(bool bInOrOut) const;
	// 获取包流,返回FALSE时,没有包可返回
	UUCPacket*	    GetPacket(UUCPacket* pData);
	// 去除一包头
	bool			DeleteHead();

	// 发送一包
	bool			SendPacket(UUPacketEXT* packet);

	// 写入一包
	bool			WritePacket(unsigned nType,unsigned nLen,char* pContent);
	// 设置套接字关联,m_Socket
	bool			AttachSocket(UUSOCKET s);
	// 取消套接字关联,m_Socket
	void			DetachSocket();

	//得到消息工厂
	UUPacketFactoryManager&	GetPacketFactory(void) { return m_PacketFactoryManager; }

private:
	UUSOCKET			m_Socket;			// 套接字
	UUCOutputStream*	m_pOutput;			// 输出buf
	UUCInputStream*	    m_pInput;			// 输入buf
	UUCPacket*		    m_pCache;			// 包流，收包，解包后
	UUCPacket*		    m_pCacheTail;		// 包流，尾元素
	int					m_PacketCount;		// 当前包数
	STATUS_CODE			m_LogicCode;		// 逻辑状态
	SOCKADDR_IN			m_SockAddr;			// 套接字地址结构体
	char				m_IP[UUIP_SIZE];		// IP地址
	unsigned			m_Port;				// 端口号
	bool				m_InitSocket;		// 网络初始化	
	char*				m_PackTemp;			// 包内容
	char*				m_PackHead;		    // 包头

//==========================================================Select 部分
public:
	// 初始化 
	bool				Init();
	// 初始化网络
	bool				InitSocket();
	// 释放网络
	bool				CleanSocket();
public:
	// 创建套接字 , 初始化自身类
	UUCSocketWrap*	CreateSocket();
	// 删除套接字
	bool				DeleteSocket(UUCSocketWrap& rWrap);
	// 设置筛选时间片
	void				SetTimeOut(int iSec, int iUsec);
	// 网络筛选
	bool				DoSelect();
	//处理收包
	bool				ProcessInput();
	// 处理输出
	bool				ProcessOutput();
	// 处理异常
	bool				ProcessError();
	// 处理流转包
	bool				ProcessPakcet();

	// 执行流转包       
	void                ExcutePacket();

	// Tick
	bool				Tick();


public:
	// 清零原始套接字集合
	void				_Zero();
	// 从原始集合中删除套接字
	void				_Clear(UUCSocketWrap& rWrap);
	// 添加套接字到原始集合
	void				_Add(UUCSocketWrap& rWrap);
private:
	// Select读套接字集合
	UUFDSET				m_SelReadSet;
	// Select写套接字集合
	UUFDSET				m_SelWriteSet;
	// Select错误套接字集合
	UUFDSET				m_SelErrorSet;	
	// 原始套接字集合
	UUFDSET				m_RawSet;
	// Select时间片
	UUTIMEVAL				m_TimeOut;
	// 原始套接字集合最大句柄值	, 当前socket id号，-1时为未连接或者断开后
	UUSOCKET				m_MaxHandle;		
	//自身管理器,指向自己
	UUCSocketWrap*		m_pSocketWrap;

	//SOCKET包管理器
	UUPacketFactoryManager	m_PacketFactoryManager;

};
}
#endif




