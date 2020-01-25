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
	tagTile							_tiles[TILEX * TILEY];			// 맵을 받아 올 타일 변수
	vector<tagTile>					_vTotalList;					// 보스 스테이지의 타일 정보 벡터로 저장해서 사용한다.
	vector<tagTile>::iterator		_viTotalList;

	deathMetal*						_deathMetal;					// 데스메탈
	player*							_player;						// 플레이어	
	stageScene*						_stageScene;
	UImanager*						_ui;
		
private:
	bool distanceCheck;												// 거리를 체크한다. (범위에 들어오거나 들어오지 않을때 값이 바뀐다.)

public:
	bossStageScene();
	~bossStageScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	// 영주가 만든 보스 스테이지맵을 불러 올 수 있게 로드 기능을 만들어야 한다.
	// 영주가 만든 보스 스테이지맵을 내가 사용 가능하도록 벡터에 저장해야 한다.
	// 맵 속성에 따라 이미지가 출력하게 만들까?
	// 타일 자체에 이미지를 저장할까? 그 타일 위치 위에 캐릭터의 렉트에 이미지를 그릴까?
	// 이동을 할 때마다 그 타일의 속성을 바꿔줘야한다.

	// 맵
	void bossStageMap_Load();											// 보스 스테이지 맵을 벡터 형식으로 저장한다.
	void findTileImage();												// 타일 이미지를 찾아준다.

	// 연산
	void z_Order_Player_Boss();											// 플레이어와 보스의 z오더

	// 플레이어
	void playerPos_Setting();											// 보스방에 처음 도착한 플레이어의 위치를 초기화 해준다.

	// 보스
	void closePlayer(player* player, deathMetal* deathMetal);			// 플레이어가 근처에 있다면 쉐도우 이미지를 벗는다.
	void closePlayer(player* player, slave* slave);						// 플레이어가 근처에 있다면 쉐도우 이미지를 벗는다.

	// 스테이지 씬과의 링크
	void stageSceneAddressLink(stageScene* stageScene) { _stageScene = stageScene; }
};

