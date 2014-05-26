#ifndef __CGMODYFY_FORMATION_H__
#define __CGMODYFY_FORMATION_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class CGModifyFormation : public UUPacketEXT
{
public:

	int playerGuid;
	unsigned char formationId;
	unsigned char srcPosition;
	unsigned char destPosition;

	CGModifyFormation();
	~CGModifyFormation();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute() ;

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_MODIFY_FORMATION, PACKET_GENERAL); }

	virtual unsigned int	GetPacketSize() const { return sizeof(int) + sizeof(unsigned char)*3; }
};

class CGModifyFormationFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new CGModifyFormation(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_MODIFY_FORMATION, PACKET_GENERAL); }
};

class CGModifyFormationHandler
{
public:
	static void Execute( CGModifyFormation* pPacket);
};

#endif