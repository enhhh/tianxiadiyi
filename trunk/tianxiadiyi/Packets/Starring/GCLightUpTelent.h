#ifndef __GCLIGHT_UP_TELENT_H__
#define __GCLIGHT_UP_TELENT_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class GCLightUpTelent : public UUPacketEXT
{
public:

	char isSuccess;

	GCLightUpTelent();
	~GCLightUpTelent();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute();

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_LIGHT_UP_TELENT, PACKET_GENERAL); }

	virtual unsigned int	GetPacketSize() const { return 0; }
};

class GCLightUpTelentFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new GCLightUpTelent(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_LIGHT_UP_TELENT, PACKET_GENERAL); }
};

class GCLightUpTelentHandler
{
public:
	static void Execute( GCLightUpTelent* pPacket);
};

#endif