#include "stdafx.h"
#include "deathMetal.h"

HRESULT deathMetal::init(string bossName, int idx, int idy, int TILE_SIZEX, int TILE_SIZEY)
{
	boss::hp = 9;														 // 데스메탈의 기본 체력 초기화
	boss::shield = 2;													 // 데스메탈의 기본 실드 초기화
	boss::attack = 1.5;													 // 데스메탈의 기본 공격력 초기화
	boss::magicAttack = 2;												 // 데스메탈의 기본 마법공격력 초기화
	boss::init(bossName, idx, idy, TILE_SIZEX, TILE_SIZEY);				 // 데스메탈의 좌표 변수 초기화

	deathMetal_Animation_Setting();										 // 데스메탈의 애니메이션 추가 함수

	boss::direction = BD_DOWN;											 // 데스메탈은 처음에 아래를 바라보고 있다.
	boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SDown");  // 데스메탈의 시작 애니메이션은 쉐도우다운
	boss::animation->start();											 // 애니메이션을 시작한다.
	boss::isMove = false;												 // 데스메탈이 움직이면 이 값이 true로 바뀐다.
	boss::isChangeAni = false;											 // 데스메탈이 움직이면 이 값이 true로 바뀐다.
	boss::isCasting = false;											 // 데스메탈이 마법을 캐스팅 중이라면 이 값이 true로 바뀐다.
	boss::isClosePlayer = false;										 // 데스메탈이 플레이어 근처에 있다면 이 값이 true로 바뀐다.

	clearThrowShield();													 // 데스메탈의 실드 정보를 초기화 해준다.

	return S_OK;
}

void deathMetal::release()
{
}

void deathMetal::update()
{
	Info_Update();												 // 데스메탈의 인덱스 정보가 바뀌면 자동으로 중점, 렉트를 갱신해준다.
	deathMetal_Animation_Test();								 // 데스메탈의 애니메이션 테스트 함수
	deathMetal_ChangePhase();									 // 데스메탈의 페이즈 체인지 함수									
	deathMetal_ChangeAnimation();								 // 데스메탈의 애니메이션 체인지 함수
	boss_Move();												 // 데스메탈의 이동 연산 함수
}

void deathMetal::render()
{
	boss::render();

	if(_throwShield.isOut) boss::render(_throwShield);	 // 페이즈 1이 끝나면 실드의 정보가 갱신되고, 그때부터 보이기 시작한다.
}

void deathMetal::clearThrowShield()
{
	// 실드 이미지를 넣는다.
	_throwShield.image = IMAGEMANAGER->findImage("deathMetal_Shield");
	_throwShield.center.x = 0;
	_throwShield.center.y = 0;
	_throwShield.angle = 0;
	_throwShield.speed = 0;
	_throwShield.isShieldUpdate = false;
	_throwShield.isOut = false;
	boss::isThrowShield = false;
}

void deathMetal::deathMetal_Animation_Setting()
{

	// 실드 있을때 이용하는 애니메이션
	int Left[] = {2, 3};
	KEYANIMANAGER->addArrayFrameAnimation("deathMetal_Left", "Death_Metal", Left, 2, 10, true);

	int ShadowLeft[] = {14, 15};
	KEYANIMANAGER->addArrayFrameAnimation("deathMetal_SLeft", "Death_Metal", ShadowLeft, 2, 10, true);

	int Up[] = {6, 7};
	KEYANIMANAGER->addArrayFrameAnimation("deathMetal_Up", "Death_Metal", Up, 2, 10, true);

	int ShadowUp[] = {18, 19};
	KEYANIMANAGER->addArrayFrameAnimation("deathMetal_SUp", "Death_Metal", ShadowUp, 2, 10, true);

	int Right[] = {0, 1};
	KEYANIMANAGER->addArrayFrameAnimation("deathMetal_Right", "Death_Metal", Right, 2, 10, true);

	int ShadowRight[] = {12, 13};
	KEYANIMANAGER->addArrayFrameAnimation("deathMetal_SRight", "Death_Metal", ShadowRight, 2, 10, true);

	int Down[] = {4, 5};
	KEYANIMANAGER->addArrayFrameAnimation("deathMetal_Down", "Death_Metal", Down, 2, 10, true);

	int ShadowDown[] = {16, 17};
	KEYANIMANAGER->addArrayFrameAnimation("deathMetal_SDown", "Death_Metal", ShadowDown, 2, 10, true);

	// 실드 없을때 이용하는 애니메이션
	int Attack[] = {8, 9};
	KEYANIMANAGER->addArrayFrameAnimation("deathMetal_Attack", "Death_Metal", Attack, 2, 10, true);

	int ShadowAttack[] = {20, 21};
	KEYANIMANAGER->addArrayFrameAnimation("deathMetal_SAttack", "Death_Metal", ShadowAttack, 2, 10, true);

	int Idle[] = {10, 11};
	KEYANIMANAGER->addArrayFrameAnimation("deathMetal_Idle", "Death_Metal", Idle, 2, 10, true);

	int ShadowIdle[] = {22, 23};
	KEYANIMANAGER->addArrayFrameAnimation("deathMetal_SIdle", "Death_Metal", ShadowIdle, 2, 10, true);
}

