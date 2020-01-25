#pragma once
#include "stdafx.h"

// �����̺� ����
enum SLAVE_TYPE
{
	SLAVE_BAT,
	SLAVE_GHOST,
	SLAVE_SKELETON,
	SLAVE_SKELETON_YELLOW,
	SLAVE_NONE
};

// �����̺� ����
enum SLAVE_DIRECTION
{
	SD_LEFT,
	SD_UP,
	SD_RIGHT,
	SD_DOWN,
	SD_NONE
};

// �����̺��� ����
enum SLAVE_STATE
{
	SS_NONE,										// ������ ���°� ����
	SS_STAY,										// �����̺�� ��� ����	(�÷��̾ ��Ʈ�� �ٶ� ������ ��Ʈ�� ��� ����, ������ ������ �ʴ´�)
	SS_PLAYER_ATTACK,								// �����̺갡 �÷��̾ �߰�
	SS_RUN											// �������� ����			(�ذ��� �Ӹ��� ��������� �ذ��� �÷��̾� �ݴ� �������� ���� ����)
};

// �����̺��� �ɷ�ġ
struct SLAVE_STATUS
{
	SLAVE_TYPE			type;						// �����̺��� Ÿ���� ��´�.
	SLAVE_DIRECTION		direction;					// �����̺갡 �ٶ󺸴� ������ ��´�.

	int					hp;							// �����̺��� ü���� ��´�.
	float				attack;						// �����̺��� ���ݷ��� ��´�.
};

// �����̺��� ��ǥ
struct SLAVE_POS
{
	RECT				rc;							// �����̺� ��Ʈ
	POINTFLOAT			center;						// �����̺� �߽� ��ǥ
	POINT				index;						// �����̺� Ÿ�� �ε��� 
};

// �����̺��� �̹���
struct SLAVE_IMAGE
{
	animation*			animation;					// �����̺��� �ִϸ��̼��� ��´�.
	image*				img;						// �����̺��� �̹����� ��´�.
};

// �����̺��� ���� ����
struct SLAVE_OPERATION
{
	// Ÿ�� ������
	int					tile_SizeX, tile_SizeY;		// Ÿ���� ����� ��Ƶд�.

	// �̵�
	float				angle;						// �̵��� ���� ����
	int					move_Count;					// �̵� ī��Ʈ (�� ���ڸ��� �����̴���)
	float				move_Tile;					// ���� Ÿ�ϱ��� �̵��� �ɸ��� �ð�
	float				move_Speed;					// ���� Ÿ�ϱ��� �̵��ϴ� �ӵ�
	float				move_Distance;				// ���� Ÿ�ϱ����� �Ÿ�
	float				worldTile;					// ���� Ÿ��

};



// ��������������������������������������� �����̺��� ���� ���������������������������������������������������
struct SLAVE_INFO
{
	SLAVE_STATUS		status;							// �����̺� �������ͽ�
	SLAVE_POS			pos;							// �����̺� ��ǥ
	SLAVE_IMAGE			image;							// �����̺� �̹���
	SLAVE_OPERATION		operation;						// �����̺� ����

	void slave_Setting()
	{
		// �������ͽ� �ʱ�ȭ
		status.type = SLAVE_NONE;
		status.direction = SD_NONE;
		status.hp = 1;							// �⺻ ü���� 1 �̴�.
		status.attack = 1.f;					// �⺻ ���ݷ��� 0.5f �̴�.

		// ��ǥ �ʱ�ȭ
		pos.index.x = pos.index.y = 0;			// �⺻ �ε����� 0�̴�.
		pos.center.x = pos.center.y = 0;		// �⺻ ������ 0�̴�.
		pos.rc = RectMake(0, 0, 0, 0);			// �⺻ ��Ʈ�� 0�̴�.
	}
};




