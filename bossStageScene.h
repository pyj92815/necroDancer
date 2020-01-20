#pragma once
#include "gameNode.h"
#include "deathMetal.h"
#include "bossStageTestTile.h"											// ���Ŀ� ���ְ� ���� Ÿ�� ����� ��ü �ؾ��Ѵ�.

class bossStageScene : public gameNode
{
private:
	bossStageTestTile*		_bossStageTile;								// ���� ���������� Ÿ���� ����
	vector<tile*>			_vTotalList;								// ���� ���������� Ÿ�� ������ �����Ѵ�.
	
	tile					_BSTList[TESTTILESIZE][TESTTILESIZE];		// �ӽ� �����ŭ ������ �����. (���Ŀ� �ڷ��� �ٲ����)
	vector<tile*>			_vBSTList;									// ���� �������� Ÿ�� ����Ʈ�� ��´�. (���� �ڷ����� ���ְ� ���� Ÿ�� �ڷ������� ��ü�ؾ��Ѵ�.)

	deathMetal*				_deathMetal;								// ������Ż
public:
	bossStageScene();
	~bossStageScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	// ���ְ� ���� ���� ������������ �ҷ� �� �� �ְ� �ε� ����� ������ �Ѵ�.
	// ���ְ� ���� ���� ������������ ���� ��� �����ϵ��� ���Ϳ� �����ؾ� �Ѵ�.
	// �� �Ӽ��� ���� �̹����� ����ϰ� �����?
	// Ÿ�� ��ü�� �̹����� �����ұ�? �� Ÿ�� ��ġ ���� ĳ������ ��Ʈ�� �̹����� �׸���?
	// �̵��� �� ������ �� Ÿ���� �Ӽ��� �ٲ�����Ѵ�.
	void bossStageMap_Load();											// ���� �������� ���� �ҷ��ͼ� �����Ѵ�.

};

