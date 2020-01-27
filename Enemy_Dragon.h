#pragma once
#include "Enemy.h"
class Enemy_Dragon:public Enemy
{
public:
	HRESULT init();
	void AniChange();
};

