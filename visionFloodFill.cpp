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
	// ����Լ� 
	// �ʱ� ����ó�� 
	if (0 > idx || 0 > idy || idx > TILEX || idy > TILEY) return;
	if (sight <= 0) return;

	bool recursionContinue = true;  // �ʱ� ���ǰ� 
	recursionContinue &= (tile[idy * TILEX + idx].wall == W_NONE);  // ����� �ϴ� ���� 
	//if (_tiles[index.y * TILEX + index.x].type == TYPE_WALL) sight = sight - 3;	// �þ�ó���� ���� �� ������ ���� 

	if (recursionContinue)
	{
		tile[idy * TILEX + idx].alphaValue = 0;
		tile[idy * TILEX + idx].alphaEyesight = true;
		setVision(tile, idx, idy - 1, sight - 1);
		setVision(tile, idx, idy + 1, sight - 1);
		setVision(tile, idx - 1, idy, sight - 1);
		setVision(tile, idx + 1, idy, sight - 1);
	}
	else 	tile[idy * TILEX + idx].alphaValue = 0;
	// 1. �� �Ѿ ���� �þ�ó���� ��� �ؾ����� 
	// 2. ���ĺ����� ���� �����ε� ��� ����
}
