#pragma once
#include"gameNode.h"

class Enemy:public gameNode
{
protected:
	
public:
	Enemy() {};
	~Enemy() {};

	virtual HRESULT init();
	virtual void relase();
	virtual void update();
	virtual void render();
};

