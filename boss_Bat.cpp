#include "stdafx.h"
#include "boss_Bat.h"

boss_Bat::boss_Bat()
{
}

boss_Bat::~boss_Bat()
{
}

HRESULT boss_Bat::init()
{
	return S_OK;
}

void boss_Bat::update()
{
	boss_Bat_ChangeAnimation();
}

void boss_Bat::boss_Bat_ChangeAnimation()
{
	// 방향에 변화가 있을때 true의 값을 넣어준다.
	if (slave::_slave.status.direction != slave::_slave.status.save_Direction)
	{
		// 다음 방향이 변화 할때까지 이곳에 들어오지 않는다.
		slave::_slave.status.save_Direction = slave::_slave.status.direction;
		slave::_slave.b_Value.isChangeAni = true;
		slave::_slave.b_Value.change_Ani = true;
	}

	// 플레이어가 근처에 있거나 멀리 갔거나 값이 변경 되었을때 들어온다.
	if (slave::_slave.b_Value.isClosePlayer != slave::_slave.b_Value.save_ClosePlayer)
	{
		// 다음 변화가 있을때까지 들어오지 않는다.
		slave::_slave.b_Value.save_ClosePlayer = slave::_slave.b_Value.isClosePlayer;
		slave::_slave.b_Value.isChangeAni = true;
		slave::_slave.b_Value.change_Ani = true;
	}

	// 데스메탈이 바라보는 방향에 따라 애니메이션을 바꿔준다.
	if (slave::_slave.b_Value.isChangeAni)	// 보스가 움직였다면 애니메이션을 바꿔주어야한다.
	{
		switch (slave::_slave.status.direction)
		{
			case SLAVE_DIRECTION::SD_LEFT:

				// 플레이어와의 거리가 가까울 경우 데스메탈이 보인다.
				if (slave::_slave.b_Value.isClosePlayer)
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("bat_Left");
				}

				// 플레이어와의 거리가 멀 경우 데스메탈은 쉐도우 상태 이미지이다.
				else
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("sBat_Left");
				}

				// 데스메탈이 해당 방향을 보고 있을때 각도를 초기화해준다.
				slave::_slave.operation.angle = PI;
				break;

			case SLAVE_DIRECTION::SD_UP:

				// 플레이어와의 거리가 가까울 경우 데스메탈이 보인다.
				if (slave::_slave.b_Value.isClosePlayer)
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("bat_Left");
				}

				// 플레이어와의 거리가 멀 경우 데스메탈은 쉐도우 상태 이미지이다.
				else
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("sBat_Left");
				}

				// 데스메탈이 해당 방향을 보고 있을때 각도를 초기화해준다.
				slave::_slave.operation.angle = PI / 180 * 90;

				break;

			case SLAVE_DIRECTION::SD_RIGHT:

				// 플레이어와의 거리가 가까울 경우 데스메탈이 보인다.
				if (slave::_slave.b_Value.isClosePlayer)
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("bat_Right");
				}

				// 플레이어와의 거리가 멀 경우 데스메탈은 쉐도우 상태 이미지이다.
				else
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("sBat_Right");
				}

				// 데스메탈이 해당 방향을 보고 있을때 각도를 초기화해준다.
				slave::_slave.operation.angle = 0;
				break;

			case SLAVE_DIRECTION::SD_DOWN:

				// 플레이어와의 거리가 가까울 경우 데스메탈이 보인다.
				if (slave::_slave.b_Value.isClosePlayer)
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("bat_Right");
				}

				// 플레이어와의 거리가 멀 경우 데스메탈은 쉐도우 상태 이미지이다.
				else
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("sBat_Right");
				}

				// 데스메탈이 해당 방향을 보고 있을때 각도를 초기화해준다.
				slave::_slave.operation.angle = PI / 180 * 270;

				break;
		}

		slave::_slave.b_Value.isChangeAni = false;		// 보스의 움직임에 따라 애니메이션을 바꿔주었다면, 다음 움직임까지 false를 주어서 다시 바뀌지 않게 한다.
	}
	// ture의 값일때 한번만 스타트 해주고 다시 false로
	if (slave::_slave.b_Value.change_Ani)
	{
		slave::_slave.b_Value.change_Ani = false;
		slave::_slave.image.animation->start();
	}
}




