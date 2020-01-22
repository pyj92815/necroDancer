#pragma once
//#include "gameNode.h"
#include "singletonBase.h"
//#include "action.h"
#include <iostream> // ���� ���� �� �ҷ����⸦ ���� ������ �����
#include <fstream> // ���� ���� �� �ҷ����⸦ ���� ������ �����
#include <string> // ���� ���� �� �ҷ����⸦ ���� ������ �����
#include <vector>
using namespace std;

#define WINSIZEX_HALF 950 / 2	// ������ ���� ������ ����
#define NOTE_INTERVAL WINSIZEX_HALF / 4 // ��Ʈ ���� ����
#define NOTE_RADIUS_X 5 // ��Ʈ �ϳ��� ���� ������ ����
#define HEARTFRAME_RATE 3 // ���� �ڵ� ������ ���� �ð�

class gameNode;

enum tagStage // �׽�Ʈ������ ������ Scene����
{
	STAGE_TITILE,
	STAGE_LOBBY,
	STAGE_1_1,
	STAGE_1_2,
	STAGE_1_3,
	BOSS
};

struct tagNote // ��Ʈ ����ü
{
	RECT rc;
	POINTFLOAT pos;
	image* img;
	float speed;
	bool isCol;
	bool isPressBtn;
};

class Beat : public singletonBase<Beat>
{
private:
	tagStage _currentStage; // ���� ��������
	string _oldSongName, _oldShopKeeper, _currentSongName, _currentShopkeeper; // ���� �� Ű���� �������� Ű �� & ���� �� Ű���� �������� Ű ��
	string _noteFileName; // ��Ʈ ���� ����(ms)�� �ҷ����� ���� ��θ�
	bool _loopSong; // �ݺ������� �ƴ��� �Ǻ��ϴ� bool

	vector<int> _vMsTimeInfo; // ��Ʈ ������ ���� ���Ͽ��� �и������� ������ ���� ����
	vector<tagNote> _vNoteLeft; // ���ʿ��� ������ ��Ʈ
	vector<tagNote> _vNoteRight; // �����ʿ��� ������ ��Ʈ
	int _countComma; // ��Ʈ�� �ҷ��ö� ',' ������ ���� �����ϴ� �뵵�� ����
	int _countNote; // ������� ��Ʈ�� � ������ ���� ���� ����
	float _deltaTime; // TIMEMANAGER���� getElapsedTime()�� �Ź� ���� �ٲ�� ���� ȣ���ϱ� ����� ������ ���� ���۵Ǳ� ��, �� ���� getElapsedTime()ȣ���ϰ� �� ���� �����ϴ� �뵵�� ���� 
	bool _activeAction; // ����� �̿�������, �� ��Ʈ�� �Ѿ������ ����, �� ����Ʈ, UIȿ�� ��� ���� �ൿ���� �Ѿ �� �ֵ��� ���� �뵵�� bool

	int _oldStageID, _currentStageID; // ���� ���������� ���� �������� ��
	unsigned int _songPos; // ���� ���� ����ð�(ms) 
	unsigned int _songLength;  // FMOD::SOUND�� getLength()�Լ��� �������� ������� �Ф�... getLength() �Լ��� ����Ͽ� ���� ���̸� ���� �� �ְ� ���� ����
	float _songLeftTime; // ���� ���� ���� �ð�
	float _pitch; // ���� ���� pitch�� (1�� �⺻ ��, 1�̸� �� ���� ������, 1�̻� �� ������)
	float _noteSpeed; // ��Ʈ�� �̵��ӵ�

	RECT heartRC, heartSmallRC, test_ShopKeeper, test_Player, test_slowPlatform, test_fastPlatform; // RECT��(����, ���� ����� ���� ���� ��Ʈ(������ ������), �÷��̾�, �������� ����, �������� ����)
	POINTFLOAT test_ShopKeeperPos, test_PlayerPos, test_SlowPlatformPos, test_FastPlatformPos; // X,Y��ǥ��(���� ����, �÷��̾�, �������� ����, �������� ����)

	image* heartImg; // ���� �̹���
	int heartFrameCount; // ���� ���� ������
	bool _isBeating; // ���� �ڵ��� �־��� �ð� ���ݸ��� �ѹ� ���� �αٰŸ��� ���� bool 


private:
	void init_AddSoundAndImg(); // ���� & �̹��� �߰�
	void init_SetObjs(); // Beat Ŭ������ �ִ� ���� ������Ʈ ������ �ʱ�ȭ

	void update_SceneCheck(); // Scene������ �޾ƿ� �Լ�
	void update_PlayerMoveTest(); // �׽�Ʈ�� �÷��̾�
	void update_SongAndNoteControl(); // ��� ��Ʈ�� �����ϴ� �Լ�
	void update_BeatEffect(); // ���� �ڵ� �� �ٲ��� �̹����� ȿ����
	void update_SoundDistanceControl(); // ���� �����̳� ���� ��� �Ÿ��� ���� �Ҹ��� ũ�⸦ �������ִ� �Լ�
	void update_PitchControl(); // ���� �ӵ��� �����ϴ� �Լ�

	void render_DebugLog(HDC getMemDC); // ����� ���� �Լ�


private:
	void Load(); // ��Ʈ ���� �ε� �Լ�
	void CreateNewNote(bool dirRight); // �� ���� ������ ��Ʈ�� ��ġ�ϴ� �Լ�. bool�� ���������� ������ ������ �ƴ��� �Ǻ�.
	void CreateNewNoteWhilePlay(bool dirRight); // �� �����ϰ� �÷��� �߿� ��Ʈ�� ��ġ�ϴ� �Լ�. bool�� ���������� ������ ������ �ƴ��� �Ǻ�.
	float GetSongVariousTime(unsigned int playTime, unsigned int songLength); // �� ��� ��Ʈ ��� ���� Ư�� ����(Ư�� �ð�)�� �̾ƿ��� ���� ���� �Լ� 


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};