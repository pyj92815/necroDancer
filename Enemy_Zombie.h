#pragma once
#include"Enemy.h"

class Enemy_Zombie:public Enemy
{
public:
	HRESULT init();
	void Move();
	void AniChange();
};

