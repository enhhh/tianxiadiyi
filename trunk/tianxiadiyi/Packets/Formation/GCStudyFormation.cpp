#include "GCStudyFormation.h"

GCStudyFormation::GCStudyFormation()
{
}

GCStudyFormation::~GCStudyFormation()
{
}

void GCStudyFormation::Read()
{
	UUCPacket::Read((char*)(&isSuccess), sizeof(char));
}

void GCStudyFormation::Write()
{
}

void GCStudyFormation::Execute()
{
	GCStudyFormationHandler::Execute(this);
}