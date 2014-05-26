#include "CGModifyFormation.h"

CGModifyFormation::CGModifyFormation()
{
	m_nLength = GetPacketSize();
	m_pData = new char[m_nLength];
	memset(m_pData,0,m_nLength);
}

CGModifyFormation::~CGModifyFormation()
{
}

void CGModifyFormation::Read()
{
}

void CGModifyFormation::Write()
{
	UUCPacket::Write((char*)(&playerGuid), sizeof(int));
	UUCPacket::Write((char*)(&formationId), sizeof(unsigned char));
	UUCPacket::Write((char*)(&srcPosition), sizeof(unsigned char));
	UUCPacket::Write((char*)(&destPosition), sizeof(unsigned char));
}

void CGModifyFormation::Execute()
{

}
