#ifndef __GCTAKE_OFF_SOUL_BEAD_H__
#define __GCTAKE_OFF_SOUL_BEAD_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class GCTakeOffSoulBead : public UUPacketEXT
{
public:

	char isSuccess;

	GCTakeOffSoulBead();
	~GCTakeOffSoulBead();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute();

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_TAKE_OFF_SOUL_BEAD, PACKET_GENERAL); }

	virtual unsigned int	GetPacketSize() const { return 0; }
};

class GCTakeOffSoulBeadFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new GCTakeOffSoulBead(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_TAKE_OFF_SOUL_BEAD, PACKET_GENERAL); }
};

class GCTakeOffSoulBeadHandler
{
public:
	static void Execute( GCTakeOffSoulBead* pPacket);
};

#endif