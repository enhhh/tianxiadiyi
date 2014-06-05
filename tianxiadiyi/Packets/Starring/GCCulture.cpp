#include "GCCulture.h"

GCCulture::GCCulture()
{
}

GCCulture::~GCCulture()
{
}

void GCCulture::Read()
{
	UUCPacket::Read((char*)(&isSuccess), sizeof(char));
}

void GCCulture::Write()
{
}

void GCCulture::Execute()
{
	GCCultureHandler::Execute(this);
}