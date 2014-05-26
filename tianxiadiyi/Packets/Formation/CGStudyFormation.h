#ifndef __CGSTUDY_FORMATION_H__
#define __CGSTUDY_FORMATION_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class CGStudyFormation : public UUPacketEXT
{
public:

	int playerGuid;
	unsigned char formationId;

	CGStudyFormation();
	~CGStudyFormation();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute() ;

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_STUDY_FORMATION, PACKET_GENERAL); }

	virtual unsigned int	GetPacketSize() const { return sizeof(int) + sizeof(unsigned char); }
};

class CGStudyFormationFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new CGStudyFormation(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_STUDY_FORMATION, PACKET_GENERAL); }
};

class CGStudyFormationHandler
{
public:
	static void Execute( CGStudyFormation* pPacket);
};

#endif