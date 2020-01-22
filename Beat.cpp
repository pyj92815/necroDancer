#include "stdafx.h"
#include "Beat.h"
#include"gameNode.h"


HRESULT Beat::init()
{
    // 사운드 추가
    init_AddSoundAndImg();

    // 오브젝트들 초기화
    init_SetObjs();
    return S_OK;
}

void Beat::release()
{
}

void Beat::update()
{
    // 씬 체크
    update_SceneCheck();

    // 플레이어 움직임
    update_PlayerMoveTest();

    // 노래 & 노트 조절
    update_SongAndNoteControl();

    // 심장 효과
    update_BeatEffect();

    // 거리에 따른 음향 크기 조절
    update_SoundDistanceControl();

    // Pitch값 조절
    update_PitchControl();
}

void Beat::render()
{
    Rectangle(_backBuffer->getMemDC(), test_slowPlatform);
    Rectangle(_backBuffer->getMemDC(), test_fastPlatform);
    Rectangle(_backBuffer->getMemDC(), test_ShopKeeper);
    Rectangle(_backBuffer->getMemDC(), test_Player);

    if (_vNoteLeft.size() > 0) // 왼쪽 노트 렌더
    {
        for (int i = 0; i < _vNoteLeft.size(); i++)
        {
            //Rectangle(getMemDC(), _noteLeft[i].rc);
            _vNoteLeft[i].img->render(_backBuffer->getMemDC(), _vNoteLeft[i].rc.left, _vNoteLeft[i].rc.top);
        }
    }
    if (_vNoteRight.size() > 0) // 오른쪽 노트 렌더
    {
        for (int i = 0; i < _vNoteRight.size(); i++)
        {
            //Rectangle(getMemDC(), _noteRight[i].rc);
            _vNoteRight[i].img->render(_backBuffer->getMemDC(), _vNoteRight[i].rc.left, _vNoteRight[i].rc.top);
        }
    }

    //Rectangle(getMemDC(), heartRC);
    IMAGEMANAGER->frameRender("Heart", _backBuffer->getMemDC(), heartImg->getX(), heartImg->getY()); // 심장 렌더

    render_DebugLog(_backBuffer->getMemDC()); // 디버그 텍스트 렌더
}


