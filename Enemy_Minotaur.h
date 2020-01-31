#pragma once
#include"Enemy.h"
class Enemy_Minotaur:public Enemy
{
public:
	HRESULT init();
	void Move();
	void AniChange();
};

