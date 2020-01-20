#include "stdafx.h"
#include "Beat.h"



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

    // 상점 주인과 거리에 따른 음향 크기 조절
    update_SoundDistanceControl();

    // Pitch값 조절
    update_PitchControl();
}

void Beat::render()
{
    Rectangle(getMemDC(), test_slowPlatform);
    Rectangle(getMemDC(), test_fastPlatform);
    Rectangle(getMemDC(), test_ShopKeeper);
    Rectangle(getMemDC(), test_Player);

    if (_noteLeft.size() > 0)
    {
        for (int i = 0; i < _noteLeft.size(); i++)
        {
            Rectangle(getMemDC(), _noteLeft[i].rc);
            _noteLeft[i].img->render(getMemDC(), _noteLeft[i].rc.left, _noteLeft[i].rc.top);
        }
    }

    //Rectangle(getMemDC(), heartRC);
    IMAGEMANAGER->frameRender("Heart", getMemDC(), heartImg->getX(), heartImg->getY());
    // 디버그 용 정보 출력
    render_DebugLog(getMemDC());
}


void Beat::init_AddSoundAndImg()
{
    //SOUNDMANAGER->addSound("BGM_LOBBY", "Music/lobby.ogg", false, true); // 원래 상태
    SOUNDMANAGER->addSound("BGM_LOBBY", "Music/lobby.ogg", true, false);
    SOUNDMANAGER->addSound("BGM_STAGE_1_1", "Music/zone1_1.ogg", true, false);
    SOUNDMANAGER->addSound("BGM_STAGE_1_2", "Music/zone1_2.ogg", true, false);
    SOUNDMANAGER->addSound("BGM_STAGE_1_3", "Music/zone1_3.ogg", true, false);
    SOUNDMANAGER->addSound("BGM_BOSS", "Music/boss_2.ogg", true, false);

    SOUNDMANAGER->addSound("NPC_Stage_1_1_shopkeeper", "Music/zone1_1_shopkeeper.ogg", true, false);
    SOUNDMANAGER->addSound("NPC_Stage_1_2_shopkeeper", "Music/zone1_2_shopkeeper.ogg", true, false);
    SOUNDMANAGER->addSound("NPC_Stage_1_3_shopkeeper", "Music/zone1_3_shopkeeper.ogg", true, false);

    IMAGEMANAGER->addImage("GreenNote", "image/player/TEMP_beat_marker.bmp", 12, 64, true, RGB(255, 0, 255));
    IMAGEMANAGER->addImage("RedNote", "image/player/TEMP_beat_marker_red.bmp", 12, 64, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("Heart", "image/player/TEMP_beat_heart.bmp", 164, 104, 2, 1, true, RGB(255, 0, 255));
}

void Beat::init_SetObjs()
{
    _currentStage = STAGE_LOBBY;
    _noteFileName = _currentSongName = _oldSongName = "";
    heartFrameCount = heartFrameRate = _isBeating = _activeAction = _deltaTime = _countNote = _countComma = _oldStageID = _currentStageID = _songPos = _pitch = _noteSpeed = 0;

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

void Beat::update_SceneCheck()
{
    if (KEYMANAGER->isOnceKeyDown('E')) _currentStage = STAGE_LOBBY, _currentStageID = (int)_currentStage, _currentSongName = "BGM_LOBBY", _currentShopkeeper = "", _noteFileName = "Music/lobby.txt", Load();
    else if (KEYMANAGER->isOnceKeyDown('R')) _currentStage = STAGE_1_1, _currentStageID = (int)_currentStage, _currentSongName = "BGM_STAGE_1_1", _currentShopkeeper = "NPC_Stage_1_1_shopkeeper", _noteFileName = "Music/zone1_1.txt", Load();
    else if (KEYMANAGER->isOnceKeyDown('T')) _currentStage = STAGE_1_2, _currentStageID = (int)_currentStage, _currentSongName = "BGM_STAGE_1_2", _currentShopkeeper = "NPC_Stage_1_2_shopkeeper", _noteFileName = "Music/zone1_2.txt", Load();
    else if (KEYMANAGER->isOnceKeyDown('Y')) _currentStage = STAGE_1_3, _currentStageID = (int)_currentStage, _currentSongName = "BGM_STAGE_1_3", _currentShopkeeper = "NPC_Stage_1_3_shopkeeper", _noteFileName = "Music/zone1_3.txt", Load();
    else if (KEYMANAGER->isOnceKeyDown('U')) _currentStage = BOSS, _currentStageID = (int)_currentStage, _currentSongName = "BGM_BOSS", _currentShopkeeper = "", _noteFileName = "Music/boss_2.txt", Load();
}

void Beat::update_PlayerMoveTest()
{
    if (KEYMANAGER->isStayKeyDown(VK_UP)) test_PlayerPos.y -= 3;
    if (KEYMANAGER->isStayKeyDown(VK_LEFT)) test_PlayerPos.x -= 3;
    if (KEYMANAGER->isStayKeyDown(VK_DOWN)) test_PlayerPos.y += 3;
    if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) test_PlayerPos.x += 3;
    test_Player = RectMakeCenter(test_PlayerPos.x, test_PlayerPos.y, 25, 25);
}

void Beat::update_SongAndNoteControl()
{
    // 프로그램 최초 실행 후 재생한 곡이 아직 아무것도 없는 경우에 키를 입력한 경우
    if (_currentSongName != "" && _oldSongName == "")
    {
        _oldSongName = _currentSongName;
    }
    if (_currentShopkeeper != "" && _oldShopKeeper == "")
    {
        _oldShopKeeper = _currentShopkeeper;
    }

    // 현재 스테이지가 기존 스테이지와 다를 때
    if (_currentStageID != _oldStageID)
    {
        _noteSpeed = 0;
        _noteLeft.clear();
        SOUNDMANAGER->stop(_oldSongName), SOUNDMANAGER->stop(_oldShopKeeper);
        SOUNDMANAGER->play(_currentSongName), SOUNDMANAGER->play(_currentShopkeeper);
        _oldSongName = _currentSongName;
        _oldShopKeeper = _currentShopkeeper;
        _oldStageID = _currentStageID;
        _deltaTime = TIMEMANAGER->getElapsedTime();

        for (int i = 0; i < 4; i++) // 새 노트로 리셋
        {
            tagNote setStartNote;
            setStartNote.pos = { (float)WINSIZEX_HALF - (NOTE_INTERVAL * (i + 1)), WINSIZEY - 100 };
            setStartNote.img = new image;
            setStartNote.img = IMAGEMANAGER->findImage("GreenNote");
            setStartNote.img->setX(setStartNote.pos.x - setStartNote.img->getWidth() / 2);
            setStartNote.img->setY(setStartNote.pos.y - setStartNote.img->getHeight() / 2);
            setStartNote.rc = RectMakeCenter(setStartNote.pos.x, setStartNote.pos.y, setStartNote.img->getWidth(), setStartNote.img->getHeight());
            setStartNote.speed = _deltaTime / ((_msTimeInfo[_countNote + 1] - _msTimeInfo[_countNote]) / 1000.0f) * NOTE_INTERVAL * SOUNDMANAGER->getPitch(_currentSongName, _pitch);
            setStartNote.isCol = false;
            _noteLeft.push_back(setStartNote);
            ++_countNote;
        }
    }

    if (_songPos > 0) // 곡이 시작되었을때
    {
        for (int i = 0; i < _noteLeft.size(); i++)
        {
            if (_noteLeft[i].pos.x >= WINSIZEX / 2)
            {
                _noteLeft.erase(_noteLeft.begin() + i);
                _activeAction = true;

                if (_noteLeft.size() <= 0) break;

                if (_countNote < _countComma - 3) // 노트 오차 보정(맨 처음 노트 스킵한 거 1개, 텍스트에 불러온 끝의 쓰레기 정보 2개만큼 뺌)
                {
                    tagNote newNote;
                    newNote.pos = { 0, WINSIZEY - 100 };
                    newNote.img = IMAGEMANAGER->findImage("GreenNote");
                    newNote.img->setX(newNote.pos.x - newNote.img->getWidth() / 2);
                    newNote.img->setY(newNote.pos.y - newNote.img->getHeight() / 2);
                    newNote.rc = RectMakeCenter(newNote.pos.x, newNote.pos.y, newNote.img->getWidth(), newNote.img->getHeight());
                    newNote.speed = _deltaTime / ((_msTimeInfo[_countNote + 1] - _msTimeInfo[_countNote]) / 1000.0f) * NOTE_INTERVAL * SOUNDMANAGER->getPitch(_currentSongName, _pitch);
                    newNote.isCol = false;
                    _noteLeft.push_back(newNote);
                    ++_countNote;
                }
            }
            _noteLeft[i].pos.x += _deltaTime / ((_msTimeInfo[_countNote + 1] - _msTimeInfo[_countNote]) / 1000.0f) * NOTE_INTERVAL * SOUNDMANAGER->getPitch(_currentSongName, _pitch);
            _noteLeft[i].img->setX(_noteLeft[i].pos.x - _noteLeft[i].img->getWidth() / 2);
            _noteLeft[i].img->setY(_noteLeft[i].pos.y - _noteLeft[i].img->getHeight() / 2);
            _noteLeft[i].rc = RectMakeCenter(_noteLeft[i].pos.x, _noteLeft[i].pos.y, _noteLeft[i].img->getWidth(), _noteLeft[i].img->getHeight());

            RECT temp;
            if (IntersectRect(&temp, &_noteLeft[i].rc, &heartRC))
            {
                _isBeating = true;
                _noteLeft[i].isCol = true;
            }
        }
    }
}

void Beat::update_BeatEffect()
{
    if (_isBeating)
    {
        ++heartFrameRate;
        heartImg->setFrameX(1);
        if (heartFrameRate > HEARTFRAME_RATE)
        {
            heartFrameRate = 0;
            _isBeating = false;
            heartImg->setFrameX(0);
        }
    }
}

void Beat::update_SoundDistanceControl()
{
    float getDistaceTemp = getDistance(test_PlayerPos.x, test_PlayerPos.y, test_ShopKeeperPos.x, test_ShopKeeperPos.y);
    if (getDistaceTemp < 40) SOUNDMANAGER->setVolume(_currentShopkeeper, 1);
    else if (getDistaceTemp >= 40 && getDistaceTemp < 80) SOUNDMANAGER->setVolume(_currentShopkeeper, 0.75f);
    else if (getDistaceTemp >= 80 && getDistaceTemp < 120) SOUNDMANAGER->setVolume(_currentShopkeeper, 0.50f);
    else SOUNDMANAGER->setVolume(_currentShopkeeper, 0.25f);
}

void Beat::update_PitchControl()
{
    RECT temp;
    if (IntersectRect(&temp, &test_Player, &test_slowPlatform))
    {
        SOUNDMANAGER->setPitch(_currentShopkeeper, 0.875f);
        SOUNDMANAGER->setPitch(_currentSongName, 0.875f);
    }
    else if ((IntersectRect(&temp, &test_Player, &test_fastPlatform)))
    {
        SOUNDMANAGER->setPitch(_currentShopkeeper, 1.125f);
        SOUNDMANAGER->setPitch(_currentSongName, 1.125f);
    }
    else
    {
        SOUNDMANAGER->setPitch(_currentShopkeeper, 1);
        SOUNDMANAGER->setPitch(_currentSongName, 1);
    }

}

void Beat::render_DebugLog(HDC getMemDC)
{
    if (_currentSongName != "")
    {
        char display_Pitch[128];
        sprintf_s(display_Pitch, sizeof(display_Pitch), "%f", SOUNDMANAGER->getPitch(_currentSongName, _pitch));
        TextOut(getMemDC, 100, 100, display_Pitch, strlen(display_Pitch));

        char display_songPos[256];
        sprintf_s(display_songPos, sizeof(display_songPos), "%d", SOUNDMANAGER->getSongPosition(_currentSongName, _songPos));
        TextOut(getMemDC, 100, 120, display_songPos, strlen(display_songPos));

        char display_endVec[256];
        sprintf_s(display_endVec, sizeof(display_endVec), "%d", _noteLeft.size());
        TextOut(getMemDC, 100, 140, display_endVec, strlen(display_endVec));

        char display_noteInfoLength[256];
        sprintf_s(display_noteInfoLength, sizeof(display_noteInfoLength), "%d", _msTimeInfo.size());
        TextOut(getMemDC, 100, 160, display_noteInfoLength, strlen(display_noteInfoLength));

        char display_countComma[256];
        sprintf_s(display_countComma, sizeof(display_countComma), "%d", heartFrameRate);
        TextOut(getMemDC, 100, 180, display_countComma, strlen(display_countComma));

        char display_checkInfo[256];
        sprintf_s(display_checkInfo, sizeof(display_checkInfo), "%d", _countNote);
        TextOut(getMemDC, 100, 200, display_checkInfo, strlen(display_checkInfo));
    }
}

void Beat::Load()
{
    // 선형 보간 이동시 _noteInfo[0]과 _noteInfo.size() - 1요소는 의미없는 값이므로 제외한다. 단, _noteInfo[0]은 애니메이션이 움직여야하니 애니메이션 흘러가는 값에는 추가
    if (_msTimeInfo.size() > 0)
    {
        _msTimeInfo.clear(); // 벡터 재사용을 위한 클리어
        _countNote = _countComma = 0;
    }

    ifstream readFile;
    string tempWord;
    readFile.open(_noteFileName);

    if (readFile.is_open())
    {
        while (!readFile.eof())
        {
            char temp;
            readFile.get(temp);

            if (temp == ',')
            {
                ++_countComma;
                _msTimeInfo.push_back(atoi(tempWord.c_str())); // 변환 순서 : 문자열 -> char*로 변환 -> atoi는 char*을 int로 변환
                tempWord = "";
                continue;
            }
            tempWord += temp;
        }
        //_msTimeInfo.erase(_msTimeInfo.begin() + (_msTimeInfo.size() - 1)); // 현재 구조상 맨 마지막 부분에 0을 항상 저장하므로 맨 마지막 요소를 제거함
        readFile.close();
    }
}