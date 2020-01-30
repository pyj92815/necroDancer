#pragma once
#include"Enemy.h"
class Enemy_Bat:public Enemy
{
public:
	void Action();
	void Move();
	void RandDirection();
	void AniChange();
};

