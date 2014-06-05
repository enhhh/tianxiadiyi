#ifndef __GC_FIX_FORMATION_H__
#define __GC_FIX_FORMATION_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class GCFixFormation : public UUPacketEXT
{
public:
	char isSuccess;

	GCFixFormation();
	~GCFixFormation();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute();

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_FIX_FORMATION, PACKET_GENERAL); }

	virtual unsigned int	GetPacketSize() const { return 0; }
};

class GCFixFormationFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new GCFixFormation(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_FIX_FORMATION, PACKET_GENERAL); }
};

class GCFixFormationHandler
{
public:
	static void Execute( GCFixFormation* pPacket);
};

#endif