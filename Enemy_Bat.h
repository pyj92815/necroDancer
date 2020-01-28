#pragma once
#include"Enemy.h"
class Enemy_Bat:public Enemy
{
private:

	int count;

public:
	HRESULT init();
	void Action();
	void Move();
	void AniChange();
};

