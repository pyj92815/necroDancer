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
	findBossType(bossName);											// 보스의 타입을 저장한다.
	findBossImage();												// 보스의 타입을 이용하여 이미지를 찾아 넣는다.
	settingBossPos(_idx, _idy, _tileSizeX, _tileSizeY);				// 보스의 좌표 변수들을 초기화 한다.
	settingBossMoveVariable(_tileSizeX, _tileSizeY);				// 보스의 이동에 필요한 변수를 초기화한다.
	settingBossVariable();											// 보스에서 사용할 변수 초기화
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
	//PatBlt(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY, BLACKNESS);
	// aniRender는 센터 중심으로 그려진다.
	_image->aniRender(CAMERAMANAGER->getWorldDC(), center.x, center.y - (_image->getFrameHeight() / 3), ani);

	// 보스의 체력 게이지는 한대 맞고 표시 된다.
	// 실제 체력 갯수에 맞게 오른쪽에서부터 왼쪽까지 그려준다.
	// 잃은 체력은 왼쪽에서 오른쪽으로 그려준다.
	// 실제 체력 갯수가 늘어나면 잃은 체력 갯수가 늘어남
	if(hp < max_HP) showBossHP();

	if (KEYMANAGER->isStayKeyDown('P'))
	{
		// 보스가 위치한 타일의 렉트
		Rectangle(CAMERAMANAGER->getWorldDC(), rc);
	}
}

void boss::render(ThrowShield info)
{
	info.image->render(CAMERAMANAGER->getWorldDC(), info.rc.left, info.rc.top);
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
		_image = IMAGEMANAGER->findImage("Death_Metal");
		break;

	case EMPTY:
		_image = IMAGEMANAGER->findImage("Test_Floor");
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

void boss::settingBossVariable()
{
	boss_Bool.PHASE_BOOL.PHASE_1_Set = false;
	boss_Bool.PHASE_BOOL.PHASE_2_Set = false;
	boss_Bool.PHASE_BOOL.PHASE_3_Set = false;
	boss_Bool.PHASE_BOOL.PHASE_4_Set = false;

	boss_Bool.boss_Die = false;
	boss_Bool.phase4_MoveX_Direction = false;
	boss_Bool.phase4_MoveX_End = false;
	boss_Bool.phase4_MoveX_Direction_Find = false;
	boss_Bool.phase4_MagicRangeSave = false;

	move_Count = 0;

	slave_Summon.isCasting = false;
	slave_Summon.cTime = 0;
	slave_Summon.cTime_M = 0;
	slave_Summon.rnd = 0;

	boss_FireBall.isCasting = false;
	boss_FireBall.cTime = 0;
	boss_FireBall.cTime_M = 0;

}

void boss::showBossHP()
{
	float tempHP_SizeX = IMAGEMANAGER->findImage("Boss_Hp_Full")->getWidth();
	float tempHP_SizeY = IMAGEMANAGER->findImage("Boss_Hp_Full")->getHeight();
	float tempBoss_SizeY = IMAGEMANAGER->findImage("Death_Metal")->getFrameHeight();

	// 현재 남은 체력만큼 이미지를 오른쪽에서 왼쪽으로 그려준다.
	for (int i = 0; i < hp; ++i)
	{
		IMAGEMANAGER->findImage("Boss_Hp_Full")->render(CAMERAMANAGER->getWorldDC(),
			((center.x + tempHP_SizeX * 4) - tempHP_SizeX / 2) - (i * tempHP_SizeX)
				, center.y - tempBoss_SizeY);
	}

	// 잃은 체력은 오른쪽에서 왼쪽으로 그려준다.
	for (int i = 0; i < max_HP - hp; ++i)
	{
		IMAGEMANAGER->findImage("Boss_Hp_Null")->render(CAMERAMANAGER->getWorldDC(),
			((center.x - tempHP_SizeX * 4) - tempHP_SizeX / 2) + (i * tempHP_SizeX)
			, center.y - tempBoss_SizeY);
	}


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

