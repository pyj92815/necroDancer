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
	boss::isChangeAni = false;											 // ������Ż�� �����̸� �� ���� true�� �ٲ��.
	boss::isCasting = false;											 // ������Ż�� ������ ĳ���� ���̶�� �� ���� true�� �ٲ��.
	boss::isClosePlayer = false;										 // ������Ż�� �÷��̾� ��ó�� �ִٸ� �� ���� true�� �ٲ��.

	clearThrowShield();													 // ������Ż�� �ǵ� ������ �ʱ�ȭ ���ش�.

	return S_OK;
}

void deathMetal::release()
{
}

void deathMetal::update()
{
	Info_Update();												 // ������Ż�� �ε��� ������ �ٲ�� �ڵ����� ����, ��Ʈ�� �������ش�.
	deathMetal_Animation_Test();								 // ������Ż�� �ִϸ��̼� �׽�Ʈ �Լ�
	deathMetal_ChangePhase();									 // ������Ż�� ������ ü���� �Լ�									
	deathMetal_ChangeAnimation();								 // ������Ż�� �ִϸ��̼� ü���� �Լ�
	boss_Move();												 // ������Ż�� �̵� ���� �Լ�
}

void deathMetal::render()
{
	boss::render();

	if(_throwShield.isOut) boss::render(_throwShield);	 // ������ 1�� ������ �ǵ��� ������ ���ŵǰ�, �׶����� ���̱� �����Ѵ�.
}

void deathMetal::clearThrowShield()
{
	// �ǵ� �̹����� �ִ´�.
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

	// ������Ż�� ������ �ٲٰ�, �ִϸ��̼��� �ٲٱ� ���� true������ ����
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD1))
	{
		boss::direction = BD_LEFT;
		worldTime = TIMEMANAGER->getWorldTime();	// ���� Ÿ���� �����Ѵ�.
													// ���� �Լ� ��������

		//boss::index.x--; // �̵��� ��� �������� �ε����� �Ȱ��ش�?
		boss::isChangeAni = true;	// ������ �������ٸ� �ִϸ��̼��� �ٲ��־���Ѵ�.
		boss::isMove = true;
	}

	// ������Ż�� ������ �ٲٰ�, �ִϸ��̼��� �ٲٱ� ���� true������ ����
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD5))
	{
		boss::direction = BD_UP;
		worldTime = TIMEMANAGER->getWorldTime();	// ���� Ÿ���� �����Ѵ�.
													// ���� �Լ� ��������

		//boss::index.y--;
		boss::isChangeAni = true;	// ������ �������ٸ� �ִϸ��̼��� �ٲ��־���Ѵ�.
		boss::isMove = true;
	}

	// ������Ż�� ������ �ٲٰ�, �ִϸ��̼��� �ٲٱ� ���� true������ ����
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD3))
	{
		boss::direction = BD_RIGHT;
		worldTime = TIMEMANAGER->getWorldTime();	// ���� Ÿ���� �����Ѵ�.
													// ���� �Լ� ��������

		//boss::index.x++;
		boss::isChangeAni = true;	// ������ �������ٸ� �ִϸ��̼��� �ٲ��־���Ѵ�.
		boss::isMove = true;
	}

	// ������Ż�� ������ �ٲٰ�, �ִϸ��̼��� �ٲٱ� ���� true������ ����
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD2))
	{
		boss::direction = BD_DOWN;
		worldTime = TIMEMANAGER->getWorldTime();	// ���� Ÿ���� �����Ѵ�.
													// ���� �Լ� ��������

		//boss::index.y++;
		boss::isChangeAni = true;	// ������ �������ٸ� �ִϸ��̼��� �ٲ��־���Ѵ�.
		boss::isMove = true;
	}

	// ������Ż�� �ִϸ��̼��� ���� ������� �ٲٰ� ����
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD4))
	{
		boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Attack");
		boss::animation->start();
	}

	// ������Ż�� �ִϸ��̼��� ��� ������� �ٲٰ� ����
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD6))
	{
		boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Idle");
		boss::animation->start();
	}

	// ������Ż�� ü���� ���ҽ�Ų��.
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD7))
	{
		boss::setBoss_HP_Hit();	// ������ ü���� 1 ���� ��Ų��.
		boss::isChangeAni = true;
	}

	// �÷��̾ ��ó�� ������ true ������ false (�׽�Ʈ��)
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD8))
	{
		boss::isClosePlayer = true;	// �÷��̾ ������ �ִٸ� true
		boss::isChangeAni = true;
	}

	// ������Ż �ǵ� �׽�Ʈ��
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
	// ������Ż�� �ٶ󺸴� ���⿡ ���� �ִϸ��̼��� �ٲ��ش�.
	if (boss::isChangeAni)	// ������ �������ٸ� �ִϸ��̼��� �ٲ��־���Ѵ�.
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
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Idle");
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
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SIdle");
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

			// ������Ż�� �ش� ������ ���� ������ ������ �ʱ�ȭ���ش�.
			boss::angle = PI;
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
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Idle");
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
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SIdle");
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

			// ������Ż�� �ش� ������ ���� ������ ������ �ʱ�ȭ���ش�.
			boss::angle = PI / 180 * 90;

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
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Idle");
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
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SIdle");
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

			// ������Ż�� �ش� ������ ���� ������ ������ �ʱ�ȭ���ش�.
			boss::angle = 0;

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
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_Idle");
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
						boss::animation = KEYANIMANAGER->findAnimation("deathMetal_SIdle");
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

			// ������Ż�� �ش� ������ ���� ������ ������ �ʱ�ȭ���ش�.
			boss::angle = PI / 180 * 270;

			break;
		}
		boss::isChangeAni = false;		// ������ �����ӿ� ���� �ִϸ��̼��� �ٲ��־��ٸ�, ���� �����ӱ��� false�� �־ �ٽ� �ٲ��� �ʰ� �Ѵ�.
	}
}

