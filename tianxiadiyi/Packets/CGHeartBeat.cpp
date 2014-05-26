#include "CGHeartBeat.h"

CGHeartBeat::CGHeartBeat()
{
	m_nLength = GetPacketSize();
	m_pData = new char[m_nLength];
	memset(m_pData,0,m_nLength);
}

CGHeartBeat::~CGHeartBeat()
{
}

void CGHeartBeat::Read()
{

}

void CGHeartBeat::Write()
{
	UUCPacket::Write((char*)(&heartBeat1), sizeof(int));
}

void CGHeartBeat::Execute()
{

}
