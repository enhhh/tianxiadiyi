#include "GCGeneralList.h"

GCGeneralList::GCGeneralList()
{
	m_nLength = GetPacketSize();
	m_pData = new char[m_nLength];
	memset(m_pData,0,m_nLength);
}

GCGeneralList::~GCGeneralList()
{
}

void GCGeneralList::Read()
{
	UUCPacket::Read((char*)(&num), sizeof(unsigned char));

	for (int i = 0; i < num; i++)
	{
		int generalId = 0;
		UUCPacket::Read((char*)(&generalId), sizeof(int));
		generalVector.push_back(generalId);
	}
}

void GCGeneralList::Write()
{
}

void GCGeneralList::Execute()
{
	GCGeneralListHandler::Execute(this);
}