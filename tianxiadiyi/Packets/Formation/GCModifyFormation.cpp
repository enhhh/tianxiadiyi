#include "GCModifyFormation.h"

GCModifyFormation::GCModifyFormation()
{
	m_nLength = GetPacketSize();
	m_pData = new char[m_nLength];
	memset(m_pData,0,m_nLength);
}

GCModifyFormation::~GCModifyFormation()
{
}

void GCModifyFormation::Read()
{
	UUCPacket::Read((char*)(&isSuccess), sizeof(char));
}

void GCModifyFormation::Write()
{
}

void GCModifyFormation::Execute()
{
	GCModifyFormationHandler::Execute(this);
}