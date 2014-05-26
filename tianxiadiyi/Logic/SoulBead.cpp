#include "SoulBead.h"

SoulBead::SoulBead(int id)
{
	armature = NULL;

	const tDataBase* soulBeadTab = CDataBaseSystem::GetMe()->GetDataBase(DBC_SOUL_BEAD);
	const _DBC_SOUL_BEAD* soulBead = (_DBC_SOUL_BEAD*)soulBeadTab->Search_LineNum_EQU(id);
	attribute = *soulBead;
}

SoulBead::~SoulBead()
{
}