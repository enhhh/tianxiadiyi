#include "GCFormationList.h"

GCFormationList::GCFormationList()
{
	m_nLength = GetPacketSize();
	m_pData = new char[m_nLength];
	memset(m_pData,0,m_nLength);
}

GCFormationList::~GCFormationList()
{
}

void GCFormationList::Read()
{
	for (int i = 0; i < 10; i++)
	{
		UUCPacket::Read((char*)(&formation[i][0]), sizeof(unsigned char));
		UUCPacket::Read((char*)(&formation[i][1]), sizeof(unsigned char));
	}
}

void GCFormationList::Write()
{
}

void GCFormationList::Execute()
{
	GCFormationListHandler::Execute(this);
}