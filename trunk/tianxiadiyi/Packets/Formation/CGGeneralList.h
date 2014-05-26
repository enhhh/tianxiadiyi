#ifndef __CGGENERAL_LIST_H__
#define __CGGENERAL_LIST_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class CGGeneralList : public UUPacketEXT
{
public:

	int playerGuid;

	CGGeneralList();
	~CGGeneralList();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute() ;

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_GENERAL_LIST, PACKET_GENERAL); }

	virtual unsigned int	GetPacketSize() const { return sizeof(int); }
};

class CGGeneralListFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new CGGeneralList(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_GENERAL_LIST, PACKET_GENERAL); }
};

class CGGeneralListHandler
{
public:
	static void Execute( CGGeneralList* pPacket);
};

#endif