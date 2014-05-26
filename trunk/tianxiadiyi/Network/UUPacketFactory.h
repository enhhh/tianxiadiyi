#ifndef __UUPACKET_FACTORY_H__
#define __UUPACKET_FACTORY_H__

#include "UUPacketEXT.h"

class UUPacketFactory
{
public:
	virtual ~UUPacketFactory() {}

	virtual UUPacketEXT*    CreatePacket() = 0;

	virtual unsigned short  GetPacketID() const = 0;
};

#endif