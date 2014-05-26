#include "CGStudyFormation.h"

CGStudyFormation::CGStudyFormation()
{
	m_nLength = GetPacketSize();
	m_pData = new char[m_nLength];
	memset(m_pData,0,m_nLength);
}

CGStudyFormation::~CGStudyFormation()
{
}

void CGStudyFormation::Read()
{
}

void CGStudyFormation::Write()
{
	UUCPacket::Write((char*)(&playerGuid), sizeof(int));
	UUCPacket::Write((char*)(&formationId), sizeof(unsigned char));
}

void CGStudyFormation::Execute()
{

}
