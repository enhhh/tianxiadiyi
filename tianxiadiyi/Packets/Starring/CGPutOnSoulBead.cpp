#include "CGPutOnSoulBead.h"

CGPutOnSoulBead::CGPutOnSoulBead()
{
	m_nLength = GetPacketSize();
	m_pData = new char[m_nLength];
	memset(m_pData,0,m_nLength);
}

CGPutOnSoulBead::~CGPutOnSoulBead()
{
}

void CGPutOnSoulBead::Read()
{
}

void CGPutOnSoulBead::Write()
{
	UUCPacket::Write((char*)(&playerGuid), sizeof(int));
	UUCPacket::Write((char*)(&srcPosition), sizeof(char));
	UUCPacket::Write((char*)(&destPosition), sizeof(char));
}

void CGPutOnSoulBead::Execute()
{
}