void Beat::init_AddSoundAndImg() // 사운드 & 이미지 추가
{
    SOUNDMANAGER->addSound("BGM_LOBBY", "Music/lobby.ogg", false, true);
    SOUNDMANAGER->addSound("BGM_STAGE_1_1", "Music/zone1_1.ogg", true, false);
    SOUNDMANAGER->addSound("BGM_STAGE_1_2", "Music/zone1_2.ogg", true, false);
    SOUNDMANAGER->addSound("BGM_STAGE_1_3", "Music/zone1_3.ogg", true, false);
    SOUNDMANAGER->addSound("BGM_BOSS", "Music/boss_2.ogg", false, true);

    SOUNDMANAGER->addSound("NPC_Stage_1_1_shopkeeper", "Music/zone1_1_shopkeeper.ogg", true, false);
    SOUNDMANAGER->addSound("NPC_Stage_1_2_shopkeeper", "Music/zone1_2_shopkeeper.ogg", true, false);
    SOUNDMANAGER->addSound("NPC_Stage_1_3_shopkeeper", "Music/zone1_3_shopkeeper.ogg", true, false);

    IMAGEMANAGER->addImage("GreenNote", "image/player/TEMP_beat_marker.bmp", 12, 64, true, RGB(255, 0, 255));
    IMAGEMANAGER->addImage("RedNote", "image/player/TEMP_beat_marker_red.bmp", 12, 64, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("Heart", "image/player/TEMP_beat_heart.bmp", 205, 130, 2, 1, true, RGB(255, 0, 255));
}

void Beat::init_SetObjs() // Beat 클래스에서 제어하고 사용할 여러 변수들 초기화 전용 함수
{
    _currentStage = STAGE_LOBBY;
    _noteFileName = _currentSongName = _oldSongName = "";
    _songLeftTime = heartFrameCount = _isBeating = _activeAction = _deltaTime = _countNote = _countComma = _oldStageID = _currentStageID = _songLength = _songPos = _pitch = _noteSpeed = 0;

    test_ShopKeeperPos = { WINSIZEX / 2, WINSIZEY / 2 };
    test_ShopKeeper = RectMakeCenter(test_ShopKeeperPos.x, test_ShopKeeperPos.y, 50, 50);

    test_PlayerPos = { (WINSIZEX / 2) - 100, WINSIZEY / 2 };
    test_Player = RectMakeCenter(test_PlayerPos.x, test_PlayerPos.y, 25, 25);

    test_SlowPlatformPos = { (WINSIZEX / 2) - 100, (WINSIZEY / 2) - 200 };
    test_slowPlatform = RectMakeCenter(test_SlowPlatformPos.x, test_SlowPlatformPos.y, 48, 48);

    test_FastPlatformPos = { (WINSIZEX / 2) + 100, (WINSIZEY / 2) - 200 };
    test_fastPlatform = RectMakeCenter(test_FastPlatformPos.x, test_FastPlatformPos.y, 48, 48);

    heartImg = IMAGEMANAGER->findImage("Heart");
    heartImg->setFrameY(0), heartImg->setFrameX(0);
    heartImg->setX(WINSIZEX_HALF - heartImg->getFrameWidth() / 2), heartImg->setY((WINSIZEY - heartImg->getFrameHeight()) - heartImg->getFrameHeight() / 2);
    heartRC = RectMakeCenter(heartImg->getX() + heartImg->getFrameWidth() / 2, heartImg->getY() + heartImg->getFrameHeight() / 2, heartImg->getFrameWidth(), heartImg->getFrameHeight());
}

void Beat::update_SceneCheck() // 씬 정보를 받아올 함수
{
    if (KEYMANAGER->isOnceKeyDown('E')) _currentStage = STAGE_LOBBY, _currentStageID = (int)_currentStage, _currentSongName = "BGM_LOBBY", _currentShopkeeper = "", _noteFileName = "Music/lobby.txt", Load(), _loopSong = true;
    else if (KEYMANAGER->isOnceKeyDown('R')) _currentStage = STAGE_1_1, _currentStageID = (int)_currentStage, _currentSongName = "BGM_STAGE_1_1", _currentShopkeeper = "NPC_Stage_1_1_shopkeeper", _noteFileName = "Music/zone1_1.txt", Load(), _loopSong = false;
    else if (KEYMANAGER->isOnceKeyDown('T')) _currentStage = STAGE_1_2, _currentStageID = (int)_currentStage, _currentSongName = "BGM_STAGE_1_2", _currentShopkeeper = "NPC_Stage_1_2_shopkeeper", _noteFileName = "Music/zone1_2.txt", Load(), _loopSong = false;
    else if (KEYMANAGER->isOnceKeyDown('Y')) _currentStage = STAGE_1_3, _currentStageID = (int)_currentStage, _currentSongName = "BGM_STAGE_1_3", _currentShopkeeper = "NPC_Stage_1_3_shopkeeper", _noteFileName = "Music/zone1_3.txt", Load(), _loopSong = false;
    else if (KEYMANAGER->isOnceKeyDown('U')) _currentStage = BOSS, _currentStageID = (int)_currentStage, _currentSongName = "BGM_BOSS", _currentShopkeeper = "", _noteFileName = "Music/boss_2.txt", Load(), _loopSong = true;
}

void Beat::update_PlayerMoveTest() // 테스트용 플레이어
{
    if (KEYMANAGER->isStayKeyDown(VK_UP)) test_PlayerPos.y -= 3;
    if (KEYMANAGER->isStayKeyDown(VK_LEFT)) test_PlayerPos.x -= 3;
    if (KEYMANAGER->isStayKeyDown(VK_DOWN)) test_PlayerPos.y += 3;
    if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) test_PlayerPos.x += 3;
    test_Player = RectMakeCenter(test_PlayerPos.x, test_PlayerPos.y, 25, 25);
}

