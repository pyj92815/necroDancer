#pragma once
#include "gameNode.h"
#include "animation.h"
#include "jump.h"
#include "action.h"			   // 보간개념 이동할때 사용하기 위한 
#include "alphaImageEffect.h"  // 이펙트 사용

class Enemy;

enum PLAYERSTATE	// (미사용) 추후 수정 예정 
{
	PLAYERSTATE_UP,
	PLAYERSTATE_DOWN,
	PLAYERSTATE_RIGHT,
	PLAYERSTATE_LEFT
};

enum PLAYERDIRECTION
{
	PLAYERDIRECTION_UP,
	PLAYERDIRECTION_DOWN,
	PLAYERDIRECTION_RIGHT,
	PLAYERDIRECTION_LEFT
};

enum PLAYERWAEPON
{
	PLAYERWAEPON_DAGGER,
	PLAYERWAEPON_LONGSWORD,
	PLAYERWAEPON_BROADSWORD,
	PLAYERWAEPON_RAPIER,
	PLAYERWAEPON_SPEAR,
	PLAYERWAEPON_NONE,
};

struct tagPlayer
{
	animation* headAni;		// 머리 애니매이션
	animation* bodyAni;		// 몸   애니매이션 
	PLAYERSTATE state;		// 플레이어의 상태
	PLAYERWAEPON weapon;
	PLAYERDIRECTION direction;	// 플레이어의 방향    
	image* headImage;		// 머리 이미지 
	image* bodyImage;		// 몸통 
	RECT rc;				// RECT
	float x, y;				// 좌표 X,Y  

	int idx, idy;			// 타일의 인덱스 번호 
	int count;				// 프레임 카운터 
	int currnetFrameX, currnetFrameY;	// 프레임 X,Y
	int sight;				// 플레이어의 시야값 기본 5
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
	bool _isKeyPress;		// KEY 입력중 노트 판단 
	bool _isKeyDown;		// KEY 입력 판단

	alphaImageEffect* _effect;
	vector<alphaImageEffect*>		     _vEffect;  // 빗나감 이펙트 
	vector<alphaImageEffect*>::iterator _viEffect;

	//타일 판정을 하기 위한 타일값
	map<PLAYERDIRECTION, tagTile*>				_mPlayerTile;
	map<PLAYERDIRECTION, tagTile*>::iterator	_miPlayerTile;

	//공격판정을 하기 위한 타일 값
	map<PLAYERDIRECTION, Enemy*>				_mPlayerAttackTile;
	map<PLAYERDIRECTION, Enemy*>::iterator	_miPlayerAttackTile;
public:
	player();
	~player();

	HRESULT init(int idx, int idy, int tileSizeX, int tileSizeY);
	void release();
	void update();
	void render();

	void playerMove();
	void playerMissEffect();					// 이펙트
	void playerShovelEffect(tagTile* tile);
	void playerAttackEffect(const char* imageName,tagTile* tile, int frameY);
	void playerAttackEffect(const char* imageName, float x, float y, int frameY);
	void playerAttackEffect(const char* imageName, int x, int y, int frameY);


	
	void keyControl();

	//접근자 
	tagPlayer getPlayer() { return _player; }			// 플레이어 값 반환 
	int getSight() { return _player.sight; }			// 시야 값 반환 
	PLAYERSTATE getState() { return _player.state; }	// 플레이어의 상태 값 반환 (HG가 추가했음)
	PLAYERDIRECTION getDirection() { return _player.direction; }	

	bool getPlayerKey() { return _isKeyPress; }
	void setPlayerKey(bool value = false) {	_isKeyPress = value;}  // 
	void setPlayerKeyDown() { _isKeyDown = false; }

	float* getPlayerY() { return &_player.y; }

	//타일 셋팅
	void setPlayerTile(map<PLAYERDIRECTION, tagTile*> tile) { _mPlayerTile = tile; }
	void setPlayerAttackTile(map<PLAYERDIRECTION, Enemy*> tile) { _mPlayerAttackTile = tile; }

	//타일검출
	void tileCheck();
	void StateMove();			//이동 
	void StateAttack();			//공격
	void StateShovel();

};


// 연휴동안 한것
/*
1. ALPHAEFFECT 고친거
2. 비트 인터벌 끝나면 플레이어 동작 가능하게 한것 
3. 플레이어 기준으로 4개의 충돌처리 


해야할것 

1. ENEMY 공격
2. ITEM 획득 및 사용하는거



*/