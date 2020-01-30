#include "stdafx.h"
#include "miniMap.h"

miniMap::miniMap()
{
}

miniMap::~miniMap()
{
}

HRESULT miniMap::init()
{
	// 가로 세로 52 -> 2로 변환  40 x 40 타일의 개수  
	// 
	// 미니맵의 크기 ( )
	// x, y -> rc left top  비율로 줄여 => 그리기  




	return S_OK;
}

void miniMap::release()
{

}

void miniMap::update()
{
}

void miniMap::render()
{
	int i = -1;

	for (_viStageMap = _vStageMap.begin(); _viStageMap != _vStageMap.end(); ++_viStageMap)
	{
		i++;
		if ((*_viStageMap)->type == TYPE_NONE) continue;
		if ((*_viStageMap)->terrain != TR_NONE)
		{
			if ((*_viStageMap)->alphaEyesight)
			{
				IMAGEMANAGER->findImage("terrainTiles")->frameRender(CAMERAMANAGER->getWorldDC(), 
					(*_viStageMap)->rc.left, (*_viStageMap)->rc.top, (*_viStageMap)->terrainFrameX, (*_viStageMap)->terrainFrameY);

				
						HBRUSH brush = CreateSolidBrush(RGB(255, 1, 2));
						HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
						RECT temp;
						temp = RectMake(750+(i%130*4), 450+(i/130*4),
							4, 4);
						Rectangle(getMemDC(), temp);
						SelectObject(getMemDC(), oldBrush);
						DeleteObject(brush);
				
			}
			else
			{
				IMAGEMANAGER->findImage("terrainTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(),
					(*_viStageMap)->rc.left, (*_viStageMap)->rc.top, (*_viStageMap)->terrainFrameX, (*_viStageMap)->terrainFrameY, (*_viStageMap)->alphaValue);
				//안밝혀진 부분
			}
			continue;
		}
	}
	//// 이외의 렌더 
	for (_viStageMap = _vStageMap.begin(); _viStageMap != _vStageMap.end(); ++_viStageMap)
	{
		if ((*_viStageMap)->type == TYPE_NONE) continue;
		if ((*_viStageMap)->alphaValue <= 0)
		{
			if ((*_viStageMap)->wall != W_NONE)
			{
				IMAGEMANAGER->findImage("wallTiles")->frameRender(CAMERAMANAGER->getWorldDC(), (*_viStageMap)->rc.left, (*_viStageMap)->rc.top - 52, (*_viStageMap)->wallFrameX, (*_viStageMap)->wallFrameY);
				continue;
			}
			if ((*_viStageMap)->trap != TRAP_NONE)
			{
				IMAGEMANAGER->findImage("trapTiles")->frameRender(CAMERAMANAGER->getWorldDC(), (*_viStageMap)->rc.left, (*_viStageMap)->rc.top, (*_viStageMap)->trapFrameX, (*_viStageMap)->trapFrameY);
				continue;
			}
		}
		else
		{
			if ((*_viStageMap)->wall != W_NONE)
			{
				IMAGEMANAGER->findImage("wallTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), (*_viStageMap)->rc.left, (*_viStageMap)->rc.top, (*_viStageMap)->wallFrameX, (*_viStageMap)->wallFrameY, (*_viStageMap)->alphaValue);
				continue;
			}
			if ((*_viStageMap)->trap != TRAP_NONE)
			{
				IMAGEMANAGER->findImage("trapTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), (*_viStageMap)->rc.left, (*_viStageMap)->rc.top, (*_viStageMap)->trapFrameX, (*_viStageMap)->trapFrameY, (*_viStageMap)->alphaValue);
				continue;
			}
		}
	}

}
