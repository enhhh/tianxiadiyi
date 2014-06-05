#ifndef __GCSWAP_SOUL_BEAD_H__
#define __GCSWAP_SOUL_BEAD_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class GCSwapSoulBead : public UUPacketEXT
{
public:

	char isSuccess;

	GCSwapSoulBead();
	~GCSwapSoulBead();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute();

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_SWAP_SOUL_BEAD, PACKET_GENERAL); }

	virtual unsigned int	GetPacketSize() const { return 0; }
};

class GCSwapSoulBeadFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new GCSwapSoulBead(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_SWAP_SOUL_BEAD, PACKET_GENERAL); }
};

class GCSwapSoulBeadHandler
{
public:
	static void Execute( GCSwapSoulBead* pPacket);
};

#endif