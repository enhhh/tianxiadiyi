#ifndef __GCCULTURE_H__
#define __GCCULTURE_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class GCCulture : public UUPacketEXT
{
public:
	char isSuccess;

	GCCulture();
	~GCCulture();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute();

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_GENERAL, PACKET_CG_CULTURE); }

	virtual unsigned int	GetPacketSize() const { return 0; }
};

class GCCultureFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new GCCulture(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_GENERAL, PACKET_CG_CULTURE); }
};

class GCCultureHandler
{
public:
	static void Execute( GCCulture* pPacket);
};

#endif