#include "GCSelectFormation.h"

GCSelectFormation::GCSelectFormation()
{
}

GCSelectFormation::~GCSelectFormation()
{
}

void GCSelectFormation::Read()
{
	for (int i = 0; i < 9; i++)
	{
		UUCPacket::Read((char*)(&formationId[i]), sizeof(int));
	}
}

void GCSelectFormation::Write()
{
}

void GCSelectFormation::Execute()
{
	GCSelectFormationHandler::Execute(this);
}