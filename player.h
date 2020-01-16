#pragma once
#include "gameNode.h"
#include "animation.h"
#include "action.h"		    // 보간개념 이동할때 사용하기 위한 

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
	animation* ani;		 	// 애니매이션
	PLAYERSTATE state;		// 플레이어의 상태
	image* image;			// 이미지 
	RECT rc;				// RECT
	float x, y;				// 좌표 X,Y  
	int idx, idy;			// 타일의 인덱스 번호 
	int count;				// 프레임 카운터 
	int currnetFrameX, currnetFrameY;	// 프레임 X,Y
	int direction;			// 플레이어의 방향   1 ( 좌 , 우 ) 0 
};

class player : public gameNode
{
private:
	tagPlayer _head;	//  머리
	tagPlayer _body;	//  몸 

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

