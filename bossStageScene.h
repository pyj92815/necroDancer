#pragma once
#include "gameNode.h"
#include "deathMetal.h"
#include "bossStageTestTile.h"

class player;

class bossStageScene : public gameNode
{
private:
	bossStageTestTile*		_bossStageTile;			// ���� ���������� Ÿ���� ����
	vector<tile*>			_vTotalList;		// ���� ���������� Ÿ�� ������ �����Ѵ�.

	deathMetal*				_deathMetal;		// ������Ż
	player*					_player;			// �÷��̾�

public:
	bossStageScene();
	~bossStageScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setPlayerAddressLink(player* player) { _player = player; }		// player ��ũ

	// ���ְ� ���� ���� ������������ �ҷ� �� �� �ְ� �ε� ����� ������ �Ѵ�.
	// ���ְ� ���� ���� ������������ ���� ��� �����ϵ��� ���Ϳ� �����ؾ� �Ѵ�.
	// �� �Ӽ��� ���� �̹����� ����ϰ� �����?
	// Ÿ�� ��ü�� �̹����� �����ұ�? �� Ÿ�� ��ġ ���� ĳ������ ��Ʈ�� �̹����� �׸���?
	// �̵��� �� ������ �� Ÿ���� �Ӽ��� �ٲ�����Ѵ�.

};

