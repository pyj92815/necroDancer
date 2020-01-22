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
	//�κ��丮
	invenTag _attackInven;
	invenTag _shovelInven;
	invenTag _itemInven;
	invenTag _bombInven;
	invenTag _throwInven;
	invenTag _bodyInven;
	invenTag _headInven;

	invenTag _coinInven;
	invenTag _daiaInven;

	//���ڵ�
	invenTag _downLeft;
	invenTag _upDown;
	invenTag _upLeft;

	//��Ʈ
	heartTag _heart[3];

	float _currentFrameX;
	float _currentFrameY;

	animation* _FrameWork;

	image* _scoreNum;
	image* _scoreX;
	image* _daiaNum;

	int _coinTest;				//���߿� �÷��̾ ���� �浹�� ���ڷ� �޾ƿ��� �Լ��� �ٲ��ָ� �ɵ�
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

