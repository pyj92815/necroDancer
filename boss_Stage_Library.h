#pragma once
#include "stdafx.h"

struct BOSS_STAGE_EFFECT_VECTOR
{
	image*		 img;			// 뿌려질 이펙트 이미지를 담는다.
	RECT         rc;			// 렉트 좌표
	POINTFLOAT	 center;		// 중점 좌표

	int			 Max_FrameX;	// 이미지의 맥스 프레임
};
