#pragma once
#include "gameNode.h"
#include <map>
#include "player.h"



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
	map<tagItem*, POINTFLOAT>		  	_mInven;
	map<tagItem*, POINTFLOAT>::iterator _miInven;

private:
	vector<tagItem*>					_vInven;
	vector<tagItem*>::iterator			_viInven;
	player* _pm;
	tagPlayer* _player;

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
	
	float* _hp;

	int _heartBeatCnt;
	bool _heatBeatStop;
	bool _heatBeatStop2;
	int _currentFrameSpeed;
	int _frameCount;

	float tx;
	bool interval;

	//슬롯 고정할 위치 좌표
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

	void setInven(vector<tagItem*> inven) { _vInven = inven; }
	void setPlayerInfo(tagPlayer* player) { _player  = player; }
	

};

