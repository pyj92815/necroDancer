#pragma once
#include"Enemy.h"
class Enemy_Slime_Orange:public Enemy
{
private:
	bool light_change;
public:
	HRESULT init();
	void Action();
	void Move();
	void Attack();
	void AniChange();
};

