#pragma once
#include "gameNode.h"
#include "player.h"
#include "playerTestTile.h"  //바닥 테스트 타일 
#include "bossStageScene.h"	// 보스 스테이지에서 플레이어 정보 링크를 위해 전방선언용


class playerManager: public gameNode
{
private:
	player* _player;
	playerTestTile* _ptt;   // 지울예정
	bossStageScene* _bossStageScene;	// 보스 스테이지에서 플레이어 정보 링크를 위해 전방선언용
public:
	playerManager() {}
	~playerManager() {}

	HRESULT init();
	void release();
	void update();
	void render();

};
