#pragma once
#include "gameNode.h"
#include "deathMetal.h"

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinmainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

class stageScene;
class UImanager;
class player;

class bossStageScene : public gameNode
{
private:
	tagTile							_tiles[TILEX * TILEY];			// ���� �޾� �� Ÿ�� ����
	vector<tagTile>					_vTotalList;					// ���� ���������� Ÿ�� ���� ���ͷ� �����ؼ� ����Ѵ�.
	vector<tagTile>::iterator		_viTotalList;

	deathMetal*						_deathMetal;					// ������Ż
	player*							_player;						// �÷��̾�	
	stageScene*						_stageScene;
	UImanager*						_ui;
		
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

	void bossStageMap_Load();											// ���� �������� ���� ���� �������� �����Ѵ�.
	void findTileImage();												// Ÿ�� �̹����� ã���ش�.
	void z_Order_Player_Boss();											// �÷��̾�� ������ z����

	void stageSceneAddressLink(stageScene* stageScene) { _stageScene = stageScene; }
};

