#ifndef __GCGENERAL_LIST_H__
#define __GCGENERAL_LIST_H__

#include <vector>

#include "Network\UUPacketEXT.h"
#include "Network\UUPacketFactory.h"
#include "Network\UUPacketFactoryManager.h"

using namespace std;

class GCGeneralList : public UUPacketEXT
{
public:
	unsigned char num;
	vector<int> generalVector;

	GCGeneralList();
	~GCGeneralList();

	virtual void			Read() ;

	virtual void			Write();

	virtual void			Execute();

	virtual unsigned short	GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_GENERAL_LIST, PACKET_GENERAL); }

	virtual unsigned int	GetPacketSize() const { return 0; }
};

class GCGeneralListFactory : public UUPacketFactory
{
public:
	UUPacketEXT*    CreatePacket() { return new GCGeneralList(); }

	unsigned short  GetPacketID() const { return MAKE_PACKET_ID(PACKET_CG_GENERAL_LIST, PACKET_GENERAL); }
};

class GCGeneralListHandler
{
public:
	static void Execute( GCGeneralList* pPacket);
};

#endif