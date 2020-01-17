#pragma once
#include "gameNode.h"
#include "player.h"
#include "playerTestTile.h"  //�ٴ� �׽�Ʈ Ÿ�� 



class playerManager: public gameNode
{
private:
	player* _player;
	playerTestTile* _ptt;   // ���￹��

public:
	playerManager() {}
	~playerManager() {}

	HRESULT init();
	void release();
	void update();
	void render();

};
