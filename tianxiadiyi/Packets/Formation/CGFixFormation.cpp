#include "CGFixFormation.h"

CGFixFormation::CGFixFormation()
{
	m_nLength = GetPacketSize();
	m_pData = new char[m_nLength];
	memset(m_pData,0,m_nLength);
}

CGFixFormation::~CGFixFormation()
{
}

void CGFixFormation::Read()
{
}

void CGFixFormation::Write()
{
	UUCPacket::Write((char*)(&playerGuid), sizeof(int));
	UUCPacket::Write((char*)(&formationId), sizeof(unsigned char));
	UUCPacket::Write((char*)(&generalId), sizeof(int));
	UUCPacket::Write((char*)(&position), sizeof(unsigned char));
}

void CGFixFormation::Execute()
{

}
