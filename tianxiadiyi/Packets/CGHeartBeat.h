#ifndef __CGHEART_BEAT_H__
#define __CGHEART_BEAT_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class CGHeartBeat : public UUPacketEXT
{
public:
	int heartBeat1;

	CGHeartBeat();
	~CGHeartBeat();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute() ;

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_HEARTBEAT, PACKET_CG_HEARTBEAT); }

	virtual unsigned int	GetPacketSize() const { return sizeof(int); }
};

class CGHeartBeatFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new CGHeartBeat(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_HEARTBEAT, PACKET_CG_HEARTBEAT); }
};

class CGHeartBeatHandler
{
public:
	static void Execute( CGHeartBeat* pPacket);
};

#endif