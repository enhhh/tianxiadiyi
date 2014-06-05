#include "GCSoulBeadList.h"

GCSoulBeadList::GCSoulBeadList()
{
}

GCSoulBeadList::~GCSoulBeadList()
{
}

void GCSoulBeadList::Read()
{
	UUCPacket::Read((char*)(&num), sizeof(int));

	maxPageNum = (num-1) / 12 + 1;

	if (maxPageNum > 0)
	{
		soulBeadArray = new int[maxPageNum*12];

		for (int i = 0; i < num; i++)
		{
			UUCPacket::Read((char*)(&soulBeadArray[i]), sizeof(int));
		}
	}
}

void GCSoulBeadList::Write()
{
}

void GCSoulBeadList::Execute()
{
	GCSoulBeadListHandler::Execute(this);
}