#ifndef __GCSOUL_BEAD_EQUIP_LIST_H__
#define __GCSOUL_BEAD_EQUIP_LIST_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class GCSoulBeadEquipList : public UUPacketEXT
{
public:
	int soulBeadArray[10];

	GCSoulBeadEquipList();
	~GCSoulBeadEquipList();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute();

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_SOUL_BEAD_EQUIP_LIST, PACKET_GENERAL); }

	virtual unsigned int	GetPacketSize() const { return 0; }
};

class GCSoulBeadEquipListFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new GCSoulBeadEquipList(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_SOUL_BEAD_EQUIP_LIST, PACKET_GENERAL); }
};

class GCSoulBeadEquipListHandler
{
public:
	static void Execute( GCSoulBeadEquipList* pPacket);
};

#endif