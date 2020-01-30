#include "stdafx.h"
#include "player.h"
#include "EnemyManager.h"
#include "Enemy.h"

player::player()
{
}

player::~player()
{
}

HRESULT player::init(int idx, int idy, int tileSizeX, int tileSizeY)
{
	imageSetting();			 // 이미지 
	_jump = new jump;		 // 점프 클래스
	_jump->init();
	//애니매이션 초기화 
	_player.headAni = KEYANIMANAGER->findAnimation("headRight");			// 애니매이션 이미지
	_player.bodyAni = KEYANIMANAGER->findAnimation("bodyRight");
	_player.headImage = IMAGEMANAGER->findImage("player1_heads");			// 이미지
	_player.bodyImage = IMAGEMANAGER->findImage("player1_armor_body_xmas");
	_player.headAni->start();
	_player.bodyAni->start();
	_player.direction = PLAYERDIRECTION_RIGHT;				// 방향 오른쪽	RIGHT
	_player.weapon = PLAYERWAEPON_NONE;						// 무기			NONE
	_player.sight = 5;										// 시야 값		7
	_player.damage = 1;										// 데미지        1
	_player.idx = idx;										// 인덱스 X
	_player.idy = idy;										// 인덱스 Y
	_player.score = 0;				// 점수
	_player.coin = 0;				// 돈
	_player.diamond = 0;			// 다이아몬드
	_player.x = _player.idx * tileSizeX + (tileSizeX / 2);
	_player.y = _player.idy * tileSizeY + (tileSizeY / 3);
	_player.rc = RectMakeCenter(_player.x, _player.y, _player.bodyImage->getFrameWidth(), _player.headImage->getFrameHeight());
	_shadow = _player.y;
	_player.isArmor = false;
	_player.isWeapon = false;

	_distance = tileSizeY;			//  타일 중점 거리
	_time = 0.15;					//  MOVE 시간 

	_isMoving = false;		 // MOVE 판단
	_isKeyPress = false;     // 노트 판단 
	_isKeyDown = false;      // KEY 입력 판단

	destroyAllWindows(); // 임시 설정
	return S_OK;
}

void player::release()
{
}

void player::update()
{
	_jump->update();							  // JUMP
	if (!_jump->getJumping()) _shadow = _player.y; // 그림자의 위치(제트오더 점프 시 벽뒤로 넘어가지 않게 하기 위한 변수)

	keyControl();					// KEY
	playerMove();					// MOVE

	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		(*_viEffect)->update();
	}
	CAMERAMANAGER->set_CameraXY(_player.idx * _distance + (_distance / 2), _player.idy * _distance + (_distance / 3)); // 카메라 세팅

	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		playerEffect_Attack("swipe_dagger", _player.x, _player.y, 0);
	}
}

void player::render()
{
	_player.bodyImage->aniRender(CAMERAMANAGER->getWorldDC(), _player.x, _player.y, _player.bodyAni);	// 몸
	_player.headImage->aniRender(CAMERAMANAGER->getWorldDC(), _player.x, _player.y, _player.headAni);	// 얼굴 
}

void player::effectRender()
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		(*_viEffect)->render(CAMERAMANAGER->getWorldDC());
	}
	for (int i = 0; i < _vInven.size(); i++)
	{
		if (_vInven[i]->armor != A_NONE)
		{
			IMAGEMANAGER->findImage("armorTiles")->frameRender(CAMERAMANAGER->getWorldDC(), i * 100, WINSIZEY / 2, _vInven[i]->frameX, _vInven[i]->frameY);
		}
		if (_vInven[i]->weapon != WP_NONE)
		{
			IMAGEMANAGER->findImage("weaponTiles")->frameRender(CAMERAMANAGER->getWorldDC(), i * 100, WINSIZEY / 2, _vInven[i]->frameX, _vInven[i]->frameY);
		}
		if (_vInven[i]->stuff != ST_NONE)
		{
			IMAGEMANAGER->findImage("stuffTiles")->frameRender(CAMERAMANAGER->getWorldDC(), i * 100, WINSIZEY / 2, _vInven[i]->frameX, _vInven[i]->frameY);
		}
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

	// 만약 월드 시간이 도달하면 
	if (_time + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		// 위치를 고정시키고 MOVE BOOL값을 false로
		_player.x = _player.idx * _distance + (_distance / 2);
		_player.y = _player.idy * _distance + (_distance / 3);

		_isMoving = false;	    // 선형 보간 
		_isKeyDown = false;
		//_isKeyPress = false;  // key 입력 초기화 
	}
}

