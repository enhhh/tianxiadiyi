#ifndef __GC_MODIFY_FORMATION_H__
#define __GC_MODIFY_FORMATION_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class GCModifyFormation : public UUPacketEXT
{
public:
	char isSuccess;

	GCModifyFormation();
	~GCModifyFormation();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute();

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_MODIFY_FORMATION, PACKET_GENERAL); }

	virtual unsigned int	GetPacketSize() const { return 0; }
};

class GCModifyFormationFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new GCModifyFormation(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_MODIFY_FORMATION, PACKET_GENERAL); }
};

class GCModifyFormationHandler
{
public:
	static void Execute( GCModifyFormation* pPacket);
};

#endif