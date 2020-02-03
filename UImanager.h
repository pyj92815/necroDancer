#pragma once
#include "gameNode.h"
#include "player.h"

enum HEARTSTATE							//하트 HP상태
{
	HEARTSTATE_FULL,
	HEARTSTATE_HALF,
	HEARTSTATE_NULL
};
enum HEARTTURN							//하트 움직임 상태
{
	TURN_ON,
	TURN_OFF
};
enum INVENSTATE							//인벤토리 상태
{
	INVENSTATE_FULL,
	INVENSTATE_NULL
};

struct heartTag							//하트 구조체
{
	image* image;
	HEARTSTATE state;
	HEARTTURN turn;
	animation* anime;
};
struct invenTag							//인벤토리 구조체
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

private:
	vector<tagItem*>					_vInven;		//인벤토리 벡터
	vector<tagItem*>::iterator			_viInven;		//인벤토리 이터레이터
	player* _pm;										//플레이어 포인터
	tagPlayer* _player;									//플레이어 구조체 포인터

	//인벤토리 구조체
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
	animation* _FrameWork;			//애니메이션
	bool _heartinterval;			//비트에 따라 바뀌는 불값
	int _heartBeatCnt;				//카운트

	//스코어 & 다이아
	image* _scoreNum;
	image* _scoreX;
	image* _daiaNum;
	int _coinvalue;	
	int _diavalue;

	int _hp;						//플레이어 HP

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
	
	void set_HP() { _hp--; }												//플레이어 HP
	void setInven(vector<tagItem*> inven) { _vInven = inven; }				//인벤 아이템
	void setPlayerInfo(tagPlayer* player) { _player  = player; }			//플레이어
	

};

