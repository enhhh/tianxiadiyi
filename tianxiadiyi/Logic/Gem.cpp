#include "Gem.h"

Gem::Gem(int id)
{
	const tDataBase* gemTab = CDataBaseSystem::GetMe()->GetDataBase(DBC_GEM);
	const _DBC_GEM* gem = (_DBC_GEM*)gemTab->Search_LineNum_EQU(id);
	attribute = *gem;

	type = GEM;
}

Gem::~Gem()
{
}
