#include "GCStarringAttribute.h"

GCStarringAttribute::GCStarringAttribute()
{
}

GCStarringAttribute::~GCStarringAttribute()
{
}

void GCStarringAttribute::Read()
{
	UUCPacket::Read((char*)(&wuLi), sizeof(int));
	UUCPacket::Read((char*)(&zhiLi), sizeof(int));
	UUCPacket::Read((char*)(&tiLi), sizeof(int));
	UUCPacket::Read((char*)(&minJie), sizeof(int));
}

void GCStarringAttribute::Write()
{
}

void GCStarringAttribute::Execute()
{
	GCStarringAttributeHandler::Execute(this);
}