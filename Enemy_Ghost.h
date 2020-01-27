#pragma once
#include"Enemy.h"
class Enemy_Ghost:public Enemy
{
public:
	HRESULT init();
	void AniChange();
};

