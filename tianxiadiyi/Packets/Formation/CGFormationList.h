#ifndef __CGFORMATION_LIST_H__
#define __CGFORMATION_LIST_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class CGFormationList : public UUPacketEXT
{
public:

	int playerGuid;

	CGFormationList();
	~CGFormationList();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute() ;

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_FORMATION_LIST, PACKET_GENERAL); }

	virtual unsigned int	GetPacketSize() const { return sizeof(int); }
};

class CGFormationListFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new CGFormationList(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_FORMATION_LIST, PACKET_GENERAL); }
};

class CGFormationListHandler
{
public:
	static void Execute( CGFormationList* pPacket);
};

#endif