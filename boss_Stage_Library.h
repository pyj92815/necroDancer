#pragma once
#include "stdafx.h"

struct BOSS_STAGE_EFFECT_VECTOR
{
	image*		 img;			// 뿌려질 이펙트 이미지를 담는다.
	RECT         rc;			// 렉트 좌표
	POINTFLOAT	 center;		// 중점 좌표

	int			 Max_FrameX;	// 이미지의 맥스 프레임
};


enum class FIND_CHOICE_XY
{
	FC_XY,						// 양방향 찾기
	FC_X,						// x방향 찾기
	FC_Y						// y방향 찾기
};

enum class FIND_ANGLE
{
	FA_RT,						// 2시
	FA_TL,						// 10시
	FA_LB,						// 7시
	FA_BR						// 5시
};

enum class SHORT_XY
{
	SHORT_NONE,					// NULL
	SHORT_X,					// x가 짧다.
	SHORT_Y						// y가 짧다
};