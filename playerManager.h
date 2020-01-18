#pragma once
#include "gameNode.h"
#include "player.h"
#include "playerTestTile.h"  //�ٴ� �׽�Ʈ Ÿ�� 
#include "bossStageScene.h"	// ���� ������������ �÷��̾� ���� ��ũ�� ���� ���漱���


class playerManager: public gameNode
{
private:
	player* _player;
	playerTestTile* _ptt;   // ���￹��
	bossStageScene* _bossStageScene;	// ���� ������������ �÷��̾� ���� ��ũ�� ���� ���漱���
public:
	playerManager() {}
	~playerManager() {}

	HRESULT init();
	void release();
	void update();
	void render();

};
