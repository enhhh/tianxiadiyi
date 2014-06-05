#ifndef __CGSOUL_BEAD_LIST_H__
#define __CGSOUL_BEAD_LIST_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class CGSoulBeadList : public UUPacketEXT
{
public:

	int playerGuid;

	CGSoulBeadList();
	~CGSoulBeadList();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute() ;

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_SOUL_BEAD_LIST, PACKET_GENERAL); }

	virtual unsigned int	GetPacketSize() const { return sizeof(int); }
};

class CGSoulBeadListFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new CGSoulBeadList(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_SOUL_BEAD_LIST, PACKET_GENERAL); }
};

class CGSoulBeadListHandler
{
public:
	static void Execute( CGSoulBeadList* pPacket);
};

#endif