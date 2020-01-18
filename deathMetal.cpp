#include "stdafx.h"
#include "deathMetal.h"

HRESULT deathMetal::init(string bossName, int idx, int idy, int TILE_SIZEX, int TILE_SIZEY)
{
	boss::hp = 9;														 // ������Ż�� �⺻ ü�� �ʱ�ȭ
	boss::shield = 2;													 // ������Ż�� �⺻ �ǵ� �ʱ�ȭ
	boss::attack = 1.5;													 // ������Ż�� �⺻ ���ݷ� �ʱ�ȭ
	boss::magicAttack = 2;												 // ������Ż�� �⺻ �������ݷ� �ʱ�ȭ
	boss::init(bossName, idx, idy, TILE_SIZEX, TILE_SIZEY);				 // ������Ż�� ��ǥ ���� �ʱ�ȭ

	deathMetal_Animation_Setting();										 // ������Ż�� �ִϸ��̼� �߰� �Լ�

	boss::direction = BD_DOWN;											 // ������Ż�� ó���� �Ʒ��� �ٶ󺸰� �ִ�.
	boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SDown");  // ������Ż�� ���� �ִϸ��̼��� ������ٿ�
	boss::animation->start();											 // �ִϸ��̼��� �����Ѵ�.
	boss::isMove = false;												 // ������Ż�� �����̸� �� ���� true�� �ٲ��.
	boss::isCasting = false;											 // ������Ż�� ������ ĳ���� ���̶�� �� ���� true�� �ٲ��.
	boss::isClosePlayer = false;										 // ������Ż�� �÷��̾� ��ó�� �ִٸ� �� ���� true�� �ٲ��.

	return S_OK;
}

void deathMetal::release()
{
}

void deathMetal::update()
{
	Info_Update();												 // ������Ż�� �ε��� ������ �ٲ�� �ڵ����� ����, ��Ʈ�� �������ش�.
	deathMetal_Animation_Test();								 // ������Ż�� �ִϸ��̼� �׽�Ʈ �Լ�
	deathMetal_ChangeAnimation();								 // ������Ż�� �ִϸ��̼� ü���� �Լ�
	deathMetal_ChangePhase();									 // ������Ż�� ������ ü���� �Լ�
}

void deathMetal::render()
{

	boss::render();
}

void deathMetal::deathMetal_Animation_Setting()
{

	// �ǵ� ������ �̿��ϴ� �ִϸ��̼�
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

	// �ǵ� ������ �̿��ϴ� �ִϸ��̼�
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
	// �ִϸ��̼� �׽�Ʈ �Լ�

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
		boss::setBoss_HP_Hit();	// ������ ü���� 1 ���� ��Ų��.
		boss::isMove = true;
	}
}

