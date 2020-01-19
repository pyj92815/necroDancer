#include "stdafx.h"
#include "bossMove.h"

bossMove::bossMove()
{
	xx = 0;
}

bossMove::~bossMove()
{
}

float bossMove::getMoveSpeed(float time, float distance)
{
	float elapsedTime = TIMEMANAGER->getElapsedTime();

	// distance의 거리를 time만큼의 시간에 걸쳐 도달하기 위한 속도값을 구해준다.
	float moveSpeed = (elapsedTime / time) * distance;

	return moveSpeed;
}

void bossMove::startMove(float* time, float* distance, float* angle, float* speed, 
	float* worldTime, POINTFLOAT* _center, POINT* index, BOSS_DIRECTION direction, bool* Move)
{
	float elapsedTime = TIMEMANAGER->getElapsedTime();

	// 원하는 거리에 해당 시간에 도착하려면 얼마의 속도로 이동 해야하는지 계산을 해준다.
	*speed = (elapsedTime / *time) * *distance;

	// 도착지점까지 각도와 속도에 맞춰서 원하는 시간에 도달하게 한다.
	(*_center).x = (*_center).x + cosf(*angle) * *speed;
	(*_center).y = (*_center).y + (-sinf(*angle) * *speed);

	cout << (*_center).x << endl;
	//cout << *time << endl;
	
	// 만약 해당 시간에 도달했다면
	if (*time + *worldTime <= TIMEMANAGER->getWorldTime())
	{
		//*worldTime = TIMEMANAGER->getWorldTime(); // ? 이건 왜?
	
		// 방향에 맞게 index의 값을 수정해준다.
		switch (direction)
		{
		case BD_LEFT:
			(*index).x--;
			break;
	
		case BD_UP:
			(*index).y--;
			break;
	
		case BD_RIGHT:
			(*index).x++;
			break;
	
		case BD_DOWN:
			(*index).y++;
			break;
		}

		// 위치 보정하고, Move를 꺼준다.
		(*_center).x = (*index).x * *distance + (*distance / 2);
		(*_center).y = (*index).y * *distance + (*distance / 2);
	
		*Move = false;
	}
}

