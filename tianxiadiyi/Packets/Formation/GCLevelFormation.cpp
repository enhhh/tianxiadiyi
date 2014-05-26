#include "GCLevelUpFormation.h"

GCLevelUpFormation::GCLevelUpFormation()
{
	m_nLength = GetPacketSize();
	m_pData = new char[m_nLength];
	memset(m_pData,0,m_nLength);
}

GCLevelUpFormation::~GCLevelUpFormation()
{
}

void GCLevelUpFormation::Read()
{
	UUCPacket::Read((char*)(&formationId), sizeof(char));
	UUCPacket::Read((char*)(&formationLevel), sizeof(char));
}

void GCLevelUpFormation::Write()
{
}

void GCLevelUpFormation::Execute()
{
	GCLevelUpFormationHandler::Execute(this);
}