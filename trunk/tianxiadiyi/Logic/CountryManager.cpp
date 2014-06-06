#include "CountryManager.h"

static CountryManager* countryManager = NULL;

CountryManager::CountryManager()
{
	for (int i = 0; i < 20; i++)
	{
		CountryMember countryMember = 
		{
			10086,
			"т╛аж",
			1,
			1,
			10086,
			3,
			7
		};

		countryMemberVector.push_back(countryMember);
	}

	selectId = 0;
}

CountryManager::~CountryManager()
{
}

CountryManager* CountryManager::getTheOnlyInstance()
{
	if (!countryManager)
	{
		countryManager = new CountryManager();
	}

	return countryManager;
}

void CountryManager::verify()
{
}

void CountryManager::modify()
{

}

void CountryManager::appointment()
{

}

void CountryManager::quit()
{

}

void CountryManager::kick()
{
	if (countryMemberVector.size() == 0)
	{
		return;
	}
	
	countryMemberVector.erase(countryMemberVector.begin()+selectId);
	selectId -= 1;

	if (selectId < 0)
	{
		selectId = 0;
	}
}
