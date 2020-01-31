#pragma once
#include "gameNode.h"
#include <map>
#include "playerManager.h"



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
	bool open;

};

class UImanager : public gameNode
{
private:
	vector<tagItem*>					_vInven;
	vector<tagItem*>::iterator			_viInven;

	//�κ��丮
	map<OBJECT, invenTag> _mInven;
	map<OBJECT, invenTag>::iterator _miInven;

	invenTag _attackInven;
	invenTag _shovelInven;
	invenTag _itemInven;
	invenTag _bombInven;
	invenTag _throwInven;
	invenTag _bodyInven;
	invenTag _headInven;
	invenTag _feetInven;
	invenTag _torchInven;
	invenTag _ringInven;
	
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
	bool _heatBeatStop;
	bool _heatBeatStop2;
	int _currentFrameSpeed;
	int _frameCount;

	float tx;
	int interval;

	//���� ������ ��ġ ��ǥ
	float _x1Slot , _y1Slot;
	float _x2Slot , _y2Slot;
	float _x3Slot , _y3Slot;
	float _x4Slot , _y4Slot;
	float _x5Slot;
	float _x6Slot;
	float _x7Slot;


public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	void set_HP() { hp--; }

	void getInven(vector<tagItem*> inven) { _vInven = inven; }
	void effectRender();
	void makeItem(WEAPON weapon, ARMOR armor, STUFF stuff, int framex, int framey, int sight, int damege, float guard, float hp);
};

