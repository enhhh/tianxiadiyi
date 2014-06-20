#ifndef __ADVANCED_MANAGER_H__
#define __ADVANCED_MANAGER_H__

#include <vector>
#include <string>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "GeneralManager.h"
#include "Sprite\General.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace std;

class AdvancedManager
{
public:
	GeneralManager* generalManager;
	General* general;

	AdvancedManager();
	~AdvancedManager();

	static AdvancedManager* getTheOnlyInstance();
	void init();
	int getAdvancedAddAttribute();
	vector<string> getAdvancedConsume();
	void advanced();
};

#endif