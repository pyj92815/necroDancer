#pragma once
#include "Enemy.h"
class Enemy_Skeleton:public Enemy
{
public:
	HRESULT init();
	void Move();
	void AniChange();
};

