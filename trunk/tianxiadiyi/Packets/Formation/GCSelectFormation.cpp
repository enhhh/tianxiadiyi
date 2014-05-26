#include "GCSelectFormation.h"

GCSelectFormation::GCSelectFormation()
{
	m_nLength = GetPacketSize();
	m_pData = new char[m_nLength];
	memset(m_pData,0,m_nLength);
}

GCSelectFormation::~GCSelectFormation()
{
}

void GCSelectFormation::Read()
{
	for (int i = 0; i < 9; i++)
	{
		UUCPacket::Read((char*)(&formationId[i]), sizeof(int));
	}
}

void GCSelectFormation::Write()
{
}

void GCSelectFormation::Execute()
{
	GCSelectFormationHandler::Execute(this);
}