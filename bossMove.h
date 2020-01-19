#pragma once
#include "bossLibrary.h"

class bossMove
{
private:
	int xx;
	
public:
	bossMove();
	~bossMove();

	float getMoveSpeed(float time, float distance);		// ���ϴ� �Ÿ��� ���ϴ� �ð��� �����Ϸ��� � ���ǵ�� �����ϴ��� ���� �� �ִ�.

	// ���ϴ� �Ÿ��� ���ϴ� �ð��� �����Ϸ��� � ���ǵ�� �����ϴ��� ���� �� �ִ�.
	// ������ �ӵ��� �̿��Ͽ� �÷��̾ ���ϴ� ������ �̵� ��Ų��.
	// ��ǥ �ð��� �����Ѵٸ� bool���� �ٲ㼭 �������ش�.
	void startMove(float* time, float* distance, float* angle, float* speed,
		float* worldTime, POINTFLOAT* _center, POINT* index, BOSS_DIRECTION direction, bool* Move);

};

