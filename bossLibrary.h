#pragma once
#include "stdafx.h"


// 보스 종류
enum BOSSTYPE
{
	EMPTY,
	DEATH_METAL
};

// 보스 페이즈 종류
enum BOSS_PHASESTATE	// 보스의 페이즈 상태
{
	BP_NORMAL,
	BP_PHASE_1,
	BP_PHASE_2,
	BP_PHASE_3,
	BP_PHASE_4
};

// 보스 방향 종류
enum BOSS_DIRECTION		// 보스의 방향
{
	BD_LEFT,
	BD_UP,
	BD_RIGHT,
	BD_DOWN
};

// 데스메탈 실드 좌표에 관한 정보를 담는곳
typedef struct tagThrowShield
{
	RECT			rc;					// 렉트
	POINTFLOAT		center;				// 중점
	image*			image;				// 실드 이미지를 담는다.
	float			angle;				// 날아가는 각도
	float			speed;				// 날아가는 속도
	bool			isShieldUpdate;		// 실드 위치 갱신 유무
	bool			isOut;				// 이 값이 true라면 삭제
	BOSS_DIRECTION	direction;			// 보스가 바라보는 방향을 저장한다. (방향에 따라 방패를 날리는 각도가 다르다.)
}ThrowShield;

// 보스의 점프 함수
struct tagBossJump
{
	float			 jumpPow;							// 점프 변수
	float			 gravity;							// 중력 변수
	POINTFLOAT		 start;								// 시작 위치
	bool			 isJumping;							// 점프중이라면 true
};


struct BOSS_PHASE_SETTING_BOOL
{
	bool PHASE_1_Set;	// 1페이즈 셋팅을 했다면 true로 바꾼다. (1번만 적용하기 위해서)
	bool PHASE_2_Set;	// 2페이즈 셋팅을 했다면 true로 바꾼다. (1번만 적용하기 위해서)
	bool PHASE_3_Set;	// 3페이즈 셋팅을 했다면 true로 바꾼다. (1번만 적용하기 위해서)
	bool PHASE_4_Set;	// 4페이즈 셋팅을 했다면 true로 바꾼다. (1번만 적용하기 위해서)
};

// 보스에서 사용하는 BOOL 값을 모아둔 구조체
struct BOSS_BOOL
{
	BOSS_PHASE_SETTING_BOOL		PHASE_BOOL;

	bool						get_Beat;		// 박자를 받았으면 true로 변한다.
	bool						boss_Die;		// 보스가 죽었다면 true의 값을 가진다.
};

struct BOSS_SUMMONS_SKILL
{
	bool						isCasting;		// 스킬 캐스팅
	int							cTime;			// 쿨타임
	int							cTime_M;		// 콘스트 쿨타임

	int							rnd;			// 랜덤 값
};