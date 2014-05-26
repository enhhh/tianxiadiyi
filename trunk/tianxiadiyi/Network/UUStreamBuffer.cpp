/*
**�ļ����ƣ�
**�����������׽������ݻ������ʵ��
**�ļ�˵����
**��    �ߣ�uutc
**����ʱ�䣺
**��    �ģ�2013-05-06
*/
#include "UUStreamBuffer.h"
#include "UUSocketAPI.h"
#include "UUSocketWrap.h"
#include <stdio.h>

UUCInputStream::UUCInputStream(UUCSocketWrap* pSocket, int iLen/*=DEFAULT_BUFF_SIZE*/, int iMaxLen/*=MAX_BUFF_SIZE*/)
{
	m_pSocket = pSocket;
	m_iLen = iLen;
	m_iMaxLen = iMaxLen;
	m_iHead = m_iTail = 0;
	m_pBuf = new char[iLen];
	memset(m_pBuf, 0, m_iLen);
}

UUCInputStream::~UUCInputStream()
{
	if (m_pBuf != NULL)
	{
		delete [] m_pBuf;
	}
}

int UUCInputStream::__GetUsedCount() const
{
	if (m_iHead <= m_iTail)
	{
		return m_iTail-m_iHead;
	}
	else
	{
		return (m_iLen-m_iHead) + m_iTail;
	}
}

int UUCInputStream::__GetFreeCount() const
{
	return m_iLen-__GetUsedCount()-1;
}


bool UUCInputStream::__Resize(int iNeed)
{
	int iStep = m_iLen * 2;
	//int iInc = (iNeed>BUFF_SIZE_INC_STEP ? iNeed : BUFF_SIZE_INC_STEP);
	while(iNeed > iStep)
	{
		iStep += iStep;
	}
	//int iInc = iStep;
	int iNewSize = iStep;
	char* pNewBuf = new char[iNewSize];
	if (pNewBuf == NULL)
	{
		return false;
	}
	memset(pNewBuf, 0, iNewSize);

	if (m_iHead < m_iTail)
	{
		memcpy(pNewBuf, &m_pBuf[m_iHead], m_iTail-m_iHead);
	}
	else if (m_iHead > m_iTail)
	{
		memcpy(pNewBuf, &m_pBuf[m_iHead], m_iLen-m_iHead);
		memcpy(pNewBuf+m_iLen-m_iHead, m_pBuf, m_iTail);
	}
	else
	{
		//printf("Network Lib Error! Head = %d, Tail = %d\n", m_iHead, m_iTail);
	}

	delete[] m_pBuf;
	m_pBuf = pNewBuf;

	m_iTail = __GetUsedCount();
	m_iHead = 0;
	m_iLen = iNewSize;

	return true;
}
bool UUCInputStream::SetBuffDefaultSize(int iSize)
{
	return __Resize(iSize);
}

void UUCInputStream::Reset()
{
	memset(m_pBuf, 0, sizeof(char)*m_iLen);
	m_iHead = 0;
	m_iTail = 0;
}

int UUCInputStream::ReadBuff(char* pBuf, int iLen)
{
	if (iLen > __GetUsedCount())
	{
		iLen = __GetUsedCount();
	}

	if (m_iHead <= m_iTail)
	{
		memcpy(pBuf, &m_pBuf[m_iHead], iLen);
		m_iHead += iLen;
	}
	else
	{
		int iTailCount = m_iLen-m_iHead;
		if (iLen <= iTailCount)
		{
			memcpy(pBuf, &m_pBuf[m_iHead], iLen);
			m_iHead += iLen;
		}
		else
		{
			memcpy(pBuf, &m_pBuf[m_iHead], iTailCount);
			memcpy(pBuf+iTailCount, m_pBuf, iLen-iTailCount);
			m_iHead = iLen-iTailCount;
		}
	}

	return iLen;
}

//�������ݺ���궨��
#define ONRECEIVE(uReceived) {\
	if (uReceived == UUSOCKET_ERROR){\
	if (errno == UUEWOULD_BLOCK)\
		return 0;\
	else{\
		m_pSocket->SetStatusCode(UUCSocketWrap::RECV_FAIL);\
		return -1;}}\
	if (uReceived == 0){\
		m_pSocket->SetStatusCode(UUCSocketWrap::RECV_FAIL);\
		return -1;}\
}