void deathMetal::deathMetal_Animation_Test()
{
	// 애니메이션 테스트 함수

	// 데스메탈의 방향을 바꾸고, 애니메이션을 바꾸기 위해 true값으로 수정
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD1))
	{
		boss::direction = BD_LEFT;
		worldTime = TIMEMANAGER->getWorldTime();	// 월드 타임을 저장한다.
													// 점프 함수 만들어야함

		//boss::index.x--; // 이동이 모두 끝났으면 인덱스를 옴겨준다?
		boss::isChangeAni = true;	// 보스가 움직였다면 애니메이션을 바꿔주어야한다.
		boss::isMove = true;
	}

	// 데스메탈의 방향을 바꾸고, 애니메이션을 바꾸기 위해 true값으로 수정
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD5))
	{
		boss::direction = BD_UP;
		worldTime = TIMEMANAGER->getWorldTime();	// 월드 타임을 저장한다.
													// 점프 함수 만들어야함

		//boss::index.y--;
		boss::isChangeAni = true;	// 보스가 움직였다면 애니메이션을 바꿔주어야한다.
		boss::isMove = true;
	}

	// 데스메탈의 방향을 바꾸고, 애니메이션을 바꾸기 위해 true값으로 수정
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD3))
	{
		boss::direction = BD_RIGHT;
		worldTime = TIMEMANAGER->getWorldTime();	// 월드 타임을 저장한다.
													// 점프 함수 만들어야함

		//boss::index.x++;
		boss::isChangeAni = true;	// 보스가 움직였다면 애니메이션을 바꿔주어야한다.
		boss::isMove = true;
	}

	// 데스메탈의 방향을 바꾸고, 애니메이션을 바꾸기 위해 true값으로 수정
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD2))
	{
		boss::direction = BD_DOWN;
		worldTime = TIMEMANAGER->getWorldTime();	// 월드 타임을 저장한다.
													// 점프 함수 만들어야함

		//boss::index.y++;
		boss::isChangeAni = true;	// 보스가 움직였다면 애니메이션을 바꿔주어야한다.
		boss::isMove = true;
	}

	// 데스메탈의 애니메이션을 공격 모션으로 바꾸고 실행
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD4))
	{
		boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Attack");
		boss::animation->start();
	}

	// 데스메탈의 애니메이션을 대기 모션으로 바꾸고 실행
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD6))
	{
		boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Idle");
		boss::animation->start();
	}

	// 데스메탈의 체력을 감소시킨다.
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD7))
	{
		boss::setBoss_HP_Hit();	// 보스의 체력을 1 감소 시킨다.
		boss::isChangeAni = true;
	}

	// 플레이어가 근처에 있으면 true 없으면 false (테스트용)
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD8))
	{
		boss::isClosePlayer = true;	// 플레이어가 가까이 있다면 true
		boss::isChangeAni = true;
	}

	// 데스메탈 실드 테스트용
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD9))
	{
		boss::hp = 8;
		deathMetal_ShieldPosUpdate();
		boss::isThrowShield = false;
		_throwShield.isShieldUpdate = false;
		_throwShield.isOut = false;
		boss::isChangeAni = true;
	}
}

