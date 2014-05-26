/*
**文件名称：
**功能描述：套接字API抽象类实现
**文件说明：抽象出与平台无关的套接字API
**作    者：uutc
**创建时间：
**修    改1：
**修    改：
*/
#ifndef _UUSocketAPI_H_
#define _UUSocketAPI_H_

#include "UUSocketDef.h"
#include "UUCommonType.h"

/************************************************************************/
// 抽象套接字API
/************************************************************************/
//extern "C" {
class UUCSocketAPI
{
public:
	UUCSocketAPI();
	~UUCSocketAPI();
public:
	// 创建套接字
	static UUSOCKET	Create();
	// 关闭套接字
	static int		Close(UUSOCKET s);
	// 终止套接字
	static int		Shutdown(UUSOCKET s, int iHow); 
	// 连接
	static int		Connect(UUSOCKET s, const char* pIP, const unsigned& rPort);
	// 筛选

	static int 		Select (int iFds, UUFDSET* pReadFds, UUFDSET* pWriteFds, UUFDSET* pErrorFds, UUTIMEVAL &rTimeout);
	// 发送数据
	static int		Send(UUSOCKET s, const char* pBuf, int iLen, int iFlag);
	// 接收数据
	static int		Recv(UUSOCKET s, char* pBuf, int iLen, int iFlag);
public:
	// 设置I/O模式；非阻塞(1) 阻塞（0）
	static int		SetIOMode(UUSOCKET s, int bNonBlock);
	// 获取socket的输入缓存待读取的数据量
	static unsigned int		GetInBuffReadableData(UUSOCKET s);
	// 设置套接字选项
	static int		SetSockOpt(UUSOCKET s, int iLevel, int iOptName, const int* pOptVal, int iOptLen);
	// 获取套接字选项
	static int		GetSockOpt(UUSOCKET s, int iLevel, int iOptName, int* pOptVal, int& iOptLen);
	// 清零套接字集合
	static void		FdZero(UUFDSET& rfdSet);
	// 从集合删除套接字
	static void		FdClear(UUSOCKET fd, UUFDSET& rfdSet);
	// 添加套接字到集合
	static void		FdSet(UUSOCKET fd, UUFDSET& rfdSet);
	// 检测套机字是否在集合内
	static bool		FdCheck(UUSOCKET fd, const UUFDSET& rfdSet);
};

//}
#endif


