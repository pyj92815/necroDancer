#pragma once
#include "gameNode.h"


class itemManager : public gameNode
{
private:
	struct ITEM
	{
		int frameX;
		int frameY;
		float x;
		float y;
		int x;
		int y;
	};

	vector<itemManager::ITEM> _vItem;

public:

	itemManager();
	~itemManager();
	
	HRESULT init();
	void release();
	void update();
	void render();

	void crateItem();

};

