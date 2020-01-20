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
	addBossImage();													// 보스 이미지 추가 함수
	findBossType(bossName);											// 보스의 타입을 저장한다.
	findBossImage();												// 보스의 타입을 이용하여 이미지를 찾아 넣는다.
	settingBossPos(_idx, _idy, _tileSizeX, _tileSizeY);				// 보스의 좌표 변수들을 초기화 한다.
	settingBossMoveVariable(_tileSizeX, _tileSizeY);				// 보스의 이동에 필요한 변수를 초기화한다.

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
	// aniRender는 센터 중심으로 그려진다.
	image->aniRender(getMemDC(), center.x, center.y - (image->getFrameHeight() / 3), animation);

	if (KEYMANAGER->isStayKeyDown('P'))
	{
		// 보스가 위치한 타일의 렉트
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

	// 보스의 스킬 이미지
	IMAGEMANAGER->addFrameImage("Boss_Fire_0", "./image/Enemy/boss/boss_Fire_0.bmp", 336, 96, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boss_Fire_1", "./image/Enemy/boss/boss_Fire_1.bmp", 336, 96, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boss_Fire_2", "./image/Enemy/boss/boss_Fire_2.bmp", 336, 96, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Boss_Fire_3", "./image/Enemy/boss/boss_Fire_3.bmp", 336, 96, 7, 2, true, RGB(255, 0, 255));

	// 테스트용 이미지
	IMAGEMANAGER->addFrameImage("Test_Heart", "./image/Enemy/boss/beat_heart_test.bmp", 164, 104, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Test_Floor", "./image/Enemy/boss/floor_test.bmp", 156, 104, 3, 2, true, RGB(255, 0, 255));
}

void boss::findBossType(string bossname)
{
	if (bossname == "데스메탈" || bossname == "데스_메탈") type = (BOSSTYPE)DEATH_METAL;
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

	// 보스의 이미지 크기가 타일보다 크기 때문에 중점 - 이미지 절반으로 렉트 left를 구하고, 렉트 bottom - 이미지 높이를 이용하여 top을 구한다.
	rc = RectMake(idx * tileSizeX, idy * tileSizeY, tileSizeX, tileSizeY);

	// 중점을 만든다.
	center.x = (rc.left + rc.right) / 2;
	center.y = (rc.top + rc.bottom) / 2;

	_tileSize_X = tileSizeX;
	_tileSize_Y = tileSizeY;
}

void boss::settingBossMoveVariable(int tileSizeX, int tileSizeY)
{
	angle = 0;										// 보스가 이동 해야 하는 각도
	time = 0.2f;									// 다음 타일까지 이동 시간
	distance = tileSizeX;							// 다음 타일까지의 거리
	speed = move.getMoveSpeed(time, distance);		// 다음 타일까지 이동 속도
}

void boss::Info_Update()
{
	if (!isMove)
	{
		// 보스의 이미지 크기가 타일보다 크기 때문에 중점 - 이미지 절반으로 렉트 left를 구하고, 렉트 bottom - 이미지 높이를 이용하여 top을 구한다.
		rc = RectMake(index.x * _tileSize_X, index.y * _tileSize_Y, _tileSize_X, _tileSize_Y);

		center.x = (rc.left + rc.right) / 2;
		center.y = (rc.top + rc.bottom) / 2;
	}
}

void boss::boss_Move()
{
	// 보스가 움직였다면 true
	if (isMove) move.startMove(&time, &distance, &angle, &speed, &worldTime, &center, &index, direction, &isMove);

	// 보스가 움직였다면 점프 상태가 true
	// 보스가 점프를 했을때 필요한 값은
	// 보스의 좌표, 값을 저장 수정 가능한 속도?, 방향에 맞게 수치는 다르게
	// 값을 주면 계속 연산을 해야한다. 해당 bool값이 꺼질때까지
	if (isJump) move.jumping(&direction, &center, &jump);
}

