#include "stdafx.h"
#include "boss.h"

boss::boss()
	: hp(0), shield(0), attack(0), magicAttack(0), skill_Casting_Cnt(0), angle(0), speed(0), worldTime(0)
	
{
}

boss::~boss()
{
}

HRESULT boss::init(string bossName, int _idx, int _idy, int _tileSizeX, int _tileSizeY)
{
	addBossImage();													// ���� �̹��� �߰� �Լ�
	findBossType(bossName);											// ������ Ÿ���� �����Ѵ�.
	findBossImage();												// ������ Ÿ���� �̿��Ͽ� �̹����� ã�� �ִ´�.
	settingBossPos(_idx, _idy, _tileSizeX, _tileSizeY);				// ������ ��ǥ �������� �ʱ�ȭ �Ѵ�.
	settingBossMoveVariable(_tileSizeX, _tileSizeY);				// ������ �̵��� �ʿ��� ������ �ʱ�ȭ�Ѵ�.

	return S_OK;
}

void boss::release()
{
}

void boss::update()
{
}

void boss::render()
{
	// aniRender�� ���� �߽����� �׷�����.
	image->aniRender(getMemDC(), center.x, center.y - (image->getFrameHeight() / 3), animation);

	if (KEYMANAGER->isStayKeyDown('P'))
	{
		// ������ ��ġ�� Ÿ���� ��Ʈ
		Rectangle(getMemDC(), rc);
	}
}

void boss::render(ThrowShield info)
{
	info.image->render(getMemDC(), info.rc.left, info.rc.top);
}

void boss::addBossImage()
{
	IMAGEMANAGER->addImage("deathMetal_SceneImage", "./image/Enemy/boss/deathMetal_Image.bmp", 960, 398, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("deathMetal_Shield", "./image/Enemy/boss/deathMetal_Shield.bmp", 90, 46, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Death_Metal", "./image/Enemy/boss/death_metal.bmp", 2112, 212, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boss_Ghost", "./image/Enemy/boss/boss_Ghost.bmp", 192, 96, 4, 2, true, RGB(255, 0, 255));

	// ������ ��ų �̹���
	IMAGEMANAGER->addFrameImage("Boss_Fire_0", "./image/Enemy/boss/boss_Fire_0.bmp", 336, 96, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boss_Fire_1", "./image/Enemy/boss/boss_Fire_1.bmp", 336, 96, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boss_Fire_2", "./image/Enemy/boss/boss_Fire_2.bmp", 336, 96, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boss_Fire_3", "./image/Enemy/boss/boss_Fire_3.bmp", 336, 96, 7, 2, true, RGB(255, 0, 255));

	// �׽�Ʈ�� �̹���
	IMAGEMANAGER->addFrameImage("Test_Heart", "./image/Enemy/boss/beat_heart_test.bmp", 164, 104, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Test_Floor", "./image/Enemy/boss/floor_test.bmp", 156, 104, 3, 2, true, RGB(255, 0, 255));
}

void boss::findBossType(string bossname)
{
	if (bossname == "������Ż" || bossname == "����_��Ż") type = (BOSSTYPE)DEATH_METAL;
	else type = (BOSSTYPE)EMPTY;
}

void boss::findBossImage()
{
	switch (type)
	{
	case DEATH_METAL:
		image = IMAGEMANAGER->findImage("Death_Metal");
		break;

	case EMPTY:
		image = IMAGEMANAGER->findImage("Test_Floor");
		break;
	}
}

void boss::settingBossPos(int idx, int idy, int tileSizeX, int tileSizeY)
{
	index.x = idx;
	index.y = idy;

	// ������ �̹��� ũ�Ⱑ Ÿ�Ϻ��� ũ�� ������ ���� - �̹��� �������� ��Ʈ left�� ���ϰ�, ��Ʈ bottom - �̹��� ���̸� �̿��Ͽ� top�� ���Ѵ�.
	rc = RectMake(idx * tileSizeX, idy * tileSizeY, tileSizeX, tileSizeY);

	// ������ �����.
	center.x = (rc.left + rc.right) / 2;
	center.y = (rc.top + rc.bottom) / 2;

	_tileSize_X = tileSizeX;
	_tileSize_Y = tileSizeY;
}

void boss::settingBossMoveVariable(int tileSizeX, int tileSizeY)
{
	angle = 0;										// ������ �̵� �ؾ� �ϴ� ����
	time = 0.2f;									// ���� Ÿ�ϱ��� �̵� �ð�
	distance = tileSizeX;							// ���� Ÿ�ϱ����� �Ÿ�
	speed = move.getMoveSpeed(time, distance);		// ���� Ÿ�ϱ��� �̵� �ӵ�
}

void boss::Info_Update()
{
	if (!isMove)
	{
		// ������ �̹��� ũ�Ⱑ Ÿ�Ϻ��� ũ�� ������ ���� - �̹��� �������� ��Ʈ left�� ���ϰ�, ��Ʈ bottom - �̹��� ���̸� �̿��Ͽ� top�� ���Ѵ�.
		rc = RectMake(index.x * _tileSize_X, index.y * _tileSize_Y, _tileSize_X, _tileSize_Y);

		center.x = (rc.left + rc.right) / 2;
		center.y = (rc.top + rc.bottom) / 2;
	}
}

void boss::boss_Move()
{
	// ������ �������ٸ� true
	if (isMove) move.startMove(&time, &distance, &angle, &speed, &worldTime, &center, &index, direction, &isMove);

	// ������ �������ٸ� ���� ���°� true
	// ������ ������ ������ �ʿ��� ����
	// ������ ��ǥ, ���� ���� ���� ������ �ӵ�?, ���⿡ �°� ��ġ�� �ٸ���
	// ���� �ָ� ��� ������ �ؾ��Ѵ�. �ش� bool���� ����������
	if (isJump) move.jumping(&direction, &center, &jump);
}