void player::playerEffect_Miss()
{
	alphaImageEffect* effect;
	effect = new alphaImageEffect;
	effect->init("player_effect_missed", CAMERAMANAGER->get_CameraX() + BEATMANAGER->getHeartMiddle() - 30, CAMERAMANAGER->get_CameraY() + (WINSIZEY - 200), 10, SLOW);
	_vEffect.push_back(effect);
}

void player::playerEffect_Shovel(tagTile* tile)
{
	alphaImageEffect* effect;
	effect = new alphaImageEffect;
	effect->init("shovel_basic", tile->rc.left, tile->rc.top - 30, 10, TIMESLOW);
	_vEffect.push_back(effect);
	if (tile->wall == W_SHOP_WALL || tile->wall == W_END_WALL || tile->wall == W_BOSS_WALL) return;
	CAMERAMANAGER->Camera_WorldDC_Shake(); // 문제는 예외처리 때문에 카메라 0,0에서는 작동 안함 
}

// 타일 위치
void player::playerEffect_Attack(const char* imageName, tagTile* tile, int frameY)
{
	alphaImageEffect* effect;
	effect = new alphaImageEffect;
	effect->init(imageName, tile->rc.left, tile->rc.top, 0, frameY, FRAMEIMAGE);
	_vEffect.push_back(effect);
}
// 좌표값 x,y의 위치
void player::playerEffect_Attack(const char* imageName, float x, float y, int frameY)
{
	alphaImageEffect* effect;
	effect = new alphaImageEffect;
	effect->init(imageName, x, y, 0, frameY, FRAMEIMAGE);
	_vEffect.push_back(effect);
}

