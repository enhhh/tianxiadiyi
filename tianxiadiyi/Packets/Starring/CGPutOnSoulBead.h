#ifndef __CGPUT_ON_SOUL_BEAD_H__
#define __CGPUT_ON_SOUL_BEAD_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class CGPutOnSoulBead : public UUPacketEXT
{
public:
	
	int playerGuid;
	char srcPosition;
	char destPosition;

	CGPutOnSoulBead();
	~CGPutOnSoulBead();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute() ;

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_PUT_ON_SOUL_BEAD, PACKET_GENERAL); }

	virtual unsigned int	GetPacketSize() const { return sizeof(int) + sizeof(char)*2; }
};

class CGPutOnSoulBeadFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new CGPutOnSoulBead(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_PUT_ON_SOUL_BEAD, PACKET_GENERAL); }
};

class CGPutOnSoulBeadHandler
{
public:
	static void Execute( CGPutOnSoulBead* pPacket);
};

#endif