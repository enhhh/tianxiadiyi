#include "GCGeneralList.h"

GCGeneralList::GCGeneralList()
{
}

GCGeneralList::~GCGeneralList()
{
}

void GCGeneralList::Read()
{
	UUCPacket::Read((char*)(&num), sizeof(unsigned char));

	for (int i = 0; i < num; i++)
	{
		int generalId = 0;
		UUCPacket::Read((char*)(&generalId), sizeof(int));
		generalVector.push_back(generalId);
	}
}

void GCGeneralList::Write()
{
}

void GCGeneralList::Execute()
{
	GCGeneralListHandler::Execute(this);
}