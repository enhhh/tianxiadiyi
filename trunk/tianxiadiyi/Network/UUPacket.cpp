#include "UUPacket.h"

void UUCPacket::Read( char* buf, unsigned int len )
{
	memcpy( buf, m_pData+skip, len ) ;
	skip += len;
}

void UUCPacket::Write( const char* buf, unsigned int len )
{
	memcpy(m_pData+skip, buf, len ) ;
	skip += len;
}