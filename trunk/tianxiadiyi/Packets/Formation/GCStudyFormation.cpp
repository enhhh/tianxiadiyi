#include "GCStudyFormation.h"

GCStudyFormation::GCStudyFormation()
{
	m_nLength = GetPacketSize();
	m_pData = new char[m_nLength];
	memset(m_pData,0,m_nLength);
}

GCStudyFormation::~GCStudyFormation()
{
}

void GCStudyFormation::Read()
{
	UUCPacket::Read((char*)(&isSuccess), sizeof(char));
}

void GCStudyFormation::Write()
{
}

void GCStudyFormation::Execute()
{
	GCStudyFormationHandler::Execute(this);
}