void deathMetal::deathMetal_ChangeAnimation()
{
	// 데스메탈이 바라보는 방향에 따라 애니메이션을 바꿔준다.
	if (boss::isChangeAni)	// 보스가 움직였다면 애니메이션을 바꿔주어야한다.
	{
		switch (boss::direction)
		{
		case BD_LEFT:
			// 데스메탈은 1페이즈에선 방패를 들고 있는 애니메이션이다.
			if (boss::phase == BP_PHASE_1)
			{
				// 플레이어와의 거리가 가까울 경우 데스메탈이 보인다.
				if (boss::isClosePlayer)
				{
					boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Left");
					boss::animation->start();
				}

				// 플레이어와의 거리가 멀 경우 데스메탈은 쉐도우 상태 이미지이다.
				else
				{
					boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SLeft");
					boss::animation->start();
				}
			}

			// 데스메탈은 2페이즈부터는 공격모션, 대기모션 2개로만 움직인다.
			else
			{
				// 플레이어와의 거리가 가까울 경우 데스메탈이 보인다.
				if (boss::isClosePlayer)
				{
					// 마법 캐스팅 중이 아닐때는 대기모션
					if (!boss::isCasting)
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Idle");
						boss::animation->start();
					}

					// 마법 캐스팅 중일때는 공격 모션
					else
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Attack");
						boss::animation->start();
					}
				}

				// 플레이어와의 거리가 멀 경우 데스메탈은 쉐도우 상태 이미지이다.
				else
				{
					// 마법 캐스팅 중이 아닐때는 대기모션
					if (!boss::isCasting)
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SIdle");
						boss::animation->start();
					}

					// 마법 캐스팅 중일때는 공격 모션
					else
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SAttack");
						boss::animation->start();
					}
				}
			}

			// 데스메탈이 해당 방향을 보고 있을때 각도를 초기화해준다.
			boss::angle = PI;
			break;

		case BD_UP:
			// 데스메탈은 1페이즈에선 방패를 들고 있는 애니메이션이다.
			if (boss::phase == BP_PHASE_1)
			{
				// 플레이어와의 거리가 가까울 경우 데스메탈이 보인다.
				if (boss::isClosePlayer)
				{
					boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Up");
					boss::animation->start();
				}

				// 플레이어와의 거리가 멀 경우 데스메탈은 쉐도우 상태 이미지이다.
				else
				{
					boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SUp");
					boss::animation->start();
				}
			}

			// 데스메탈은 2페이즈부터는 공격모션, 대기모션 2개로만 움직인다.
			else
			{
				// 플레이어와의 거리가 가까울 경우 데스메탈이 보인다.
				if (boss::isClosePlayer)
				{
					// 마법 캐스팅 중이 아닐때는 대기모션
					if (!boss::isCasting)
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Idle");
						boss::animation->start();
					}

					// 마법 캐스팅 중일때는 공격 모션
					else
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Attack");
						boss::animation->start();
					}
				}

				// 플레이어와의 거리가 멀 경우 데스메탈은 쉐도우 상태 이미지이다.
				else
				{
					// 마법 캐스팅 중이 아닐때는 대기모션
					if (!boss::isCasting)
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SIdle");
						boss::animation->start();
					}

					// 마법 캐스팅 중일때는 공격 모션
					else
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SAttack");
						boss::animation->start();
					}
				}
			}

			// 데스메탈이 해당 방향을 보고 있을때 각도를 초기화해준다.
			boss::angle = PI / 180 * 90;

			break;

		case BD_RIGHT:
			// 데스메탈은 1페이즈에선 방패를 들고 있는 애니메이션이다.
			if (boss::phase == BP_PHASE_1)
			{
				// 플레이어와의 거리가 가까울 경우 데스메탈이 보인다.
				if (boss::isClosePlayer)
				{
					boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Right");
					boss::animation->start();
				}

				// 플레이어와의 거리가 멀 경우 데스메탈은 쉐도우 상태 이미지이다.
				else
				{
					boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SRight");
					boss::animation->start();
				}
			}

			// 데스메탈은 2페이즈부터는 공격모션, 대기모션 2개로만 움직인다.
			else
			{
				// 플레이어와의 거리가 가까울 경우 데스메탈이 보인다.
				if (boss::isClosePlayer)
				{
					// 마법 캐스팅 중이 아닐때는 대기모션
					if (!boss::isCasting)
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Idle");
						boss::animation->start();
					}

					// 마법 캐스팅 중일때는 공격 모션
					else
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Attack");
						boss::animation->start();
					}
				}

				// 플레이어와의 거리가 멀 경우 데스메탈은 쉐도우 상태 이미지이다.
				else
				{
					// 마법 캐스팅 중이 아닐때는 대기모션
					if (!boss::isCasting)
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SIdle");
						boss::animation->start();
					}

					// 마법 캐스팅 중일때는 공격 모션
					else
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SAttack");
						boss::animation->start();
					}
				}
			}

			// 데스메탈이 해당 방향을 보고 있을때 각도를 초기화해준다.
			boss::angle = 0;

			break;

		case BD_DOWN:
			// 데스메탈은 1페이즈에선 방패를 들고 있는 애니메이션이다.
			if (boss::phase == BP_PHASE_1)
			{
				// 플레이어와의 거리가 가까울 경우 데스메탈이 보인다.
				if (boss::isClosePlayer)
				{
					boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Down");
					boss::animation->start();
				}

				// 플레이어와의 거리가 멀 경우 데스메탈은 쉐도우 상태 이미지이다.
				else
				{
					boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SDown");
					boss::animation->start();
				}
			}

			// 데스메탈은 2페이즈부터는 공격모션, 대기모션 2개로만 움직인다.
			else
			{
				// 플레이어와의 거리가 가까울 경우 데스메탈이 보인다.
				if (boss::isClosePlayer)
				{
					// 마법 캐스팅 중이 아닐때는 대기모션
					if (!boss::isCasting)
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Idle");
						boss::animation->start();
					}

					// 마법 캐스팅 중일때는 공격 모션
					else
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Attack");
						boss::animation->start();
					}
				}

				// 플레이어와의 거리가 멀 경우 데스메탈은 쉐도우 상태 이미지이다.
				else
				{
					// 마법 캐스팅 중이 아닐때는 대기모션
					if (!boss::isCasting)
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SIdle");
						boss::animation->start();
					}

					// 마법 캐스팅 중일때는 공격 모션
					else
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SAttack");
						boss::animation->start();
					}
				}
			}

			// 데스메탈이 해당 방향을 보고 있을때 각도를 초기화해준다.
			boss::angle = PI / 180 * 270;

			break;
		}
		boss::isChangeAni = false;		// 보스의 움직임에 따라 애니메이션을 바꿔주었다면, 다음 움직임까지 false를 주어서 다시 바뀌지 않게 한다.
	}
}

