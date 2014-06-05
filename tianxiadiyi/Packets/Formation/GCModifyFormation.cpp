#include "GCModifyFormation.h"

GCModifyFormation::GCModifyFormation()
{
}

GCModifyFormation::~GCModifyFormation()
{
}

void GCModifyFormation::Read()
{
	UUCPacket::Read((char*)(&isSuccess), sizeof(char));
}

void GCModifyFormation::Write()
{
}

void GCModifyFormation::Execute()
{
	GCModifyFormationHandler::Execute(this);
}