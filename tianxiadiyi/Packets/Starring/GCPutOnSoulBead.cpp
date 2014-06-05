#include "GCPutOnSoulBead.h"

GCPutOnSoulBead::GCPutOnSoulBead()
{
}

GCPutOnSoulBead::~GCPutOnSoulBead()
{
}

void GCPutOnSoulBead::Read()
{
	UUCPacket::Read((char*)(&isSuccess), sizeof(char));
}

void GCPutOnSoulBead::Write()
{
}

void GCPutOnSoulBead::Execute()
{
	GCPutOnSoulBeadHandler::Execute(this);
}