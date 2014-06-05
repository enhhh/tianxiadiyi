#ifndef __GCPUT_ON_SOUL_BEAD_H__
#define __GCPUT_ON_SOUL_BEAD_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class GCPutOnSoulBead : public UUPacketEXT
{
public:
	char isSuccess;

	GCPutOnSoulBead();
	~GCPutOnSoulBead();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute();

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_PUT_ON_SOUL_BEAD, PACKET_GENERAL); }

	virtual unsigned int	GetPacketSize() const { return 0; }
};

class GCPutOnSoulBeadFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new GCPutOnSoulBead(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_PUT_ON_SOUL_BEAD, PACKET_GENERAL); }
};

class GCPutOnSoulBeadHandler
{
public:
	static void Execute( GCPutOnSoulBead* pPacket);
};

#endif