#include "CGLevelUpFormation.h"

CGLevelUpFormation::CGLevelUpFormation()
{
	m_nLength = GetPacketSize();
	m_pData = new char[m_nLength];
	memset(m_pData,0,m_nLength);
}

CGLevelUpFormation::~CGLevelUpFormation()
{
}

void CGLevelUpFormation::Read()
{
}

void CGLevelUpFormation::Write()
{
	UUCPacket::Write((char*)(&playerGuid), sizeof(int));
	UUCPacket::Write((char*)(&formationId), sizeof(unsigned char));
}

void CGLevelUpFormation::Execute()
{

}
