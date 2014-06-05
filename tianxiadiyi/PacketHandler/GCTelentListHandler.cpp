#include "Packets\Starring\GCTelentList.h"
#include "Logic\StarringManager.h"

void GCTelentListHandler::Execute( GCTelentList* pPacket)
{
	StarringManager* starringManager = StarringManager::getTheOnlyInstance();

	for (int i = 0; i < 5; i++)
	{
		starringManager->telentLightPoint[i] = pPacket->light[i];
	}
}
