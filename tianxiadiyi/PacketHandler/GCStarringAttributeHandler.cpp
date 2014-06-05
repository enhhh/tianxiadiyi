#include "Packets\Starring\GCStarringAttribute.h"
#include "..\TianXiaDiYi.h"

void GCStarringAttributeHandler::Execute( GCStarringAttribute* pPacket)
{
	Player* player = TianXiaDiYi::getTheOnlyInstance()->mainCityScene->player;
	
	player->attribute.wuLi = pPacket->wuLi;
	player->attribute.zhiLi = pPacket->zhiLi;
	player->attribute.tiLi = pPacket->tiLi;
	player->attribute.minJie = pPacket->minJie;
}