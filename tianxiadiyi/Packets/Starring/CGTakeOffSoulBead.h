#ifndef __CGTAKE_OFF_SOUL_BEAD_H__
#define __CGTAKE_OFF_SOUL_BEAD_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class CGTakeOffSoulBead : public UUPacketEXT
{
public:

	int playerGuid;
	char srcPosition;
	char destPosition;

	CGTakeOffSoulBead();
	~CGTakeOffSoulBead();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute() ;

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_TAKE_OFF_SOUL_BEAD, PACKET_GENERAL); }

	virtual unsigned int	GetPacketSize() const { return sizeof(int) + sizeof(char)*2; }
};

class CGTakeOffSoulBeadFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new CGTakeOffSoulBead(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_TAKE_OFF_SOUL_BEAD, PACKET_GENERAL); }
};

class CGTakeOffSoulBeadHandler
{
public:
	static void Execute( CGTakeOffSoulBead* pPacket);
};

#endif