int UUCInputStream::FillBuff()
{
	int iFlag = 0;
	unsigned int uFilled = 0;
	unsigned int uReceived = 0;
	unsigned int uFree = 0;

	if (m_iHead <= m_iTail)
	{
		if (m_iHead == 0)
		{
			// H   T		LEN=10
			// 0123456789
			// abcd......
			uFree = m_iLen-m_iTail-1;
			if (uFree > 0)
			{
				uReceived = UUCSocketAPI::Recv(m_pSocket->GetSocket(), &m_pBuf[m_iTail], uFree, iFlag);
				ONRECEIVE(uReceived);

				m_iTail += uReceived;
				uFilled += uReceived;
			}
			
			//����û�ж���
			if (uReceived == uFree)
			{
				//��ȡInBuff�ɶ�������
				unsigned int uAvail = UUCSocketAPI::GetInBuffReadableData(m_pSocket->GetSocket());
				if (uAvail > 0)
				{
					//���뻺�泬��
					if (int(m_iLen+uAvail+1) > m_iMaxLen)
					{
						//��λ
						Reset();
						m_pSocket->SetStatusCode(UUCSocketWrap::INPUT_OVERFLOW);
						return -1;
					}
					
					//���ô�С
					if (!__Resize(uAvail+1))
					{
						m_pSocket->SetStatusCode(UUCSocketWrap::RECV_FAIL);
						return -1;
					}
					
					//��������
					uReceived = UUCSocketAPI::Recv(m_pSocket->GetSocket(), &m_pBuf[m_iTail], uAvail, iFlag);
					ONRECEIVE(uReceived);

					m_iTail += uReceived;
					uFilled += uReceived;
				}		
			}
		}
		//m_iHead != 0
		else	
		{
			//    H   T		LEN=10
			// 0123456789
			// ...abcd...
			//�Ƚ��յ���벿
			uFree = m_iLen-m_iTail;
			if (uFree > 0)
			{
				uReceived = UUCSocketAPI::Recv(m_pSocket->GetSocket(), &m_pBuf[m_iTail], uFree, iFlag);
				ONRECEIVE(uReceived);

				m_iTail = (m_iTail+uReceived)%m_iLen;
				uFilled += uReceived;
			}
			
			//���ܻ�����Ҫ���յ�����
			if (uReceived == uFree)
			{
				//�����ж������ݿ��Զ�
				unsigned int uAvail = UUCSocketAPI::GetInBuffReadableData(m_pSocket->GetSocket());
				if (uAvail > 0)
				{
					uFree = m_iHead-1;
					if (uFree != 0)
					{
						uReceived = UUCSocketAPI::Recv(m_pSocket->GetSocket(), &m_pBuf[0], uFree, iFlag);
						ONRECEIVE(uReceived);

						m_iTail += uReceived;
						uFilled += uReceived;
					}
					//���ܻ�������Ҫ����
					if (uReceived == uFree)
					{
						uAvail = UUCSocketAPI::GetInBuffReadableData(m_pSocket->GetSocket());
						if (uAvail > 0)
						{
							//����
							if (int(m_iLen+uAvail+1) > m_iMaxLen)
							{
								//��λ
								Reset();
								m_pSocket->SetStatusCode(UUCSocketWrap::INPUT_OVERFLOW);
								return -1;
							}
							//������С
							if (!__Resize(uAvail+1))
							{
								m_pSocket->SetStatusCode(UUCSocketWrap::RECV_FAIL);
								return -1;
							}
							//����
							uReceived = UUCSocketAPI::Recv(m_pSocket->GetSocket(), &m_pBuf[m_iTail], uFree, iFlag);
							ONRECEIVE(uReceived);

							m_iTail += uReceived;
							uFilled += uReceived;
						}			
					}
				}			
			}		
		}
	}
	// m_iHead > m_iTail
	else
	{
		//     T  H		LEN=10
		// 0123456789
		// abcd...efg
		
		uFree = m_iHead-m_iTail -1;
		if (uFree > 0)
		{
			//����
			uReceived = UUCSocketAPI::Recv(m_pSocket->GetSocket(), &m_pBuf[m_iTail], uFree, iFlag);
			ONRECEIVE(uReceived);

			m_iTail += uReceived;
			uFilled += uReceived;

			//���ܻ���������Ҫ����
			if (uReceived == uFree)
			{
				//��ȡInBuff�ɶ�����
				unsigned int uAvail = UUCSocketAPI::GetInBuffReadableData(m_pSocket->GetSocket());
				if (uAvail > 0)
				{
					//����
					if (int(m_iLen+uAvail+1) > m_iMaxLen)
					{
						//��λ����
						Reset();
						m_pSocket->SetStatusCode(UUCSocketWrap::INPUT_OVERFLOW);
						return -1;
					}

					//������С
					if (!__Resize(uAvail+1))
					{
						m_pSocket->SetStatusCode(UUCSocketWrap::RECV_FAIL);
						return -1;
					}
					//����
					uReceived = UUCSocketAPI::Recv(m_pSocket->GetSocket(), &m_pBuf[m_iTail], uAvail, iFlag);
					ONRECEIVE(uReceived);

					m_iTail += uReceived;
					uFilled += uReceived;	
				}	
			}
		}
	}

	//���ؽ��յ�������
	return uFilled;
}

