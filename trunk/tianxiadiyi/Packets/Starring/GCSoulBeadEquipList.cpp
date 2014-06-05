#include "GCSoulBeadEquipList.h"

GCSoulBeadEquipList::GCSoulBeadEquipList()
{
}

GCSoulBeadEquipList::~GCSoulBeadEquipList()
{
}

void GCSoulBeadEquipList::Read()
{
	for (int i = 0; i < 10; i++)
	{
		UUCPacket::Read((char*)(&soulBeadArray[i]), sizeof(int));
	}
}

void GCSoulBeadEquipList::Write()
{
}

void GCSoulBeadEquipList::Execute()
{
	GCSoulBeadEquipListHandler::Execute(this);
}