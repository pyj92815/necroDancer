#pragma once
#include"Enemy.h"
class Enemy_Warith:public Enemy
{
public:
	HRESULT init();
	void Move();
	void AniChange();
};

