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
	imageSetting();			 // �̹��� 
	_jump = new jump;		 // ���� Ŭ����
	_jump->init();
	//�ִϸ��̼� �ʱ�ȭ 
	_player.headAni = KEYANIMANAGER->findAnimation("headRight");			// �ִϸ��̼� �̹���
	_player.bodyAni = KEYANIMANAGER->findAnimation("bodyRight");
	_player.headImage = IMAGEMANAGER->findImage("player1_heads");			// �̹���
	_player.bodyImage = IMAGEMANAGER->findImage("player1_armor_body_xmas");
	_player.headAni->start();
	_player.bodyAni->start();
	_player.direction = PLAYERDIRECTION_RIGHT;				// ���� ������	RIGHT
	_player.weapon = PLAYERWAEPON_NONE;						// ����			NONE
	_player.sight = 7;										// �þ� ��		7
	_player.idx = idx;										// �ε��� X
	_player.idy = idy;										// �ε��� Y
	_player.x = _player.idx * tileSizeX + (tileSizeX / 2);
	_player.y = _player.idy * tileSizeY + (tileSizeY / 3);
	_player.rc = RectMakeCenter(_player.x, _player.y, _player.bodyImage->getFrameWidth(), _player.headImage->getFrameHeight());

	_distance = tileSizeY;			//  Ÿ�� ���� �Ÿ�
	_time = 0.15;					//  MOVE �ð� 

	_isMoving = false;		 // MOVE �Ǵ�
	_isKeyPress = false;     // ��Ʈ �Ǵ� 
	_isKeyDown = false;      // KEY �Է� �Ǵ�

	destroyAllWindows(); // �ӽ� ����
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

	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		(*_viEffect)->update();
	}
	CAMERAMANAGER->set_CameraXY(_player.idx * _distance + (_distance / 2), _player.idy * _distance + (_distance / 3)); // ī�޶� ����
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

	// ���� ���� �ð��� �����ϸ� 
	if (_time + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		// ��ġ�� ������Ű�� MOVE BOOL���� false��
		_player.x = _player.idx * _distance + (_distance / 2);
		_player.y = _player.idy * _distance + (_distance / 3);

		_isMoving = false;	    // ���� ���� 
		_isKeyDown = false;		
		//_isKeyPress = false;  // key �Է� �ʱ�ȭ 
	}
}

void player::playerEffect_Miss()
{
	alphaImageEffect* effect;
	effect = new alphaImageEffect;
	effect->init("player_effect_missed", CAMERAMANAGER->get_CameraX() + BEATMANAGER->getHeartMiddle() - 30, CAMERAMANAGER->get_CameraY() + (WINSIZEY - 200),10, SLOW);
	_vEffect.push_back(effect);
}

void player::playerEffect_Shovel(tagTile* tile)
{
	alphaImageEffect* effect;
	effect = new alphaImageEffect;
	effect->init("shovel_basic", tile->rc.left,tile->rc.top, 10,TIMESLOW);
	_vEffect.push_back(effect);
	CAMERAMANAGER->Camera_WorldDC_Shake(); // ������ ����ó�� ������ ī�޶� 0,0������ �۵� ���� 
}
// Ÿ�� ��ġ
void player::playerEffect_Attack(const char* imageName,tagTile* tile, int frameY)
{
	alphaImageEffect* effect;
	effect = new alphaImageEffect;
	effect->init(imageName, tile->rc.left, tile->rc.top, 0,frameY, FRAMEIMAGE);
	_vEffect.push_back(effect);
}
// ��ǥ�� x,y�� ��ġ
void player::playerEffect_Attack(const char* imageName, float x, float y, int frameY)
{
	alphaImageEffect* effect;
	effect = new alphaImageEffect;
	effect->init(imageName, x, y, 0, frameY, FRAMEIMAGE);
	_vEffect.push_back(effect);
}
// idx, idy�� ��ġ
void player::playerEffect_Attack(const char* imageName, int x, int y, int frameY)
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
		if (KEYMANAGER->isOncekeytwoDown(VK_LEFT, VK_UP))
		{
			_isKeyDown = true;
			cout << "�̰� ü�� Ű " << endl;
		}
		else if (KEYMANAGER->isOncekeytwoDown(VK_LEFT, VK_DOWN))
		{
			_isKeyDown = true;
			cout << "�̰� ��ź Ű " << endl;
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_player.direction = PLAYERDIRECTION_UP; 
			_isKeyDown = true;
			if (BEATMANAGER->getInterval())
			{
				tileCheck();
			}
			else
			{
				playerEffect_Miss();
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
				playerEffect_Miss();
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
				playerEffect_Miss();
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
				playerEffect_Miss();
			}
		}
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
					playerEffect_Shovel(_miPlayerTile->second);
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
						playerEffect_Attack("swipe_dagger", _miPlayerTile->second, 0);
						break;
					case PLAYERWAEPON_LONGSWORD:
						playerEffect_Attack("swipe_longsword����", (_player.idx) * 52 , (_player.idy- 2) * 52, 0);

						break;
					case PLAYERWAEPON_BROADSWORD:
						playerEffect_Attack("swipe_broadsword����", (_player.idx-1) * 52, (_player.idy - 1) * 52, 0);

						break;
					case PLAYERWAEPON_RAPIER:
						playerEffect_Attack("swipe_rapier����", _player.idx * 52, (_player.idy - 2) * 52, 0);
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
					playerEffect_Shovel(_miPlayerTile->second);
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
						playerEffect_Attack("swipe_dagger", _miPlayerTile->second, 1);
						break;
					case PLAYERWAEPON_LONGSWORD:
						playerEffect_Attack("swipe_longsword����", _miPlayerTile->second, 1);

						break;
					case PLAYERWAEPON_BROADSWORD:
						playerEffect_Attack("swipe_broadsword����", (_player.idx - 1) * 52, (_player.idy + 1) * 52, 1);

						break;
					case PLAYERWAEPON_RAPIER:
						playerEffect_Attack("swipe_rapier����", _player.idx * 52, (_player.idy + 1) * 52, 1);
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
					playerEffect_Shovel(_miPlayerTile->second);
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
						playerEffect_Attack("swipe_dagger", _miPlayerTile->second, 2);
						break;
					case PLAYERWAEPON_LONGSWORD:
						playerEffect_Attack("swipe_longsword�¿�", (_player.idx-2) * 52, _player.idy * 52, 0);
						break;
					case PLAYERWAEPON_BROADSWORD:
						playerEffect_Attack("swipe_broadsword�¿�", (_player.idx - 1) * 52, (_player.idy - 1) * 52, 0);

						break;
					case PLAYERWAEPON_RAPIER:
						playerEffect_Attack("swipe_rapier�¿�", (_player.idx - 2) * 52, _player.idy  * 52, 0);
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
					playerEffect_Shovel(_miPlayerTile->second);
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
						playerEffect_Attack("swipe_dagger", _miPlayerTile->second, 3);
						break;
					case PLAYERWAEPON_LONGSWORD:
						playerEffect_Attack("swipe_longsword�¿�", _miPlayerTile->second, 1);

						break;
					case PLAYERWAEPON_BROADSWORD:
						playerEffect_Attack("swipe_broadsword�¿�", (_player.idx + 1) * 52, (_player.idy - 1) * 52, 1);

						break;
					case PLAYERWAEPON_RAPIER:
						playerEffect_Attack("swipe_rapier�¿�", (_player.idx + 1) * 52, _player.idy * 52, 1);
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
