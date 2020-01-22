#include "stdafx.h"
#include "player.h"

player::player()
{
}

player::~player()
{
}

HRESULT player::init(int idx, int idy, int tileSizeX, int tileSizeY)
{
	// 이미지 
	_player.headImage = IMAGEMANAGER->addFrameImage("player1_heads", "./image/player/player1_heads.bmp", 384, 96, 8, 2, true, RGB(255, 0, 255));
	_player.bodyImage = IMAGEMANAGER->addFrameImage("player1_armor_body_xmas", "./image/player/player1_armor_body_xmas.bmp", 384, 240, 8, 5, true, RGB(255, 0, 255));

	//빗나감 이펙트
	IMAGEMANAGER->addImage("player_effect_missed", "./image/player/TEMP_missed.bmp", 72, 26, true, RGB(255, 0, 255), true);

	// 플레이어 상태
	_player.state = PLAYERSTATE_RIGHT;
	_player.sight = 1;

	_miss = "player_effect_missed";

	//오른쪽 
	int headRight[] = { 0,1,2,3,4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("headRight", "player1_heads", headRight, 8, 10, true);

	int bodyRight[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("bodyRight", "player1_armor_body_xmas", bodyRight, 4, 10, true);
	// 왼쪽 
	int headLeft[] = { 15,14,13,12,11,10,9,8 };
	KEYANIMANAGER->addArrayFrameAnimation("headLeft", "player1_heads", headLeft, 8, 10, true);

	int bodyLeft[] = { 7,6,5,4 };
	KEYANIMANAGER->addArrayFrameAnimation("bodyLeft", "player1_armor_body_xmas", bodyLeft, 4, 10, true);

	//애니매이션 초기화 
	_player.headAni = KEYANIMANAGER->findAnimation("headRight");
	_player.bodyAni = KEYANIMANAGER->findAnimation("bodyRight");

	//플레이어의 위치 index값
	_player.idx = idx;
	_player.idy = idy;

	//플레이어의 초기값 
	_player.x = _player.idx * tileSizeX + (tileSizeX / 2);
	_player.y = _player.idy * tileSizeY + (tileSizeY / 3);

	_distance = tileSizeY;			// 타일의 distance 

	_player.rc = RectMakeCenter(_player.x, _player.y, _player.bodyImage->getFrameWidth(), _player.headImage->getFrameHeight());

	//애니매이션 시작 
	_player.headAni->start();
	_player.bodyAni->start();

	//선형 보간 
	_action = new action;
	_action->init();
	_isMoving = false;		 // bool move
	_time = 0.2;			 // 움직이는 시간 

	// 점프 
	_jump = new jump;
	_jump->init();

	_isKeyPress = false;     // key 눌렸을때를 판단하는 
	destroyAllWindows();

	//effect

	_isMiss = false;

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	_jump->update();				// JUMP
	keyControl();					// KEY
	playerMove();					// MOVE
	playerMiss();					// MISS  빗나감 
	CAMERAMANAGER->set_CameraXY(_player.idx * _distance + (_distance / 2), _player.idy * _distance + (_distance / 3));



	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_isMiss = true;
	}

	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		(*_viEffect)->update();
	}
}

void player::render()
{
	_player.bodyImage->aniRender(CAMERAMANAGER->getWorldDC(), _player.x, _player.y, _player.bodyAni);	// 몸
	_player.headImage->aniRender(CAMERAMANAGER->getWorldDC(), _player.x, _player.y, _player.headAni);	// 얼굴 

	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		(*_viEffect)->render(CAMERAMANAGER->getWorldDC());
	}
}

void player::playerMove()
{
	if (!_isMoving) return;

	float elapsedTime = TIMEMANAGER->getElapsedTime();

	//200정도의 거리를 2초에 걸쳐서 도달해야한다면 속도값을 구해줌
	float moveSpeed = (elapsedTime / _time) * _distance;

	//이미지를 도착지점까지 각도와 속도를 맞춰서 원하는 시간에 도달케 한다
	_player.x = _player.x + cosf(_angle) * moveSpeed;
	_player.y = _player.y + (-sinf(_angle) * moveSpeed);

	float time = TIMEMANAGER->getElapsedTime();

	// 만약 월드 시간이 도달하면 
	if (_time + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		// 위치를 고정시키고 MOVE BOOL값을 false로
		_player.x = _player.idx * _distance + (_distance / 2);
		_player.y = _player.idy * _distance + (_distance / 3);

		_isMoving = false;	  // 선형 보간 
		_isKeyPress = false;  // key 입력 초기화 
	}
}

void player::playerMiss()
{
	if (!_isMiss) return;
	alphaImageEffect* effect;
	effect = new alphaImageEffect;
	effect->init(_miss, CAMERAMANAGER->get_CameraX() + 100, CAMERAMANAGER->get_CameraY() + 100,10);
	_vEffect.push_back(effect);
	_isMiss = false;
}

void player::keyControl()
{
	if (!_isKeyPress)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (BEATMANAGER->getBeating())
			{
				_player.idy--;			// 좌표Y값--
				_isKeyPress = true;		// key 입력 
				//선형보간
				_angle = getAngle(_player.x, _player.y, _player.x, _player.y - _distance);  // 방향 
				_worldTimeCount = TIMEMANAGER->getWorldTime();								// 월드 시간 
				_isMoving = true;															// MOVE

				_jump->jumping(&_player.x, &_player.y, 2, 1.5, true); //점프 
			}
			else
			{
				_isMiss = true;
			}
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (BEATMANAGER->getBeating())
			{
				_player.idy++;	// 좌표Y값++
				_isKeyPress = true;		// key 입력 
				//선형보간
				_angle = getAngle(_player.x, _player.y, _player.x, _player.y + _distance);  // 방향 
				_worldTimeCount = TIMEMANAGER->getWorldTime();								// 월드 시간 
				_isMoving = true;															// MOVE

				_jump->jumping(&_player.x, &_player.y, 8, 1.5);	//점프 
			}
			else
			{
				_isMiss = true;
			}
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (BEATMANAGER->getBeating())
			{
			_isKeyPress = true;		// key 입력 
			//이미지 관련
			_player.headAni = KEYANIMANAGER->findAnimation("headLeft");
			_player.bodyAni = KEYANIMANAGER->findAnimation("bodyLeft");
			_player.headAni->start();
			_player.bodyAni->start();
			_player.idx--;	// 좌표 X값--
			//선형보간
			_angle = getAngle(_player.x, _player.y, _player.x - _distance, _player.y);	// 방향 
			_worldTimeCount = TIMEMANAGER->getWorldTime();								// 월드 시간 
			_isMoving = true;															// MOVE
			_jump->jumping(&_player.x, &_player.y, 7, 1.5);	//점프 
			}
			else
			{
				_isMiss = true;
			}
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (BEATMANAGER->getBeating())
			{
				_isKeyPress = true;		// key 입력 
				//이미지 관련
				_player.headAni = KEYANIMANAGER->findAnimation("headRight");
				_player.bodyAni = KEYANIMANAGER->findAnimation("bodyRight");
				_player.headAni->start();
				_player.bodyAni->start();
				_player.idx++;	// 좌표 X값++
				//선형보간
				_angle = getAngle(_player.x, _player.y, _player.x + _distance, _player.y);  // 방향 
				_worldTimeCount = TIMEMANAGER->getWorldTime();								// 월드 시간 
				_isMoving = true;															// MOVE
				_jump->jumping(&_player.x, &_player.y, 7, 1.5);	// 점프
			}
			else
			{
				_isMiss = true;
			}
		}
	}
}
