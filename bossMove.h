#pragma once
#include "bossLibrary.h"

class bossMove
{
private:
	
public:
	bossMove();
	~bossMove();

	float getMoveSpeed(float time, float distance);		// 원하는 거리를 원하는 시간에 도착하려면 어떤 스피드로 가야하는지 구할 수 있다.

	// 원하는 거리를 원하는 시간에 도착하려면 어떤 스피드로 가야하는지 구할 수 있다.
	// 구해진 속도를 이용하여 플레이어를 원하는 각도로 이동 시킨다.
	// 목표 시간에 도달한다면 bool값을 바꿔서 리턴해준다.
	void startMove(float* time, float* distance, float* angle, float* speed,
		float* worldTime, POINTFLOAT* _center, POINT* index, BOSS_DIRECTION direction, bool* Move);

	// 보스의 방향을 이용하여 어느 방향으로 이동을 하는지를 구할 수 있다.
	// 보스의 중점 x, y를 이용하여 위치 계산을 한다.
	// 보스가 점프 연산하는중에 필요한 변수를 이용한다. (속도, 중력 등)
	void jumping(BOSS_DIRECTION* direction, POINTFLOAT* center, tagBossJump* jump);
};

