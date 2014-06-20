#ifndef __CHAPTER_MANAGER_H__
#define __CHAPTER_MANAGER_H__

#include <vector>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "tinytab\DataBase.h"
#include "tinytab\DBC_Struct.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace std;

struct Charpter
{
	bool isEnabel;
};

class ChapterManager
{
public:

	vector<Charpter>chapterVector;
	int selectChapterId;
	int selectRoundId;
	int selectLevelId;

	bool formationArmyArray[3][3];

	ChapterManager();
	~ChapterManager();

	static ChapterManager* getTheOnlyInstance();

	vector<string> getArmyVector();

	void setArmyFormation();
};

#endif