// idx, idy의 위치
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
			cout << "이건 체력 키 " << endl;
		}
		else if (KEYMANAGER->isOncekeytwoDown(VK_LEFT, VK_DOWN))
		{
			_isKeyDown = true;
			cout << "이건 폭탄 키 " << endl;
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
	_isKeyPress = true;				// 인터벌 사이에 누름 
	bool action = false;			// 액션을 취했는지 안했는지 판단할 예정 

	// 상하좌우의 타일정보
	for (_miPlayerTile = _mPlayerTile.begin(); _miPlayerTile != _mPlayerTile.end(); ++_miPlayerTile)
	{
		//UP타일
		if (_miPlayerTile->first  == _player.direction)
		{
			//타일의 종류를 판단
			switch (_miPlayerTile->second->type)
			{
			case TYPE_WALL:
				wallCheck();
				action = true;
				break;
			case TYPE_TRAP:
				trapCheck();
				action = true;
				break;
			case TYPE_ITEM_ARMOR:
			case TYPE_ITEM_WEAPON:
			case TYPE_ITEM_STUFF:
				itempCheck();
				StateMove();
				action = true;
				break;
			default:
				break;
			}
			break;
		}
	}
	if (action) return;
	// ENEMY 타일 정보 ( 작성 예정 )
	for (_miPlayerEnemyTile = _mPlayerEnemyTile.begin(); _miPlayerEnemyTile != _mPlayerEnemyTile.end(); ++_miPlayerEnemyTile)
	{
		if (_player.weapon == PLAYERWAEPON_NONE)
		{
			action = true;
			break;
		}
		// 1. 이펙트와 몬스터 데미지다는것만 하기
		// 2. 타일 지우는거 확인하기 
		if (_miPlayerEnemyTile->first == _player.direction)
		{
			switch (_player.weapon)
			{
			case PLAYERWAEPON_DAGGER:
				//_miPlayerEnemyTile->second->
				break;
			case PLAYERWAEPON_LONGSWORD:
				break;
			case PLAYERWAEPON_RAPIER:
				break;
			case PLAYERWAEPON_SPEAR:
				break;
			case PLAYERWAEPON_BROADSWORD:
				break;
			default:
				break;
			}
		}
	
	
		//up
		//else if (_player.weapon != PLAYERWAEPON_NONE) // 무기가 있는지 없는지 판단
			//{
			//	// 몬스터 타일 돌려야 함 
			//	switch (_player.weapon)
			//	{
			//	case PLAYERWAEPON_DAGGER:
			//		playerEffect_Attack("swipe_dagger", _miPlayerTile->second, 0);
			//		break;
			//	case PLAYERWAEPON_LONGSWORD:
			//		playerEffect_Attack("swipe_longsword상하", (_player.idx) * 52, (_player.idy - 2) * 52, 0);

			//		break;
			//	case PLAYERWAEPON_BROADSWORD:
			//		playerEffect_Attack("swipe_broadsword상하", (_player.idx - 1) * 52, (_player.idy - 1) * 52, 0);

			//		break;
			//	case PLAYERWAEPON_RAPIER:
			//		playerEffect_Attack("swipe_rapier상하", _player.idx * 52, (_player.idy - 2) * 52, 0);
			//		break;
			//	default:
			//		break;
			//	}
			//}
		// down
		//else if (_player.weapon != PLAYERWAEPON_NONE) // 무기가 있는지 없는지 판단
			//{
			//	// 몬스터 타일 돌려야 함 
			//	switch (_player.weapon)
			//	{
			//	case PLAYERWAEPON_DAGGER:
			//		playerEffect_Attack("swipe_dagger", _miPlayerTile->second, 1);
			//		break;
			//	case PLAYERWAEPON_LONGSWORD:
			//		playerEffect_Attack("swipe_longsword상하", _miPlayerTile->second, 1);

			//		break;
			//	case PLAYERWAEPON_BROADSWORD:
			//		playerEffect_Attack("swipe_broadsword상하", (_player.idx - 1) * 52, (_player.idy + 1) * 52, 1);

			//		break;
			//	case PLAYERWAEPON_RAPIER:
			//		playerEffect_Attack("swipe_rapier상하", _player.idx * 52, (_player.idy + 1) * 52, 1);
			//		break;
			//	default:
			//		break;
			//	}

		//left
		//else if (_player.weapon != PLAYERWAEPON_NONE) // 무기가 있는지 없는지 판단
			//{
			//	// 몬스터 타일 돌려야 함 
			//	switch (_player.weapon)
			//	{
			//	case PLAYERWAEPON_DAGGER:
			//		playerEffect_Attack("swipe_dagger", _miPlayerTile->second, 2);
			//		break;
			//	case PLAYERWAEPON_LONGSWORD:
			//		playerEffect_Attack("swipe_longsword좌우", (_player.idx - 2) * 52, _player.idy * 52, 0);
			//		break;
			//	case PLAYERWAEPON_BROADSWORD:
			//		playerEffect_Attack("swipe_broadsword좌우", (_player.idx - 1) * 52, (_player.idy - 1) * 52, 0);

			//		break;
			//	case PLAYERWAEPON_RAPIER:
			//		playerEffect_Attack("swipe_rapier좌우", (_player.idx - 2) * 52, _player.idy * 52, 0);
			//		break;
			//	default:
			//		break;
			//	}
			//}
			//else
			//{
			//	StateMove();
			//}
		//right
			//else if (_player.weapon != PLAYERWAEPON_NONE) // 무기가 있는지 없는지 판단
			//{
			//	// 몬스터 타일 돌려야 함 
			//	switch (_player.weapon)
			//	{
			//	case PLAYERWAEPON_DAGGER:
			//		playerEffect_Attack("swipe_dagger", _miPlayerTile->second, 3);
			//		break;
			//	case PLAYERWAEPON_LONGSWORD:
			//		playerEffect_Attack("swipe_longsword좌우", _miPlayerTile->second, 1);

			//		break;
			//	case PLAYERWAEPON_BROADSWORD:
			//		playerEffect_Attack("swipe_broadsword좌우", (_player.idx + 1) * 52, (_player.idy - 1) * 52, 1);

			//		break;
			//	case PLAYERWAEPON_RAPIER:
			//		playerEffect_Attack("swipe_rapier좌우", (_player.idx + 1) * 52, _player.idy * 52, 1);
			//		break;
			//	default:
			//		break;
			//	}
			//}
			//else
			//{
			//	StateMove();
			//}
			//break;
	}

	if (!action) StateMove();
}

