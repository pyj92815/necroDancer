#pragma once
#include "gameNode.h"			// 게임노드
#include "alphaImageEffect.h"   // 이펙트 사용
#include "playerLibrary.h"		// 라이브러리
#include "animation.h"		    // 애니매이션
#include "jump.h"				// 점프

class player : public gameNode
{
private:
	//벽 타일 판단 MAP
	map<PLAYERDIRECTION, tagTile*>				_mPlayerTile;
	map<PLAYERDIRECTION, tagTile*>::iterator	_miPlayerTile;

	//공격판정 판단 MAP
	map<PLAYERDIRECTION, Enemy*>			_mPlayerEnemyTile;
	map<PLAYERDIRECTION, Enemy*>::iterator	_miPlayerEnemyTile;

	//슬레이브 
	map<PLAYERDIRECTION, slave*>            _mPlayerSlaveTile;
	map<PLAYERDIRECTION, slave*>::iterator _miPlayerSlaveTile;

	//데스메탈
	map<PLAYERDIRECTION, deathMetal*>            _mPlayerdeathMetalTile;
	map<PLAYERDIRECTION, deathMetal*>::iterator   _miPlayerdeathMetalTile;

	//이펙트 vector
	vector<alphaImageEffect*>		     _vEffect; 
	vector<alphaImageEffect*>::iterator _viEffect;

	//인벤토리 
	vector<tagItem*>				_vInven;
	vector<tagItem*>::iterator  _viInven;
private:
	tagPlayer	_player;	// 플레이어
	jump*		_jump;		// 점프 
	NOWSTAGE _nowStage;     // 현재 스테이지 
	float _worldTimeCount;	// 월드 타임 
	float _distance;		// 타일 중점 거리 
	float _time;			// 시간 
	float _angle;			// 각도 
	float _shadow;			// 그림자

	int _previousIdx;	    // 이전 idx,idy
	int _previousIdy;

	bool _isMoving;			// BOOL 선형보간이동
	bool _isKeyPress;		// KEY 입력 중 노트 판단 
	bool _isKeyDown;		// KEY 입력 판단
	bool _reversMove;		// 무기가 없을 때

	array<int,4> bodyRight; // 장비 바꾸기 위한 배열 
	array<int,4> bodyLeft;	// 

	tagItem* currentItem;
	//tagItem* currentWeapon;
	//tagItem* currentPotion;
	//tagItem* currenttorch;

public:
	player();
	~player();

	HRESULT init(int idx, int idy, int tileSizeX, int tileSizeY);
	void release();
	void update();
	void render();
	void effectRender();

	// 세팅 함수 
	void keyControl();	 // 사용키
	void playerMove();	 // 이동 

	// 이펙트 관련 함수 
	void playerEffect_Miss();					
	void playerEffect_Shovel(tagTile* tile);
	void playerEffect_Attack(const char* imageName,tagTile* tile, int frameY);
	void playerEffect_Attack(const char* imageName, float x, float y, int frameY);
	void playerEffect_Attack(const char* imageName, int x, int y, int frameY);
	void playerEffect_Attack();

	// 타일검출
	void tileCheck();	
	void wallCheck();	 // 벽판단
	void enemyCheck();	 // 몬스터 판단
	void trapCheck();	 // 함정 판단
	void itempCheck();   // 아이템 판단

	void makeItem(WEAPON weapon, ARMOR armor, STUFF stuff, int framex, int framey ,int sight,int damege, float guard, float hp);

	void playerHit(int damage) { _player.hp = _player.hp - damage; }
	//플레이어 상태판단
	void StateMove();		// 이동 판단		

	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 접근자 설정자■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	tagPlayer			getPlayer()			{ return _player; }			   //  전역 사용 
	PLAYERDIRECTION		getDirection()		{ return _player.direction; }  //  방향 
	bool   getPlayerKey()	{ return _isKeyPress;}	  // 비트매니저 사용 
	float* getPlayerY()		{ return &_shadow; }	  // 제트오더 사용 
	tagPlayer* PlayerAddress() { return &_player; }

	void setPlayerKeyDown()				  { _isKeyDown = false; }  // 비트매니저 KEY초기화
	void setPlayerKey(bool value = false) {	_isKeyPress = value;}  // 비트매니저 사용  

