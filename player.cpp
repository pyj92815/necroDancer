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
	// �̹��� 
	_player.headImage = IMAGEMANAGER->addFrameImage("player1_heads", "./image/player/player1_heads.bmp", 384, 96, 8, 2, true, RGB(255, 0, 255));
	_player.bodyImage = IMAGEMANAGER->addFrameImage("player1_armor_body_xmas", "./image/player/player1_armor_body_xmas.bmp", 384, 240, 8, 5, true, RGB(255, 0, 255));

	//������ ����Ʈ
	IMAGEMANAGER->addImage("player_effect_missed", "./image/player/TEMP_missed.bmp", 72, 26, true, RGB(255, 0, 255), true);

	// �÷��̾� ����
	_player.state = PLAYERSTATE_RIGHT;
	_player.sight = 1;

	_miss = "player_effect_missed";

	//������ 
	int headRight[] = { 0,1,2,3,4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("headRight", "player1_heads", headRight, 8, 10, true);

	int bodyRight[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("bodyRight", "player1_armor_body_xmas", bodyRight, 4, 10, true);
	// ���� 
	int headLeft[] = { 15,14,13,12,11,10,9,8 };
	KEYANIMANAGER->addArrayFrameAnimation("headLeft", "player1_heads", headLeft, 8, 10, true);

	int bodyLeft[] = { 7,6,5,4 };
	KEYANIMANAGER->addArrayFrameAnimation("bodyLeft", "player1_armor_body_xmas", bodyLeft, 4, 10, true);

	//�ִϸ��̼� �ʱ�ȭ 
	_player.headAni = KEYANIMANAGER->findAnimation("headRight");
	_player.bodyAni = KEYANIMANAGER->findAnimation("bodyRight");

	//�÷��̾��� ��ġ index��
	_player.idx = idx;
	_player.idy = idy;

	//�÷��̾��� �ʱⰪ 
	_player.x = _player.idx * tileSizeX + (tileSizeX / 2);
	_player.y = _player.idy * tileSizeY + (tileSizeY / 3);

	_distance = tileSizeY;			// Ÿ���� distance 

	_player.rc = RectMakeCenter(_player.x, _player.y, _player.bodyImage->getFrameWidth(), _player.headImage->getFrameHeight());

	//�ִϸ��̼� ���� 
	_player.headAni->start();
	_player.bodyAni->start();

	//���� ���� 
	_action = new action;
	_action->init();
	_isMoving = false;		 // bool move
	_time = 0.2;			 // �����̴� �ð� 

	// ���� 
	_jump = new jump;
	_jump->init();

	_isKeyPress = false;     // key ���������� �Ǵ��ϴ� 
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
	playerMiss();					// MISS  ������ 
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
	_player.bodyImage->aniRender(CAMERAMANAGER->getWorldDC(), _player.x, _player.y, _player.bodyAni);	// ��
	_player.headImage->aniRender(CAMERAMANAGER->getWorldDC(), _player.x, _player.y, _player.headAni);	// �� 

	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		(*_viEffect)->render(CAMERAMANAGER->getWorldDC());
	}
}

void player::playerMove()
{
	if (!_isMoving) return;

	float elapsedTime = TIMEMANAGER->getElapsedTime();

	//200������ �Ÿ��� 2�ʿ� ���ļ� �����ؾ��Ѵٸ� �ӵ����� ������
	float moveSpeed = (elapsedTime / _time) * _distance;

	//�̹����� ������������ ������ �ӵ��� ���缭 ���ϴ� �ð��� ������ �Ѵ�
	_player.x = _player.x + cosf(_angle) * moveSpeed;
	_player.y = _player.y + (-sinf(_angle) * moveSpeed);

	float time = TIMEMANAGER->getElapsedTime();

	// ���� ���� �ð��� �����ϸ� 
	if (_time + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		// ��ġ�� ������Ű�� MOVE BOOL���� false��
		_player.x = _player.idx * _distance + (_distance / 2);
		_player.y = _player.idy * _distance + (_distance / 3);

		_isMoving = false;	  // ���� ���� 
		_isKeyPress = false;  // key �Է� �ʱ�ȭ 
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
				_player.idy--;			// ��ǥY��--
				_isKeyPress = true;		// key �Է� 
				//��������
				_angle = getAngle(_player.x, _player.y, _player.x, _player.y - _distance);  // ���� 
				_worldTimeCount = TIMEMANAGER->getWorldTime();								// ���� �ð� 
				_isMoving = true;															// MOVE

				_jump->jumping(&_player.x, &_player.y, 2, 1.5, true); //���� 
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
				_player.idy++;	// ��ǥY��++
				_isKeyPress = true;		// key �Է� 
				//��������
				_angle = getAngle(_player.x, _player.y, _player.x, _player.y + _distance);  // ���� 
				_worldTimeCount = TIMEMANAGER->getWorldTime();								// ���� �ð� 
				_isMoving = true;															// MOVE

				_jump->jumping(&_player.x, &_player.y, 8, 1.5);	//���� 
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
			_isKeyPress = true;		// key �Է� 
			//�̹��� ����
			_player.headAni = KEYANIMANAGER->findAnimation("headLeft");
			_player.bodyAni = KEYANIMANAGER->findAnimation("bodyLeft");
			_player.headAni->start();
			_player.bodyAni->start();
			_player.idx--;	// ��ǥ X��--
			//��������
			_angle = getAngle(_player.x, _player.y, _player.x - _distance, _player.y);	// ���� 
			_worldTimeCount = TIMEMANAGER->getWorldTime();								// ���� �ð� 
			_isMoving = true;															// MOVE
			_jump->jumping(&_player.x, &_player.y, 7, 1.5);	//���� 
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
				_isKeyPress = true;		// key �Է� 
				//�̹��� ����
				_player.headAni = KEYANIMANAGER->findAnimation("headRight");
				_player.bodyAni = KEYANIMANAGER->findAnimation("bodyRight");
				_player.headAni->start();
				_player.bodyAni->start();
				_player.idx++;	// ��ǥ X��++
				//��������
				_angle = getAngle(_player.x, _player.y, _player.x + _distance, _player.y);  // ���� 
				_worldTimeCount = TIMEMANAGER->getWorldTime();								// ���� �ð� 
				_isMoving = true;															// MOVE
				_jump->jumping(&_player.x, &_player.y, 7, 1.5);	// ����
			}
			else
			{
				_isMiss = true;
			}
		}
	}
}
