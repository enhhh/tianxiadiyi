#ifndef __CGTELENT_LIST_H__
#define __CGTELENT_LIST_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class CGTelentList : public UUPacketEXT
{
public:

	int playerGuid;

	CGTelentList();
	~CGTelentList();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute() ;

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_TELENT_LIST, PACKET_GENERAL); }

	virtual unsigned int	GetPacketSize() const { return sizeof(int); }
};

class CGTelentListFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new CGTelentList(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_TELENT_LIST, PACKET_GENERAL); }
};

class CGTelentListHandler
{
public:
	static void Execute( CGTelentList* pPacket);
};

#endif