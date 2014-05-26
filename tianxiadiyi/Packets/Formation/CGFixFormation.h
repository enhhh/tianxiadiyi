#ifndef __CGFIX_FORMATION_H__
#define __CGFIX_FORMATION_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class CGFixFormation : public UUPacketEXT
{
public:

	int playerGuid;
	unsigned char formationId;
	int generalId;
	unsigned char position;

	CGFixFormation();
	~CGFixFormation();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute() ;

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_FIX_FORMATION, PACKET_GENERAL); }

	virtual unsigned int	GetPacketSize() const { return sizeof(int)*2 + sizeof(unsigned char)*2; }
};

class CGFixFormationFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new CGFixFormation(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_FIX_FORMATION, PACKET_GENERAL); }
};

class CGFixFormationHandler
{
public:
	static void Execute( CGFixFormation* pPacket);
};

#endif