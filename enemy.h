#pragma once
#include"animation.h"
#include"gameNode.h"
#include<vector>
struct info
{
	image* image;
};

class Enemy:public gameNode
{
protected:
	vector<info> _vInfo;
	vector<info>::iterator _viInfo;


public:
	Enemy() {};
	~Enemy() {};

	virtual HRESULT init();
	virtual void relase();
	virtual void update();
	virtual void render();
};

