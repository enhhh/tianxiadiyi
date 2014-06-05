#ifndef __CGLIGHT_UP_TELENT_H__
#define __CGLIGHT_UP_TELENT_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class CGLightUpTelent : public UUPacketEXT
{
public:

	int playerGuid;
	char type;

	CGLightUpTelent();
	~CGLightUpTelent();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute() ;

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_LIGHT_UP_TELENT, PACKET_GENERAL); }

	virtual unsigned int	GetPacketSize() const { return sizeof(int) + sizeof(byte); }
};

class CGLightUpTelentFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new CGLightUpTelent(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_LIGHT_UP_TELENT, PACKET_GENERAL); }
};

class CGLightUpTelentHandler
{
public:
	static void Execute( CGLightUpTelent* pPacket);
};

#endif