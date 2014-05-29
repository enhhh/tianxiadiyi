#include "FormationManager.h"

static FormationManager* formationManager = NULL;

// ����
bool formationArrary[11][3][3] = 
{
	    // ������
	{
		{false, false, false},
		{true, false, false},
		{false, false, false}
	},
	    // һ�ֳ�����
	{
		{true, true, false},
		{true, false, false},
		{true, true, false}
	},
		// ������ˮ��
	{
		{true, true, false},
		{false, true, false},
		{true, true, false}
	},
		// ���������
	{
		{false, false, true},
		{true, true, true},
		{false, false, true}
	},
		// ���Ŷ�����
	{
		{false, true, false},
		{false, true, true},
		{true, true, true}
	},
		// �廢Ⱥ����
	{
		{true, true, true},
		{true, false, false},
		{true, false, false}
	},
		// ����������
	{
		{false, true, false},
		{false, true, false},
		{true, true, true}
	},
		// ����������
	{
		{false, true, true},
		{false, true, false},
		{true, true, false}
	},
		// ���Ž�����
	{
		{false, true, true},
		{true, false, false},
		{false, true, true}
	},
		// ����������
	{
		{true, false, true},
		{false, true, false},
		{true, false, true}
	},
		// ʮ�������
	{
		{true, true, true},
		{true, true, true},
		{true, true, true}
	},
};

FormationManager::FormationManager()
{
	for (int i = 0; i < 11; i++)
	{
		formationVector.push_back(new Formation(i));
	}

	generalVector = GeneralManager::getTheOnlyInstance()->generalVector;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			generalSpriteArray[i][j].general = NULL;
			generalSpriteArray[i][j].sprite = NULL;
		}
	}

	selectPreId = 0; 
	selectId = 0;

	pageNum = 0;
	maxPageNum = (generalVector.size()-1) / 8 + 1;

	if (generalVector.size() == 0)
	{
		maxPageNum = 0;
	}
}

FormationManager::~FormationManager()
{
}

FormationManager* FormationManager::getTheOnlyInstance()
{
	if (!formationManager)
	{
		formationManager = new FormationManager();
	}

	return formationManager;
}