void deathMetal::deathMetal_ChangePhase()
{
	if (boss::hp > 7)		boss::phase = BP_PHASE_1;
	else if (boss::hp > 5)	boss::phase = BP_PHASE_2;
	else if (boss::hp > 3)	boss::phase = BP_PHASE_3;
	else if (boss::hp > 0)	boss::phase = BP_PHASE_4; 

	// ������Ż ������
	// HP 9 ~ 7 : ���и� ��� �� ���ڸ��� �̵��ϸ鼭 �÷��̾�� �ٰ�����.
	//            �Ϲ� ����� ���и� �� ������ ���� ��Ż�� ���鿡�� �����ϸ� �ڷ� ƨ��Ը� �� ���̸�, ���ÿ� ���㰡 ��ȯ�ȴ�.
	//            �ݵ�� ���̳� �ڸ� �����ؾ� �Ѵ�. �ٸ� ���� ȿ���� �ִ� ���⸦ ����ϸ� ���鿡���� ������ �� �ִ�.
	// HP 6 ~ 5 : ���и� ���� ������ �� ���ڸ��� �����̸鼭 �÷��̾�� �Ÿ��� �д�. �̵��� "Come to me!"��� ��ġ�� ���� ���ø��µ�,
	//            ���� �� ���� ���� ���ݹ��� ������ 1~3 ������ �ذ��� ��ȯ�Ѵ�. �̶����ʹ� ���ݹ����� �ݴ������� ���� �̵��Ѵ�.
	// HP 4 ~ 3 : "End of the line!"�� ��ġ�� ��� �ذ��� ��ȯ�Ѵ�.
	// HP 2 ~ 1 : �� ���ڸ��� �̵��ϱ� �����ϸ鼭 �����̳� ������ ���� �ٴ´�. �� �� ���������� �÷��̾ ���󰡸鼭 �� ���ڸ���
	//            "Bathe in fire!"�� ��ġ�� ���������� ���̾�� �߻��Ѵ�.

	// ���� ���� ����� 2�� �ٲ����, �ǵ带 ���� ������ �ʾҴٸ� �����Ѵ�. (�ǵ� ������ �ִϸ��̼� �Լ�)
	if (boss::phase == BP_PHASE_2 && !boss::isThrowShield)	deathMetal_ThrowShield();


}

