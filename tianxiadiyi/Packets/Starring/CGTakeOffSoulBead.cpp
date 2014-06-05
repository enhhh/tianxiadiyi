#include "CGTakeOffSoulBead.h"

CGTakeOffSoulBead::CGTakeOffSoulBead()
{
	m_nLength = GetPacketSize();
	m_pData = new char[m_nLength];
	memset(m_pData,0,m_nLength);
}

CGTakeOffSoulBead::~CGTakeOffSoulBead()
{
}

void CGTakeOffSoulBead::Read()
{
}

void CGTakeOffSoulBead::Write()
{
	UUCPacket::Write((char*)(&playerGuid), sizeof(int));
	UUCPacket::Write((char*)(&srcPosition), sizeof(char));
	UUCPacket::Write((char*)(&destPosition), sizeof(char));
}

void CGTakeOffSoulBead::Execute()
{
}
