#ifndef __GCHEART_BEAT_H__
#define __GCHEART_BEAT_H__

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

class GCHeartBeat : public UUPacketEXT
{
public:
	int heartBeat2;

	GCHeartBeat();
	~GCHeartBeat();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute();

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_HEARTBEAT, PACKET_CG_HEARTBEAT); }

	virtual unsigned int	GetPacketSize() const { return sizeof(int); }
};

class GCHeartBeatFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new GCHeartBeat(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_HEARTBEAT, PACKET_CG_HEARTBEAT); }
};

class GCHeartBeatHandler
{
public:
	static void Execute( GCHeartBeat* pPacket);
};

#endif