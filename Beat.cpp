#include "stdafx.h"
#include "Beat.h"
#include"gameNode.h"


HRESULT Beat::init()
{
    // ���� �߰�
    init_AddSoundAndImg();

    // ������Ʈ�� �ʱ�ȭ
    init_SetObjs();
    return S_OK;
}

void Beat::release()
{
}

void Beat::update()
{
    // �� üũ
    update_SceneCheck();

    // �÷��̾� ������
    update_PlayerMoveTest();

    // �뷡 & ��Ʈ ����
    update_SongAndNoteControl();

    // ���� ȿ��
    update_BeatEffect();

    // �Ÿ��� ���� ���� ũ�� ����
    update_SoundDistanceControl();

    // Pitch�� ����
    update_PitchControl();
}

void Beat::render()
{
    Rectangle(_backBuffer->getMemDC(), test_slowPlatform);
    Rectangle(_backBuffer->getMemDC(), test_fastPlatform);
    Rectangle(_backBuffer->getMemDC(), test_ShopKeeper);
    Rectangle(_backBuffer->getMemDC(), test_Player);

    if (_vNoteLeft.size() > 0) // ���� ��Ʈ ����
    {
        for (int i = 0; i < _vNoteLeft.size(); i++)
        {
            //Rectangle(getMemDC(), _noteLeft[i].rc);
            _vNoteLeft[i].img->render(_backBuffer->getMemDC(), _vNoteLeft[i].rc.left, _vNoteLeft[i].rc.top);
        }
    }
    if (_vNoteRight.size() > 0) // ������ ��Ʈ ����
    {
        for (int i = 0; i < _vNoteRight.size(); i++)
        {
            //Rectangle(getMemDC(), _noteRight[i].rc);
            _vNoteRight[i].img->render(_backBuffer->getMemDC(), _vNoteRight[i].rc.left, _vNoteRight[i].rc.top);
        }
    }

    //Rectangle(getMemDC(), heartRC);
    IMAGEMANAGER->frameRender("Heart", _backBuffer->getMemDC(), heartImg->getX(), heartImg->getY()); // ���� ����

    render_DebugLog(_backBuffer->getMemDC()); // ����� �ؽ�Ʈ ����
}


void Beat::init_AddSoundAndImg() // ���� & �̹��� �߰�
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

void Beat::init_SetObjs() // Beat Ŭ�������� �����ϰ� ����� ���� ������ �ʱ�ȭ ���� �Լ�
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

void Beat::update_SceneCheck() // �� ������ �޾ƿ� �Լ�
{
    if (KEYMANAGER->isOnceKeyDown('E')) _currentStage = STAGE_LOBBY, _currentStageID = (int)_currentStage, _currentSongName = "BGM_LOBBY", _currentShopkeeper = "", _noteFileName = "Music/lobby.txt", Load(), _loopSong = true;
    else if (KEYMANAGER->isOnceKeyDown('R')) _currentStage = STAGE_1_1, _currentStageID = (int)_currentStage, _currentSongName = "BGM_STAGE_1_1", _currentShopkeeper = "NPC_Stage_1_1_shopkeeper", _noteFileName = "Music/zone1_1.txt", Load(), _loopSong = false;
    else if (KEYMANAGER->isOnceKeyDown('T')) _currentStage = STAGE_1_2, _currentStageID = (int)_currentStage, _currentSongName = "BGM_STAGE_1_2", _currentShopkeeper = "NPC_Stage_1_2_shopkeeper", _noteFileName = "Music/zone1_2.txt", Load(), _loopSong = false;
    else if (KEYMANAGER->isOnceKeyDown('Y')) _currentStage = STAGE_1_3, _currentStageID = (int)_currentStage, _currentSongName = "BGM_STAGE_1_3", _currentShopkeeper = "NPC_Stage_1_3_shopkeeper", _noteFileName = "Music/zone1_3.txt", Load(), _loopSong = false;
    else if (KEYMANAGER->isOnceKeyDown('U')) _currentStage = BOSS, _currentStageID = (int)_currentStage, _currentSongName = "BGM_BOSS", _currentShopkeeper = "", _noteFileName = "Music/boss_2.txt", Load(), _loopSong = true;
}

void Beat::update_PlayerMoveTest() // �׽�Ʈ�� �÷��̾�
{
    if (KEYMANAGER->isStayKeyDown(VK_UP)) test_PlayerPos.y -= 3;
    if (KEYMANAGER->isStayKeyDown(VK_LEFT)) test_PlayerPos.x -= 3;
    if (KEYMANAGER->isStayKeyDown(VK_DOWN)) test_PlayerPos.y += 3;
    if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) test_PlayerPos.x += 3;
    test_Player = RectMakeCenter(test_PlayerPos.x, test_PlayerPos.y, 25, 25);
}