void player::wallCheck()
{
	// 타입 및 설정해야함 
	switch (_miPlayerTile->second->wall)
	{
	case W_WALL:
	case W_WALL2:
		playerEffect_Shovel(_miPlayerTile->second);
		_miPlayerTile->second->type = TYPE_TERRAIN;
		_miPlayerTile->second->wall = W_NONE;
		_miPlayerTile->second->terrain = TR_BASIC_STAGE_TILE;
		_miPlayerTile->second->terrainFrameX = 1;
		_miPlayerTile->second->terrainFrameY = 1;
		break;
	case W_ITEM_WALL:
		playerEffect_Shovel(_miPlayerTile->second);
		_miPlayerTile->second->type = TYPE_TERRAIN;
		_miPlayerTile->second->wall = W_NONE;
		_miPlayerTile->second->terrain = TR_NONE;
		_miPlayerTile->second->terrainFrameX = 1;
		_miPlayerTile->second->terrainFrameY = 1;
		if (RND->getInt(10) % 2 == 0)
		{
			_miPlayerTile->second->type = TYPE_ITEM_ARMOR;
			_miPlayerTile->second->armorFrameX = RND->getInt(4);
			_miPlayerTile->second->armorFrameY = 1;
		}
		else if (RND->getInt(10) % 2 == 1)
		{
			_miPlayerTile->second->type = TYPE_ITEM_WEAPON;
			_miPlayerTile->second->weaponFrameX = RND->getInt(4);
			_miPlayerTile->second->weaponFrameY = 0;
		}
		break;
	case  W_END_WALL:
	case  W_BOSS_WALL:
	case  W_SHOP_WALL:
		playerEffect_Shovel(_miPlayerTile->second);
		break;
	case W_DOOR:
		_miPlayerTile->second->type = TYPE_TERRAIN;
		_miPlayerTile->second->wall = W_NONE;
		_miPlayerTile->second->terrain = TR_BASIC_STAGE_TILE;
		_miPlayerTile->second->terrainFrameX = 1;
		_miPlayerTile->second->terrainFrameY = 1;
		break;
	default:
		_miPlayerTile->second->type = TYPE_TERRAIN;
		_miPlayerTile->second->wall = W_NONE;
		_miPlayerTile->second->terrain = TR_BASIC_STAGE_TILE;
		_miPlayerTile->second->terrainFrameX = 1;
		_miPlayerTile->second->terrainFrameY = 1;
		break;
	}
}

void player::enemyCheck()
{
}

void player::trapCheck()
{
}

