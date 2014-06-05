#include "GCLevelUpFormation.h"

GCLevelUpFormation::GCLevelUpFormation()
{
}

GCLevelUpFormation::~GCLevelUpFormation()
{
}

void GCLevelUpFormation::Read()
{
	UUCPacket::Read((char*)(&formationId), sizeof(char));
	UUCPacket::Read((char*)(&formationLevel), sizeof(char));
}

void GCLevelUpFormation::Write()
{
}

void GCLevelUpFormation::Execute()
{
	GCLevelUpFormationHandler::Execute(this);
}