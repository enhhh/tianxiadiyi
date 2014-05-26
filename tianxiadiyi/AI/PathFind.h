#ifndef __PATH_FIND_H__
#define __PATH_FIND_H__

#include <list>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace std;

// ������ṹ
typedef struct tagAstartListNode
{
    // ��� x ����
    short x;

    //��� y ����
    short y;

    // ��ǰ��㵽��ʼ���Ĵ���
    short f;

    // ��ǰ��㵽Ŀ����Ĵ���
    short g;

    // �ܴ���
    short h;

    // ��ǰ��㸸���
    struct tagAstartListNode* father;

    // ��ǰ����ӽ��
    struct tagAstartListNode* next;
} AstartListNode;

// A*�㷨�ṹ
typedef struct tagAstar
{
    // open ��
    AstartListNode* openHead;

    // closed ��
    AstartListNode* closedHead;
} Astar;

class PathFind
{
public:

	PathFind();
	~PathFind();

	// ·������
	int astarPathCount;

	// ·����
	list<CCPoint> astarPathList;

	CCTMXTiledMap* tiledMap;

	int startX;
	int startY;
	int endX;
	int endY;

	static PathFind* getTheOnlyInstance();

	void setTiledMap(CCTMXTiledMap* tiledMap);

	// A*��ʼ��
	Astar* newAstar();

	// A*�ͷ�
	void deleteAstar(Astar* Astar);

	// ����ʼ��
	void AstarNodeInit(AstartListNode* current, AstartListNode* father, int x, int y, int endX, int endY);

	// ȡ�óɱ���С�Ľ��
	AstartListNode* AstarGetMinCostList(Astar* Astar);

	// ��ӽ�㵽����
	void AstarAddNode(AstartListNode* head, AstartListNode* node);

	// ��������ɾ�����
	void AstarRemoveNode(AstartListNode* head, AstartListNode* node);

	// ���Tile�Ƿ���������
	bool AstarCheckNodeInList(int x, int y, AstartListNode* head);

	// ���Tile�Ƿ��ǵ�ͼ��·��
	bool AstarIsBlock(int x, int y);

	bool AStarSearch(CCTMXTiledMap* tiledMap, int startX, int startY, int endX, int endY);
};

#endif