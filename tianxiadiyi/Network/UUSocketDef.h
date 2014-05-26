/*
**文件名称: 	UUSocketDef.h
**功能描述:		
**文件说明:		Socket关联类型定义, win / linux
**作者:			uutc
**创建时间:	
**修    改：2013-05-06
*/
#ifndef __UUTC_SOCKETDEF__
#define __UUTC_SOCKETDEF__

#if defined (_WIN32_)
	
	#ifndef FD_SETSIZE
	#define FD_SETSIZE 1024
	#endif /* 定义在winsock2.h之前，覆盖其中的FD_SETSIZE定义 */
	#include <stdio.h>
	#include<queue> 
	#include <Winsock2.h>
	#pragma comment( lib, "Ws2_32" )

#else 
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <sys/select.h>
	#include <stdio.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <sys/un.h>
	#include <unistd.h>
	#include <errno.h>
	#include <fcntl.h>
	#include <sys/param.h>
	#include <stropts.h>
	#include <sys/ioctl.h>
	#include <pthread.h>

#endif

typedef struct sockaddr		SOCKADDR;
typedef struct sockaddr_in	SOCKADDR_IN;
#define UUSOL_SOCKET 		SOL_SOCKET
#define UUSO_RCVBUF 		SO_RCVBUF

#if defined (_WIN32_)
	typedef SOCKET			UUSOCKET;
	typedef int             UUSOCKETLEN_T;
	typedef fd_set			UUFDSET;
	typedef timeval			UUTIMEVAL;
	typedef unsigned long	UUULONG;
	#define UUINVALID_SOCKET INVALID_SOCKET
	#define UUSOCKET_ERROR SOCKET_ERROR
	#define UUSHUTDOWN_BOTH	SD_BOTH
	#define UUEWOULD_BLOCK	WSAEWOULDBLOCK
#else 
	typedef int				UUSOCKET;
	typedef unsigned long   UUULONG;
	typedef socklen_t		UUSOCKETLEN_T;
	typedef fd_set			UUFDSET;
	typedef fd_mask			UUFDMASK;
	typedef timeval			UUTIMEVAL;
	#define UUINVALID_SOCKET	-1
	#define UUSOCKET_ERROR	-1
	#define UUSHUTDOWN_BOTH	SHUT_RDWR
	#define UUEWOULD_BLOCK	EWOULDBLOCK
#endif

#endif