void Beat::update_SongAndNoteControl() // 곡과 노트 제어
{
    SOUNDMANAGER->getSongPosition(_currentSongName, _songPos); // 현재 진행 중인 곡의 진행 시간을 받아 옴(ms)
    _songLeftTime = GetSongVariousTime(_songPos, _songLength); // 현재 곡이 얼만큼 남았는지 알려줌

    // 프로그램 최초 실행 후 재생한 곡이 아직 아무것도 없는 경우에 키를 입력한 경우
    if (_currentSongName != "" && _oldSongName == "")
    {
        _oldSongName = _currentSongName;
    }
    if (_currentShopkeeper != "" && _oldShopKeeper == "")
    {
        _oldShopKeeper = _currentShopkeeper;
    }

    // 현재 스테이지가 기존 스테이지와 다를 때 초기화해주는 것들(노트 속도, 남은 시간, 벡터들, 재생 곡 교체, 현재 곡 정보를 담을 키 값들 교체, 델타 타임 다시 받기, 초기 노트 생성)
    if (_currentStageID != _oldStageID)
    {
        _noteSpeed = 0; 
        _songLeftTime = 0;
        _vNoteLeft.clear();
        _vNoteRight.clear();
        SOUNDMANAGER->stop(_oldSongName), SOUNDMANAGER->stop(_oldShopKeeper);
        SOUNDMANAGER->play(_currentSongName), SOUNDMANAGER->play(_currentShopkeeper);
        _oldSongName = _currentSongName;
        _oldShopKeeper = _currentShopkeeper;
        _oldStageID = _currentStageID;
        _deltaTime = TIMEMANAGER->getElapsedTime();

        CreateNewNote(true);
        CreateNewNote(false);
    }

    if (_songPos > 0) // 곡이 시작되었을때
    {
        for (int i = 0; i < _vNoteRight.size(); i++) // 오른쪽 노트
        {
            if (_vNoteRight[i].pos.x <= WINSIZEX / 2) // 오른쪽으로 나오는 노트가 중점 x값보다 작은 경우 (노트가 중점을 넘을 때)
            {
                _vNoteRight.erase(_vNoteRight.begin() + i); // 넘어간 노트 삭제
                if (_vNoteRight.size() <= 0) break; // 노트 벡터의 크기가 0 이하일때 충돌을 막기 위해 Break; <이거 안하면 밑에 이동하는 코드에 접근하고 터져버림>

                if (_countNote < _countComma - 3) // 노트 생성 수가 노트 정보 길이 - 3보다 작은 경우(노트 개수 오차 보정(맨 처음 노트 스킵한 거 1개, 텍스트에 불러온 끝의 쓰레기 정보 2개만큼 뺌))
                {
                    CreateNewNoteWhilePlay(true); // 노트 생성
                }
                else // 노트 생성 수가 기존 노트 정보 길이를 넘어갈 때
                {
                    if (_loopSong) // 곡이 반복 곡일때
                    {
                        _countNote = 0; // 노트를 다시 세기 위해 초기화
                        CreateNewNoteWhilePlay(true);
                    }
                }
            }
            _vNoteRight[i].pos.x -= _deltaTime / ((_vMsTimeInfo[_countNote + 1] - _vMsTimeInfo[_countNote]) / 1000.0f) * NOTE_INTERVAL * SOUNDMANAGER->getPitch(_currentSongName, _pitch); // 노트 이동 (델타 타임 / 현재 노트 시간(ms)값 * 노트 간격 * 현재 곡 pitch 값)
            _vNoteRight[i].img->setX(_vNoteRight[i].pos.x - _vNoteRight[i].img->getWidth() / 2); // 이미지 위치 세팅
            _vNoteRight[i].img->setY(_vNoteRight[i].pos.y - _vNoteRight[i].img->getHeight() / 2); // 이미지 위치 세팅
            _vNoteRight[i].rc = RectMakeCenter(_vNoteRight[i].pos.x, _vNoteRight[i].pos.y, _vNoteRight[i].img->getWidth(), _vNoteRight[i].img->getHeight()); // 노트의 렉터 위치 잡기

            RECT temp;
            if (IntersectRect(&temp, &_vNoteRight[i].rc, &heartRC)) // 노트가 심장이랑 충돌 시 
            {
                if (!_vNoteRight[i].isCol) _isBeating = true; // 심장 이미지 변경을 위해 true로 변경
                _vNoteRight[i].isCol = true; // 인터벌이 다 지나고 두 번 심장이 두근거리는 것을 방지하기 위해 true로 변경
            }
        } // 여기까지가 오른쪽 노트

        for (int i = 0; i < _vNoteLeft.size(); i++) // 왼쪽 노트, 위와 같이 해석하면 됨
        {
            if (_vNoteLeft[i].pos.x >= WINSIZEX / 2)
            {
                _vNoteLeft.erase(_vNoteLeft.begin() + i);

                if (_vNoteLeft.size() <= 0) break;

                if (_countNote < _countComma - 3)
                {
                    CreateNewNoteWhilePlay(false);
                    ++_countNote; // 노트를 셀 때, 양쪽 다 세면 값이 2씩 증가하므로 한 쪽만 세준다.
                }
                else
                {
                    if (_loopSong)
                    {
                        _countNote = 0;
                        CreateNewNoteWhilePlay(false);
                        ++_countNote; // 노트를 셀 때, 양쪽 다 세면 값이 2씩 증가하므로 한 쪽만 세준다.
                    }
                }
            }
            _vNoteLeft[i].pos.x += _deltaTime / ((_vMsTimeInfo[_countNote + 1] - _vMsTimeInfo[_countNote]) / 1000.0f) * NOTE_INTERVAL * SOUNDMANAGER->getPitch(_currentSongName, _pitch);
            _vNoteLeft[i].img->setX(_vNoteLeft[i].pos.x - _vNoteLeft[i].img->getWidth() / 2);
            _vNoteLeft[i].img->setY(_vNoteLeft[i].pos.y - _vNoteLeft[i].img->getHeight() / 2);
            _vNoteLeft[i].rc = RectMakeCenter(_vNoteLeft[i].pos.x, _vNoteLeft[i].pos.y, _vNoteLeft[i].img->getWidth(), _vNoteLeft[i].img->getHeight());

            RECT temp;
            if (IntersectRect(&temp, &_vNoteLeft[i].rc, &heartRC))
            {
                if (!_vNoteLeft[i].isCol) _isBeating = true;
                _vNoteLeft[i].isCol = true;
            }
        } // 여기까지가 왼쪽 노트
    }
}

