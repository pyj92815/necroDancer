#pragma once
#include "gameNode.h"
#include "player.h"


class playerManager: public gameNode
{
private:
	player* _player;

public:
	playerManager() {}
	~playerManager() {}

	HRESULT init();
	void release();
	void update();
	void render();

	player* getPlayerInfo() { return _player; }
};
