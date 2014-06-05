#include "CGLightUpTelent.h"

CGLightUpTelent::CGLightUpTelent()
{
	m_nLength = GetPacketSize();
	m_pData = new char[m_nLength];
	memset(m_pData,0,m_nLength);
}

CGLightUpTelent::~CGLightUpTelent()
{
}

void CGLightUpTelent::Read()
{

}

void CGLightUpTelent::Write()
{
	UUCPacket::Write((char*)(&playerGuid), sizeof(int));
	UUCPacket::Write((char*)(&type), sizeof(char));
}

void CGLightUpTelent::Execute()
{
}
