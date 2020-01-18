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
	boss::isCasting = false;											 // 데스메탈이 마법을 캐스팅 중이라면 이 값이 true로 바뀐다.
	boss::isClosePlayer = false;										 // 데스메탈이 플레이어 근처에 있다면 이 값이 true로 바뀐다.

	return S_OK;
}

void deathMetal::release()
{
}

void deathMetal::update()
{
	Info_Update();												 // 데스메탈의 인덱스 정보가 바뀌면 자동으로 중점, 렉트를 갱신해준다.
	deathMetal_Animation_Test();								 // 데스메탈의 애니메이션 테스트 함수
	deathMetal_ChangeAnimation();								 // 데스메탈의 애니메이션 체인지 함수
	deathMetal_ChangePhase();									 // 데스메탈의 페이즈 체인지 함수
}

void deathMetal::render()
{

	boss::render();
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

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD1))
	{
		boss::direction = BD_LEFT;
		boss::isMove = true;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD5))
	{
		boss::direction = BD_UP;
		boss::isMove = true;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD3))
	{
		boss::direction = BD_RIGHT;
		boss::isMove = true;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD2))
	{
		boss::direction = BD_DOWN;
		boss::isMove = true;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD4))
	{
		boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Attack");
		boss::animation->start();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD6))
	{
		boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Idle");
		boss::animation->start();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD7))
	{
		boss::setBoss_HP_Hit();	// 보스의 체력을 1 감소 시킨다.
		boss::isMove = true;
	}
}

void deathMetal::deathMetal_ChangeAnimation()
{
	// 데스메탈이 바라보는 방향에 따라 애니메이션을 바꿔준다.
	if (boss::isMove)
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
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Idel");
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
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SIdel");
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
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Idel");
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
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SIdel");
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
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Idel");
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
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SIdel");
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
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Idel");
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
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SIdel");
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
			break;
		}

		boss::isMove = false;	// 보스의 움직임에 따라 애니메이션을 바꿔주었다면, 다음 움직임까지 false를 주어서 다시 바뀌지 않게 한다.
	}
}

void deathMetal::deathMetal_ChangePhase()
{
	if (boss::hp > 7) boss::phase = BP_PHASE_1;
	else if (boss::hp > 5) boss::phase = BP_PHASE_2;
	else if (boss::hp > 3) boss::phase = BP_PHASE_3;
	else if (boss::hp > 0) boss::phase = BP_PHASE_4; 

	// 데스메탈 페이즈
	// HP 9 ~ 7 : 방패를 들고 세 박자마다 이동하면서 플레이어에게 다가간다.
	//            일반 무기로 방패를 든 상태의 데스 메탈을 정면에서 공격하면 뒤로 튕기게만 할 뿐이며, 동시에 박쥐가 소환된다.
	//            반드시 옆이나 뒤를 공격해야 한다. 다만 관통 효과가 있는 무기를 사용하면 정면에서도 공격할 수 있다.
	// HP 6 ~ 5 : 방패를 집어 던지고 두 박자마다 움직이면서 플레이어와 거리를 둔다. 이따금 "Come to me!"라고 외치며 손을 들어올리는데,
	//            직후 네 박자 동안 공격받지 않으면 1~3 마리의 해골을 소환한다. 이때부터는 공격받으면 반대편으로 순간 이동한다.
	// HP 4 ~ 3 : "End of the line!"을 외치며 노란 해골을 소환한다.
	// HP 2 ~ 1 : 한 박자마다 이동하기 시작하면서 왼쪽이나 오른쪽 벽에 붙는다. 그 후 세로축으로 플레이어를 따라가면서 네 박자마다
	//            "Bathe in fire!"을 외치며 양직선으로 파이어볼을 발사한다.
}
