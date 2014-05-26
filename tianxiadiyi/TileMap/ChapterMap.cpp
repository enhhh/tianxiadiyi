#include "ChapterMap.h"

ChapterMap::ChapterMap()
{
	tiledMap = CCTMXTiledMap::create("map/huLaoChpaterMap.tmx");
}

ChapterMap::~ChapterMap()
{
}

void ChapterMap::updateEXT(float delta)
{
}

CCTMXTiledMap* ChapterMap::getTMXTiledMap()
{
	return tiledMap;
}