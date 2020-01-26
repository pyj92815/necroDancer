#pragma once
#include "stdafx.h"

#define SCREENMOVESPEED 5

// 무브 팔레트 
struct MovePalette
{
	RECT terrainTile;
	RECT wallTile;
	RECT trapTile;
	POINT pos_Start;	// 마우스로 클릭한 지점 좌표를 담아둔다.
	POINT pos_End;		// 마우스의 현재 위치 좌표를 담아둔다.
	bool isClick;		// 마우스를 눌렀는지 안 눌렀는지
	bool choice;		// 그리길 원하는 이미지를 클릭 했다.
};
