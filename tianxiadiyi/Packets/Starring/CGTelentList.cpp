#include "CGTelentList.h"

CGTelentList::CGTelentList()
{
	m_nLength = GetPacketSize();
	m_pData = new char[m_nLength];
	memset(m_pData,0,m_nLength);
}

CGTelentList::~CGTelentList()
{
}

void CGTelentList::Read()
{

}

void CGTelentList::Write()
{
	UUCPacket::Write((char*)(&playerGuid), sizeof(int));
}

void CGTelentList::Execute()
{
}
