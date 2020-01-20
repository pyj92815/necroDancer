#pragma once
#include "bossLibrary.h"

class bossMove
{
private:
	
public:
	bossMove();
	~bossMove();

	float getMoveSpeed(float time, float distance);		// ���ϴ� �Ÿ��� ���ϴ� �ð��� �����Ϸ��� � ���ǵ�� �����ϴ��� ���� �� �ִ�.

	// ���ϴ� �Ÿ��� ���ϴ� �ð��� �����Ϸ��� � ���ǵ�� �����ϴ��� ���� �� �ִ�.
	// ������ �ӵ��� �̿��Ͽ� �÷��̾ ���ϴ� ������ �̵� ��Ų��.
	// ��ǥ �ð��� �����Ѵٸ� bool���� �ٲ㼭 �������ش�.
	void startMove(float* time, float* distance, float* angle, float* speed,
		float* worldTime, POINTFLOAT* _center, POINT* index, BOSS_DIRECTION direction, bool* Move);

	// ������ ������ �̿��Ͽ� ��� �������� �̵��� �ϴ����� ���� �� �ִ�.
	// ������ ���� x, y�� �̿��Ͽ� ��ġ ����� �Ѵ�.
	// ������ ���� �����ϴ��߿� �ʿ��� ������ �̿��Ѵ�. (�ӵ�, �߷� ��)
	void jumping(BOSS_DIRECTION* direction, POINTFLOAT* center, tagBossJump* jump);
};

