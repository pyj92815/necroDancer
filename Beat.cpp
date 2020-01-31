#include "stdafx.h"
#include "Beat.h"
#include"gameNode.h"
#include "player.h"
#include "alphaImageEffect.h"

vector<alphaImageEffect*>		     _vEffect;  // ������ ����Ʈ 
vector<alphaImageEffect*>::iterator _viEffect;



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
    update_SetSceneMusic();
    
    // �÷��̾� ������
    // update_PlayerMoveTest();
    
    // �뷡 & ��Ʈ ����
    update_SongAndNoteControl();
    
    Move();
    
    // ���� ȿ��
    update_BeatEffect();
    
    // �Ÿ��� ���� ���� ũ�� ����
    update_SoundDistanceControl();
    
    // Pitch�� ����
    update_PitchControl();
}

void Beat::render()
{
    //Rectangle(_backBuffer->getMemDC(), test_slowPlatform);
    //Rectangle(_backBuffer->getMemDC(), test_fastPlatform);
    //Rectangle(_backBuffer->getMemDC(), test_ShopKeeper);
    //Rectangle(_backBuffer->getMemDC(), test_Player);
    //Rectangle(_backBuffer->getMemDC(), heartRC); // ���� ��Ʈ ����
    IMAGEMANAGER->frameRender("Heart", _backBuffer->getMemDC(), heartImg->getX(), heartImg->getY()); // ���� ����

    if (_vNoteLeft.size() > 0) // ���� ��Ʈ ����
    {
        for (int i = 0; i < _vNoteLeft.size(); i++)
        {
            if (!_vNoteLeft[i].isRender) continue;
            //Rectangle(_backBuffer->getMemDC(), _vNoteLeft[i].rc);
            _vNoteLeft[i].img->alphaRender(_backBuffer->getMemDC(), _vNoteLeft[i].rc.left, _vNoteLeft[i].rc.top, _vNoteLeft[i].alpha);
        }
    }
    if (_vNoteRight.size() > 0) // ������ ��Ʈ ����
    {
        for (int i = 0; i < _vNoteRight.size(); i++)
        {
            if (!_vNoteRight[i].isRender) continue;
            //Rectangle(_backBuffer->getMemDC(), _vNoteRight[i].rc);
            _vNoteRight[i].img->alphaRender(_backBuffer->getMemDC(), _vNoteRight[i].rc.left, _vNoteRight[i].rc.top, _vNoteRight[i].alpha);
        }
    }

    for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
    {
        (*_viEffect)->render(_backBuffer->getMemDC());
    }
    IMAGEMANAGER->frameRender("Heart", _backBuffer->getMemDC(), heartImg->getX(), heartImg->getY()); // ���� ����
    render_DebugLog(_backBuffer->getMemDC()); // ����� �ؽ�Ʈ ����
}

void Beat::HitNoteEffect(float x, float y)
{
    alphaImageEffect* noteHitEffect;
    noteHitEffect = new alphaImageEffect;
    noteHitEffect->init("GreenNote", x, y, 5, STOP);
    _vEffect.push_back(noteHitEffect);
}


void Beat::init_AddSoundAndImg() // ���� & �̹��� �߰�
{
    //SOUNDMANAGER->addSound("BGM_LOBBY", "Music/lobby.ogg", false, true);
    SOUNDMANAGER->addSound("BGM_LOBBY", "Music/lobby.ogg", true, false);
    SOUNDMANAGER->addSound("BGM_STAGE_1_1", "Music/zone1_1.ogg", true, false);
    SOUNDMANAGER->addSound("BGM_STAGE_1_2", "Music/zone1_2.ogg", true, false);
    SOUNDMANAGER->addSound("BGM_STAGE_1_3", "Music/zone1_3.ogg", true, false);
    SOUNDMANAGER->addSound("BGM_BOSS", "Music/boss_2.ogg", false, true);

    SOUNDMANAGER->addSound("NPC_Stage_1_1_shopkeeper", "Music/zone1_1_shopkeeper.ogg", true, false);
    SOUNDMANAGER->addSound("NPC_Stage_1_2_shopkeeper", "Music/zone1_2_shopkeeper.ogg", true, false);
    SOUNDMANAGER->addSound("NPC_Stage_1_3_shopkeeper", "Music/zone1_3_shopkeeper.ogg", true, false);

    IMAGEMANAGER->addImage("GreenNote", "image/player/TEMP_beat_marker.bmp", 12, 64, true, RGB(255, 0, 255), true);
    IMAGEMANAGER->addImage("RedNote", "image/player/TEMP_beat_marker_red.bmp", 12, 64, true, RGB(255, 0, 255), true);
    IMAGEMANAGER->addFrameImage("Heart", "image/player/TEMP_beat_heart.bmp", 220, 138, 2, 1, true, RGB(255, 0, 255));
}

