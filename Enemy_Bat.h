#pragma once
#include"Enemy.h"
class Enemy_Bat:public Enemy
{
public:
	HRESULT init();
	void Action();
	void Move();
	void AniChange();
};

