#include "CGSelectFormation.h"

CGSelectFormation::CGSelectFormation()
{
	m_nLength = GetPacketSize();
	m_pData = new char[m_nLength];
	memset(m_pData,0,m_nLength);
}

CGSelectFormation::~CGSelectFormation()
{
}

void CGSelectFormation::Read()
{
}

void CGSelectFormation::Write()
{
	UUCPacket::Write((char*)(&playerGuid), sizeof(int));
	UUCPacket::Write((char*)(&formationId), sizeof(unsigned char));
}

void CGSelectFormation::Execute()
{

}
