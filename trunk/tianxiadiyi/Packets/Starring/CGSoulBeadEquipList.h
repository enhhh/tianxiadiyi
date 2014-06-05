#ifndef __CGSOUL_BEAD_EQUIP_LIST_H__
#define __CGSOUL_BEAD_EQUIP_LIST_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class CGSoulBeadEquipList : public UUPacketEXT
{
public:
	int playerGuid;

	CGSoulBeadEquipList();
	~CGSoulBeadEquipList();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute() ;

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_SOUL_BEAD_EQUIP_LIST, PACKET_GENERAL); }

	virtual unsigned int	GetPacketSize() const { return sizeof(int); }
};

class CGSoulBeadEquipListFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new CGSoulBeadEquipList(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_SOUL_BEAD_EQUIP_LIST, PACKET_GENERAL); }
};

class CGSoulBeadEquipListHandler
{
public:
	static void Execute( CGSoulBeadEquipList* pPacket);
};

#endif