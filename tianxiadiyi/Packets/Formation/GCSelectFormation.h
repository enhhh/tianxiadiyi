#ifndef __GC_SELECT_FORMATION_H__
#define __GC_SELECT_FORMATION_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class GCSelectFormation : public UUPacketEXT
{
public:
	unsigned char formationId[9];

	GCSelectFormation();
	~GCSelectFormation();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute();

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_SELECT_FORMATION, PACKET_GENERAL); }

	virtual unsigned int	GetPacketSize() const { return 0; }
};

class GCSelectFormationFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new GCSelectFormation(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_SELECT_FORMATION, PACKET_GENERAL); }
};

class GCSelectFormationHandler
{
public:
	static void Execute( GCSelectFormation* pPacket);
};

#endif