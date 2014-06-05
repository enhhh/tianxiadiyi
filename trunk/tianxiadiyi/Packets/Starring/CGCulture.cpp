#include "CGCulture.h"

CGCulture::CGCulture()
{
	m_nLength = GetPacketSize();
	m_pData = new char[m_nLength];
	memset(m_pData,0,m_nLength);
}

CGCulture::~CGCulture()
{
}

void CGCulture::Read()
{
}

void CGCulture::Write()
{
	UUCPacket::Write((char*)(&playerGuid), sizeof(int));
	UUCPacket::Write((char*)(&type), sizeof(char));
}

void CGCulture::Execute()
{
}