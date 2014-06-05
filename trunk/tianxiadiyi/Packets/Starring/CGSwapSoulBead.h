#ifndef __CGSWAP_SOUL_BEAD_H__
#define __CGSWAP_SOUL_BEAD_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class CGSwapSoulBead : public UUPacketEXT
{
public:

	int playerGuid;
	char type;
	char srcPosition;
	char destPosition;

	CGSwapSoulBead();
	~CGSwapSoulBead();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute() ;

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_SWAP_SOUL_BEAD, PACKET_GENERAL); }

	virtual unsigned int	GetPacketSize() const { return sizeof(int) + sizeof(char)*3; }
};

class CGSwapSoulBeadFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new CGSwapSoulBead(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_SWAP_SOUL_BEAD, PACKET_GENERAL); }
};

class CGSwapSoulBeadHandler
{
public:
	static void Execute( CGSwapSoulBead* pPacket);
};

#endif