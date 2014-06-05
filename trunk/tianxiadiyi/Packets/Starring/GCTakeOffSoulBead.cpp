#include "GCTakeOffSoulBead.h"

GCTakeOffSoulBead::GCTakeOffSoulBead()
{
}

GCTakeOffSoulBead::~GCTakeOffSoulBead()
{
}

void GCTakeOffSoulBead::Read()
{
	UUCPacket::Read((char*)(&isSuccess), sizeof(char));
}

void GCTakeOffSoulBead::Write()
{
}

void GCTakeOffSoulBead::Execute()
{
	GCTakeOffSoulBeadHandler::Execute(this);
}