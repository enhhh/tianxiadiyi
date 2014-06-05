#ifndef __GCTELENT_LIST_H__
#define __GCTELENT_LIST_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class GCTelentList : public UUPacketEXT
{
public:

	char light[5];

	GCTelentList();
	~GCTelentList();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute();

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_TELENT_LIST, PACKET_GENERAL); }

	virtual unsigned int	GetPacketSize() const { return 0; }
};

class GCTelentListFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new GCTelentList(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_TELENT_LIST, PACKET_GENERAL); }
};

class GCTelentListHandler
{
public:
	static void Execute( GCTelentList* pPacket);
};

#endif