bool UUCInputStream::Peek(char* pBuf, int iLen) const
{
	if (pBuf == NULL)
	{
		return false;
	}
	if (iLen <= 0)
	{
		return false;
	}
	if (!CheckSize(iLen)) 
	{
		return false;
	}
	
	try
	{
		//�������ݵ�pBuf
		if (m_iHead < m_iTail)
		{
			memcpy(pBuf, &m_pBuf[m_iHead], iLen);
		}
		else if (m_iHead > m_iTail)
		{
			int iRearCount = m_iLen-m_iHead;
			if (iRearCount >= iLen)
			{
				memcpy(pBuf, &m_pBuf[m_iHead], iLen);
			}
			else
			{
				//�����������
				memcpy(pBuf, &m_pBuf[m_iHead], iRearCount);
				//����ǰ������
				memcpy(pBuf+iRearCount, m_pBuf, iLen-iRearCount);
			}
		}
		return true;
	}
	catch (...)
	{
		return false;
	}
}

bool UUCInputStream::CheckSize(int iCheckSize) const
{
	if (iCheckSize < 0)
	{
		return false;
	}
	return __GetUsedCount()>=iCheckSize;
}

void UUCInputStream::Skip(int iOffset)
{
	if (iOffset != 0)
	{
		m_iHead = (iOffset+m_iHead)%m_iLen;
		if (m_iHead < 0)
		{
			m_iHead += m_iLen;
		}
	}
}

void UUCInputStream::SetBuffMaxSize(int iSize)
{
	m_iMaxLen = iSize;
}

int UUCInputStream::GetBuffMaxSize() const
{
	return m_iMaxLen;
}

int UUCInputStream::GetBuffUsedSize() const
{
	return __GetUsedCount();
}


UUCOutputStream::UUCOutputStream(UUCSocketWrap* pSocket, int iLen/*=DEFAULT_BUFF_SIZE*/, int iMaxLen/*=MAX_BUFF_SIZE*/)
{
	m_pSocket = pSocket;
	m_iLen = iLen;
	m_iMaxLen = iMaxLen;
	m_iHead = m_iTail = 0;
	m_pBuf = new char[iLen];
	memset(m_pBuf, 0, m_iLen);
}

UUCOutputStream::~UUCOutputStream()
{
	if (m_pBuf != NULL)
	{
		delete [] m_pBuf;
	}
}

int UUCOutputStream::WriteBuff(const char* pBuf, int iLen)
{
	int iFreeCnt = __GetFreeCount();
	if (iFreeCnt < iLen+1)
	{
		//bool bRet = __Resize(iLen-iFreeCnt);
		if (!__Resize(iLen-iFreeCnt))
		{
			return -1;
		}
	}

	if (m_iHead <= m_iTail)
	{
		int iFreeTail = m_iLen-m_iTail;
		if (iFreeTail >= iLen)
		{
			memcpy(&m_pBuf[m_iTail], pBuf, iLen);
		}
		else
		{
			memcpy(&m_pBuf[m_iTail], pBuf, iFreeTail);
			memcpy(m_pBuf, &pBuf[iFreeTail], iLen-iFreeTail);
		}
	}
	else
	{
		memcpy(&m_pBuf[m_iTail], pBuf, iLen);
	}

	//�ƶ�βָ��
	m_iTail = (m_iTail+iLen)%m_iLen;

	return iLen;
}

bool UUCOutputStream::SetBuffDefaultSize(int iSize)
{
	return __Resize(iSize);
}

void UUCOutputStream::Reset()
{
	memset(m_pBuf, 0, sizeof(char)*m_iLen);
	m_iHead = 0;
	m_iTail = 0;
}