void deathMetal::deathMetal_ChangePhase()
{
	if (boss::hp > 7)		boss::phase = BP_PHASE_1;
	else if (boss::hp > 5)	boss::phase = BP_PHASE_2;
	else if (boss::hp > 3)	boss::phase = BP_PHASE_3;
	else if (boss::hp > 0)	boss::phase = BP_PHASE_4; 

	// 데스메탈 페이즈
	// HP 9 ~ 7 : 방패를 들고 세 박자마다 이동하면서 플레이어에게 다가간다.
	//            일반 무기로 방패를 든 상태의 데스 메탈을 정면에서 공격하면 뒤로 튕기게만 할 뿐이며, 동시에 박쥐가 소환된다.
	//            반드시 옆이나 뒤를 공격해야 한다. 다만 관통 효과가 있는 무기를 사용하면 정면에서도 공격할 수 있다.
	// HP 6 ~ 5 : 방패를 집어 던지고 두 박자마다 움직이면서 플레이어와 거리를 둔다. 이따금 "Come to me!"라고 외치며 손을 들어올리는데,
	//            직후 네 박자 동안 공격받지 않으면 1~3 마리의 해골을 소환한다. 이때부터는 공격받으면 반대편으로 순간 이동한다.
	// HP 4 ~ 3 : "End of the line!"을 외치며 노란 해골을 소환한다.
	// HP 2 ~ 1 : 한 박자마다 이동하기 시작하면서 왼쪽이나 오른쪽 벽에 붙는다. 그 후 세로축으로 플레이어를 따라가면서 네 박자마다
	//            "Bathe in fire!"을 외치며 양직선으로 파이어볼을 발사한다.

	// 만약 보스 페이즈가 2로 바뀌었고, 실드를 아직 던지지 않았다면 실행한다. (실드 던지는 애니메이션 함수)
	if (boss::phase == BP_PHASE_2 && !boss::isThrowShield)	deathMetal_ThrowShield();


}

