#include "stdafx.h"
#include "boss_Ghost.h"

boss_Ghost::boss_Ghost()
{
}

boss_Ghost::~boss_Ghost()
{
}

HRESULT boss_Ghost::init()
{
	return S_OK;
}

void boss_Ghost::update()
{
	boss_Ghost_ChangeAnimation();
	slave::slave_Pos_Setting();
}

void boss_Ghost::move()
{
}

void boss_Ghost::boss_Ghost_ChangeAnimation()
{
	// ���⿡ ��ȭ�� ������ true�� ���� �־��ش�.
	if (slave::_slave.status.direction != slave::_slave.status.save_Direction)
	{
		// ���� ������ ��ȭ �Ҷ����� �̰��� ������ �ʴ´�.
		slave::_slave.status.save_Direction = slave::_slave.status.direction;
		slave::_slave.b_Value.isChangeAni = true;
		slave::_slave.b_Value.change_Ani = true;
	}

	// �÷��̾ ��ó�� �ְų� �ָ� ���ų� ���� ���� �Ǿ����� ���´�.
	if (slave::_slave.b_Value.isClosePlayer != slave::_slave.b_Value.save_ClosePlayer)
	{
		// ���� ��ȭ�� ���������� ������ �ʴ´�.
		slave::_slave.b_Value.save_ClosePlayer = slave::_slave.b_Value.isClosePlayer;
		slave::_slave.b_Value.isChangeAni = true;
		slave::_slave.b_Value.change_Ani = true;
	}

	// ������Ż�� �ٶ󺸴� ���⿡ ���� �ִϸ��̼��� �ٲ��ش�.
	if (slave::_slave.b_Value.isChangeAni)	// ������ �������ٸ� �ִϸ��̼��� �ٲ��־���Ѵ�.
	{
		switch (slave::_slave.status.direction)
		{
			case SLAVE_DIRECTION::SD_LEFT:

				// �÷��̾���� �Ÿ��� ����� ��� ��Ʈ�� ���δ�.
				if (slave::_slave.b_Value.isClosePlayer)
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("ghost_Left");
				}

				// �÷��̾���� �Ÿ��� �� ��� ��Ʈ�� ������ ���� �̹����̴�.
				else
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("sGhost_Left");
				}

				// ��Ʈ�� �ش� ������ ���� ������ ������ �ʱ�ȭ���ش�.
				slave::_slave.operation.angle = PI;
				break;

			case SLAVE_DIRECTION::SD_RIGHT:

				// �÷��̾���� �Ÿ��� ����� ��� ��Ʈ�� ���δ�.
				if (slave::_slave.b_Value.isClosePlayer)
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("ghost_Right");
				}

				// �÷��̾���� �Ÿ��� �� ��� ��Ʈ�� ������ ���� �̹����̴�.
				else
				{
					slave::_slave.image.animation = KEYANIMANAGER->findAnimation("sGhost_Right");
				}

				// ��Ʈ�� �ش� ������ ���� ������ ������ �ʱ�ȭ���ش�.
				slave::_slave.operation.angle = 0;
				break;

			case SLAVE_DIRECTION::SD_UP: case SLAVE_DIRECTION::SD_DOWN:

				// ��Ʈ�� ������ �ٶ󺸰� �ִٰ� �� �Ǵ� �Ʒ��� �ö� ���� ���
				if (slave::_slave.operation.angle == PI)
				{
					// �÷��̾���� �Ÿ��� ����� ��� ��Ʈ�� ���δ�.
					if (slave::_slave.b_Value.isClosePlayer)
					{
						slave::_slave.image.animation = KEYANIMANAGER->findAnimation("ghost_Left");
					}

					// �÷��̾���� �Ÿ��� �� ��� ��Ʈ�� ������ ���� �̹����̴�.
					else
					{
						slave::_slave.image.animation = KEYANIMANAGER->findAnimation("sGhost_Left");
					}
				}

				// ��Ʈ�� �������� �ٶ󺸰� �ִٰ�  �� �Ǵ� �Ʒ��� �ö� ���� ���
				if (slave::_slave.operation.angle == 0)
				{
					// �÷��̾���� �Ÿ��� ����� ��� ��Ʈ�� ���δ�.
					if (slave::_slave.b_Value.isClosePlayer)
					{
						slave::_slave.image.animation = KEYANIMANAGER->findAnimation("ghost_Right");
					}

					// �÷��̾���� �Ÿ��� �� ��� ��Ʈ�� ������ ���� �̹����̴�.
					else
					{
						slave::_slave.image.animation = KEYANIMANAGER->findAnimation("sGhost_Right");
					}
				}

				break;
		}

		slave::_slave.b_Value.isChangeAni = false;		// ������ �����ӿ� ���� �ִϸ��̼��� �ٲ��־��ٸ�, ���� �����ӱ��� false�� �־ �ٽ� �ٲ��� �ʰ� �Ѵ�.
	}
	// ture�� ���϶� �ѹ��� ��ŸƮ ���ְ� �ٽ� false��
	if (slave::_slave.b_Value.change_Ani)
	{
		slave::_slave.b_Value.change_Ani = false;
		slave::_slave.image.animation->start();
	}
}


