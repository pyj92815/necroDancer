#pragma once
#include "gameNode.h"
#include "bossKinds.h"
#include "slaveManager.h"
#include "boss_Stage_Library.h"
#include "addImage_Boss.h"
#include "Collision.h"
#include "stageScene.h"
#include "zOrder.h"
#include "visionFloodFill.h"

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
	ADD_BOSS_IMAGE*								_addBossImage;					// 보스 이미지 생성
	ADD_SLAVE_IMAGE*							_addSlaveImage;					// 보스 슬레이브 이미지 생성

	Collision									_collision;						// 충돌 클래스

	BOSS_STAGE_OPEN								_scene_Starter;					// 보스 등장씬 관련 변수

	tagTile										_tiles[TILEX * TILEY];			// 맵을 받아 올 타일 변수
	vector<tagTile*>							_vTotalList;					// 보스 스테이지의 타일 정보 벡터로 저장해서 사용한다.
	vector<tagTile*>::iterator					_viTotalList;

	//vector<tagTile*>							_vTotalList;					// 보스 스테이지의 타일 정보 벡터로 저장해서 사용한다.
	//vector<tagTile*>::iterator				_viTotalList;

	vector<BOSS_STAGE_EFFECT_VECTOR*>			_vEffect;						// 이펙트 벡터
	vector<BOSS_STAGE_EFFECT_VECTOR*>::iterator _viEffect;						// 이펙트 이터에이터
	 
	stageScene*									_stageScene;					// 스테이지 씬
	UImanager*									_ui;							// ui
	player*										_player;						// 플레이어	
	deathMetal*									_deathMetal;					// 데스메탈
	slaveManager*								_sm;							// 슬레이브 매니저
	zOrder*										_zOrder;
	visionFloodFill*							_floodFill;
private:
	bool distanceCheck;															// 거리를 체크한다. (범위에 들어오거나 들어오지 않을때 값이 바뀐다.)
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
	void bossStageMap_Load();													// 보스 스테이지 맵을 벡터 형식으로 저장한다.
	void findTileImage();														// 타일 이미지를 찾아준다.

	// 연산
	void z_Order_Player_Boss();													// 플레이어와 보스의 z오더

	// 플레이어
	void playerPos_Setting();													// 보스방에 처음 도착한 플레이어의 위치를 초기화 해준다.

	// 보스 & 슬레이브
	void closePlayer(player* player, deathMetal* deathMetal);					// 플레이어가 근처에 있다면 쉐도우 이미지를 벗는다.
	void searchSlave(vector<slave*> vSlaveList, player* player);				// 플레이어가 근처에 있다면 쉐도우 이미지를 벗는다.
	void closePlayer_Slave(player* player, SLAVE_INFO* slave);					// 플레이어가 근처에 있다면 쉐도우 이미지를 벗는다.
	void findPlayer(player* player, deathMetal* deathMetal, UImanager* ui);		// 플레이어의 위치를 찾는다. (데스메탈)
	SLAVE_DIRECTION findPlayer(player* player, SLAVE_INFO* slave);				// 플레이어의 위치를 찾는다. (슬레이브)

	void boss_Move_Player();													// 보스가 플레이어에게 움직이는 연산
	void slave_Move_Player();													// 슬레이브가 플레이어에게 움직이는 연산

	void boss_Base_Attack_Render();
	void boss_Base_Attack_Render(string skillName, player* player);				// 보스의 근접 공격 애니메이션을 그려준다.

	void start_Slave_Create();												

	// 스테이지 씬과의 링크
	void stageSceneAddressLink(stageScene* stageScene) { _stageScene = stageScene; }

	void bossSceneSetting();													// 보스 등장씬 변수 초기화
	void bossSceneStart();														// 보스 등장씬 연산
	void bossSceneRender();														// 보스 등장씬 출력
	void bossSceneDoorOpen();													// 보스방 문을 여는 연산
	void bossClear();															// 보스 클리어 시 벽이 열리는것

	void boss_PhaseMove();														// 보스 페이즈 연산
	
};