void deathMetal::deathMetal_ShieldPosUpdate()
{
	// 렉트를 구한다. (중점x - 실드이미지 가로 / 2, 중점y - 보스이미지 세로 / 2, 실드이미지 가로, 실드이미지 세로)
	_throwShield.rc = RectMake(boss::center.x - _throwShield.image->getWidth() / 2, 
		boss::center.y - boss::image->getFrameHeight() / 2, _throwShield.image->getWidth(), _throwShield.image->getHeight());

	// 렉트를 이용하여 중점을 구한다.
	_throwShield.center.x = (_throwShield.rc.left + _throwShield.rc.right) / 2;
	_throwShield.center.y = (_throwShield.rc.top + _throwShield.rc.bottom) / 2;

	// 실드가 처음 날아갈 각도 (보스가 바라보는 방향에 따라 방패가 날아가는 각도가 다르다.)
	switch (boss::direction)
	{
	case BD_LEFT:
			_throwShield.angle = PI / 180 * 190;
		break;

	case BD_UP:
			_throwShield.angle = PI / 180 * 100;
		break;

	case BD_RIGHT:
			_throwShield.angle = PI / 180 * 40;
		break;

	case BD_DOWN:
			_throwShield.angle = PI / 180 * 330;
		break;
	}
	
	// 보스가 바라보는 방향을 저장해둔다. (이후에 보스가 이동을 할 수 있기 때문에)
	_throwShield.direction = boss::direction;

	// 실드가 날아가는 속도
	_throwShield.speed = 3.0f;

	// 셋팅은 한번만 한다.
	_throwShield.isShieldUpdate = true;		// 모든 좌표 셋팅이 끝났다면 true의 값으로 변경
	_throwShield.isOut = true;				// 셋팅이 끝났다면 방패를 출력해준다.
}

void deathMetal::deathMetal_ThrowShield()
{
	if(!_throwShield.isShieldUpdate) deathMetal_ShieldPosUpdate();		// 데스메탈의 좌표를 이용하여 실드의 위치를 갱신해준다. (갱신 후 ture의 값으로 변경 한다.)

	// 실드는 정해진 속도만큼 저장 된 각도로 날아간다.
	_throwShield.center.x += cosf(_throwShield.angle) * _throwShield.speed;
	_throwShield.center.y += -sinf(_throwShield.angle) * _throwShield.speed;

	// 실드의 각도를 미세하게 바꿔준다. (유턴을 하도록 만들기 위해)
	_throwShield.angle += 0.07f;

	// 실드의 렉트 위치를 갱신해준다.
	_throwShield.rc = RectMake(_throwShield.center.x - _throwShield.image->getWidth() / 2,
		_throwShield.center.y - _throwShield.image->getHeight() / 2, _throwShield.image->getWidth(), _throwShield.image->getHeight());

	// 실드 움직임이 모두 끝나면 isThrowShield의 값이 true가 되고 출력과 연산을 모두 종료한다.
	// 보스의 방향에 따라 실드가 사라지는 각도가 다르기 때문에 다시 한번 스위치문을 돌려준다.
	switch (_throwShield.direction)
	{
	case BD_LEFT:
		if (_throwShield.angle >= PI / 180 * 360)
		{
			boss::isThrowShield = true;					// 실드 연산이 끝났다면 true
			_throwShield.isOut = false;					// 실드 이미지를 더 이상 그리지 않도록 false
		}
		break;

	case BD_UP:
		if (_throwShield.angle >= PI / 180 * 270)
		{
			boss::isThrowShield = true;					// 실드 연산이 끝났다면 true
			_throwShield.isOut = false;					// 실드 이미지를 더 이상 그리지 않도록 false
		}
		break;

	case BD_RIGHT:
		if (_throwShield.angle >= PI / 180 * 210)
		{
			boss::isThrowShield = true;					// 실드 연산이 끝났다면 true
			_throwShield.isOut = false;					// 실드 이미지를 더 이상 그리지 않도록 false
		}
		break;

	case BD_DOWN:
		if (_throwShield.angle >= PI / 180 * 500)
		{
			boss::isThrowShield = true;					// 실드 연산이 끝났다면 true
			_throwShield.isOut = false;					// 실드 이미지를 더 이상 그리지 않도록 false
		}
		break;
	}
}
