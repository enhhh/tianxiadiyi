#ifndef __GCSTARRING_ATTRIBUTE_H__
#define __GCSTARRING_ATTRIBUTE_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class GCStarringAttribute : public UUPacketEXT
{
public:
	// 武力
	int wuLi;
	// 智力
	int zhiLi;
	// 体力
	int tiLi;
	// 敏捷
	int minJie;

	GCStarringAttribute();
	~GCStarringAttribute();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute();

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_GENERAL, PACKET_CG_STARRING_ATTRIBUTE); }

	virtual unsigned int	GetPacketSize() const { return 0; }
};

class GCStarringAttributeFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new GCStarringAttribute(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_GENERAL, PACKET_CG_STARRING_ATTRIBUTE); }
};

class GCStarringAttributeHandler
{
public:
	static void Execute( GCStarringAttribute* pPacket);
};

#endif