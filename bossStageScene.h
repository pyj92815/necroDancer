#pragma once
#include "gameNode.h"
#include "bossKinds.h"

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
		
private:
	bool distanceCheck;												// �Ÿ��� üũ�Ѵ�. (������ �����ų� ������ ������ ���� �ٲ��.)

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

	// ��
	void bossStageMap_Load();											// ���� �������� ���� ���� �������� �����Ѵ�.
	void findTileImage();												// Ÿ�� �̹����� ã���ش�.

	// ����
	void z_Order_Player_Boss();											// �÷��̾�� ������ z����

	// �÷��̾�
	void playerPos_Setting();											// �����濡 ó�� ������ �÷��̾��� ��ġ�� �ʱ�ȭ ���ش�.

	// ����
	void closePlayer(player* player, deathMetal* deathMetal);			// �÷��̾ ��ó�� �ִٸ� ������ �̹����� ���´�.
	void closePlayer(player* player, slave* slave);						// �÷��̾ ��ó�� �ִٸ� ������ �̹����� ���´�.

	// �������� ������ ��ũ
	void stageSceneAddressLink(stageScene* stageScene) { _stageScene = stageScene; }
};

