#include "stdafx.h"
#include "player.h"
#include "Enemy.h"

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
	//����Ʈ
	IMAGEMANAGER->addImage("shovel_basic", "./image/player/shovel_basic.bmp", 48, 48, true, RGB(255, 0, 255), true); // �� 
	IMAGEMANAGER->addImage("player_effect_missed", "./image/player/TEMP_missed.bmp", 72, 26, true, RGB(255, 0, 255), true);  // ������ 
	IMAGEMANAGER->addFrameImage("swipe_dagger", "./image/player/swipe_dagger.bmp", 144, 192,3,4, true, RGB(255, 0, 255));
	// ���
	IMAGEMANAGER->addFrameImage("swipe_longsword����", "./image/player/swipe_longsword����.bmp", 192, 192, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("swipe_longsword�¿�", "./image/player/swipe_longsword�¿�.bmp", 384, 96, 4, 2, true, RGB(255, 0, 255));
	// ���� ��
	IMAGEMANAGER->addFrameImage("swipe_broadsword����", "./image/player/swipe_broadsword����.bmp", 432, 96, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("swipe_broadsword�¿�", "./image/player/swipe_broadsword�¿�.bmp", 144,288, 3, 2, true, RGB(255, 0, 255));
	// �����Ǿ� 
	IMAGEMANAGER->addFrameImage("swipe_rapier����", "./image/player/swipe_rapier����.bmp", 192, 192, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("swipe_rapier�¿�", "./image/player/swipe_rapier�¿�.bmp", 384, 96, 4, 2, true, RGB(255, 0, 255));


	// �÷��̾� ����
	_player.direction = PLAYERDIRECTION_RIGHT;
	_player.sight = 7;
	_player.weapon = PLAYERWAEPON_RAPIER;
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
	_time = 0.15;			 // �����̴� �ð� 

	// ���� 
	_jump = new jump;
	_jump->init();

	_isKeyPress = false;     // key �������� ��Ʈ�� �߰������� �Ǵ��ϴ� 
	_isKeyDown = false;      // key �Է��� �Ǵ� �ϴ� 
	destroyAllWindows();

	//��������Ʈ

	

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

	CAMERAMANAGER->set_CameraXY(_player.idx * _distance + (_distance / 2), _player.idy * _distance + (_distance / 3));

	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		(*_viEffect)->update();
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{

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
		//_isKeyPress = false;  // key �Է� �ʱ�ȭ 
		_isKeyDown = false;
	}
}

void player::playerMissEffect()
{
	alphaImageEffect* effect;
	effect = new alphaImageEffect;
	effect->init("player_effect_missed", CAMERAMANAGER->get_CameraX() + BEATMANAGER->getHeartMiddle() - 30, CAMERAMANAGER->get_CameraY() + (WINSIZEY - 200),10, SLOW);
	_vEffect.push_back(effect);
}

void player::playerShovelEffect(tagTile* tile)
{
	alphaImageEffect* effect;
	effect = new alphaImageEffect;
	effect->init("shovel_basic", tile->rc.left,tile->rc.top, 10,TIMESLOW);
	_vEffect.push_back(effect);
}

void player::playerAttackEffect(const char* imageName,tagTile* tile, int frameY)
{
	alphaImageEffect* effect;
	effect = new alphaImageEffect;
	effect->init(imageName, tile->rc.left, tile->rc.top, 0,frameY, FRAMEIMAGE);
	_vEffect.push_back(effect);
}

void player::playerAttackEffect(const char* imageName, float x, float y, int frameY)
{
	alphaImageEffect* effect;
	effect = new alphaImageEffect;
	effect->init(imageName, x, y, 0, frameY, FRAMEIMAGE);
	_vEffect.push_back(effect);
}

void player::playerAttackEffect(const char* imageName, int x, int y, int frameY)
{
	alphaImageEffect* effect;
	effect = new alphaImageEffect;
	effect->init(imageName, x, y, 0, frameY, FRAMEIMAGE);
	_vEffect.push_back(effect);
}

void player::keyControl()
{
	if (!_isKeyDown)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_player.direction = PLAYERDIRECTION_UP; 
			_isKeyDown = true;
			if (BEATMANAGER->getInterval())
			{
				tileCheck();
			}
			else
			{
				playerMissEffect();
			}
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_player.direction = PLAYERDIRECTION_DOWN;
			_isKeyDown = true;
			if (BEATMANAGER->getInterval())
			{
				tileCheck();
			}
			else
			{
				playerMissEffect();
			}
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			_player.direction = PLAYERDIRECTION_LEFT;
			_isKeyDown = true;
			if (BEATMANAGER->getInterval())
			{
				tileCheck();
			}
			else
			{
				playerMissEffect();
			}
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			_player.direction = PLAYERDIRECTION_RIGHT;
			_isKeyDown = true;
			if (BEATMANAGER->getInterval())
			{
				tileCheck();
			}
			else
			{
				playerMissEffect();
			}
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		//_isKeyPress = false;
		//_isKeyDown = false;
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		//_isKeyPress = false;
		//_isKeyDown = false;
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		//_isKeyPress = false;
		//_isKeyDown = false;
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		//_isKeyPress = false;
		//_isKeyDown = false;
	}

}

void player::tileCheck()
{
	_isKeyPress = true;				// ���͹� ���̿� ���� 
	
		for (_miPlayerTile = _mPlayerTile.begin(); _miPlayerTile != _mPlayerTile.end(); ++_miPlayerTile)
		{
			if (_miPlayerTile->first == PLAYERDIRECTION_UP && 
				_miPlayerTile->first == _player.direction)
			{
				if (_miPlayerTile->second->wall != W_NONE)
				{
					playerShovelEffect(_miPlayerTile->second);
					_miPlayerTile->second->type = TYPE_TERRAIN;
					_miPlayerTile->second->wall = W_NONE;
					_miPlayerTile->second->terrain = TR_BASIC_STAGE_TILE;
					_miPlayerTile->second->terrainFrameX = 0;
					_miPlayerTile->second->terrainFrameY = 0;
				}
				else if (_player.weapon != PLAYERWAEPON_NONE) // ���Ⱑ �ִ��� ������ �Ǵ�
				{
					// ���� Ÿ�� ������ �� 
					switch (_player.weapon)
					{
					case PLAYERWAEPON_DAGGER:
						playerAttackEffect("swipe_dagger", _miPlayerTile->second, 0);
						break;
					case PLAYERWAEPON_LONGSWORD:
						playerAttackEffect("swipe_longsword����", (_player.idx) * 52 , (_player.idy- 2) * 52, 0);

						break;
					case PLAYERWAEPON_BROADSWORD:
						playerAttackEffect("swipe_broadsword����", (_player.idx-1) * 52, (_player.idy - 1) * 52, 0);

						break;
					case PLAYERWAEPON_RAPIER:
						playerAttackEffect("swipe_rapier����", _player.idx * 52, (_player.idy - 2) * 52, 0);
						break;
					default:
						break;
					}
				}
				else
				{
					StateMove();
				}

				break;
			}
		
			if (_miPlayerTile->first == PLAYERDIRECTION_DOWN &&
				_miPlayerTile->first == _player.direction)
			{
				if (_miPlayerTile->second->wall != W_NONE)
				{
					playerShovelEffect(_miPlayerTile->second);
					_miPlayerTile->second->type = TYPE_TERRAIN;
					_miPlayerTile->second->wall = W_NONE;
					_miPlayerTile->second->terrain = TR_BASIC_STAGE_TILE;
					_miPlayerTile->second->terrainFrameX = 0;
					_miPlayerTile->second->terrainFrameY = 0;
				}
				else if (_player.weapon != PLAYERWAEPON_NONE) // ���Ⱑ �ִ��� ������ �Ǵ�
				{
					// ���� Ÿ�� ������ �� 
					switch (_player.weapon)
					{
					case PLAYERWAEPON_DAGGER:
						playerAttackEffect("swipe_dagger", _miPlayerTile->second, 1);
						break;
					case PLAYERWAEPON_LONGSWORD:
						playerAttackEffect("swipe_longsword����", _miPlayerTile->second, 1);

						break;
					case PLAYERWAEPON_BROADSWORD:
						playerAttackEffect("swipe_broadsword����", (_player.idx - 1) * 52, (_player.idy + 1) * 52, 1);

						break;
					case PLAYERWAEPON_RAPIER:
						playerAttackEffect("swipe_rapier����", _player.idx * 52, (_player.idy + 1) * 52, 1);
						break;
					default:
						break;
					}
				}
				else
				{
					StateMove();
				}
				break;
			}
		
			if (_miPlayerTile->first == PLAYERDIRECTION_LEFT &&
				_miPlayerTile->first == _player.direction)
			{
				if (_miPlayerTile->second->wall != W_NONE)
				{
					playerShovelEffect(_miPlayerTile->second);
					_miPlayerTile->second->type = TYPE_TERRAIN;
					_miPlayerTile->second->wall = W_NONE;
					_miPlayerTile->second->terrain = TR_BASIC_STAGE_TILE;
					_miPlayerTile->second->terrainFrameX = 0;
					_miPlayerTile->second->terrainFrameY = 0;
				}
				else if (_player.weapon != PLAYERWAEPON_NONE) // ���Ⱑ �ִ��� ������ �Ǵ�
				{
					// ���� Ÿ�� ������ �� 
					switch (_player.weapon)
					{
					case PLAYERWAEPON_DAGGER:
						playerAttackEffect("swipe_dagger", _miPlayerTile->second, 2);
						break;
					case PLAYERWAEPON_LONGSWORD:
						playerAttackEffect("swipe_longsword�¿�", (_player.idx-2) * 52, _player.idy * 52, 0);
						break;
					case PLAYERWAEPON_BROADSWORD:
						playerAttackEffect("swipe_broadsword�¿�", (_player.idx - 1) * 52, (_player.idy - 1) * 52, 0);

						break;
					case PLAYERWAEPON_RAPIER:
						playerAttackEffect("swipe_rapier�¿�", (_player.idx - 2) * 52, _player.idy  * 52, 0);
						break;
					default:
						break;
					}
				}
				else
				{
					StateMove();
				}
				break;
			}

			if (_miPlayerTile->first == PLAYERDIRECTION_RIGHT &&
				_miPlayerTile->first == _player.direction)
			{
				if (_miPlayerTile->second->wall != W_NONE)
				{
					playerShovelEffect(_miPlayerTile->second);
					_miPlayerTile->second->type = TYPE_TERRAIN;
					_miPlayerTile->second->wall = W_NONE;
					_miPlayerTile->second->terrain = TR_BASIC_STAGE_TILE;
					_miPlayerTile->second->terrainFrameX = 0;
					_miPlayerTile->second->terrainFrameY = 0;
				}
				else if (_player.weapon != PLAYERWAEPON_NONE) // ���Ⱑ �ִ��� ������ �Ǵ�
				{
					// ���� Ÿ�� ������ �� 
					switch (_player.weapon)
					{
					case PLAYERWAEPON_DAGGER:
						playerAttackEffect("swipe_dagger", _miPlayerTile->second, 3);
						break;
					case PLAYERWAEPON_LONGSWORD:
						playerAttackEffect("swipe_longsword�¿�", _miPlayerTile->second, 1);

						break;
					case PLAYERWAEPON_BROADSWORD:
						playerAttackEffect("swipe_broadsword�¿�", (_player.idx + 1) * 52, (_player.idy - 1) * 52, 1);

						break;
					case PLAYERWAEPON_RAPIER:
						playerAttackEffect("swipe_rapier�¿�", (_player.idx + 1) * 52, _player.idy * 52, 1);
						break;
					default:
						break;
					}
				}
				else
				{
					StateMove();
				}
				break;
			}
		}

}

void player::StateMove()
{
	switch (_player.direction)
	{
	case PLAYERDIRECTION_UP:
		_player.idy--;			// ��ǥY��--
			//��������
		_angle = getAngle(_player.x, _player.y, _player.x, _player.y - _distance);  // ���� 
		_worldTimeCount = TIMEMANAGER->getWorldTime();								// ���� �ð� 
		_isMoving = true;															// MOVE

		_jump->jumping(&_player.x, &_player.y, 2, 1.5, true); //���� 
		break;
	case PLAYERDIRECTION_DOWN:
		_player.idy++;	// ��ǥY��++
		//��������
		_angle = getAngle(_player.x, _player.y, _player.x, _player.y + _distance);  // ���� 
		_worldTimeCount = TIMEMANAGER->getWorldTime();								// ���� �ð� 
		_isMoving = true;															// MOVE

		_jump->jumping(&_player.x, &_player.y, 8, 1.5);	//���� 
		break;
	case PLAYERDIRECTION_RIGHT:
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
		break;
	case PLAYERDIRECTION_LEFT:
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
		break;
	default:
		break;
	}
}

void player::StateAttack()
{
	switch (_player.direction)
	{
	case PLAYERDIRECTION_UP:
		break;
	case PLAYERDIRECTION_DOWN:
		break;
	case PLAYERDIRECTION_RIGHT:
		break;
	case PLAYERDIRECTION_LEFT:
		break;
	default:
		break;
	}
}

void player::StateShovel()
{
	switch (_player.direction)
	{
	case PLAYERDIRECTION_UP:
		break;
	case PLAYERDIRECTION_DOWN:
		break;
	case PLAYERDIRECTION_RIGHT:
		break;
	case PLAYERDIRECTION_LEFT:
		break;
	default:
		break;
	}
}
