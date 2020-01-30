#pragma once
#include "gameNode.h"

class visionFloodFill : public gameNode
{

public:
	visionFloodFill();
	~visionFloodFill();

	HRESULT init();
	void release();
	void update();
	void render();

	void setVision(tagTile* tile, int idx, int idy, int sight);
};

