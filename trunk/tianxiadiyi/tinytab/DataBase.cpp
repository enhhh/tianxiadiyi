
/**	GMDataBase.cpp
 *
 *	���ܣ�	����ȫ�������ñ�
 *
 *	�޸ļ�¼��
 *			080324	���� DBC_EQUIP_LOC ������ǻ�װ������
 *			
 *			080331	���� DayTips.tab
 *			080410	���� TopList.tab
 *			080410	���� questlog.tab
 */
#include <assert.h>

#include "DataBase.h"
#include "DBC.h"
#include "DBC_Struct.h"

//============================================================================

CDataBase::CDataBase(INT id)
{
	m_pFileDBC = new DBC::DBCFile(id);
}

CDataBase::~CDataBase()
{
	delete m_pFileDBC;
}


const tDataBase::DBC_FIELD* CDataBase::Search_Index_EQU(INT iIndexValue) const 
{
	return (DBC_FIELD*)m_pFileDBC->Search_Index_EQU(iIndexValue);
}

const tDataBase::DBC_FIELD* CDataBase::Search_LineNum_EQU(INT iLineNum) const
{
	return  (DBC_FIELD*)m_pFileDBC->Search_Posistion(iLineNum, 0); 
}

// ����ĳ�е���ָ��ֵ�ĵ�һ��
const tDataBase::DBC_FIELD* CDataBase::Search_First_Column_Equ(INT nColumnNum, const DBC_FIELD& value) const
{
	return (DBC_FIELD*)m_pFileDBC->Search_First_Column_Equ(nColumnNum, value.iValue);
}


//����ĳ�е���ָ��ֵ�ĵ�nRow��
const tDataBase::DBC_FIELD*	CDataBase::Search_Column_Equ(INT nRow,INT nColumnNum, const DBC_FIELD& value) const
{
	return (DBC_FIELD*)m_pFileDBC->Search_Column_Equ(nRow,nColumnNum,value.iValue);
}

// ȡ��ID
INT CDataBase::GetID(VOID) const
{
	return m_pFileDBC->GetID(); 
}

// ȡ������
UINT CDataBase::GetFieldsNum(VOID) const
{ 
	return m_pFileDBC->GetFieldsNum(); 
}

// ȡ�ü�¼������
UINT CDataBase::GetRecordsNum(VOID) const
{ 
	return m_pFileDBC->GetRecordsNum(); 
}

// ֱ�Ӵ�һ��dbc�ļ�
BOOL CDataBase::Util_OpenDBCFromTxt(const CHAR* szFileName, DBC::DBCFile* pDBCFile)
{
	STRING strFileName = "tab/";
	strFileName += szFileName;
	if (::PathFileExistsA(strFileName.c_str()))
	{
		return pDBCFile->OpenFromTXT(strFileName.c_str()); 
	}

	return FALSE;
}

BOOL CDataBase::OpenFromTXT(const CHAR* szFileName)
{
	return Util_OpenDBCFromTxt(szFileName, m_pFileDBC);
}


vector<CHAR*> CDataBase::GetSplitData(const CHAR* szData)
{
	vector<CHAR*> splitVector;
	CHAR s[] = "1|2|3|4|5";
	const CHAR* d = "|";
	CHAR* p;

	p = strtok(s, d);

	while(p)
	{
		splitVector.push_back(p);
		p = strtok(NULL, d);
	}

	return splitVector;
}

INT CDataBase::GetSplitData_Int( const CHAR* szData, UINT nCount)
{
	return -1;
}

INT CDataBase::GetCharOff(const CHAR* szStr, const CHAR ch, UINT nCount)
{
	if (NULL == szStr)
		return -1;

	int nNum = 0;
	int nSize = (int)strlen(szStr);

	for (int i=0; i<nSize; ++i)
	{
		if (ch == szStr[i])
		{
			++nNum;
			if (nNum >= nCount)
				return i;
		}
	}

	return -1;
}


//============================================================================
CDataBaseSystem* CDataBaseSystem::s_pMe = NULL;

CDataBaseSystem::CDataBaseSystem()
{
	s_pMe = this;
}

CDataBaseSystem::~CDataBaseSystem()
{
}


VOID CDataBaseSystem::Initial(VOID*)
{
	OpenAllDataBase();
}

VOID CDataBaseSystem::Release(VOID)
{
	CloseAllDataBase();
}

VOID CDataBaseSystem::OpenAllDataBase(VOID)
{
	// ������Ҫ�򿪵����ݿⶨ��
	struct _DATABASE_DEFINE
	{
		INT				idDatabase;
		const CHAR*		pFileName;
	};

	_DATABASE_DEFINE  s_dbToLoad[] = 
	{
		{ DBC_GENERAL,  "general.txt"	},	// �佫��
		{ DBC_SOLIDER,  "solider.txt"	},	// ʿ����
		{ DBC_FORMATION,  "formation.txt"	},	// ���ͱ�
		{ DBC_EQUIPMENT,  "equipment.txt"	},	// װ����
		{ DBC_SKILL,  "skill.txt"	},	// ���ܱ�
		{ DBC_GEM,  "gem.txt"	},	// ��ʯ��
		{ DBC_SOUL_BEAD,  "soulBead.txt"	},	// �����
		{ DBC_RIDE,  "ride.txt"	},	// �����
		{ DBC_TELENT,  "talent.txt"	},	// �츳��
		{ DBC_GEM_STRENGTHEN, "gemStrengthen.txt"} // ��ʯǿ����
	};

	// ���������ݿ�
	INT nNum = sizeof(s_dbToLoad)/sizeof(_DATABASE_DEFINE);
	for(INT i=0; i<nNum; i++)
	{
		CDataBase* pDataBase = new CDataBase(s_dbToLoad[i].idDatabase);
		if( !pDataBase )
			return; //KLhrow( "New DataBase %d Error!", nNum );

		if(!(pDataBase->OpenFromTXT (s_dbToLoad[i].pFileName)))
		{
			return; //KLThrow("Open %s Error!", s_dbToLoad[i].pFileName);
		}

		if(m_mapDataBaseBuf.find(s_dbToLoad[i].idDatabase) != m_mapDataBaseBuf.end())
		{
			return; //KLThrow("DBC ID Multi define(%s)", s_dbToLoad[i].pFileName);
		}

		m_mapDataBaseBuf.insert(std::make_pair(s_dbToLoad[i].idDatabase, pDataBase));
	}
}

VOID CDataBaseSystem::CloseAllDataBase(VOID)
{
	std::map< INT, CDataBase* >::iterator it;
	for(it = m_mapDataBaseBuf.begin(); it!=m_mapDataBaseBuf.end(); it++)
	{
		if(it->second)
		{
			delete (it->second);
			it->second = NULL;
		}
	}

	m_mapDataBaseBuf.clear();
}

const tDataBase* CDataBaseSystem::GetDataBase(INT idDataBase) const
{
	std::map< INT, CDataBase* >::const_iterator it = m_mapDataBaseBuf.find(idDataBase);
	return (const tDataBase*)(it->second);
}