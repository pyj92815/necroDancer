#pragma once

class Enemy;

enum PLAYERDIRECTION			// �÷��̾��� ����
{
	PLAYERDIRECTION_UP,		
	PLAYERDIRECTION_DOWN,
	PLAYERDIRECTION_LEFT,
	PLAYERDIRECTION_RIGHT
};

enum PLAYERWAEPON				// �÷��̾��� ����
{
	PLAYERWAEPON_NONE,			// �������
	PLAYERWAEPON_SPEAR,			// �ս��Ǿ�
	PLAYERWAEPON_DAGGER,		// �ܰ�
	PLAYERWAEPON_RAPIER,		// �����Ǿ�
	PLAYERWAEPON_LONGSWORD,		// �ռҵ�
	PLAYERWAEPON_BROADSWORD,	// ��ε�ҵ�
};

struct tagPlayer				//�÷��̾��� ����
{
	PLAYERDIRECTION direction;	// ����   
	PLAYERWAEPON weapon;		// ���� 
	animation* headAni;			// �Ӹ� �ִϸ��̼�
	animation* bodyAni;			// ��   �ִϸ��̼� 
	image* headImage;			//	    �̹��� 
	image* bodyImage;			//      �̹��� 
	RECT rc;					// RECT
	float x, y;					// ��ǥ ��(X,Y)  
	float maxHp;				// �ִ� HP
	float hp;					// hp
	float armor;				// ���
	int idx, idy;				// �ε��� (idx,idy)
	int sight;					// �þ߰�
	int damage;					// ���ݷ� 
};

struct tagItem
{
	TYPE type;
	WEAPON weapon;
	ARMOR armor;
	int armorFrameX;			//������ ��ȣ
	int armorFrameY;			//������ ��ȣ
	int weaponFrameX;			//������ ��ȣ
	int weaponFrameY;			//������ ��ȣ
	int sight;			// �þ߰�
	int damege;			// ���ݷ�
	float guard;			// ���� 
	float hp;				// ü�� 
};