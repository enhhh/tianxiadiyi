#ifndef __CGCULTURE_H__
#define __CGCULTURE_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class CGCulture : public UUPacketEXT
{
public:

	int playerGuid;
	char type;

	CGCulture();
	~CGCulture();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute() ;

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_CULTURE, PACKET_GENERAL); }

	virtual unsigned int	GetPacketSize() const { return sizeof(int) + sizeof(char); }
};

class CGCultureFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new CGCulture(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_CULTURE, PACKET_GENERAL); }
};

class CGCultureHandler
{
public:
	static void Execute( CGCulture* pPacket);
};

#endif