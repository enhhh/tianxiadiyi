#ifndef __SPRITE_STATES_H_
#define __SPRITE_STATES_H_

#include "Sprite\Sprite.h"

// վ��
class Sprite;
class Stand
{
public:
	static void enter(Sprite* sprite);
	static void execute(Sprite* sprite);
	static void exit(Sprite* sprite);
};

// ����
class Walk
{
public:
	static void enter(Sprite* sprite);
	static void execute(Sprite* sprite);
	static void exit(Sprite* sprite);
};

// ǰ��
class ForwardWalk
{
public:
	static void enter(Sprite* sprite);
	static void execute(Sprite* sprite);
	static void exit(Sprite* sprite);
};

// ����
class BackwardWalk
{
public:
	static void enter(Sprite* sprite);
	static void execute(Sprite* sprite);
	static void exit(Sprite* sprite);
};

// ���
class FastForwardRun
{
public:
	static void enter(Sprite* sprite);
	static void execute(Sprite* sprite);
	static void exit(Sprite* sprite);
};

// ����
class FastBackwardRun
{
public:
	static void enter(Sprite* sprite);
	static void execute(Sprite* sprite);
	static void exit(Sprite* sprite);
};

// ��Ծ
class JumpUp
{
public:
	static void enter(Sprite* sprite);
	static void execute(Sprite* sprite);
	static void exit(Sprite* sprite);
};

// ����
class JumpDown
{
public:
	static void enter(Sprite* sprite);
	static void execute(Sprite* sprite);
	static void exit(Sprite* sprite);
};

// ����
class GoDown
{
public:
	static void enter(Sprite* sprite);
	static void execute(Sprite* sprite);
	static void exit(Sprite* sprite);
};

// ����
class GoUp
{
public:
	static void enter(Sprite* sprite);
	static void execute(Sprite* sprite);
	static void exit(Sprite* sprite);
};

// ����
class Attack
{
public:
	static void enter(Sprite* sprite);
	static void execute(Sprite* sprite);
	static void exit(Sprite* sprite);
};

// ����
class Hurt
{
public:
	static void enter(Sprite* sprite);
	static void execute(Sprite* sprite);
	static void exit(Sprite* sprite);
};

// ����
class Dead
{
public:
	static void enter(Sprite* sprite);
	static void execute(Sprite* sprite);
	static void exit(Sprite* sprite);
};

#endif