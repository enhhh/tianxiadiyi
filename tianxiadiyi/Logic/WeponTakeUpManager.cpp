#include "WeponTakeUpManager.h"

static WeponTakeUpManager* weponTakeUpManagerManager = NULL;

WeponTakeUpManager::WeponTakeUpManager()
{
	itemManager = ItemManager::getTheOnlyInstance();
	generalManager = GeneralManager::getTheOnlyInstance();

	init();
}

WeponTakeUpManager::~WeponTakeUpManager()
{
}

WeponTakeUpManager* WeponTakeUpManager::getTheOnlyInstance()
{
	if (!weponTakeUpManagerManager)
	{
		weponTakeUpManagerManager = new WeponTakeUpManager();
	}

	return weponTakeUpManagerManager;
}

void WeponTakeUpManager::init()
{
	general = generalManager->generalVector[generalManager->selectGeneralId];
	equipment = generalManager->generalVector[generalManager->selectGeneralId]->equipmentArray[generalManager->selectEquipmentId];

	equipmentVector.clear();

	for (int i = 0; i < itemManager->maxPageNum*16; i++)
	{
		Item* item = itemManager->itemArray[i];

		if (item != NULL)
		{
			if (item->type == EQUIPMENT)
			{
				Equipment* equipment = (Equipment*)item;
				WeponTakeUpEquipment weponTakeUpEquipment = {i, equipment};

				switch (generalManager->selectEquipmentId)
				{
				case GENERAL_WU_QI:

					switch(general->attribute.zhiYe)
					{
					case MENG_JIANG:

						if ((equipment->attribute.zhongLei == DAO) ||
							(equipment->attribute.zhongLei == GONG_JIAN) ||
							(equipment->attribute.zhongLei == QIANG)
							)
						{
							equipmentVector.push_back(weponTakeUpEquipment);
						}

						break;
					case MOU_SHI:

						if ((equipment->attribute.zhongLei == SHANG_ZI) ||
							(equipment->attribute.zhongLei == JIAN)
							)
						{
							equipmentVector.push_back(weponTakeUpEquipment);
						}

						break;
					}
					break;
				case GENERAL_BING_FU:
					
					if (equipment->attribute.zhongLei == BING_FU)
					{
						equipmentVector.push_back(weponTakeUpEquipment);
					}
					
					break;
				case GENERAL_BING_SHU:
					
					if (equipment->attribute.zhongLei == BING_SHU)
					{
						equipmentVector.push_back(weponTakeUpEquipment);
					}
					
					break;
				case GENERAL_KAI_JIA:

					if ((equipment->attribute.zhongLei == KAI_JIA) && (equipment->attribute.xingBie == equipment->attribute.xingBie))
					{
						equipmentVector.push_back(weponTakeUpEquipment);
					}

					break;
				case GENERAL_PI_FENG:

					if ((equipment->attribute.zhongLei == PI_FENG) && (equipment->attribute.xingBie == equipment->attribute.xingBie))
					{
						equipmentVector.push_back(weponTakeUpEquipment);
					}

					break;
				case GENERAL_ZUO_JI:

					if (equipment->attribute.zhongLei == ZUO_JI)
					{
						equipmentVector.push_back(weponTakeUpEquipment);
					}

					break;
				}
			}
		}
	}

	selectEquipmentId = 0;

	pageNum = 0;
	maxPageNum = (equipmentVector.size()-1) / 3 + 1;

	if (equipmentVector.size() == 0)
	{
		maxPageNum = 0;
	}
}

void WeponTakeUpManager::takeUp()
{
	if (selectEquipmentId < equipmentVector.size())
	{
		WeponTakeUpEquipment weponTakeUpEquipment = equipmentVector[selectEquipmentId];
		
		Equipment* generalEquipment = generalManager->generalVector[generalManager->selectGeneralId]->equipmentArray[generalManager->selectEquipmentId];

		if (generalEquipment != NULL)
		{
			Equipment* t = (Equipment*)itemManager->itemArray[weponTakeUpEquipment.id];
			itemManager->itemArray[weponTakeUpEquipment.id] = generalManager->generalVector[generalManager->selectGeneralId]->equipmentArray[generalManager->selectEquipmentId];
			generalManager->generalVector[generalManager->selectGeneralId]->equipmentArray[generalManager->selectEquipmentId] = t;

			equipmentVector.erase(equipmentVector.begin()+selectEquipmentId);
		}
		else
		{
			generalManager->generalVector[generalManager->selectGeneralId]->equipmentArray[generalManager->selectEquipmentId] = weponTakeUpEquipment.equipment;
			itemManager->itemArray[weponTakeUpEquipment.id] = NULL;

			int zhiYe = generalManager->generalVector[generalManager->selectGeneralId]->attribute.zhiYe;
		}
	}
}