void Beat::init_SetObjs() // Beat Ŭ�������� �����ϰ� ����� ���� ������ �ʱ�ȭ ���� �Լ�
{
    _currentStage = STAGE_LOBBY;

    _noteFileName = _currentSongName = _oldSongName = ""; // �ҷ��� ���� �̸�, ���� �� �̸�, ���� �� �̸� �ʱ�ȭ
    noteTimeIntervalCount = inputIntervalCount = _songLeftTime = heartFrameCount = _isBeating
        = _countNote = _oldStageID = _currentStageID = _songLength = _songPos = _pitch = 0;

    musicID = 0;
    musicID_Temp = -1;

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
    heartImg->setX((float)WINSIZEX_HALF - heartImg->getFrameWidth() / 2), heartImg->setY(((float)WINSIZEY - heartImg->getFrameHeight()) - heartImg->getFrameHeight() / 2);
    heartRC = RectMakeCenter(heartImg->getX() + heartImg->getFrameWidth() / 2, heartImg->getY() + heartImg->getFrameHeight() / 2, heartImg->getFrameWidth(), heartImg->getFrameHeight());
}

void Beat::update_SetSceneMusic() // �� ������ �޾ƿ� �Լ�
{
    if (musicID == 1) _currentStage = STAGE_LOBBY, _currentStageID = (int)_currentStage, _currentSongName = "BGM_LOBBY", _currentShopkeeper = "", _noteFileName = "Music/lobby.txt", Load(), _loopSong = false;
    else if (musicID == 2) _currentStage = STAGE_1_1, _currentStageID = (int)_currentStage, _currentSongName = "BGM_STAGE_1_1", _currentShopkeeper = "NPC_Stage_1_1_shopkeeper", _noteFileName = "Music/zone1_1.txt", Load(), _loopSong = false;
    else if (musicID == 3) _currentStage = STAGE_1_2, _currentStageID = (int)_currentStage, _currentSongName = "BGM_STAGE_1_2", _currentShopkeeper = "NPC_Stage_1_2_shopkeeper", _noteFileName = "Music/zone1_2.txt", Load(), _loopSong = false;
    else if (musicID == 4) _currentStage = STAGE_1_3, _currentStageID = (int)_currentStage, _currentSongName = "BGM_STAGE_1_3", _currentShopkeeper = "NPC_Stage_1_3_shopkeeper", _noteFileName = "Music/zone1_3.txt", Load(), _loopSong = false;
    else if (musicID == 5) _currentStage = BOSS, _currentStageID = (int)_currentStage, _currentSongName = "BGM_BOSS", _currentShopkeeper = "", _noteFileName = "Music/boss_2.txt", Load(), _loopSong = true;
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

    // ���� ���������� ���� ���������� �ٸ� �� �ʱ�ȭ���ִ� �͵�(��Ʈ �ӵ�, ���� �ð�, ���͵�, ��� �� ��ü, ���� �� ������ ���� Ű ���� ��ü, ��Ÿ Ÿ�� �ٽ� �ޱ�, �ʱ� ��Ʈ ����)
    if (_currentStageID != _oldStageID)
    {
        musicID_Temp = musicID;
        _songLeftTime = 0;
        _vNoteLeft.clear();
        _vNoteRight.clear();
        SOUNDMANAGER->play(_currentSongName), SOUNDMANAGER->play(_currentShopkeeper);
        _oldSongName = _currentSongName;
        _oldShopKeeper = _currentShopkeeper;
        _oldStageID = _currentStageID;

        if (TIMEMANAGER->getFrameRate() > 10)
        {
            _deltaTime = TIMEMANAGER->getElapsedTime();
        }
        else
        {
            _deltaTime = 0.016f;
        }

        TIMEMANAGER->setCountTimeResetSwitch(true); // ���� �ð� ����
        TIMEMANAGER->setCountTimeSwitch(true); // �ð� ���� ON

        CreateNewNote(true);
        CreateNewNote(false);
    }

    if (_songPos > 0) // ���� ���۵Ǿ�����
    {
        for (int i = 0; i < _vNoteLeft.size(); i++)
        {
            noteTimeIntervalCount = TIMEMANAGER->getCountTime();
            //if (_vNoteLeft.size() <= 0) break;
            //if (_vNoteLeft[i].pos.x >= WINSIZEX_HALF) // ���� ��Ʈ�� ���� x��ǥ �� �̻��� ���
            //{
            //    _player->setPlayerKeyDown();
            //    inputIntervalCount = 0;
            //    _vNoteRight.erase(_vNoteRight.begin() + i);
            //    _vNoteLeft.erase(_vNoteLeft.begin() + i);
            //    
            //    break;
            //}
            if (_vNoteLeft.size() < 0)
                break;

            if (noteTimeIntervalCount >= noteTimeInterval)
            {
                TIMEMANAGER->setCountTime(0);
                noteTimeIntervalCount = 0;

                if (_countNote < _vMsTimeInfo.size() - 5) // ��Ʈ ���� ���� ��Ʈ ���� ���� - 3���� ���� ���(��Ʈ ���� ���� ����(�� ó�� ��Ʈ ��ŵ�� �� 1��, �ؽ�Ʈ�� �ҷ��� ���� ������ ���� 2����ŭ ��))
                {
                    CreateNewNoteWhilePlay(true); // ��Ʈ ����
                    CreateNewNoteWhilePlay(false); // ��Ʈ ����
                }
                else // ��Ʈ ���� ���� ���� ��Ʈ ���� ���̸� �Ѿ ��
                {
                    if (_loopSong) // ���� �ݺ� ���϶�
                    {
                        _countNote = 0; // ��Ʈ�� �ٽ� ���� ���� �ʱ�ȭ
                        CreateNewNoteWhilePlay(true); // ��Ʈ ����
                        CreateNewNoteWhilePlay(false); // ��Ʈ ����
                    }
                }
            }
            _vNoteRight[i].img->setX(_vNoteRight[i].pos.x - _vNoteRight[i].img->getWidth() / 2); // �̹��� ��ġ ����
            _vNoteRight[i].img->setY(_vNoteRight[i].pos.y - _vNoteRight[i].img->getHeight() / 2); // �̹��� ��ġ ����
            _vNoteRight[i].rc = RectMakeCenter(_vNoteRight[i].pos.x, _vNoteRight[i].pos.y, _vNoteRight[i].img->getWidth(), _vNoteRight[i].img->getHeight()); // ��Ʈ�� ��Ʈ ��ġ ���

            _vNoteLeft[i].img->setX(_vNoteLeft[i].pos.x - _vNoteLeft[i].img->getWidth() / 2);
            _vNoteLeft[i].img->setY(_vNoteLeft[i].pos.y - _vNoteLeft[i].img->getHeight() / 2);
            _vNoteLeft[i].rc = RectMakeCenter(_vNoteLeft[i].pos.x, _vNoteLeft[i].pos.y, _vNoteLeft[i].img->getWidth(), _vNoteLeft[i].img->getHeight());

            if (inputIntervalCount > 0.000f)
            {
                Interval = true;
            }
            else Interval = false;

            if (i != 3 && _vNoteLeft[i].alpha < 255)    // ��Ʈ ����� ������ ���İ� ���� ��Ű��
            {
                _vNoteLeft[i].alpha += 3;
                _vNoteRight[i].alpha += 3;
            }
        }

        // ����Ʈ, ���� ���� �Ŀ� ��Ʈ ����Ʈ�� ���� �ִ� ��츦 �����.
        for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
        {
            (*_viEffect)->update();
        }
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
        sprintf_s(display_songPos, sizeof(display_songPos), "%d", _countNote);
        TextOut(getMemDC, 100, 120, display_songPos, strlen(display_songPos));

        char display_endVec[256];
        sprintf_s(display_endVec, sizeof(display_endVec), "%f", inputIntervalCount);
        TextOut(getMemDC, 100, 140, display_endVec, strlen(display_endVec));

        char display_songLength[256];
        sprintf_s(display_songLength, sizeof(display_songLength), "%d", _oldStageID);
        TextOut(getMemDC, 100, 180, display_songLength, strlen(display_songLength));

        char display_checkInfo[256];
        sprintf_s(display_checkInfo, sizeof(display_checkInfo), "%d", _currentStageID);
        TextOut(getMemDC, 100, 200, display_checkInfo, strlen(display_checkInfo));

        char display_checkAverSpeed[256];
        sprintf_s(display_checkAverSpeed, sizeof(display_checkAverSpeed), "(_vMsTimeInfo[i + 1] - _vMsTimeInfo[i]) / 1000.0f : %f", (_vMsTimeInfo[_countNote + 1] - _vMsTimeInfo[_countNote]) / 1000.0f);
        TextOut(getMemDC, 100, 220, display_checkAverSpeed, strlen(display_checkAverSpeed));
    }
}

