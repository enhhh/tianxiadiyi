#include "GCFormationList.h"

GCFormationList::GCFormationList()
{
}

GCFormationList::~GCFormationList()
{
}

void GCFormationList::Read()
{
	for (int i = 0; i < 10; i++)
	{
		UUCPacket::Read((char*)(&formation[i][0]), sizeof(unsigned char));
		UUCPacket::Read((char*)(&formation[i][1]), sizeof(unsigned char));
	}
}

void GCFormationList::Write()
{
}

void GCFormationList::Execute()
{
	GCFormationListHandler::Execute(this);
}