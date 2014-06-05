#include "GCHeartBeat.h"

GCHeartBeat::GCHeartBeat()
{
}

GCHeartBeat::~GCHeartBeat()
{
}

void GCHeartBeat::Read()
{
	UUCPacket::Read((char*)(&heartBeat2), sizeof(int));
}

void GCHeartBeat::Write()
{
}

void GCHeartBeat::Execute()
{
	GCHeartBeatHandler::Execute(this);
}