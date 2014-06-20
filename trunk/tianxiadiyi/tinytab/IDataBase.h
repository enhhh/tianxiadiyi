
/**	GIDataBase.h
 */

#pragma once


#include "BaseType.h"


/// ����WXSJ_DBC.h�еĹ�����
namespace DBC
{
	class DBCFile;
};

//===================================================
/// �ͻ������ڴ����ݿ�(DataBaseClient)

/// �ڴ����ݿ�
class tDataBase
{
public:

	/// �ֶ���������
	enum DBC_FIELD_TYPE
	{
		T_INT		= 0,	// ����
		T_FLOAT		= 1,	// ������
		T_STRING	= 2,	// �ַ���
	};

	// ���ݶ�
	union DBC_FIELD
	{
		FLOAT		fValue;
		INT			iValue;
		const CHAR*	pString;	// Just for runtime!

		// Construct
		DBC_FIELD() {}
		DBC_FIELD(INT value) { iValue = value; }
		DBC_FIELD(FLOAT value) { fValue = value; }
		DBC_FIELD(const CHAR* value) { pString = value; }
	};

public:

	// ������������
	virtual const DBC_FIELD* Search_Index_EQU(INT iIndexValue) const = 0;
	// ������
	virtual const DBC_FIELD* Search_LineNum_EQU(INT iLineNum) const = 0;
	// ����ĳ�е���ָ��ֵ�ĵ�һ��
	virtual const DBC_FIELD* Search_First_Column_Equ(INT nColumnNum, const DBC_FIELD& value) const = 0;
	//����ĳ�е���ָ��ֵ�ĵ�nRow��
	virtual const DBC_FIELD* Search_Column_Equ(INT nRow,INT nColumnNum, const DBC_FIELD& value) const = 0;

public:

	virtual	const DBC::DBCFile* GetDBCFile( VOID ) const = 0;
	// ȡ��ID
	virtual INT GetID(VOID) const = 0;
	// ȡ������
	virtual UINT GetFieldsNum(VOID) const = 0;
	// ȡ�ü�¼������
	virtual UINT GetRecordsNum(VOID) const = 0;
};	// class

/** ���ݿ������
 */
class tDataBaseSystem
{
public:
	/** ��ϵͳ���������ݿ� */
	virtual VOID OpenAllDataBase(VOID) = 0;
	/** �ر�ϵͳ���������ݿ� */
	virtual VOID CloseAllDataBase(VOID) = 0;
	/** �õ�һ���ѽ��򿪵����ݿ⣬�������ݿ�ָ�� */
	virtual const tDataBase* GetDataBase(INT idDataBase) const = 0;
};	// class