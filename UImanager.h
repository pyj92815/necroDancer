#pragma once
#include "gameNode.h"


enum HEARTSTATE
{
	HEARTSTATE_FULL,
	HEARTSTATE_HALF,
	HEARTSTATE_NULL
};
enum INVENSTATE
{
	INVENSTATE_FULL,
	INVENSTATE_NULL
};
enum HEARTTURN
{
	TURN_ON,
	TURN_OFF
};

struct heartTag
{
	image* image;
	HEARTSTATE state;
	HEARTTURN turn;
	animation* anime;
};

struct invenTag
{
	image* image;
	RECT rc;
	INVENSTATE state;
	float x;
	float y;

};

class UImanager : public gameNode
{
private:
	//인벤토리
	invenTag _attackInven;
	invenTag _shovelInven;
	invenTag _itemInven;
	invenTag _bombInven;
	invenTag _throwInven;
	invenTag _bodyInven;
	invenTag _headInven;

	invenTag _coinInven;
	invenTag _daiaInven;

	//글자들
	invenTag _downLeft;
	invenTag _upDown;
	invenTag _upLeft;

	//하트
	heartTag _heart[3];

	float _currentFrameX;
	float _currentFrameY;

	animation* _FrameWork;

	image* _scoreNum;
	image* _scoreX;
	image* _daiaNum;

	int _coinTest;				//나중에 플레이어가 코인 충돌시 숫자로 받아오는 함수로 바꿔주면 될듯
	int _diaTest;

	int hp;

	int _heartBeatCnt;
	int _currentFrameSpeed;
	int _frameCount;


public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

