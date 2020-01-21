#pragma once
#include "gameNode.h"
#include "animation.h"
#include "jump.h"
#include "action.h"		    // �������� �̵��Ҷ� ����ϱ� ���� 

enum PLAYERSTATE	// (�̻��) ���� ���� ���� 
{
	PLAYERSTATE_LEFTSTOP,
	PLAYERSTATE_RIGHTSTOP,
	PLAYERSTATE_UP,
	PLAYERSTATE_DOWN,
	PLAYERSTATE_RIGHT,
	PLAYERSTATE_LEFT
};

struct tagPlayer
{
	animation* headAni;		// �Ӹ� �ִϸ��̼�
	animation* bodyAni;		// ��   �ִϸ��̼� 
	PLAYERSTATE state;		// �÷��̾��� ����
	image* headImage;		// �Ӹ� �̹��� 
	image* bodyImage;		// ���� 
	RECT rc;				// RECT
	float x, y;				// ��ǥ X,Y  
	int idx, idy;			// Ÿ���� �ε��� ��ȣ 
	int count;				// ������ ī���� 
	int currnetFrameX, currnetFrameY;	// ������ X,Y
	int direction;			// �÷��̾��� ����   1 ( �� , �� ) 0 
	int sight;				// �÷��̾��� �þ߰� �⺻ 1
};

class player : public gameNode
{
private:
	tagPlayer _player;	//  �Ӹ�

	jump* _jump;		// ���� 
	action* _action;    // ��������

	float _distance;	// Ÿ�� ���� �Ÿ� 
	float _time;		// �ð� 
	float _angle;		// ���� 
	float _worldTimeCount;	// ���� Ÿ�� 

	bool _isMoving;			// BOOL ���������̵�
	bool _isKeyPress;		// KEY �Է��� �Ǵ� 
public:
	player();
	~player();

	HRESULT init(int idx, int idy, int tileSizeX, int tileSizeY);
	void release();
	void update();
	void render();

	void playerMove();
	void keyControl();
	//������ 
	tagPlayer getPlayer() { return _player; }	// �÷��̾� �� ��ȯ 
	int getSight() { return _player.sight; }	// �þ� �� ��ȯ 
	PLAYERSTATE getState() { return _player.state; }	// �÷��̾��� ���� �� ��ȯ (HG�� �߰�����)
};