int UUCOutputStream::FlushBuff()
{
	//�������ӵĻ��泬�������ã������˿ͻ��˶Ͽ�����
	if (m_iLen > m_iMaxLen)
	{
		delete [] m_pBuf;
		m_pBuf = new char[DEFAULT_BUFF_SIZE];
		memset(m_pBuf, 0, sizeof(m_pBuf));
		m_iHead = m_iTail = 0;
		m_pSocket->SetStatusCode(UUCSocketWrap::OUTPUT_OVERFLOW);
		return -1;
	}

//================================================================================================ ��ʽʱ��������������λ��
#if defined (_WIN32_)
	int iFlag = MSG_DONTROUTE;
#else // (_LINUX64_)
	int iFlag = MSG_NOSIGNAL;
#endif

	int iTotalSend = 0;
	int iSend = 0;

	try
	{
		if (m_iTail > m_iHead)
		{
			int iLen = m_iTail-m_iHead;
			while (iLen > 0)
			{
				iSend = UUCSocketAPI::Send(m_pSocket->GetSocket(), &m_pBuf[m_iHead], iLen, iFlag);

				if (iSend == UUSOCKET_ERROR)
				{
					if (errno == UUEWOULD_BLOCK)
					{
						//����...
						return 0;
					}
					else
					{
						m_pSocket->SetStatusCode(UUCSocketWrap::SEND_FAIL);
						return -1;
					}		
				}

				if (iSend == 0)
				{
					return 0;
				}

				iTotalSend += iSend;
				m_iHead += iSend;
				iLen -= iSend;

				Sleep(100);
			}
		}
		else if (m_iTail < m_iHead)
		{
			//���ͺ�벿��
			int iLen1 = m_iLen-m_iHead;
			while (iLen1 > 0)
			{
				iSend = UUCSocketAPI::Send(m_pSocket->GetSocket(), &m_pBuf[m_iHead], iLen1, iFlag);
				if (iSend == UUSOCKET_ERROR)
				{
					if (errno == UUEWOULD_BLOCK)
					{
						//����...
						return 0;
					}
					else
					{
						m_pSocket->SetStatusCode(UUCSocketWrap::SEND_FAIL);
						return -1;
					}		
				}

				if (iSend == 0)
				{
					return 0;
				}

				iTotalSend += iSend;
				m_iHead += iSend;
				iLen1 -= iSend;

				Sleep(100);
			}

			//����ǰ�벿��
			m_iHead = 0;
			int iLen2 = m_iTail;
			while (iLen2 > 0)
			{
				iSend = UUCSocketAPI::Send(m_pSocket->GetSocket(), &m_pBuf[m_iHead], iLen2, iFlag);

				if (iSend == UUSOCKET_ERROR)
				{
					if (errno == UUEWOULD_BLOCK)
					{
						//����...
						return 0;
					}
					else
					{
						m_pSocket->SetStatusCode(UUCSocketWrap::SEND_FAIL);
						return -1;
					}		
				}

				if (iSend == 0)
				{
					return 0;
				}

				iTotalSend += iSend;
				m_iHead += iSend;
				iLen2 -= iSend;

				Sleep(100);
			}
		}
	}
	catch (...)
	{
		if (iSend > 0)
		{
			m_iHead += iSend;
		}
	}

	m_iHead = 0;
	m_iTail = 0;

	return iTotalSend;
}

void UUCOutputStream::SetBuffMaxSize(int iSize)
{
	m_iMaxLen = iSize;
}

int UUCOutputStream::GetBuffMaxSize() const
{
	return m_iMaxLen;
}

int UUCOutputStream::GetBuffUsedSize() const
{
	return __GetUsedCount();
}

bool UUCOutputStream::__Resize(int iNeed)
{	
	int iStep = m_iLen * 2;
	//int iInc = (iNeed>BUFF_SIZE_INC_STEP ? iNeed : BUFF_SIZE_INC_STEP);
	while(iNeed > iStep)
	{
		iStep += iStep;
	}
	//int iInc = iStep;
	int iNewSize = iStep;

	char* pNewBuf = new char[iNewSize];
	if (pNewBuf == NULL)
	{
		return false;
	}
	memset(pNewBuf, 0, iNewSize);

	if (m_iHead < m_iTail)
	{
		memcpy(pNewBuf, &m_pBuf[m_iHead], m_iTail-m_iHead);
	}
	else if (m_iHead > m_iTail)
	{
		memcpy(pNewBuf, &m_pBuf[m_iHead], m_iLen-m_iHead);
		memcpy(pNewBuf+m_iLen-m_iHead, m_pBuf, m_iTail);
	}

	delete [] m_pBuf;
	m_pBuf = pNewBuf;

	m_iTail = __GetUsedCount();
	m_iHead = 0;
	m_iLen = iNewSize;


	return true;
}

int UUCOutputStream::__GetUsedCount() const
{
	if (m_iHead <= m_iTail)
	{
		return m_iTail-m_iHead;
	}
	else
	{
		return (m_iLen-m_iHead) + m_iTail;
	}
}

int UUCOutputStream::__GetFreeCount() const
{
	return m_iLen-__GetUsedCount()-1;
}

