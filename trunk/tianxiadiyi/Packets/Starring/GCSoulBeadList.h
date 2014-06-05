#ifndef __GCSOUL_BEAD_LIST_H__
#define __GCSOUL_BEAD_LIST_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class GCSoulBeadList : public UUPacketEXT
{
public:

	int num;
	int maxPageNum;
	int* soulBeadArray;

	GCSoulBeadList();
	~GCSoulBeadList();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute();

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_SOUL_BEAD_LIST, PACKET_GENERAL); }

	virtual unsigned int	GetPacketSize() const { return 0; }
};

class GCSoulBeadListFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new GCSoulBeadList(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_SOUL_BEAD_LIST, PACKET_GENERAL); }
};

class GCSoulBeadListHandler
{
public:
	static void Execute( GCSoulBeadList* pPacket);
};

#endif