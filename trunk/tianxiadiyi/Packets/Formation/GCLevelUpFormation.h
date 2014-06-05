#ifndef __GC_LEVEL_UP_FORMATION_H__
#define __GC_LEVEL_UP_FORMATION_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class GCLevelUpFormation : public UUPacketEXT
{
public:
	unsigned char formationId;
	unsigned char formationLevel;

	GCLevelUpFormation();
	~GCLevelUpFormation();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute();

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_LEVEL_UP_FORMATION, PACKET_GENERAL); }

	virtual unsigned int	GetPacketSize() const { return 0; }
};

class GCLevelUpFormationFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new GCLevelUpFormation(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_LEVEL_UP_FORMATION, PACKET_GENERAL); }
};

class GCLevelUpFormationHandler
{
public:
	static void Execute( GCLevelUpFormation* pPacket);
};

#endif