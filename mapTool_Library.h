#pragma once
#include "stdafx.h"

#define SCREENMOVESPEED 5

// ���� �ȷ�Ʈ 
struct MovePalette
{
	RECT terrainTile;
	RECT wallTile;
	RECT trapTile;
	POINT pos_Start;	// ���콺�� Ŭ���� ���� ��ǥ�� ��Ƶд�.
	POINT pos_End;		// ���콺�� ���� ��ġ ��ǥ�� ��Ƶд�.
	bool isClick;		// ���콺�� �������� �� ��������
	bool choice;		// �׸��� ���ϴ� �̹����� Ŭ�� �ߴ�.
};
