#pragma once
#include "gameNode.h"
#include "bossKinds.h"
#include "slaveManager.h"

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

	stageScene*						_stageScene;					// �������� ��
	UImanager*						_ui;							// ui
	player*							_player;						// �÷��̾�	
	deathMetal*						_deathMetal;					// ������Ż
	slaveManager*					_sm;							// �����̺� �Ŵ���
		
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

	// ���� & �����̺�
	void closePlayer(player* player, deathMetal* deathMetal);			// �÷��̾ ��ó�� �ִٸ� ������ �̹����� ���´�.
	void closePlayer(player* player, slave* slave);						// �÷��̾ ��ó�� �ִٸ� ������ �̹����� ���´�.
	void findPlayer(player* player, deathMetal* deathMetal, UImanager* ui);			// �÷��̾��� ��ġ�� ã�´�. (������Ż)
	void findPlayer(player* player, slave* slave);						// �÷��̾��� ��ġ�� ã�´�. (�����̺�)

	void boss_Move_Player();											// ������ �÷��̾�� �����̴� ����

	void boss_Base_Attack_Render();										// ������ ���� ���� �ִϸ��̼��� �׷��ش�.

	// �������� ������ ��ũ
	void stageSceneAddressLink(stageScene* stageScene) { _stageScene = stageScene; }

};

