#pragma once
#include "singletonBase.h" // Scene별로 유동적으로 사용해야되니깐 구애받지않고 쓸 수 있도록 싱글톤을 사용함
#include <iostream> // 파일 저장 및 불러오기를 위해 선언한 헤더들
#include <fstream> // 파일 저장 및 불러오기를 위해 선언한 헤더들
#include <string> // 파일 저장 및 불러오기를 위해 선언한 헤더들
#include <vector>
using namespace std;

class gameNode; // 게임 노드와 전방 선언
class player;
class alphaEffect;

#define WINSIZEX_HALF WINSIZEX / 2	// 윈도우 가로 사이즈 절반
#define NOTE_INTERVAL WINSIZEX_HALF / 3 // 노트 사이 간격
#define NOTE_RADIUS_X 6 // 노트 하나의 가로 반지름 길이
#define HEARTFRAME_RATE 3 // 심장 박동 프레임 지연 시간


enum tagStage // 테스트용으로 선언한 Scene상태
{
	STAGE_TITILE,
	STAGE_LOBBY,
	STAGE_1_1,
	STAGE_1_2,
	STAGE_1_3,
	BOSS
};

struct tagNote // 노트 구조체
{
	RECT rc;
	POINTFLOAT pos;
	float speed;
	image* img;
	bool isCol; // 심장 박동 애니메이션 중복 방지를 위한 bool
	bool isRender;
	int alpha;
};



class Beat : public singletonBase<Beat> // 싱글톤 상속받기
{
private:
	tagStage _currentStage; // 현재 스테이지
	string _oldSongName, _oldShopKeeper, _currentSongName, _currentShopkeeper; // 이전 곡 키값과 상점주인 키 값 & 현재 곡 키값과 상점주인 키 값
	string _noteFileName; // 노트 간격 정보(ms)를 불러오기 위한 경로명
	bool _loopSong; // 반복곡인지 아닌지 판별하는 bool

	vector<int> _vMsTimeInfo; // 노트 정보가 적힌 파일에서 밀리세컨드 정보를 담을 벡터
	vector<tagNote> _vNoteLeft; // 왼쪽에서 나오는 노트
	vector<tagNote> _vNoteRight; // 오른쪽에서 나오는 노트
	int _countNote; // 현재까지 노트를 몇개 생성한 건지 세는 변수
	//float _deltaTime; // TIMEMANAGER에서 getElapsedTime()은 매번 값이 바뀌고 자주 호출하기 힘들기 때문에 곡이 시작되기 전, 한 번만 getElapsedTime()호출하고 그 값을 저장하는 용도의 변수 

	int _oldStageID, _currentStageID; // 현재 스테이지와 이전 스테이지 값
	unsigned int _songPos; // 현재 곡의 진행시간(ms) 
	unsigned int _songLength;  // FMOD::SOUND에 getLength()함수가 망가져서 만들었음 ㅠㅠ... getLength() 함수를 대신하여 곡의 길이를 받을 수 있게 만든 변수

	float _deltaTime;
	float _songLeftTime; // 현재 곡의 남은 시간
	float _pitch; // 현재 곡의 pitch값 (1이 기본 값, 1미만 시 곡이 느려짐, 1이상 시 빨라짐)

	RECT heartRC, heartSmallRC, test_ShopKeeper, test_Player, test_slowPlatform, test_fastPlatform; // RECT들(심장, 심장 가운데에 넣을 작은 렉트(아직은 수정중), 플레이어, 느려지는 발판, 빨라지는 발판)
	POINTFLOAT test_ShopKeeperPos, test_PlayerPos, test_SlowPlatformPos, test_FastPlatformPos; // X,Y좌표들(상점 주인, 플레이어, 느려지는 발판, 빨라지는 발판)

	image* heartImg; // 심장 이미지
	int heartFrameCount; // 현재 심장 프레임
	bool _isBeating; // 심장 박동을 주어진 시간 간격마다 한번 씩만 두근거리기 위한 bool

	vector<image*> _vHitNoteImg; // 알파 블렌더로 서서히 지울 노트 이미지를 저장할 이미지 전용 벡터
	float noteTimeInterval;
	float noteTimeIntervalCount;
	float inputInterval;
	float inputIntervalCount;
	bool Interval;
	player* _player;
	bool _effect;

	int musicID; // 음악의 인덱스를 정해주는 변수
	int musicID_Temp;

private:
	void init_AddSoundAndImg(); // 사운드 & 이미지 추가
	void init_SetObjs(); // Beat 클래스에 있는 여러 오브젝트 정보들 초기화

	void update_SetSceneMusic(); // Scene정보를 받아올 함수
	void update_PlayerMoveTest(); // 테스트용 플레이어
	void update_SongAndNoteControl(); // 곡과 노트를 제어하는 함수
	void update_BeatEffect(); // 심장 박동 시 바꿔줄 이미지나 효과들
	void update_SoundDistanceControl(); // 상점 주인이나 몬스터 등등 거리에 따라서 소리의 크기를 제어해주는 함수
	void update_PitchControl(); // 곡의 속도를 제어하는 함수

	void render_DebugLog(HDC getMemDC); // 디버그 전용 함수


private:
	void Load(); // 노트 파일 로드 함수
	void CreateNewNote(bool dirRight); // 곡 시작 직전에 노트를 배치하는 함수. bool은 오른쪽으로 생성할 것인지 아닌지 판별.
	void CreateNewNoteWhilePlay(bool dirRight); // 곡 시작하고 플레이 중에 노트를 배치하는 함수. bool은 오른쪽으로 생성할 것인지 아닌지 판별.
	float GetSongVariousTime(unsigned int playTime, unsigned int songLength); // 곡 제어나 노트 제어를 위해 특정 조건(특정 시간)을 뽑아오기 위해 쓰일 함수
	void Move();

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	bool getBeating() { return _isBeating; }
	void setPlayerAddressLink(player* player) { _player = player; }

	void HitNoteEffect(float x, float y);
	bool getInterval() { return  Interval; }
	float getHeartMiddle() { return (heartRC.left + heartRC.right) / 2; }
	//float lerp(float start, float end, float timeAmount) { return float(start + ((float)(end - start) * timeAmount)); }
	float lerp(float start, float end, float timeAmount) { return (float)((end - start) * timeAmount); }

	void SetMusicID(int _musicID) { musicID = _musicID; } // 음악 인덱스를 새로 지정해주는 setter! (id --> <1 = 로비>,  <2 = 스테이지 1_1>,  <3 = 스테이지 1_2>, <4 = 스테이지 1_3>, <5 = 보스>) 
	int GetMusicID() { return musicID; } // 음악 인덱스를 가져오는 getter

	void AllStopMusic();
};