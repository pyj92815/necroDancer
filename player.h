#pragma once
#include "gameNode.h"
#include "animation.h"
#include "jump.h"
#include "action.h"		    // 보간개념 이동할때 사용하기 위한 

enum PLAYERSTATE	// (미사용) 추후 수정 예정 
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
	animation* headAni;		// 머리 애니매이션
	animation* bodyAni;		// 몸   애니매이션 
	PLAYERSTATE state;		// 플레이어의 상태
	image* headImage;		// 머리 이미지 
	image* bodyImage;		// 몸통 
	RECT rc;				// RECT
	float x, y;				// 좌표 X,Y  
	int idx, idy;			// 타일의 인덱스 번호 
	int count;				// 프레임 카운터 
	int currnetFrameX, currnetFrameY;	// 프레임 X,Y
	int direction;			// 플레이어의 방향   1 ( 좌 , 우 ) 0 
	int sight;				// 플레이어의 시야값 기본 1
};

class player : public gameNode
{
private:
	tagPlayer _player;	//  머리

	jump* _jump;		// 점프 
	action* _action;    // 선형보간

	float _distance;	// 타일 중점 거리 
	float _time;		// 시간 
	float _angle;		// 각도 
	float _worldTimeCount;	// 월드 타임 

	bool _isMoving;			// BOOL 선형보간이동
	bool _isKeyPress;		// KEY 입력중 판단 
public:
	player();
	~player();

	HRESULT init(int idx, int idy, int tileSizeX, int tileSizeY);
	void release();
	void update();
	void render();

	void playerMove();
	void keyControl();
	//접근자 
	tagPlayer getPlayer() { return _player; }	// 플레이어 값 반환 
	int getSight() { return _player.sight; }	// 시야 값 반환 
	PLAYERSTATE getState() { return _player.state; }	// 플레이어의 상태 값 반환 (HG가 추가했음)
};
