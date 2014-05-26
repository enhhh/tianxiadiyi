#include "GCFixFormation.h"

GCFixFormation::GCFixFormation()
{
	m_nLength = GetPacketSize();
	m_pData = new char[m_nLength];
	memset(m_pData,0,m_nLength);
}

GCFixFormation::~GCFixFormation()
{
}

void GCFixFormation::Read()
{
	UUCPacket::Read((char*)(&isSuccess), sizeof(char));
}

void GCFixFormation::Write()
{
}

void GCFixFormation::Execute()
{
	GCFixFormationHandler::Execute(this);
}