	//벽 타일 세팅
	void setPlayerTile(map<PLAYERDIRECTION, tagTile*> tile)		 { _mPlayerTile = tile; }
	void setPlayerEnemyTile(map<PLAYERDIRECTION, Enemy*> tile)	 { _mPlayerEnemyTile = tile; }
	void setSlaveTile(map<PLAYERDIRECTION, slave*> tile) { _mPlayerSlaveTile = tile; }
	void setDeathMetal(map<PLAYERDIRECTION, deathMetal*> tile) { _mPlayerdeathMetalTile = tile; }
	
	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 인벤토리 상호 작용  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	//void setEnemyAddressLink(EnemyManager* enemyManager) { }
	void itemUse();

	//이미지 세팅
	void imageSetting()
	{
		//플레이어 이미지
		IMAGEMANAGER->addFrameImage("player1_heads", "./image/player/player1_heads.bmp", 384, 96, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("player1_armor_body_xmas", "./image/player/player1_armor_body_xmas.bmp", 384, 240, 8, 5, true, RGB(255, 0, 255));
		//이펙트
		IMAGEMANAGER->addImage("shovel_basic", "./image/player/shovel_basic.bmp", 48, 48, true, RGB(255, 0, 255), true); // 삽 
		IMAGEMANAGER->addImage("player_effect_missed", "./image/player/TEMP_missed.bmp", 72, 26, true, RGB(255, 0, 255), true);  // 빗나감 
		IMAGEMANAGER->addFrameImage("swipe_dagger", "./image/player/swipe_dagger.bmp", 144, 192, 3, 4, true, RGB(255, 0, 255));
		// 긴검
		IMAGEMANAGER->addFrameImage("swipe_longsword상하", "./image/player/swipe_longsword상하.bmp", 192, 192, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("swipe_longsword좌우", "./image/player/swipe_longsword좌우.bmp", 384, 96, 4, 2, true, RGB(255, 0, 255));
		// 넓은 검
		IMAGEMANAGER->addFrameImage("swipe_broadsword상하", "./image/player/swipe_broadsword상하.bmp", 432, 96, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("swipe_broadsword좌우", "./image/player/swipe_broadsword좌우.bmp", 144, 288, 3, 2, true, RGB(255, 0, 255));
		// 레이피어 
		IMAGEMANAGER->addFrameImage("swipe_rapier상하", "./image/player/swipe_rapier상하.bmp", 192, 192, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("swipe_rapier좌우", "./image/player/swipe_rapier좌우.bmp", 384, 96, 4, 2, true, RGB(255, 0, 255));
	
		//오른쪽 애니매이션
		int headRight[] = { 0,1,2,3,4,5,6,7 };
		KEYANIMANAGER->addArrayFrameAnimation("headRight", "player1_heads", headRight, 8, 10, true);

		int bodyRight[] = { 0,1,2,3 };
		KEYANIMANAGER->addArrayFrameAnimation("bodyRight", "player1_armor_body_xmas", bodyRight, 4, 10, true);

		// 왼쪽 애니매이션
		int headLeft[] = { 15,14,13,12,11,10,9,8 };
		KEYANIMANAGER->addArrayFrameAnimation("headLeft", "player1_heads", headLeft, 8, 10, true);

		int	bodyLeft[] = { 7,6,5,4 };
		KEYANIMANAGER->addArrayFrameAnimation("bodyLeft", "player1_armor_body_xmas", bodyLeft, 4, 10, true);

	}
	void itemRemove(int num) { _vInven.erase(_vInven.begin() + num); }
	void itemRemove()  // 시험용 안될 가능성 높음 
	{
		for (int i = 0; i < _vInven.size(); ++i)
		{
			if (_vInven[i]->type != W_NONE) this->itemRemove(i);
		}
	}

	// 보스에서 몬스터 타일 초기화 
	void collisionSettingStage() 
	{
		if (!_mPlayerEnemyTile.empty()) _mPlayerEnemyTile.clear();
		if (!_mPlayerTile.empty())_mPlayerTile.clear();
	}
	// 스테이지에서 보스 타일 초기화 
	void collisionSettingBoss()
	{
		if(!_mPlayerSlaveTile.empty())_mPlayerSlaveTile.clear();
		if(!_mPlayerdeathMetalTile.empty())_mPlayerdeathMetalTile.clear();
	}

	void setStage() { _nowStage = NOWSTAGE_STAGE; }
	void setBossStage() { _nowStage = NOWSTAGE_BOSS; }
};


