#include "CGGeneralList.h"

CGGeneralList::CGGeneralList()
{
	m_nLength = GetPacketSize();
	m_pData = new char[m_nLength];
	memset(m_pData,0,m_nLength);
}

CGGeneralList::~CGGeneralList()
{
}

void CGGeneralList::Read()
{

}

void CGGeneralList::Write()
{
	UUCPacket::Write((char*)(&playerGuid), sizeof(int));
}

void CGGeneralList::Execute()
{

}
