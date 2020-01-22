#pragma once
#include "gameNode.h"
#include "action.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#define WINSIZEX_HALF WINSIZEX / 2
#define NOTE_INTERVAL WINSIZEX_HALF / 4
#define NOTE_RADIUS_X 5
#define HEARTFRAME_RATE 3


enum tagStage
{
	STAGE_TITILE,
	STAGE_LOBBY,
	STAGE_1_1,
	STAGE_1_2,
	STAGE_1_3,
	BOSS
};

struct tagNote
{
	RECT rc;
	POINTFLOAT pos;
	image* img;
	float speed;
	bool isCol;
	bool isPressBtn;
};


//class NoteHit : public gameNode
//{
//private:
//	tagNote hitNote;
//	int alpha;
//
//public:
//	virtual HRESULT init(tagNote note);
//	virtual void release();
//	virtual void update();
//	virtual void render();
//};


class Beat : public gameNode
{
private:
	tagStage _currentStage;
	string _oldSongName, _currentSongName, _oldShopKeeper, _currentShopkeeper;
	string _noteFileName;
	bool _loopSong;

	vector<int> _vMsTimeInfo;
	vector<tagNote> _vNoteLeft;
	vector<tagNote> _vNoteRight;
	int _countComma;
	int _countNote;
	float _deltaTime;
	bool _activeAction;

	int _oldStageID, _currentStageID;
	unsigned int _songPos;
	unsigned int _songLength;  // FMOD::SOUND에 getLength()함수가 망가져서 만들었음 ㅠㅠ...
	float _songLeftTime;
	float _pitch;
	float _noteSpeed;

	RECT heartRC, heartSmallRC, test_ShopKeeper, test_Player, test_slowPlatform, test_fastPlatform;
	POINTFLOAT test_ShopKeeperPos, test_PlayerPos, test_SlowPlatformPos, test_FastPlatformPos;

	image* heartImg;
	int heartFrameRate, heartFrameCount;
	bool _isBeating;

	//NoteHit* _hitNote;
	//vector<NoteHit*> _vHitNote;


private:
	void init_AddSoundAndImg();
	void init_SetObjs();

	void update_SceneCheck();
	void update_PlayerMoveTest();
	void update_SongAndNoteControl();
	void update_BeatEffect();
	void update_SoundDistanceControl();
	void update_PitchControl();

	void render_DebugLog(HDC getMemDC);


private:
	void Load();
	float GetSongVariousTime(unsigned int playTime, unsigned int songLength);


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};