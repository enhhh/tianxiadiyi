#include "CGFormationList.h"

CGFormationList::CGFormationList()
{
	m_nLength = GetPacketSize();
	m_pData = new char[m_nLength];
	memset(m_pData,0,m_nLength);
}

CGFormationList::~CGFormationList()
{
}

void CGFormationList::Read()
{
}

void CGFormationList::Write()
{
	UUCPacket::Write((char*)(&playerGuid), sizeof(int));
}

void CGFormationList::Execute()
{

}
