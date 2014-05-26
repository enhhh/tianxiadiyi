#ifndef __UUPACKETEXT_H__
#define __UUPACKETEXT_H__

#include "UUPacket.h"

class Player;

#define MAKE_PACKET_ID(a, b) ((a<<8) + (b))
#define GET_PACKET_ID(a) ((a>>8)
#define GET_PACKET_SUB_ID(a) (a&OxFF)

class UUPacketEXT : public UUCPacket
{
public:
	UUPacketEXT(){};
	virtual ~UUPacketEXT(){};

	virtual void            CleanUp(){};

	virtual void            Read() = 0;

	virtual void            Write() = 0;

	virtual void            Execute() = 0;

	virtual	unsigned short  GetPacketID()const = 0;

	virtual	unsigned int    GetPacketSize()const = 0 ;
};

#endif