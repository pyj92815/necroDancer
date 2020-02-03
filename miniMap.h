#pragma once
#include "gameNode.h"
#include "EnemyManager.h"
#include "playerManager.h"


class miniMap : public gameNode
{
private:
	vector<tagTile*>					_vStageMap;									//타일 정보 벡터
	vector<tagTile*>::iterator			_viStageMap;								//타일 정보 이터레이터

	EnemyManager* _em;																//에너미
	playerManager* _pm;																//플레이어

	const char* _imageName;															//미니맵 이미지 넣을 키값 변수
	float _playerX;
	float _playerY;

public:
	miniMap();
	~miniMap();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void getStageMap(vector<tagTile*> stageMap) { _vStageMap = stageMap; }			//타일 정보
	void getEnemyPoint(EnemyManager* em) { _em = em; }								//에너미 위치 정보
	void setPlayerXY(float x, float y)												//플레이어 위치 좌표 정보
	{
		_playerX = x; 
		_playerY = y;
	}
};

