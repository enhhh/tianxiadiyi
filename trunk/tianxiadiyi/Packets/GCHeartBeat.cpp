#include "GCHeartBeat.h"

GCHeartBeat::GCHeartBeat()
{
	m_nLength = GetPacketSize();
	m_pData = new char[m_nLength];
	memset(m_pData,0,m_nLength);
}

GCHeartBeat::~GCHeartBeat()
{
}

void GCHeartBeat::Read()
{
	UUCPacket::Read((char*)(&heartBeat2), sizeof(int));
}

void GCHeartBeat::Write()
{
}

void GCHeartBeat::Execute()
{
	GCHeartBeatHandler::Execute(this);
}