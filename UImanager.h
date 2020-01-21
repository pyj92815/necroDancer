#pragma once
#include "gameNode.h"
#include <vector>

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

struct heartTag
{
	image* image;
	HEARTSTATE state;
	
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

	//���ڵ�
	invenTag _downLeft;
	invenTag _upDown;
	invenTag _upLeft;

	//��Ʈ
	heartTag _heart[3];

	float _currentFrameX;
	float _currentFrameY;

	animation* _FrameWork;

	image* test;

	int hp;


public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

