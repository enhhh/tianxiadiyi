#include "CGStarringAttribute.h"

CGStarringAttribute::CGStarringAttribute()
{
	m_nLength = GetPacketSize();
	m_pData = new char[m_nLength];
	memset(m_pData,0,m_nLength);
}

CGStarringAttribute::~CGStarringAttribute()
{
}

void CGStarringAttribute::Read()
{

}

void CGStarringAttribute::Write()
{
	UUCPacket::Write((char*)(&playerGuid), sizeof(int));
}

void CGStarringAttribute::Execute()
{
}