void Beat::update_BeatEffect() // 심장 박동 시 변경할 심장 이미지와 변경할 이외의 것들을 제어하기 위한 함수
{
    if (_isBeating)
    {
        ++heartFrameCount;
        heartImg->setFrameX(1);
        if (heartFrameCount > HEARTFRAME_RATE)
        {
            heartFrameCount = 0;
            _isBeating = false;
            heartImg->setFrameX(0);
        }
    }
}

void Beat::update_SoundDistanceControl() // 거리에 따라 소리크기 제어
{
    float getDistaceTemp = getDistance(test_PlayerPos.x, test_PlayerPos.y, test_ShopKeeperPos.x, test_ShopKeeperPos.y);
    if (getDistaceTemp < 40) SOUNDMANAGER->setVolume(_currentShopkeeper, 1);
    else if (getDistaceTemp >= 40 && getDistaceTemp < 80) SOUNDMANAGER->setVolume(_currentShopkeeper, 0.75f);
    else if (getDistaceTemp >= 80 && getDistaceTemp < 120) SOUNDMANAGER->setVolume(_currentShopkeeper, 0.50f);
    else SOUNDMANAGER->setVolume(_currentShopkeeper, 0.25f);
}

void Beat::update_PitchControl() // 곡 속도 제어
{
    RECT temp;
    if (IntersectRect(&temp, &test_Player, &test_slowPlatform)) SOUNDMANAGER->setPitch(_currentShopkeeper, 0.875f), SOUNDMANAGER->setPitch(_currentSongName, 0.875f);
    else if ((IntersectRect(&temp, &test_Player, &test_fastPlatform))) SOUNDMANAGER->setPitch(_currentShopkeeper, 1.125f), SOUNDMANAGER->setPitch(_currentSongName, 1.125f);
    else SOUNDMANAGER->setPitch(_currentShopkeeper, 1), SOUNDMANAGER->setPitch(_currentSongName, 1);
}