void player::itempCheck()
{
	if (_miPlayerTile->second->type == TYPE_ITEM_ARMOR)
	{
		switch (_miPlayerTile->second->armor)
		{
		case A_HELMET:  // 구현해야함 
			break;
		case A_ARMOR_1:
			bodyLeft = { 15,14,13,12 };
			bodyRight = { 8,9,10,11 };
			KEYANIMANAGER->findAnimation("bodyLeft")->setPlayFrame(&bodyLeft, 4, true);
			KEYANIMANAGER->findAnimation("bodyRight")->setPlayFrame(&bodyRight, 4, true);
			makeItem(WP_NONE, A_ARMOR_1, ST_NONE, 0, 1, 0, 0, 1, 0);
			_player.guard = 1;
			break;
		case A_ARMOR_2:
			bodyLeft = { 23,22,21,20 };
			bodyRight = { 16,17,18,19 };
			KEYANIMANAGER->findAnimation("bodyLeft")->setPlayFrame(&bodyLeft, 4, true);
			KEYANIMANAGER->findAnimation("bodyRight")->setPlayFrame(&bodyRight, 4, true);
			makeItem(WP_NONE, A_ARMOR_2, ST_NONE, 1, 1, 0, 0, 2, 0);
			_player.guard = 2;
			break;
		case A_ARMOR_3:
			bodyLeft = { 31,30,29,28 };
			bodyRight = { 24,25,26,27 };
			KEYANIMANAGER->findAnimation("bodyLeft")->setPlayFrame(&bodyLeft, 4, true);
			KEYANIMANAGER->findAnimation("bodyRight")->setPlayFrame(&bodyRight, 4, true);
			makeItem(WP_NONE, A_ARMOR_3, ST_NONE, 2, 1, 0, 0, 3, 0);
			_player.guard = 3;
			break;
		case A_ARMOR_4:
			bodyLeft = { 39,38,37,36 };
			bodyRight = { 32,33,34,35 };
			KEYANIMANAGER->findAnimation("bodyLeft")->setPlayFrame(&bodyLeft, 4, true);
			KEYANIMANAGER->findAnimation("bodyRight")->setPlayFrame(&bodyRight, 4, true);
			makeItem(WP_NONE, A_ARMOR_4, ST_NONE, 3, 1, 0, 0, 4, 0);
			_player.guard = 4;
			break;
		case A_BOOTS:
			break;
		case A_RING:
			break;
		case A_TORCH_1:
			makeItem(WP_NONE, A_TORCH_1, ST_NONE, 0, 4, 1, 0, 0, 0);
			_player.sight = 6;
			break;
		case A_TORCH_2:
			makeItem(WP_NONE, A_TORCH_2, ST_NONE, 1, 4, 2, 0, 0, 0);
			_player.sight = 7;
			break;
		case A_TORCH_3:
			makeItem(WP_NONE, A_TORCH_3, ST_NONE, 2, 4, 3, 0, 0, 0);
			_player.sight = 8;
			break;
		case A_NONE:
			return;
			break;
		}
		if (_player.isArmor && ((_miPlayerTile->second->armor == A_ARMOR_1) 
			|| (_miPlayerTile->second->armor == A_ARMOR_2) 
			|| (_miPlayerTile->second->armor == A_ARMOR_3)
			|| (_miPlayerTile->second->armor == A_ARMOR_4)))
		{
			_miPlayerTile->second->type = TYPE_ITEM_ARMOR;
			_miPlayerTile->second->armor = currentArmor->armor;
			_miPlayerTile->second->weapon = currentArmor->weapon;
			_miPlayerTile->second->stuff = currentArmor->stuff;
			_miPlayerTile->second->armorFrameX = currentArmor->frameX;	  // 땅의 속성을 
			_miPlayerTile->second->armorFrameY = currentArmor->frameY;
		}
		else
		{
			_miPlayerTile->second->type = TYPE_TERRAIN;
			_miPlayerTile->second->armor = A_NONE;
			_miPlayerTile->second->weapon = WP_NONE;
			_miPlayerTile->second->stuff = ST_NONE;
			_miPlayerTile->second->terrain = TR_BASIC_STAGE_TILE;
			_miPlayerTile->second->terrainFrameX = 1;	  // 땅의 속성을 
			_miPlayerTile->second->terrainFrameY = 1;
		}
	}
	if (_miPlayerTile->second->type == TYPE_ITEM_WEAPON)
	{
		//makeItem(WEAPON weapon, ARMOR armor,int framex, int framey ,int sight,int damege, float guard, float hp);
		switch (_miPlayerTile->second->weapon)
		{
		case WP_DAGGER_1:
			makeItem(WP_DAGGER_1, A_NONE, ST_NONE, 0, 0, 0, 1, 0, 0);
			_player.weapon = PLAYERWAEPON_DAGGER;
			break;
		case WP_DAGGER_2:
			makeItem(WP_DAGGER_2, A_NONE, ST_NONE, 1, 0, 0, 1, 0, 0);
			_player.weapon = PLAYERWAEPON_DAGGER;
			break;
		case WP_RAPIER:
			makeItem(WP_RAPIER, A_NONE, ST_NONE, 2, 0, 0, 1, 0, 0);
			_player.weapon = PLAYERWAEPON_RAPIER;
			break;
		case WP_BROAD_SWORD:
			makeItem(WP_BROAD_SWORD, A_NONE, ST_NONE, 2, 2, 0, 1, 0, 0);
			_player.weapon = PLAYERWAEPON_BROADSWORD;
			break;
		case WP_LONG_SWORD:
			makeItem(WP_LONG_SWORD, A_NONE, ST_NONE, 3, 0, 0, 1, 0, 0);
			_player.weapon = PLAYERWAEPON_LONGSWORD;
			break;
		case WP_BOMB: // 구현하지 못함 
			break;
		case WP_RIFLE:
			break;
		case WP_SHOTGUN:
			break;
		case WP_SPEAR:
			break;
		case WP_MACE:
			break;
		case WP_WHIP:
			break;
		case WP_NINETAILS_WHIP:
			break;
		case WP_BOW:
			break;
		case WP_CROSS_BOW:
			break;
		case WP_NONE:
			return;
			break;
		}
		if (_player.isWeapon)
		{
			_miPlayerTile->second->type = TYPE_ITEM_WEAPON;
			_miPlayerTile->second->armor = currentWeapon->armor;
			_miPlayerTile->second->weapon = currentWeapon->weapon;
			_miPlayerTile->second->stuff = currentWeapon->stuff;
			_miPlayerTile->second->weaponFrameX = currentWeapon->frameX;	  // 땅의 속성을 
			_miPlayerTile->second->weaponFrameY = currentWeapon->frameY;
		}
		else
		{
			_miPlayerTile->second->type = TYPE_TERRAIN;
			_miPlayerTile->second->armor = A_NONE;
			_miPlayerTile->second->weapon = WP_NONE;
			_miPlayerTile->second->stuff = ST_NONE;
			_miPlayerTile->second->terrain = TR_BASIC_STAGE_TILE;
			_miPlayerTile->second->terrainFrameX = 1;	  // 땅의 속성을 
			_miPlayerTile->second->terrainFrameY = 1;
		}
	}
	if (_miPlayerTile->second->type == TYPE_ITEM_STUFF)
	{
		switch (_miPlayerTile->second->stuff)
		{
		case ST_DIAMOND:
			_player.damage++;
			break;
		case ST_ONE_COIN:
			// 코인 
			break;
		case ST_ONE_HALF_COIN:
			// 코인 증가량 
			break;
		case ST_COINS:
			_player.coin += 5;
			break;
		case ST_MORE_COINS:
			_player.coin += 15;
			break;
		case ST_APPLE:
			makeItem(WP_NONE, A_NONE, ST_APPLE, 0, 3, 0, 0, 0, 1);
			break;
		case ST_CHEESE:
			makeItem(WP_NONE, A_NONE, ST_CHEESE, 1, 3, 0, 0, 0, 2);
			break;
		case ST_MEAT:
			makeItem(WP_NONE, A_NONE, ST_CHEESE, 2, 3, 0, 0, 0, 3);
			break;
		case ST_NONE:
			return;
			break;
		}
		_miPlayerTile->second->type = TYPE_TERRAIN;
		_miPlayerTile->second->armor = A_NONE;
		_miPlayerTile->second->weapon = WP_NONE;
		_miPlayerTile->second->stuff = ST_NONE;
		_miPlayerTile->second->terrain = TR_BASIC_STAGE_TILE;
		_miPlayerTile->second->terrainFrameX = 1;	  // 땅의 속성을 
		_miPlayerTile->second->terrainFrameY = 1;
	}
}