void deathMetal::deathMetal_ShieldPosUpdate()
{
	// ��Ʈ�� ���Ѵ�. (����x - �ǵ��̹��� ���� / 2, ����y - �����̹��� ���� / 2, �ǵ��̹��� ����, �ǵ��̹��� ����)
	_throwShield.rc = RectMake(boss::center.x - _throwShield.image->getWidth() / 2, 
		boss::center.y - boss::image->getFrameHeight() / 2, _throwShield.image->getWidth(), _throwShield.image->getHeight());

	// ��Ʈ�� �̿��Ͽ� ������ ���Ѵ�.
	_throwShield.center.x = (_throwShield.rc.left + _throwShield.rc.right) / 2;
	_throwShield.center.y = (_throwShield.rc.top + _throwShield.rc.bottom) / 2;

	// �ǵ尡 ó�� ���ư� ���� (������ �ٶ󺸴� ���⿡ ���� ���а� ���ư��� ������ �ٸ���.)
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
	
	// ������ �ٶ󺸴� ������ �����صд�. (���Ŀ� ������ �̵��� �� �� �ֱ� ������)
	_throwShield.direction = boss::direction;

	// �ǵ尡 ���ư��� �ӵ�
	_throwShield.speed = 3.0f;

	// ������ �ѹ��� �Ѵ�.
	_throwShield.isShieldUpdate = true;		// ��� ��ǥ ������ �����ٸ� true�� ������ ����
	_throwShield.isOut = true;				// ������ �����ٸ� ���и� ������ش�.
}

void deathMetal::deathMetal_ThrowShield()
{
	if(!_throwShield.isShieldUpdate) deathMetal_ShieldPosUpdate();		// ������Ż�� ��ǥ�� �̿��Ͽ� �ǵ��� ��ġ�� �������ش�. (���� �� ture�� ������ ���� �Ѵ�.)

	// �ǵ�� ������ �ӵ���ŭ ���� �� ������ ���ư���.
	_throwShield.center.x += cosf(_throwShield.angle) * _throwShield.speed;
	_throwShield.center.y += -sinf(_throwShield.angle) * _throwShield.speed;

	// �ǵ��� ������ �̼��ϰ� �ٲ��ش�. (������ �ϵ��� ����� ����)
	_throwShield.angle += 0.07f;

	// �ǵ��� ��Ʈ ��ġ�� �������ش�.
	_throwShield.rc = RectMake(_throwShield.center.x - _throwShield.image->getWidth() / 2,
		_throwShield.center.y - _throwShield.image->getHeight() / 2, _throwShield.image->getWidth(), _throwShield.image->getHeight());

	// �ǵ� �������� ��� ������ isThrowShield�� ���� true�� �ǰ� ��°� ������ ��� �����Ѵ�.
	// ������ ���⿡ ���� �ǵ尡 ������� ������ �ٸ��� ������ �ٽ� �ѹ� ����ġ���� �����ش�.
	switch (_throwShield.direction)
	{
	case BD_LEFT:
		if (_throwShield.angle >= PI / 180 * 360)
		{
			boss::isThrowShield = true;					// �ǵ� ������ �����ٸ� true
			_throwShield.isOut = false;					// �ǵ� �̹����� �� �̻� �׸��� �ʵ��� false
		}
		break;

	case BD_UP:
		if (_throwShield.angle >= PI / 180 * 270)
		{
			boss::isThrowShield = true;					// �ǵ� ������ �����ٸ� true
			_throwShield.isOut = false;					// �ǵ� �̹����� �� �̻� �׸��� �ʵ��� false
		}
		break;

	case BD_RIGHT:
		if (_throwShield.angle >= PI / 180 * 210)
		{
			boss::isThrowShield = true;					// �ǵ� ������ �����ٸ� true
			_throwShield.isOut = false;					// �ǵ� �̹����� �� �̻� �׸��� �ʵ��� false
		}
		break;

	case BD_DOWN:
		if (_throwShield.angle >= PI / 180 * 500)
		{
			boss::isThrowShield = true;					// �ǵ� ������ �����ٸ� true
			_throwShield.isOut = false;					// �ǵ� �̹����� �� �̻� �׸��� �ʵ��� false
		}
		break;
	}
}
