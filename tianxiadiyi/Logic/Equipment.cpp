#include "Equipment.h"

Equipment::Equipment(int id)
{
	const tDataBase* equipmentTab = CDataBaseSystem::GetMe()->GetDataBase(DBC_EQUIPMENT);
	const _DBC_EQUIPMENT* equipment = (_DBC_EQUIPMENT*)equipmentTab->Search_LineNum_EQU(id);
	attribute = *equipment;

	gem = NULL;
	type = EQUIPMENT;
}

Equipment::~Equipment()
{
}