#include "CGSoulBeadList.h"

CGSoulBeadList::CGSoulBeadList()
{
	m_nLength = GetPacketSize();
	m_pData = new char[m_nLength];
	memset(m_pData,0,m_nLength);
}

CGSoulBeadList::~CGSoulBeadList()
{
}

void CGSoulBeadList::Read()
{

}

void CGSoulBeadList::Write()
{
	UUCPacket::Write((char*)(&playerGuid), sizeof(int));
}

void CGSoulBeadList::Execute()
{
}