void Beat::render_DebugLog(HDC getMemDC) // 디버그용 함수
{
    if (_currentSongName != "")
    {
        char display_Pitch[128];
        sprintf_s(display_Pitch, sizeof(display_Pitch), "%f", SOUNDMANAGER->getPitch(_currentSongName, _pitch));
        TextOut(getMemDC, 100, 100, display_Pitch, strlen(display_Pitch));
        
        char display_songPos[256];
        sprintf_s(display_songPos, sizeof(display_songPos), "%d", _songPos);
        TextOut(getMemDC, 100, 120, display_songPos, strlen(display_songPos));
        
        char display_endVec[256];
        sprintf_s(display_endVec, sizeof(display_endVec), "%d", _vNoteLeft.size());
        TextOut(getMemDC, 100, 140, display_endVec, strlen(display_endVec));

        char display_noteInfoLength[256];
        sprintf_s(display_noteInfoLength, sizeof(display_noteInfoLength), "%d", _vMsTimeInfo.size());
        TextOut(getMemDC, 100, 160, display_noteInfoLength, strlen(display_noteInfoLength));

        char display_songLength[256];
        sprintf_s(display_songLength, sizeof(display_songLength), "%f", _songLeftTime);
        TextOut(getMemDC, 100, 180, display_songLength, strlen(display_songLength));

        char display_checkInfo[256];
        sprintf_s(display_checkInfo, sizeof(display_checkInfo), "%d", _countNote);
        TextOut(getMemDC, 100, 200, display_checkInfo, strlen(display_checkInfo));
    }
}



void Beat::Load() // 노트 파일 로드
{
    // 선형 보간 이동시 _noteInfo[0]과 _noteInfo.size() - 1요소는 의미없는 값이므로 제외한다. 단, _noteInfo[0]은 애니메이션이 움직여야하니 애니메이션 흘러가는 값에는 추가
    if (_vMsTimeInfo.size() > 0)
    {
        _vMsTimeInfo.clear(); // 벡터 재사용을 위한 클리어
        _countNote = _countComma = 0; // 노트 정보를 새로 받아오기 위해 초기화
    }
    _songLength = 0; // 곡의 길이 값 초기화

    ifstream readFile;
    string tempWord;
    readFile.open(_noteFileName); // 파일 열기

    if (readFile.is_open()) // 파일이 정상적으로 열려있다면
    {
        while (!readFile.eof()) // 읽어오는 파일의 끝을 만날때까지 반복
        {
            char temp; // 문자를 하나씩 뽑기 위한 변수
            readFile.get(temp); // 문자 하나 뽑기 
            if (temp == ',')
            {
                ++_countComma; // 콤마 세기
                _vMsTimeInfo.push_back(atoi(tempWord.c_str())); // 변환 순서 : 문자열 -> char*로 변환 -> atoi는 char*을 int로 변환
                tempWord = ""; // string 초기화
                continue;
            }
            tempWord += temp; // 한 글자씩 string에 합침
        }
        //_msTimeInfo.erase(_msTimeInfo.begin() + (_msTimeInfo.size() - 1)); // 현재 구조상 맨 마지막 부분에 0을 항상 저장하므로 맨 마지막 요소를 제거함
        readFile.close(); // 파일 닫기
    }

    for (int i = 0; i < _vMsTimeInfo.size() - 2; i++) // FMOD::SOUND에 getLength() 함수가 망가져서 만들었음 ㅠㅠ... 아마 원인이 함수도 음악 파일 확장자에 따라서 잘 작동되는 함수가 있는 반면 아닌 함수도 있다. 예를 들어 getVolume함수 같은 경우에도 일부 확장자만 함수 사용이 가능함
    {
        int getMS = _vMsTimeInfo[i + 1] - _vMsTimeInfo[i]; // 한 개의 비트 간격을 받아오기 위해서..
        _songLength += getMS; // 길이를 담아준다. 나중엔 _songLength가 곡의 총 길이가 된다.
    }
}

