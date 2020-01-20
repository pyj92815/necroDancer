#pragma once
#include "stdafx.h"

// ���� ����
enum BOSSTYPE
{
	EMPTY,
	DEATH_METAL
};

// ���� ������ ����
enum BOSS_PHASESTATE	// ������ ������ ����
{
	BP_NORMAL,
	BP_PHASE_1,
	BP_PHASE_2,
	BP_PHASE_3,
	BP_PHASE_4
};

// ���� ���� ����
enum BOSS_DIRECTION		// ������ ����
{
	BD_LEFT,
	BD_UP,
	BD_RIGHT,
	BD_DOWN
};

// ������Ż �ǵ� ��ǥ�� ���� ������ ��°�
typedef struct tagThrowShield
{
	RECT			rc;					// ��Ʈ
	POINTFLOAT		center;				// ����
	image*			image;				// �ǵ� �̹����� ��´�.
	float			angle;				// ���ư��� ����
	float			speed;				// ���ư��� �ӵ�
	bool			isShieldUpdate;		// �ǵ� ��ġ ���� ����
	bool			isOut;				// �� ���� true��� ����
	BOSS_DIRECTION	direction;			// ������ �ٶ󺸴� ������ �����Ѵ�. (���⿡ ���� ���и� ������ ������ �ٸ���.)
}ThrowShield;

// ������ ���� �Լ�
struct tagBossJump
{
	float			 jumpPow;							// ���� ����
	float			 gravity;							// �߷� ����
	POINTFLOAT		 start;								// ���� ��ġ
	bool			 isJumping;							// �������̶�� true
};