void player::makeItem(WEAPON weapon, ARMOR armor, STUFF stuff, int framex, int framey, int sight, int damege, float guard, float hp)
{
	if (armor == A_ARMOR_1
		|| armor == A_ARMOR_2
		|| armor == A_ARMOR_3
		|| armor == A_ARMOR_4)
	{
		for (int i = 0; i < _vInven.size(); ++i)
		{
			if (_vInven[i]->armor == A_ARMOR_1
				|| _vInven[i]->armor == A_ARMOR_2
				|| _vInven[i]->armor == A_ARMOR_3
				|| _vInven[i]->armor == A_ARMOR_4)
			{
				currentArmor = _vInven[i];
				_player.isArmor = true;
				this->itemRemove(i);
				break;
			}
		}
	}
	else if (weapon != W_NONE && stuff == ST_NONE && armor == A_NONE)
	{
		for (int i = 0; i < _vInven.size(); ++i)
		{
			if (_vInven[i]->weapon == WP_DAGGER_1
				|| _vInven[i]->weapon == WP_DAGGER_2
				|| _vInven[i]->weapon == WP_RAPIER
				|| _vInven[i]->weapon == WP_BROAD_SWORD
				|| _vInven[i]->weapon == WP_LONG_SWORD)
			{
				currentWeapon = _vInven[i];
				_player.isWeapon = true;
				this->itemRemove(i);
				break;
			}
		}
	}


	tagItem* item;
	item = new tagItem;
	ZeroMemory(item, sizeof(item));
	item->weapon = weapon;
	item->armor = armor;
	item->stuff = stuff;
	item->frameX = framex;
	item->frameY = framey;
	item->sight = sight;
	item->damege = damege;
	item->guard = guard;
	item->hp = hp;
	_vInven.push_back(item);
}

void player::StateMove()
{
	switch (_player.direction)
	{
	case PLAYERDIRECTION_UP:
		_player.idy--;			// 좌표Y값--
		//선형보간
		_angle = getAngle(_player.x, _player.y, _player.x, _player.y - _distance);  // 방향 
		_worldTimeCount = TIMEMANAGER->getWorldTime();								// 월드 시간 
		_isMoving = true;															// MOVE

		_jump->jumping(&_player.x, &_player.y, 2, 1.5, true); //점프 
		break;
	case PLAYERDIRECTION_DOWN:
		_player.idy++;	// 좌표Y값++
		//선형보간
		_angle = getAngle(_player.x, _player.y, _player.x, _player.y + _distance);  // 방향 
		_worldTimeCount = TIMEMANAGER->getWorldTime();								// 월드 시간 
		_isMoving = true;															// MOVE

		_jump->jumping(&_player.x, &_player.y, 8, 1.5);	//점프 
		break;
	case PLAYERDIRECTION_RIGHT:
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
		break;
	case PLAYERDIRECTION_LEFT:
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
		break;
	default:
		break;
	}
}


