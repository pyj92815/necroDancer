#include "stdafx.h"
#include "visionFloodFill.h"

visionFloodFill::visionFloodFill()
{
}

visionFloodFill::~visionFloodFill()
{
}

HRESULT visionFloodFill::init()
{
	return S_OK;
}

void visionFloodFill::release()
{
}

void visionFloodFill::update()
{
}

void visionFloodFill::render()
{
}

void visionFloodFill::setVision(tagTile* tile, int idx, int idy, int sight)
{
	// 재귀함수 
	// 초기 예외처리 
	if (0 > idx || 0 > idy || idx > TILEX || idy > TILEY) return;
	if (sight < 0) return;
	tile[idy * TILEX + idx].alphaEyesight = true;
	bool recursionContinue = true;  // 초기 조건값 
	recursionContinue &= (tile[idy * TILEX + idx].wall == W_NONE);  // 맞춰야 하는 조건 
	//recursionContinue &= (tile[idy * TILEX + idx].alphaEyesight == false);
	//if (_tiles[index.y * TILEX + index.x].type == TYPE_WALL) sight = sight - 3;	// 시야처리에 따른 값 조정할 예정 
	
	
	if (recursionContinue)
	{
		// 예외처리 
		if (tile[idy * TILEX + idx].alphaEyesight)
		{
			if (!tile[idy * TILEX + idx + 1].alphaEyesight)
			{
				setVision(tile, idx + 1, idy, sight - 1);
			}
			else if (tile[idy * TILEX + (idx - 1)].alphaEyesight)
			{
				setVision(tile, idx - 1, idy, sight - 1);
			}
			else if (tile[idy + 1 * TILEX + idx].alphaEyesight)
			{
				setVision(tile, idx, idy + 1, sight - 1);
			}
			else if (tile[(idy - 1) * TILEX + idx].alphaEyesight)
			{
				setVision(tile, idx, idy - 1, sight - 1);
			}
		}

		// 시야값 적용 
		if (sight <= 3)
		{
			tile[idy * TILEX + idx].alphaValue = 150;
		}
		else if (sight > 3 && sight < 5)
		{
			tile[idy * TILEX + idx].alphaValue = 80;
		}
		else
		{
			tile[idy * TILEX + idx].alphaValue = 0;
		}
		setVision(tile, idx, idy - 1, sight - 1);
		setVision(tile, idx, idy + 1, sight - 1);
		setVision(tile, idx - 1, idy, sight - 1);
		setVision(tile, idx + 1, idy, sight - 1);
	}
	else   tile[idy * TILEX + idx].alphaValue = 0;
	
	//	setVision(tile, idx, idy - 1, sight - 1);
	//	setVision(tile, idx, idy + 1, sight - 1);
	//	setVision(tile, idx - 1, idy, sight - 1);
	//	setVision(tile, idx + 1, idy, sight - 1);
	//}
	// 1. 벽 넘어서 까지 시야처리를 어떻게 해야할지 
	// 2. 알파블렌더가 렉에 원인인데 어떻게 할지
}
