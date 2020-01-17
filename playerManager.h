#pragma once
#include "gameNode.h"
#include "player.h"
#include "playerTestTile.h"  //바닥 테스트 타일 



class playerManager: public gameNode
{
private:
	player* _player;
	playerTestTile* _ptt;   // 지울예정

public:
	playerManager() {}
	~playerManager() {}

	HRESULT init();
	void release();
	void update();
	void render();

};
