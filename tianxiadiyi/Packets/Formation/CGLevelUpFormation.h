#ifndef __CGLEVEL_UP_FORMATION_H__
#define __CGLEVEL_UP_FORMATION_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class CGLevelUpFormation : public UUPacketEXT
{
public:

	int playerGuid;
	unsigned char formationId;

	CGLevelUpFormation();
	~CGLevelUpFormation();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute() ;

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_LEVEL_UP_FORMATION, PACKET_GENERAL); }

	virtual unsigned int	GetPacketSize() const { return sizeof(int) + sizeof(unsigned char); }
};

class CGLevelUpFormationFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new CGLevelUpFormation(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_LEVEL_UP_FORMATION, PACKET_GENERAL); }
};

class CGLevelUpFormationHandler
{
public:
	static void Execute( CGLevelUpFormation* pPacket);
};

#endif