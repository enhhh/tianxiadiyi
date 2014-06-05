#include "CGSoulBeadEquipList.h"

CGSoulBeadEquipList::CGSoulBeadEquipList()
{
	m_nLength = GetPacketSize();
	m_pData = new char[m_nLength];
	memset(m_pData,0,m_nLength);
}

CGSoulBeadEquipList::~CGSoulBeadEquipList()
{
}

void CGSoulBeadEquipList::Read()
{
}

void CGSoulBeadEquipList::Write()
{
	UUCPacket::Write((char*)(&playerGuid), sizeof(int));
}

void CGSoulBeadEquipList::Execute()
{
}
