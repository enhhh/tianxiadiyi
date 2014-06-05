#include "GCLightUpTelent.h"

GCLightUpTelent::GCLightUpTelent()
{
}

GCLightUpTelent::~GCLightUpTelent()
{
}

void GCLightUpTelent::Read()
{
	UUCPacket::Read((char*)(&isSuccess), sizeof(char));
}

void GCLightUpTelent::Write()
{
}

void GCLightUpTelent::Execute()
{
	GCLightUpTelentHandler::Execute(this);
}