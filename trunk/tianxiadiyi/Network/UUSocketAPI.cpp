/*文件名称：UUSocketAPI.cpp
**功能描述：套接字API抽象类实现
**文件说明：抽象出与平台无关的套接字API
**作    者：uutc
**创建时间：
**修    改：2013-05-06
*/
#include "UUSocketAPI.h"

UUCSocketAPI::UUCSocketAPI()
{
}

UUCSocketAPI::~UUCSocketAPI()
{
}

UUSOCKET UUCSocketAPI::Create()
{
    UUSOCKCALL_RETURN(::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP), UUSOCKET, UUINVALID_SOCKET);        
}

int UUCSocketAPI::Shutdown(UUSOCKET s, int iHow)
{
	if (UUINVALID_SOCKET != s)
    {
        UUSOCKCALL_RETURN(::shutdown(s, iHow), int, UUSOCKET_ERROR);        
    }

	return UUSOCKET_ERROR;
}

int UUCSocketAPI::Close(UUSOCKET s)
{
#if defined (_WIN32_)
    UUSOCKCALL_RETURN(::closesocket(s), int, UUSOCKET_ERROR);
#else
    UUSOCKCALL_RETURN(::close(s), int, UUSOCKET_ERROR);
#endif
}

int UUCSocketAPI::Connect(UUSOCKET s, const char* pIP, const unsigned& rPort)
{
    if ( NULL == pIP)
	{
		return -1;
	}
	SOCKADDR_IN addr_in;
	addr_in.sin_family = AF_INET;
	addr_in.sin_addr.s_addr = inet_addr(pIP);
	addr_in.sin_port = htons(rPort);
	UUSOCKETLEN_T iLen = sizeof(SOCKADDR);

    UUSOCKCALL_RETURN(::connect(s, (SOCKADDR*)&addr_in, iLen), int, UUSOCKET_ERROR);
}

int UUCSocketAPI::Select (int iFds, UUFDSET* pReadFds, UUFDSET* pWriteFds, UUFDSET* pErrorFds, UUTIMEVAL &rTimeout)
{
    UUSOCKCALL_RETURN(::select(iFds, pReadFds, pWriteFds, pErrorFds, &rTimeout), int, UUSOCKET_ERROR);
}


int UUCSocketAPI::Send(UUSOCKET s, const char* pBuf, int iLen, int iFlag)
{
	if (NULL == pBuf)
	{
        return -1;
	}
    
    UUSOCKCALL_RETURN(::send(s, pBuf, iLen, iFlag), int, UUSOCKET_ERROR);
}

int UUCSocketAPI::Recv(UUSOCKET s, char* pBuf, int iLen, int iFlag)
{
	if (NULL == pBuf)
	{
        return -1;
	}
    
    UUSOCKCALL_RETURN(::recv(s, pBuf, iLen, iFlag), int, UUSOCKET_ERROR);

}

int UUCSocketAPI::SetIOMode(UUSOCKET s, int bNonBlock)
{
#if defined (_WIN32_)
	UUSOCKCALL_RETURN(::ioctlsocket(s, FIONBIO, (UUULONG*)&bNonBlock), int, UUSOCKET_ERROR);
#else
	int iFlags = 1;
	int iRet 	= 0;
	int iMode=0;
	
    UUSOCKCALL(::ioctl(s, iMode, &iFlags) && (iFlags = fcntl(s, F_GETFL, 0)),int, UUSOCKET_ERROR,iRet);
	if(iRet < 0)
    {
       	return errno;
    }

	if (bNonBlock)
	{
		iMode |= O_NONBLOCK;
	}
	else
	{
		iMode &= ~O_NONBLOCK;
	}
	UUSOCKCALL_RETURN(::fcntl(s, F_SETFL, iMode) , int, UUSOCKET_ERROR);

#endif
}

unsigned int UUCSocketAPI::GetInBuffReadableData(UUSOCKET s)
{
	unsigned int arg = 0;
#if defined (_WIN32_)
	int iRet = 0;
	UUSOCKCALL(::ioctlsocket(s, FIONREAD, (UUULONG*)&arg), int, UUSOCKET_ERROR, iRet);
#else
	int iRet = 0;
	UUSOCKCALL(::ioctl(s, FIONREAD, &arg), int, UUSOCKET_ERROR, iRet);
#endif
	return arg;
}

int UUCSocketAPI::SetSockOpt(UUSOCKET s, int iLevel, int iOptName, const int* pOptVal, int iOptLen)
{
    if (NULL == pOptVal)
    {
        return -1;
    }
#if defined (_WIN32_)
    UUSOCKCALL_RETURN(::setsockopt(s, iLevel, iOptName, (char*)pOptVal, iOptLen), int, UUSOCKET_ERROR);
#else
    UUSOCKCALL_RETURN(::setsockopt(s, iLevel, iOptName, pOptVal, iOptLen), int, UUSOCKET_ERROR);
#endif
}

int UUCSocketAPI::GetSockOpt(UUSOCKET s, int iLevel, int iOptName, int* pOptVal, int& iOptLen)
{
    if (NULL == pOptVal)
    {
        return -1;
    }
#if defined (_WIN32_)
    UUSOCKCALL_RETURN(::getsockopt(s, iLevel, iOptName, (char*)pOptVal, &iOptLen), int, UUSOCKET_ERROR);
#else
    UUSOCKCALL_RETURN(::getsockopt(s, iLevel, iOptName, pOptVal, (UUSOCKETLEN_T*)&iOptLen), int, UUSOCKET_ERROR);
#endif
}

void UUCSocketAPI::FdZero(UUFDSET& rfdSet)
{
#if defined (_WIN32_)
	FD_ZERO(&rfdSet);
#else
	FD_ZERO(&rfdSet);
#endif
}

void UUCSocketAPI::FdClear(UUSOCKET fd, UUFDSET& rfdSet)
{
#if defined (_WIN32_)
	FD_CLR(fd, &rfdSet);
#else
	FD_CLR(fd, &rfdSet);
#endif
}

void UUCSocketAPI::FdSet(UUSOCKET fd, UUFDSET& rfdSet)
{
#if defined (_WIN32_)
	FD_SET(fd, &rfdSet);
#else
	FD_SET(fd, &rfdSet);
#endif
}

bool UUCSocketAPI::FdCheck(UUSOCKET fd, const UUFDSET& rfdSet)
{
#if defined (_WIN32_)
	return FD_ISSET(fd, &rfdSet)>0;
#else
	return FD_ISSET(fd, &rfdSet)>0;
#endif
}
