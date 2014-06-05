#ifndef __GCFORMATION_LIST_H__
#define __GCFORMATION_LIST_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class GCFormationList : public UUPacketEXT
{
public:
	unsigned char formation[10][2];

	GCFormationList();
	~GCFormationList();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute();

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_FORMATION_LIST, PACKET_GENERAL); }

	virtual unsigned int	GetPacketSize() const { return 0; }
};

class GCFormationListFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new GCFormationList(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_FORMATION_LIST, PACKET_GENERAL); }
};

class GCFormationListHandler
{
public:
	static void Execute( GCFormationList* pPacket);
};

#endif