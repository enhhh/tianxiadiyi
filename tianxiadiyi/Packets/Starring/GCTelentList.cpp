#include "GCTelentList.h"

GCTelentList::GCTelentList()
{
}

GCTelentList::~GCTelentList()
{
}

void GCTelentList::Read()
{
	for (int i = 0; i < 5; i++)
	{
		UUCPacket::Read((char*)(&light[i]), sizeof(char));
	}
}

void GCTelentList::Write()
{
}

void GCTelentList::Execute()
{
	GCTelentListHandler::Execute(this);
}