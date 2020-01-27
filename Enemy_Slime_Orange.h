#pragma once
#include"Enemy.h"
class Enemy_Slime_Orange:public Enemy
{
public:
	HRESULT init();
	void Move();
	void AniChange();
};

