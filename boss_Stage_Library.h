#pragma once
#include "stdafx.h"

struct BOSS_STAGE_EFFECT_VECTOR
{
	image*		 img;			// �ѷ��� ����Ʈ �̹����� ��´�.
	RECT         rc;			// ��Ʈ ��ǥ
	POINTFLOAT	 center;		// ���� ��ǥ

	int			 Max_FrameX;	// �̹����� �ƽ� ������
};