void deathMetal::deathMetal_ChangeAnimation()
{
	// ������Ż�� �ٶ󺸴� ���⿡ ���� �ִϸ��̼��� �ٲ��ش�.
	if (boss::isMove)
	{
		switch (boss::direction)
		{
		case BD_LEFT:
			// ������Ż�� 1������� ���и� ��� �ִ� �ִϸ��̼��̴�.
			if (boss::phase == BP_PHASE_1)
			{
				// �÷��̾���� �Ÿ��� ����� ��� ������Ż�� ���δ�.
				if (boss::isClosePlayer)
				{
					boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Left");
					boss::animation->start();
				}

				// �÷��̾���� �Ÿ��� �� ��� ������Ż�� ������ ���� �̹����̴�.
				else
				{
					boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SLeft");
					boss::animation->start();
				}
			}

			// ������Ż�� 2��������ʹ� ���ݸ��, ����� 2���θ� �����δ�.
			else
			{
				// �÷��̾���� �Ÿ��� ����� ��� ������Ż�� ���δ�.
				if (boss::isClosePlayer)
				{
					// ���� ĳ���� ���� �ƴҶ��� �����
					if (!boss::isCasting)
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Idel");
						boss::animation->start();
					}

					// ���� ĳ���� ���϶��� ���� ���
					else
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Attack");
						boss::animation->start();
					}
				}

				// �÷��̾���� �Ÿ��� �� ��� ������Ż�� ������ ���� �̹����̴�.
				else
				{
					// ���� ĳ���� ���� �ƴҶ��� �����
					if (!boss::isCasting)
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SIdel");
						boss::animation->start();
					}

					// ���� ĳ���� ���϶��� ���� ���
					else
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SAttack");
						boss::animation->start();
					}
				}
			}
			break;

		case BD_UP:
			// ������Ż�� 1������� ���и� ��� �ִ� �ִϸ��̼��̴�.
			if (boss::phase == BP_PHASE_1)
			{
				// �÷��̾���� �Ÿ��� ����� ��� ������Ż�� ���δ�.
				if (boss::isClosePlayer)
				{
					boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Up");
					boss::animation->start();
				}

				// �÷��̾���� �Ÿ��� �� ��� ������Ż�� ������ ���� �̹����̴�.
				else
				{
					boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SUp");
					boss::animation->start();
				}
			}

			// ������Ż�� 2��������ʹ� ���ݸ��, ����� 2���θ� �����δ�.
			else
			{
				// �÷��̾���� �Ÿ��� ����� ��� ������Ż�� ���δ�.
				if (boss::isClosePlayer)
				{
					// ���� ĳ���� ���� �ƴҶ��� �����
					if (!boss::isCasting)
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Idel");
						boss::animation->start();
					}

					// ���� ĳ���� ���϶��� ���� ���
					else
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Attack");
						boss::animation->start();
					}
				}

				// �÷��̾���� �Ÿ��� �� ��� ������Ż�� ������ ���� �̹����̴�.
				else
				{
					// ���� ĳ���� ���� �ƴҶ��� �����
					if (!boss::isCasting)
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SIdel");
						boss::animation->start();
					}

					// ���� ĳ���� ���϶��� ���� ���
					else
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SAttack");
						boss::animation->start();
					}
				}
			}
			break;

		case BD_RIGHT:
			// ������Ż�� 1������� ���и� ��� �ִ� �ִϸ��̼��̴�.
			if (boss::phase == BP_PHASE_1)
			{
				// �÷��̾���� �Ÿ��� ����� ��� ������Ż�� ���δ�.
				if (boss::isClosePlayer)
				{
					boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Right");
					boss::animation->start();
				}

				// �÷��̾���� �Ÿ��� �� ��� ������Ż�� ������ ���� �̹����̴�.
				else
				{
					boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SRight");
					boss::animation->start();
				}
			}

			// ������Ż�� 2��������ʹ� ���ݸ��, ����� 2���θ� �����δ�.
			else
			{
				// �÷��̾���� �Ÿ��� ����� ��� ������Ż�� ���δ�.
				if (boss::isClosePlayer)
				{
					// ���� ĳ���� ���� �ƴҶ��� �����
					if (!boss::isCasting)
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Idel");
						boss::animation->start();
					}

					// ���� ĳ���� ���϶��� ���� ���
					else
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Attack");
						boss::animation->start();
					}
				}

				// �÷��̾���� �Ÿ��� �� ��� ������Ż�� ������ ���� �̹����̴�.
				else
				{
					// ���� ĳ���� ���� �ƴҶ��� �����
					if (!boss::isCasting)
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SIdel");
						boss::animation->start();
					}

					// ���� ĳ���� ���϶��� ���� ���
					else
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SAttack");
						boss::animation->start();
					}
				}
			}
			break;

		case BD_DOWN:
			// ������Ż�� 1������� ���и� ��� �ִ� �ִϸ��̼��̴�.
			if (boss::phase == BP_PHASE_1)
			{
				// �÷��̾���� �Ÿ��� ����� ��� ������Ż�� ���δ�.
				if (boss::isClosePlayer)
				{
					boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Down");
					boss::animation->start();
				}

				// �÷��̾���� �Ÿ��� �� ��� ������Ż�� ������ ���� �̹����̴�.
				else
				{
					boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SDown");
					boss::animation->start();
				}
			}

			// ������Ż�� 2��������ʹ� ���ݸ��, ����� 2���θ� �����δ�.
			else
			{
				// �÷��̾���� �Ÿ��� ����� ��� ������Ż�� ���δ�.
				if (boss::isClosePlayer)
				{
					// ���� ĳ���� ���� �ƴҶ��� �����
					if (!boss::isCasting)
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Idel");
						boss::animation->start();
					}

					// ���� ĳ���� ���϶��� ���� ���
					else
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Attack");
						boss::animation->start();
					}
				}

				// �÷��̾���� �Ÿ��� �� ��� ������Ż�� ������ ���� �̹����̴�.
				else
				{
					// ���� ĳ���� ���� �ƴҶ��� �����
					if (!boss::isCasting)
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SIdel");
						boss::animation->start();
					}

					// ���� ĳ���� ���϶��� ���� ���
					else
					{
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SAttack");
						boss::animation->start();
					}
				}
			}
			break;
		}

		boss::isMove = false;	// ������ �����ӿ� ���� �ִϸ��̼��� �ٲ��־��ٸ�, ���� �����ӱ��� false�� �־ �ٽ� �ٲ��� �ʰ� �Ѵ�.
	}
}

void deathMetal::deathMetal_ChangePhase()
{
	if (boss::hp > 7) boss::phase = BP_PHASE_1;
	else if (boss::hp > 5) boss::phase = BP_PHASE_2;
	else if (boss::hp > 3) boss::phase = BP_PHASE_3;
	else if (boss::hp > 0) boss::phase = BP_PHASE_4; 

	// ������Ż ������
	// HP 9 ~ 7 : ���и� ��� �� ���ڸ��� �̵��ϸ鼭 �÷��̾�� �ٰ�����.
	//            �Ϲ� ����� ���и� �� ������ ���� ��Ż�� ���鿡�� �����ϸ� �ڷ� ƨ��Ը� �� ���̸�, ���ÿ� ���㰡 ��ȯ�ȴ�.
	//            �ݵ�� ���̳� �ڸ� �����ؾ� �Ѵ�. �ٸ� ���� ȿ���� �ִ� ���⸦ ����ϸ� ���鿡���� ������ �� �ִ�.
	// HP 6 ~ 5 : ���и� ���� ������ �� ���ڸ��� �����̸鼭 �÷��̾�� �Ÿ��� �д�. �̵��� "Come to me!"��� ��ġ�� ���� ���ø��µ�,
	//            ���� �� ���� ���� ���ݹ��� ������ 1~3 ������ �ذ��� ��ȯ�Ѵ�. �̶����ʹ� ���ݹ����� �ݴ������� ���� �̵��Ѵ�.
	// HP 4 ~ 3 : "End of the line!"�� ��ġ�� ��� �ذ��� ��ȯ�Ѵ�.
	// HP 2 ~ 1 : �� ���ڸ��� �̵��ϱ� �����ϸ鼭 �����̳� ������ ���� �ٴ´�. �� �� ���������� �÷��̾ ���󰡸鼭 �� ���ڸ���
	//            "Bathe in fire!"�� ��ġ�� ���������� ���̾�� �߻��Ѵ�.
}
