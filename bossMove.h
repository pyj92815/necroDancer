#pragma once
#include "bossLibrary.h"

class bossMove
{
private:
	int xx;
	
public:
	bossMove();
	~bossMove();

	float getMoveSpeed(float time, float distance);		// 원하는 거리를 원하는 시간에 도착하려면 어떤 스피드로 가야하는지 구할 수 있다.

	// 원하는 거리를 원하는 시간에 도착하려면 어떤 스피드로 가야하는지 구할 수 있다.
	// 구해진 속도를 이용하여 플레이어를 원하는 각도로 이동 시킨다.
	// 목표 시간에 도달한다면 bool값을 바꿔서 리턴해준다.
	void startMove(float* time, float* distance, float* angle, float* speed,
		float* worldTime, POINTFLOAT* _center, POINT* index, BOSS_DIRECTION direction, bool* Move);

};

