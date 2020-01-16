#pragma once
#include "gameNode.h"
#include "animation.h"
#include "action.h"		    // �������� �̵��Ҷ� ����ϱ� ���� 

enum PLAYERSTATE
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
	animation* ani;		 	// �ִϸ��̼�
	PLAYERSTATE state;		// �÷��̾��� ����
	image* image;			// �̹��� 
	RECT rc;				// RECT
	float x, y;				// ��ǥ X,Y  
	int idx, idy;			// Ÿ���� �ε��� ��ȣ 
	int count;				// ������ ī���� 
	int currnetFrameX, currnetFrameY;	// ������ X,Y
	int direction;			// �÷��̾��� ����   1 ( �� , �� ) 0 
};

class player : public gameNode
{
private:
	tagPlayer _head;	//  �Ӹ�
	tagPlayer _body;	//  �� 

	action* _action;

	float _distance;
	float _time;
	float _angle;
	float _worldTimeCount;
	bool _isMoving;
public:
	player();
	~player();

	HRESULT init(int idx, int idy, int tileSizeX, int tileSizeY);
	void release();
	void update();
	void render();

	void playerMove();
	void keyControl();
};