void Beat::Load() // ��Ʈ ���� �ε�
{
    // ���� ���� �̵��� _noteInfo[0]�� _noteInfo.size() - 1��Ҵ� �ǹ̾��� ���̹Ƿ� �����Ѵ�. ��, _noteInfo[0]�� �ִϸ��̼��� ���������ϴ� �ִϸ��̼� �귯���� ������ �߰�
    if (_vMsTimeInfo.size() < 0)
    {
        _vMsTimeInfo.clear(); // ���� ������ ���� Ŭ����
        //_countNote = _countComma = 0; // ��Ʈ ������ ���� �޾ƿ��� ���� �ʱ�ȭ
        _countNote = 0;
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
                //++_countComma; // �޸� ����
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
    for (int i = 0; i < 3; i++) // �� ��Ʈ�� ����, ������
    {
        tagNote setNote;
        int tempMS = _vMsTimeInfo[_countNote + 1] - _vMsTimeInfo[_countNote];
        int bpm = 60000 / tempMS;

        if (dirRight) // ������ �������� ���
        {
            setNote.pos = { (float)WINSIZEX_HALF + (NOTE_INTERVAL * (i + 1)), (float)(heartRC.top + heartRC.bottom) / 2 };
            setNote.speed = lerp(setNote.pos.x, setNote.pos.x - NOTE_INTERVAL, (_deltaTime / ((tempMS + bpm) / 1000.0f)));
        }
        else // ������ ������ ���
        {
            setNote.pos = { (float)WINSIZEX_HALF - (NOTE_INTERVAL * (i + 1)), (float)(heartRC.top + heartRC.bottom) / 2 };
            setNote.speed = lerp(setNote.pos.x, setNote.pos.x + NOTE_INTERVAL, (_deltaTime / ((tempMS + bpm) / 1000.0f)));
        }

        setNote.img = new image;
        setNote.img = IMAGEMANAGER->findImage("GreenNote");
        setNote.img->setX(setNote.pos.x - setNote.img->getWidth() / 2);
        setNote.img->setY(setNote.pos.y - setNote.img->getHeight() / 2);
        setNote.rc = RectMakeCenter(setNote.pos.x, setNote.pos.y, setNote.img->getWidth(), setNote.img->getHeight());
        setNote.isCol = false;
        setNote.isRender = true;
        setNote.alpha = 127;

        noteTimeInterval = (_vMsTimeInfo[_countNote + 1] - _vMsTimeInfo[_countNote]) / 1000.0f;

        if (dirRight) _vNoteRight.push_back(setNote);
        else _vNoteLeft.push_back(setNote), ++_countNote; // *ī��Ʈ ��Ʈ�� ���� �������θ� ������! ���ʴ� �ϸ� �� �� ���ϴ°Ŵϱ�!
    }
}

void Beat::CreateNewNoteWhilePlay(bool dirRight) // ��Ʈ ����, �� ���� �� (���������� ������ ���� ������ ���ϱ�)
{
    tagNote newNote;
    int tempMS = _vMsTimeInfo[_countNote + 1] - _vMsTimeInfo[_countNote];
    int bpm = 60000 / tempMS;

    if (dirRight) // ������ �������� ���
    {
        newNote.pos = { WINSIZEX, (float)(heartRC.top + heartRC.bottom) / 2 };
    }
    else // ������ ������ ���
    {
        newNote.pos = { 0, (float)(heartRC.top + heartRC.bottom) / 2 };
    }
    newNote.speed = lerp(newNote.pos.x, WINSIZEX_HALF, (_deltaTime / ((tempMS + bpm) / 1000.0f)) / 3);

    if (_loopSong) newNote.img = IMAGEMANAGER->findImage("GreenNote"); // �ݺ� ���� ��쿡�� ��� �ʷϻ� ��Ʈ �̹����� �������ش�.
    else if (_songLeftTime > (float)(_songLength / 1000) * 0.15f && !_loopSong) newNote.img = IMAGEMANAGER->findImage("GreenNote"); // ���� ���� ���� ��ü �� ������ 15%���� ū ��� �ʷϻ� ��Ʈ �̹��� ���� 
    else newNote.img = IMAGEMANAGER->findImage("RedNote"); // �׷��� �ʴٸ� ���� ��Ʈ�� ����
    newNote.img->setX(newNote.pos.x - newNote.img->getWidth() / 2);
    newNote.img->setY(newNote.pos.y - newNote.img->getHeight() / 2);

    newNote.rc = RectMakeCenter(newNote.pos.x, newNote.pos.y, newNote.img->getWidth(), newNote.img->getHeight());
    newNote.isCol = false;
    newNote.isRender = true;
    newNote.alpha = 127;

    noteTimeInterval = (_vMsTimeInfo[_countNote + 1] - _vMsTimeInfo[_countNote]) / 1000.0f;

    if (dirRight) _vNoteRight.push_back(newNote);
    else _vNoteLeft.push_back(newNote), ++_countNote; // ��Ʈ�� �� ��, ���� �� ���� ���� 2�� �����ϹǷ� �� �ʸ� ���ش�.
}

float Beat::GetSongVariousTime(unsigned int playTime, unsigned int songLength) // ���� �������� ������ �̾ƿ��� ���� �Լ�
{
    float songLeftLength = songLength - playTime;
    songLeftLength /= 1000;
    return songLeftLength;
}

void Beat::Move()
{
    if (_songPos > 0) // ���� ���۵Ǿ�����
    {
        for (int i = 0; i < _vNoteLeft.size(); i++)
        {
            _vNoteRight[i].pos.x += _vNoteRight[i].speed * SOUNDMANAGER->getPitch(_currentSongName, _pitch);
            _vNoteLeft[i].pos.x += _vNoteLeft[i].speed * SOUNDMANAGER->getPitch(_currentSongName, _pitch);

            RECT temp;
            if (IntersectRect(&temp, &_vNoteLeft[i].rc, &heartRC)) // ��Ʈ�� �����̶� �浹 �� 
            {
                if (!_vNoteLeft[i].isCol) _isBeating = true; // ���� �̹��� ������ ���� true�� ����
                _vNoteLeft[i].isCol = true; // ���͹��� �� ������ �� �� ������ �αٰŸ��� ���� �����ϱ� ���� true�� ����
                inputIntervalCount += _deltaTime; // �Է��� �� �ִ� �ð� ����

                 // �÷��̾ Ű �Է½�
                if (_player->getPlayerKey() && Interval)
                {
                    _player->setPlayerKey();
                    if (_vNoteLeft[i].pos.x < WINSIZEX_HALF)
                    {
                        HitNoteEffect(_vNoteLeft[i].pos.x - NOTE_RADIUS_X, ((heartRC.bottom + heartRC.top) / 2) - ((_vNoteLeft[i].rc.bottom - _vNoteLeft[i].rc.top) / 2));
                        _vNoteLeft[i].isRender = false;
                        _effect = true;

                        HitNoteEffect(_vNoteRight[i].pos.x - NOTE_RADIUS_X, ((heartRC.bottom + heartRC.top) / 2) - ((_vNoteRight[i].rc.bottom - _vNoteRight[i].rc.top) / 2));
                        _vNoteRight[i].isRender = false;
                        _effect = true;
                    }
                    inputIntervalCount = 0;
                }
            }
            if (_vNoteLeft[i].pos.x > WINSIZEX_HALF)
            {
                _vNoteLeft[i].isRender = false;
                _vNoteRight[i].isRender = false;
            }
            if (_vNoteLeft[i].pos.x - (heartImg->getFrameWidth() / 2) > WINSIZEX_HALF)
            {
                _player->setPlayerKey();
                _player->setPlayerKeyDown();
                inputIntervalCount = 0;
                _vNoteRight.erase(_vNoteRight.begin() + i);
                _vNoteLeft.erase(_vNoteLeft.begin() + i);
                break;
            }
        }
    }
}
