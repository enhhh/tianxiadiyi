#include "StateMachine.h"
#include "States.h"
#include "SpriteStates.h"

StateMachine::StateMachine(Sprite* sprite)
{
	previousState = NONE;
	currentState = STAND;
	this->sprite = sprite;
}

void StateMachine::enterState(int s)
{
	switch(s)
	{
		// վ��
		case STAND:
			Stand::enter(sprite);
			break;
			// ����
		case WALK:
			Walk::enter(sprite);
			break;
			// ǰ��
		case FORWARD_WALK:
			ForwardWalk::enter(sprite);
			break;
			// ����
		case BACKWARD_WALK:
			BackwardWalk::enter(sprite);
			break;
			// ���
		case FORWARD_RUN:
			FastForwardRun::enter(sprite);
			break;
			// ����
		case BACKWARD_RUN:
			FastBackwardRun::enter(sprite);
			break;
			// ��Ծ
		case JUMP_UP:
			JumpUp::enter(sprite);
			break;
			// ����
		case JUMP_DOWN:
			JumpDown::enter(sprite);
			break;
			// ����
		case GO_UP:
			GoUp::enter(sprite);
			break;
			// ����
		case GO_DOWN:
			GoDown::enter(sprite);
			break;
			// ����
		case ATTACK0:
		case ATTACK1:
		case ATTACK2:
		case ATTACK3:
		case ATTACK4:
			Attack::enter(sprite);
			break;
			// ����
		case HURT:
			Hurt::enter(sprite);
			break;
			// ����
		case DEAD:
			Dead::enter(sprite);
			break;
	}
}

void StateMachine::executeState()
{
	switch(currentState)
	{
		// վ��
		case STAND:
			Stand::execute(sprite);
			break;
			// ����
		case WALK:
			Walk::execute(sprite);
			break;
			// ǰ��
		case FORWARD_WALK:
			ForwardWalk::execute(sprite);
			break;
			// ����
		case BACKWARD_WALK:
			BackwardWalk::execute(sprite);
			break;
			// ���
		case FORWARD_RUN:
			FastForwardRun::execute(sprite);
			break;
			// ����
		case BACKWARD_RUN:
			FastBackwardRun::execute(sprite);
			break;
			// ��Ծ
		case JUMP_UP:
			JumpUp::execute(sprite);
			break;
			// ����
		case JUMP_DOWN:
			JumpDown::execute(sprite);
			break;
		    // ����
		case GO_DOWN:
			GoDown::execute(sprite);
			break;
			// ����
		case GO_UP:
			GoUp::execute(sprite);
			break;
		    // ����
		case ATTACK0:
		case ATTACK1:
		case ATTACK2:
		case ATTACK3:
		case ATTACK4:
			Attack::execute(sprite);
			break;
		    // ����
		case HURT:
			Hurt::execute(sprite);
			break;
		    // ����
		case DEAD:
			Dead::execute(sprite);
			break;
	}
}

void StateMachine::exitState(int s)
{
	switch(s)
	{
		// վ��
		case STAND:
			Stand::exit(sprite);
			break;
			// ����
		case WALK:
			Walk::exit(sprite);
			break;
			// ǰ��
		case FORWARD_WALK:
			ForwardWalk::exit(sprite);
			break;
			// ����
		case BACKWARD_WALK:
			BackwardWalk::exit(sprite);
			break;
			// ���
		case FORWARD_RUN:
			FastForwardRun::exit(sprite);
			break;
			// ����
		case BACKWARD_RUN:
			FastBackwardRun::exit(sprite);
			break;
			// ��Ծ
		case JUMP_UP:
			JumpUp::exit(sprite);
			break;
			// ����
		case JUMP_DOWN:
			JumpDown::exit(sprite);
			break;
			// ����
		case GO_DOWN:
			GoDown::exit(sprite);
			break;
			// ����
		case GO_UP:
			GoUp::exit(sprite);
			break;
			// ����
		case ATTACK0:
		case ATTACK1:
		case ATTACK2:
		case ATTACK3:
		case ATTACK4:
			Attack::exit(sprite);
			break;
			// ����
		case HURT:
			Hurt::exit(sprite);
			break;
			// ����
		case DEAD:
			Dead::exit(sprite);
			break;
	}
}

void StateMachine::setCurrentState(int s)
{
	currentState = s;
}

int StateMachine::getCurrentState()
{
	return currentState;
}

void StateMachine::setPreviousState(int s)
{
	previousState = s;
}
	
int StateMachine::getPreviousState()
{
	return previousState;
}

void StateMachine::changeState(int newState)
{
	previousState = currentState;
	exitState(currentState);
	currentState = newState;
	enterState(newState);
}

void StateMachine::revertToPreviousState()
{
	changeState(previousState);
}