void Beat::update_SongAndNoteControl() // ��� ��Ʈ ����
{
    SOUNDMANAGER->getSongPosition(_currentSongName, _songPos); // ���� ���� ���� ���� ���� �ð��� �޾� ��(ms)
    _songLeftTime = GetSongVariousTime(_songPos, _songLength); // ���� ���� ��ŭ ���Ҵ��� �˷���

    // ���α׷� ���� ���� �� ����� ���� ���� �ƹ��͵� ���� ��쿡 Ű�� �Է��� ���
    if (_currentSongName != "" && _oldSongName == "")
    {
        _oldSongName = _currentSongName;
    }
    if (_currentShopkeeper != "" && _oldShopKeeper == "")
    {
        _oldShopKeeper = _currentShopkeeper;
    }

    // ���� ���������� ���� ���������� �ٸ� �� �ʱ�ȭ���ִ� �͵�(��Ʈ �ӵ�, ���� �ð�, ���͵�, ��� �� ��ü, ���� �� ������ ���� Ű ���� ��ü, ��Ÿ Ÿ�� �ٽ� �ޱ�, �ʱ� ��Ʈ ����)
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

    if (_songPos > 0) // ���� ���۵Ǿ�����
    {
        for (int i = 0; i < _vNoteRight.size(); i++) // ������ ��Ʈ
        {
            if (_vNoteRight[i].pos.x <= WINSIZEX / 2) // ���������� ������ ��Ʈ�� ���� x������ ���� ��� (��Ʈ�� ������ ���� ��)
            {
                _vNoteRight.erase(_vNoteRight.begin() + i); // �Ѿ ��Ʈ ����
                if (_vNoteRight.size() <= 0) break; // ��Ʈ ������ ũ�Ⱑ 0 �����϶� �浹�� ���� ���� Break; <�̰� ���ϸ� �ؿ� �̵��ϴ� �ڵ忡 �����ϰ� ��������>

                if (_countNote < _countComma - 3) // ��Ʈ ���� ���� ��Ʈ ���� ���� - 3���� ���� ���(��Ʈ ���� ���� ����(�� ó�� ��Ʈ ��ŵ�� �� 1��, �ؽ�Ʈ�� �ҷ��� ���� ������ ���� 2����ŭ ��))
                {
                    CreateNewNoteWhilePlay(true); // ��Ʈ ����
                }
                else // ��Ʈ ���� ���� ���� ��Ʈ ���� ���̸� �Ѿ ��
                {
                    if (_loopSong) // ���� �ݺ� ���϶�
                    {
                        _countNote = 0; // ��Ʈ�� �ٽ� ���� ���� �ʱ�ȭ
                        CreateNewNoteWhilePlay(true);
                    }
                }
            }
            _vNoteRight[i].pos.x -= _deltaTime / ((_vMsTimeInfo[_countNote + 1] - _vMsTimeInfo[_countNote]) / 1000.0f) * NOTE_INTERVAL * SOUNDMANAGER->getPitch(_currentSongName, _pitch); // ��Ʈ �̵� (��Ÿ Ÿ�� / ���� ��Ʈ �ð�(ms)�� * ��Ʈ ���� * ���� �� pitch ��)
            _vNoteRight[i].img->setX(_vNoteRight[i].pos.x - _vNoteRight[i].img->getWidth() / 2); // �̹��� ��ġ ����
            _vNoteRight[i].img->setY(_vNoteRight[i].pos.y - _vNoteRight[i].img->getHeight() / 2); // �̹��� ��ġ ����
            _vNoteRight[i].rc = RectMakeCenter(_vNoteRight[i].pos.x, _vNoteRight[i].pos.y, _vNoteRight[i].img->getWidth(), _vNoteRight[i].img->getHeight()); // ��Ʈ�� ���� ��ġ ���

            RECT temp;
            if (IntersectRect(&temp, &_vNoteRight[i].rc, &heartRC)) // ��Ʈ�� �����̶� �浹 �� 
            {
                if (!_vNoteRight[i].isCol) _isBeating = true; // ���� �̹��� ������ ���� true�� ����
                _vNoteRight[i].isCol = true; // ���͹��� �� ������ �� �� ������ �αٰŸ��� ���� �����ϱ� ���� true�� ����
            }
        } // ��������� ������ ��Ʈ

        for (int i = 0; i < _vNoteLeft.size(); i++) // ���� ��Ʈ, ���� ���� �ؼ��ϸ� ��
        {
            if (_vNoteLeft[i].pos.x >= WINSIZEX / 2)
            {
                _vNoteLeft.erase(_vNoteLeft.begin() + i);

                if (_vNoteLeft.size() <= 0) break;

                if (_countNote < _countComma - 3)
                {
                    CreateNewNoteWhilePlay(false);
                    ++_countNote; // ��Ʈ�� �� ��, ���� �� ���� ���� 2�� �����ϹǷ� �� �ʸ� ���ش�.
                }
                else
                {
                    if (_loopSong)
                    {
                        _countNote = 0;
                        CreateNewNoteWhilePlay(false);
                        ++_countNote; // ��Ʈ�� �� ��, ���� �� ���� ���� 2�� �����ϹǷ� �� �ʸ� ���ش�.
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
        } // ��������� ���� ��Ʈ
    }
}

void Beat::update_BeatEffect() // ���� �ڵ� �� ������ ���� �̹����� ������ �̿��� �͵��� �����ϱ� ���� �Լ�
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

void Beat::update_SoundDistanceControl() // �Ÿ��� ���� �Ҹ�ũ�� ����
{
    float getDistaceTemp = getDistance(test_PlayerPos.x, test_PlayerPos.y, test_ShopKeeperPos.x, test_ShopKeeperPos.y);
    if (getDistaceTemp < 40) SOUNDMANAGER->setVolume(_currentShopkeeper, 1);
    else if (getDistaceTemp >= 40 && getDistaceTemp < 80) SOUNDMANAGER->setVolume(_currentShopkeeper, 0.75f);
    else if (getDistaceTemp >= 80 && getDistaceTemp < 120) SOUNDMANAGER->setVolume(_currentShopkeeper, 0.50f);
    else SOUNDMANAGER->setVolume(_currentShopkeeper, 0.25f);
}

void Beat::update_PitchControl() // �� �ӵ� ����
{
    RECT temp;
    if (IntersectRect(&temp, &test_Player, &test_slowPlatform)) SOUNDMANAGER->setPitch(_currentShopkeeper, 0.875f), SOUNDMANAGER->setPitch(_currentSongName, 0.875f);
    else if ((IntersectRect(&temp, &test_Player, &test_fastPlatform))) SOUNDMANAGER->setPitch(_currentShopkeeper, 1.125f), SOUNDMANAGER->setPitch(_currentSongName, 1.125f);
    else SOUNDMANAGER->setPitch(_currentShopkeeper, 1), SOUNDMANAGER->setPitch(_currentSongName, 1);
}

void Beat::render_DebugLog(HDC getMemDC) // ����׿� �Լ�
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



void Beat::Load() // ��Ʈ ���� �ε�
{
    // ���� ���� �̵��� _noteInfo[0]�� _noteInfo.size() - 1��Ҵ� �ǹ̾��� ���̹Ƿ� �����Ѵ�. ��, _noteInfo[0]�� �ִϸ��̼��� ���������ϴ� �ִϸ��̼� �귯���� ������ �߰�
    if (_vMsTimeInfo.size() > 0)
    {
        _vMsTimeInfo.clear(); // ���� ������ ���� Ŭ����
        _countNote = _countComma = 0; // ��Ʈ ������ ���� �޾ƿ��� ���� �ʱ�ȭ
    }
    _songLength = 0; // ���� ���� �� �ʱ�ȭ

    ifstream readFile;
    string tempWord;
    readFile.open(_noteFileName); // ���� ����

    if (readFile.is_open()) // ������ ���������� �����ִٸ�
    {
        while (!readFile.eof()) // �о���� ������ ���� ���������� �ݺ�
        {
            char temp; // ���ڸ� �ϳ��� �̱� ���� ����
            readFile.get(temp); // ���� �ϳ� �̱� 
            if (temp == ',')
            {
                ++_countComma; // �޸� ����
                _vMsTimeInfo.push_back(atoi(tempWord.c_str())); // ��ȯ ���� : ���ڿ� -> char*�� ��ȯ -> atoi�� char*�� int�� ��ȯ
                tempWord = ""; // string �ʱ�ȭ
                continue;
            }
            tempWord += temp; // �� ���ھ� string�� ��ħ
        }
        //_msTimeInfo.erase(_msTimeInfo.begin() + (_msTimeInfo.size() - 1)); // ���� ������ �� ������ �κп� 0�� �׻� �����ϹǷ� �� ������ ��Ҹ� ������
        readFile.close(); // ���� �ݱ�
    }

    for (int i = 0; i < _vMsTimeInfo.size() - 2; i++) // FMOD::SOUND�� getLength() �Լ��� �������� ������� �Ф�... �Ƹ� ������ �Լ��� ���� ���� Ȯ���ڿ� ���� �� �۵��Ǵ� �Լ��� �ִ� �ݸ� �ƴ� �Լ��� �ִ�. ���� ��� getVolume�Լ� ���� ��쿡�� �Ϻ� Ȯ���ڸ� �Լ� ����� ������
    {
        int getMS = _vMsTimeInfo[i + 1] - _vMsTimeInfo[i]; // �� ���� ��Ʈ ������ �޾ƿ��� ���ؼ�..
        _songLength += getMS; // ���̸� ����ش�. ���߿� _songLength�� ���� �� ���̰� �ȴ�.
    }
}

void Beat::CreateNewNote(bool dirRight) // ��Ʈ ����, �� ���� ������ (���������� ������ ���� ������ ���ϱ�)
{
    for (int i = 0; i < 4; i++) // �� ��Ʈ�� ����, ������
    {
        tagNote setNote;
        if (dirRight) setNote.pos = { (float)WINSIZEX_HALF + (NOTE_INTERVAL * (i + 1)), (float)(heartRC.top + heartRC.bottom) / 2 }; // ������ �������� ���
        else setNote.pos = { (float)WINSIZEX_HALF - (NOTE_INTERVAL * (i + 1)), (float)(heartRC.top + heartRC.bottom) / 2 }; // ������ ������ ���

        setNote.img = new image;
        setNote.img = IMAGEMANAGER->findImage("GreenNote");
        setNote.img->setX(setNote.pos.x - setNote.img->getWidth() / 2);
        setNote.img->setY(setNote.pos.y - setNote.img->getHeight() / 2);
        setNote.rc = RectMakeCenter(setNote.pos.x, setNote.pos.y, setNote.img->getWidth(), setNote.img->getHeight());
        setNote.speed = _deltaTime / ((_vMsTimeInfo[_countNote + 1] - _vMsTimeInfo[_countNote]) / 1000.0f) * NOTE_INTERVAL * SOUNDMANAGER->getPitch(_currentSongName, _pitch);
        setNote.isCol = false;
        setNote.isPressBtn = false;

        if (dirRight) _vNoteRight.push_back(setNote);
        else _vNoteLeft.push_back(setNote), ++_countNote; // *ī��Ʈ ��Ʈ�� ���� �������θ� ������! ���ʴ� �ϸ� �� �� ���ϴ°Ŵϱ�!
    }
}

void Beat::CreateNewNoteWhilePlay(bool dirRight) // ��Ʈ ����, �� ���� �� (���������� ������ ���� ������ ���ϱ�)
{
    tagNote newNote;
    if(dirRight) newNote.pos = { WINSIZEX, (float)(heartRC.top + heartRC.bottom) / 2 }; // ������ �������� ���
    else newNote.pos = { 0, (float)(heartRC.top + heartRC.bottom) / 2 }; // ������ ������ ���

    if (_loopSong) newNote.img = IMAGEMANAGER->findImage("GreenNote"); // �ݺ� ���� ��쿡�� ��� �ʷϻ� ��Ʈ �̹����� �������ش�.
    else if (_songLeftTime > (float)(_songLength / 1000) * 0.15f && !_loopSong) newNote.img = IMAGEMANAGER->findImage("GreenNote"); // ���� ���� ���� ��ü �� ������ 15%���� ū ��� �ʷϻ� ��Ʈ �̹��� ���� 
    else newNote.img = IMAGEMANAGER->findImage("RedNote"); // �׷��� �ʴٸ� ���� ��Ʈ�� ����

    newNote.img->setX(newNote.pos.x - newNote.img->getWidth() / 2);
    newNote.img->setY(newNote.pos.y - newNote.img->getHeight() / 2);
    newNote.rc = RectMakeCenter(newNote.pos.x, newNote.pos.y, newNote.img->getWidth(), newNote.img->getHeight());
    newNote.speed = _deltaTime / ((_vMsTimeInfo[_countNote + 1] - _vMsTimeInfo[_countNote]) / 1000.0f) * NOTE_INTERVAL * SOUNDMANAGER->getPitch(_currentSongName, _pitch);
    newNote.isCol = false;
    newNote.isPressBtn = false;

    if (dirRight) _vNoteRight.push_back(newNote);
    else _vNoteLeft.push_back(newNote); // *ī��Ʈ ��Ʈ�� ���� �������θ� ������! ���ʴ� �ϸ� �� �� ���ϴ°Ŵϱ�!
}

float Beat::GetSongVariousTime(unsigned int playTime, unsigned int songLength) // ���� �������� ������ �̾ƿ��� ���� �Լ�
{
    float songLeftLength = songLength - playTime;
    songLeftLength /= 1000;
    return songLeftLength;
}