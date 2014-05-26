#ifndef __CGMODIFY_FORMATION_H__
#define __CGMODIFY_FORMATION_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class CGSelectFormation : public UUPacketEXT
{
public:

	int playerGuid;
	unsigned char formationId;

	CGSelectFormation();
	~CGSelectFormation();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute() ;

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_SELECT_FORMATION, PACKET_GENERAL); }

	virtual unsigned int	GetPacketSize() const { return sizeof(int) + sizeof(unsigned char); }
};

class CGSelectFormationFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new CGSelectFormation(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_SELECT_FORMATION, PACKET_GENERAL); }
};

class CGSelectFormationHandler
{
public:
	static void Execute( CGSelectFormation* pPacket);
};

#endif