void Beat::CreateNewNote(bool dirRight) // 노트 생성, 곡 시작 직전에 (오른쪽으로 생성할 건지 말건지 정하기)
{
    for (int i = 0; i < 4; i++) // 새 노트로 리셋, 오른쪽
    {
        tagNote setNote;
        if (dirRight) setNote.pos = { (float)WINSIZEX_HALF + (NOTE_INTERVAL * (i + 1)), (float)(heartRC.top + heartRC.bottom) / 2 }; // 방향이 오른쪽인 경우
        else setNote.pos = { (float)WINSIZEX_HALF - (NOTE_INTERVAL * (i + 1)), (float)(heartRC.top + heartRC.bottom) / 2 }; // 방향이 왼쪽인 경우

        setNote.img = new image;
        setNote.img = IMAGEMANAGER->findImage("GreenNote");
        setNote.img->setX(setNote.pos.x - setNote.img->getWidth() / 2);
        setNote.img->setY(setNote.pos.y - setNote.img->getHeight() / 2);
        setNote.rc = RectMakeCenter(setNote.pos.x, setNote.pos.y, setNote.img->getWidth(), setNote.img->getHeight());
        setNote.speed = _deltaTime / ((_vMsTimeInfo[_countNote + 1] - _vMsTimeInfo[_countNote]) / 1000.0f) * NOTE_INTERVAL * SOUNDMANAGER->getPitch(_currentSongName, _pitch);
        setNote.isCol = false;
        setNote.isPressBtn = false;

        if (dirRight) _vNoteRight.push_back(setNote);
        else _vNoteLeft.push_back(setNote), ++_countNote; // *카운트 노트는 왼쪽 기준으로만 세주자! 양쪽다 하면 두 번 일하는거니깐!
    }
}

void Beat::CreateNewNoteWhilePlay(bool dirRight) // 노트 생성, 곡 시작 중 (오른쪽으로 생성할 건지 말건지 정하기)
{
    tagNote newNote;
    if(dirRight) newNote.pos = { WINSIZEX, (float)(heartRC.top + heartRC.bottom) / 2 }; // 방향이 오른쪽인 경우
    else newNote.pos = { 0, (float)(heartRC.top + heartRC.bottom) / 2 }; // 방향이 왼쪽인 경우

    if (_loopSong) newNote.img = IMAGEMANAGER->findImage("GreenNote"); // 반복 곡인 경우에는 계속 초록색 노트 이미지를 지정해준다.
    else if (_songLeftTime > (float)(_songLength / 1000) * 0.15f && !_loopSong) newNote.img = IMAGEMANAGER->findImage("GreenNote"); // 현재 남은 곡의 전체 곡 길이의 15%보다 큰 경우 초록색 노트 이미지 지정 
    else newNote.img = IMAGEMANAGER->findImage("RedNote"); // 그렇지 않다면 빨간 노트로 지정

    newNote.img->setX(newNote.pos.x - newNote.img->getWidth() / 2);
    newNote.img->setY(newNote.pos.y - newNote.img->getHeight() / 2);
    newNote.rc = RectMakeCenter(newNote.pos.x, newNote.pos.y, newNote.img->getWidth(), newNote.img->getHeight());
    newNote.speed = _deltaTime / ((_vMsTimeInfo[_countNote + 1] - _vMsTimeInfo[_countNote]) / 1000.0f) * NOTE_INTERVAL * SOUNDMANAGER->getPitch(_currentSongName, _pitch);
    newNote.isCol = false;
    newNote.isPressBtn = false;

    if (dirRight) _vNoteRight.push_back(newNote);
    else _vNoteLeft.push_back(newNote); // *카운트 노트는 왼쪽 기준으로만 세주자! 양쪽다 하면 두 번 일하는거니깐!
}

float Beat::GetSongVariousTime(unsigned int playTime, unsigned int songLength) // 곡의 여러가지 조건을 뽑아오기 위한 함수
{
    float songLeftLength = songLength - playTime;
    songLeftLength /= 1000;
    return songLeftLength;
}