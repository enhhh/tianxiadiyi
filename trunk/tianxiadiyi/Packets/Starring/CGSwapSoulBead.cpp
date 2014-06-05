#include "CGSwapSoulBead.h"

CGSwapSoulBead::CGSwapSoulBead()
{
	m_nLength = GetPacketSize();
	m_pData = new char[m_nLength];
	memset(m_pData,0,m_nLength);
}

CGSwapSoulBead::~CGSwapSoulBead()
{
}

void CGSwapSoulBead::Read()
{

}

void CGSwapSoulBead::Write()
{
	UUCPacket::Write((char*)(&playerGuid), sizeof(int));
	UUCPacket::Write((char*)(&type), sizeof(char));
	UUCPacket::Write((char*)(&srcPosition), sizeof(char));
	UUCPacket::Write((char*)(&destPosition), sizeof(char));
}

void CGSwapSoulBead::Execute()
{
}
