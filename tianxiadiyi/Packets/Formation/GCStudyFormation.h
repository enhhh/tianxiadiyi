#ifndef __GC_STUDY_FORMATION_H__
#define __GC_STUDY_FORMATION_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class GCStudyFormation : public UUPacketEXT
{
public:
	char isSuccess;

	GCStudyFormation();
	~GCStudyFormation();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute();

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_STUDY_FORMATION, PACKET_GENERAL); }

	virtual unsigned int	GetPacketSize() const { return 0; }
};

class GCStudyFormationFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new GCStudyFormation(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_STUDY_FORMATION, PACKET_GENERAL); }
};

class GCStudyFormationHandler
{
public:
	static void Execute( GCStudyFormation* pPacket);
};

#endif