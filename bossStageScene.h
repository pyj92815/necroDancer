#pragma once
#include "gameNode.h"
#include "deathMetal.h"
#include "bossStageTestTile.h"

class player;

class bossStageScene : public gameNode
{
private:
	bossStageTestTile*		_bossStageTile;			// 보스 스테이지의 타일을 생성
	vector<tile*>			_vTotalList;		// 보스 스테이지의 타일 정보를 복사한다.

	deathMetal*				_deathMetal;		// 데스메탈
	player*					_player;			// 플레이어

public:
	bossStageScene();
	~bossStageScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setPlayerAddressLink(player* player) { _player = player; }		// player 링크

	// 영주가 만든 보스 스테이지맵을 불러 올 수 있게 로드 기능을 만들어야 한다.
	// 영주가 만든 보스 스테이지맵을 내가 사용 가능하도록 벡터에 저장해야 한다.
	// 맵 속성에 따라 이미지가 출력하게 만들까?
	// 타일 자체에 이미지를 저장할까? 그 타일 위치 위에 캐릭터의 렉트에 이미지를 그릴까?
	// 이동을 할 때마다 그 타일의 속성을 바꿔줘야한다.

};

