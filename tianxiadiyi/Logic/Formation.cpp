#include "Formation.h"

Formation::Formation( int id )
{
	const tDataBase* formationTab = CDataBaseSystem::GetMe()->GetDataBase(DBC_FORMATION);
	const _DBC_FORMATION* formation = (_DBC_FORMATION*)formationTab->Search_Index_EQU(id);
	attribute = *formation;
}

Formation::~Formation()
{

}
