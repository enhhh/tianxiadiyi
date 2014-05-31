#include "CountryManager.h"

static CountryManager* countryManager = NULL;

CountryManager::CountryManager()
{
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

}
