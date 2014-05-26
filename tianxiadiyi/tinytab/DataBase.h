
/** GMDataBase.h
 *	
 *	���ܣ�	���ݿ�ϵͳ�� �ͻ���������ȡ���ݱ�
 *	
 *	�޸ļ�¼��	
 *			
 *			
 */

#pragma once
#include "IDataBase.h"

//----------------------------------------------------------
//���ݿ�
class CDataBase : public tDataBase
{
public:

	//������������
	virtual const DBC_FIELD*	Search_Index_EQU(INT iIndexValue) const;
	//������
	virtual const DBC_FIELD*	Search_LineNum_EQU(INT iLineNum) const;
	//����ĳ�е���ָ��ֵ�ĵ�һ��
	virtual const DBC_FIELD*	Search_First_Column_Equ(INT nColumnNum, const DBC_FIELD& value) const;
	virtual const DBC_FIELD*	Search_Column_Equ(INT nRow,INT nColumnNum, const DBC_FIELD& value) const;
public:

	virtual	const DBC::DBCFile*	GetDBCFile( VOID ) const		{ return m_pFileDBC; }
	//ȡ��ID
	virtual INT					GetID(VOID)const;
	//ȡ������
	virtual UINT				GetFieldsNum(VOID)const;
	//ȡ�ü�¼������
	virtual UINT				GetRecordsNum(VOID)const;
	//ֱ�Ӵ�һ��dbc�ļ�
	static BOOL					Util_OpenDBCFromTxt(const CHAR* szFileName, DBC::DBCFile* pDBCFile);

	// �и��ַ��������á�|���ָ���ַ���˳���ֳ����������������ַ���
	// ������(��Ҫ�������ַ����� �ڼ������ݣ� ������ַ���)
	static BOOL					GetSplitData( const CHAR* szData, UINT nCount, CHAR* szOutStr );

	//����GetSplitData,���и���ֵ,��INT�ͷ���
	static INT					GetSplitData_Int( const CHAR* szData, UINT nCount);

protected:
	// �����ַ����� ָ���ַ��� ��ĳ��λ��, ����Ϊ�ַ����±�
	static INT					GetCharOff( const CHAR* szStr, const CHAR ch, UINT nCount);


public:
	CDataBase(INT id);
	virtual ~CDataBase();

protected:

	//���ı��ļ�������һ�����ݿ�
	BOOL					OpenFromTXT(const CHAR* szFileName);

protected:
	DBC::DBCFile*			m_pFileDBC;

	friend class CDataBaseSystem;
};

//----------------------------------------------------------
//���ݿ������
class CDataBaseSystem : public tDataBaseSystem
{
public:
	//��ϵͳ���������ݿ�
	virtual VOID				OpenAllDataBase(VOID);
	//�ر�ϵͳ���������ݿ�
	virtual VOID				CloseAllDataBase(VOID);
	//�õ�һ���ѽ��򿪵����ݿ⣬�������ݿ�ָ��
	virtual const tDataBase*	GetDataBase(INT idDataBase) const;

public:
	virtual VOID				Initial(VOID*);
	virtual VOID				Release(VOID);

protected:

protected:
	//���ݿ�
	std::map< INT, CDataBase* >	m_mapDataBaseBuf;

public:
	CDataBaseSystem();
	virtual ~CDataBaseSystem();
	static CDataBaseSystem* GetMe(VOID) 
	{
		static CDataBaseSystem dataBaseSystem; 
		return &dataBaseSystem;
	}

protected:
	static CDataBaseSystem* s_pMe;
};