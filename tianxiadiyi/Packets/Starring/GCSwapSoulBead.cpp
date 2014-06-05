#include "GCSwapSoulBead.h"

GCSwapSoulBead::GCSwapSoulBead()
{
}

GCSwapSoulBead::~GCSwapSoulBead()
{
}

void GCSwapSoulBead::Read()
{
	UUCPacket::Read((char*)(&isSuccess), sizeof(char));
}

void GCSwapSoulBead::Write()
{
}

void GCSwapSoulBead::Execute()
{
	GCSwapSoulBeadHandler::Execute(this);
}