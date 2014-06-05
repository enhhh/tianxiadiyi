#include "GCFixFormation.h"

GCFixFormation::GCFixFormation()
{
}

GCFixFormation::~GCFixFormation()
{
}

void GCFixFormation::Read()
{
	UUCPacket::Read((char*)(&isSuccess), sizeof(char));
}

void GCFixFormation::Write()
{
}

void GCFixFormation::Execute()
{
	GCFixFormationHandler::Execute(this);
}