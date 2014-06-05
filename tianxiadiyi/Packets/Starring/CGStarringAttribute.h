#ifndef __CGSTARRING_ATTRIBUTE_H__
#define __CGSTARRING_ATTRIBUTE_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class CGStarringAttribute : public UUPacketEXT
{
public:

	int playerGuid;

	CGStarringAttribute();
	~CGStarringAttribute();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute() ;

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_GENERAL, PACKET_CG_STARRING_ATTRIBUTE); }

	virtual unsigned int	GetPacketSize() const { return sizeof(int); }
};

class CGStarringAttributeFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new CGStarringAttribute(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_GENERAL, PACKET_CG_STARRING_ATTRIBUTE); }
};

class CGStarringAttributeHandler
{
public:
	static void Execute( CGStarringAttribute* pPacket);
};

#endif