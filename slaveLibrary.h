#pragma once
#include "stdafx.h"

// 슬레이브 종류
enum class SLAVE_TYPE
{
	SLAVE_BAT,
	SLAVE_GHOST,
	SLAVE_SKELETON,
	SLAVE_SKELETON_YELLOW,
	SLAVE_NONE
};

// 슬레이브 방향
enum class SLAVE_DIRECTION
{
	SD_LEFT,
	SD_UP,
	SD_RIGHT,
	SD_DOWN,
	SD_NONE
};

// 슬레이브의 상태
enum class SLAVE_STATE
{
	SS_NONE,										// 정해진 상태가 없다
	SS_STAY,										// 슬레이브는 대기 상태	(플레이어가 고스트를 바라 봤을때 고스트는 대기 상태, 공격이 통하지 않는다)
	SS_PLAYER_ATTACK,								// 슬레이브가 플레이어를 추격
	SS_RUN											// 도망가는 상태			(해골의 머리가 사라졌을때 해골은 플레이어 반대 방향으로 도주 상태)
};

// 슬레이브의 능력치
struct SLAVE_STATUS
{
	SLAVE_TYPE			type;						// 슬레이브의 타입을 담는다.
	SLAVE_DIRECTION		direction;					// 슬레이브가 바라보는 방향을 담는다.
	SLAVE_DIRECTION		save_Direction;				// 슬레이브 방향 세이브 변수

	int					hp;							// 슬레이브의 체력을 담는다.
	float				attack;						// 슬레이브의 공격력을 담는다.
};

// 슬레이브의 좌표
struct SLAVE_POS
{
	RECT				rc;							// 슬레이브 렉트
	POINTFLOAT			center;						// 슬레이브 중심 좌표
	POINT				index;						// 슬레이브 타일 인덱스 
};

// 슬레이브의 이미지
struct SLAVE_IMAGE
{
	animation*			animation;					// 슬레이브의 애니메이션을 담는다.
	image*				img;						// 슬레이브의 이미지를 담는다.
};

// 불의 마을
struct SLAVE_BOOL
{
	bool				isClosePlayer;				// 슬레이브 근처에 플레이어가 있는지 없는지 여부.
	bool				save_ClosePlayer;			// 슬레이브가 근처에 있는지 세이브를 한다.
	bool				isChangeAni;				// 움직였다면 애니메이션을 바꿔줘야한다.
	bool				change_Ani;					// 애니메이션을 체인지가 가능한지 여부
	bool				distanceCheck;				// 플레이어와 거리 체크 
	
	bool				ghostMoveStop;				// 고스트 움직임 정지
	bool				ghostImgDirection;			// 고스트 이미지 방향
	bool				ghostJonYha;				// 고스트가 투명일땐 무적이다.

	bool				isMove;						// 무브 여부

	bool				beat;						// 비트를 받았다면 ture

	bool				isAttack;					// 공격 가능할때 true
};

// 슬레이브의 연산 변수
struct SLAVE_OPERATION
{
	// 타일 사이즈
	int					tile_SizeX, tile_SizeY;		// 타일의 사이즈를 담아둔다.

	// 이동
	float				angle;						// 이동에 쓰일 각도
	int					move_Count;					// 이동 카운트 (몇 박자마다 움직이는지)
	int					save_Move_Count;			// 이동 카운트를 저장 해 둔다.
	float				move_Time;					// 다음 타일까지 이동에 걸리는 시간
	float				move_Speed;					// 다음 타일까지 이동하는 속도
	float				move_Distance;				// 다음 타일까지의 거리
	float				worldTime;					// 월드 타임

};



// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 슬레이브의 정보 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
struct SLAVE_INFO
{
	SLAVE_STATUS		status;						// 슬레이브 스테이터스
	SLAVE_POS			pos;						// 슬레이브 좌표
	SLAVE_IMAGE			image;						// 슬레이브 이미지
	SLAVE_OPERATION		operation;					// 슬레이브 연산
	SLAVE_BOOL			b_Value;					// 슬레이브 bool값 
				
};






// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 슬레이브의 함수 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
class slaveLibrary
{

public:

	void slave_Reset(SLAVE_INFO* slave)												// 슬레이브의 변수를 기본 상태로 만든다.
	{
		// 스테이터스 초기화
		slave->status.type = SLAVE_TYPE::SLAVE_NONE;
		slave->status.direction = SLAVE_DIRECTION::SD_NONE;
		slave->status.hp = 1;														// 기본 체력은 1 이다.
		slave->status.attack = 1.f;													// 기본 공격력은 0.5f 이다.

		// 좌표 초기화
		slave->pos.index.x = slave->pos.index.y = 0;								// 기본 인덱스는 0이다.
		slave->pos.center.x = slave->pos.center.y = 0;								// 기본 중점은 0이다.
		slave->pos.rc = RectMake(0, 0, 0, 0);										// 기본 렉트는 0이다.

		// 연산 변수 초기화
		slave->operation.angle = 0;													
		slave->operation.move_Count = 0;	
		slave->operation.save_Move_Count = 0;
		slave->operation.move_Distance = 0;											
		slave->operation.move_Speed = 0;											
		slave->operation.move_Time = 0.2f;											
		slave->operation.worldTime = 0;												
		slave->operation.tile_SizeX = TILESIZE;										
		slave->operation.tile_SizeY = TILESIZE;				

		// bool 변수 초기화
		slave->b_Value.change_Ani = false;
		slave->b_Value.isChangeAni = false;
		slave->b_Value.isClosePlayer = false;
		slave->b_Value.save_ClosePlayer = false;
		slave->b_Value.distanceCheck = false;
		slave->b_Value.isMove = false;
		slave->b_Value.isAttack = false;
		slave->b_Value.ghostMoveStop = false;
		slave->b_Value.ghostImgDirection = false;
		slave->b_Value.ghostJonYha = false;

		// 이미지, 애니메이션 할당
		slave->image.img = new image;
		slave->image.animation = new animation;
	}




	void slave_Setting(SLAVE_INFO* slave, SLAVE_TYPE(type))							// 슬레이브의 타입에 맞게 스테이터스를 만들어준다.
	{

		switch (type)
		{
		case SLAVE_TYPE::SLAVE_BAT:
			slave->status.type = SLAVE_TYPE::SLAVE_BAT;								// 슬레이브의 타입을 정해준다.
			slave->status.direction = SLAVE_DIRECTION::SD_DOWN;						// 기본 방향은 아래를 향한다.
			slave->status.hp = 1;													// 기본 체력을 정해준다.
			slave->image.img = IMAGEMANAGER->findImage("boss_Bat");					// 슬레이브의 이미지를 찾아서 넣어준다.
			slave->image.animation = KEYANIMANAGER->findAnimation("sBat_Left");		// 슬레이브의 애니메이션을 찾아서 넣어준다.
			slave->operation.move_Count = 3;										// 슬레이브의 이동 박자
			slave->operation.save_Move_Count = 3;									// 슬레이브의 세이브 박자
			
			break;

		case SLAVE_TYPE::SLAVE_GHOST:
			slave->status.type = SLAVE_TYPE::SLAVE_GHOST;							// 슬레이브의 타입을 정해준다.
			slave->status.direction = SLAVE_DIRECTION::SD_DOWN;						// 기본 방향은 아래를 향한다.
			slave->status.hp = 1;													// 기본 체력을 정해준다.
			slave->image.img = IMAGEMANAGER->findImage("boss_Ghost");				// 슬레이브의 이미지를 찾아서 넣어준다.
			slave->image.animation = KEYANIMANAGER->findAnimation("sGhost_Left");	// 슬레이브의 애니메이션을 찾아서 넣어준다.
			slave->operation.move_Count = 1;										// 슬레이브의 이동 박자
			slave->operation.save_Move_Count = 1;									// 슬레이브의 세이브 박자

			break;

		case SLAVE_TYPE::SLAVE_SKELETON:
			slave->status.type = SLAVE_TYPE::SLAVE_SKELETON;						// 슬레이브의 타입을 정해준다.
			slave->status.direction = SLAVE_DIRECTION::SD_DOWN;						// 기본 방향은 아래를 향한다.
			slave->status.hp = 2;													// 기본 체력을 정해준다.
			slave->image.img = IMAGEMANAGER->findImage("boss_Skeleton");			// 슬레이브의 이미지를 찾아서 넣어준다.
			slave->image.animation = KEYANIMANAGER->findAnimation("sSkel_Left");		// 슬레이브의 애니메이션을 찾아서 넣어준다.
			slave->operation.move_Count = 2;										// 슬레이브의 이동 박자
			slave->operation.save_Move_Count = 2;									// 슬레이브의 세이브 박자

			break;

		case SLAVE_TYPE::SLAVE_SKELETON_YELLOW:
			slave->status.type = SLAVE_TYPE::SLAVE_SKELETON_YELLOW;					// 슬레이브의 타입을 정해준다.
			slave->status.direction = SLAVE_DIRECTION::SD_DOWN;						// 기본 방향은 아래를 향한다.
			slave->status.hp = 2;													// 기본 체력을 정해준다.
			slave->image.img = IMAGEMANAGER->findImage("boss_Skeleton_Yellow");		// 슬레이브의 이미지를 찾아서 넣어준다.
			slave->image.animation = KEYANIMANAGER->findAnimation("sSkelY_Left");	// 슬레이브의 애니메이션을 찾아서 넣어준다.
			slave->operation.move_Count = 2;										// 슬레이브의 이동 박자
			slave->operation.save_Move_Count = 2;									// 슬레이브의 세이브 박자

			break;

		case SLAVE_TYPE::SLAVE_NONE:
			slave->status.type = SLAVE_TYPE::SLAVE_NONE;							// 슬레이브의 타입을 정해준다.
			slave->status.direction = SLAVE_DIRECTION::SD_DOWN;						// 기본 방향은 아래를 향한다.
			slave->status.hp = 1;													// 기본 체력을 정해준다.
			slave->image.img = IMAGEMANAGER->findImage("boss_Bat");					// 슬레이브의 이미지를 찾아서 넣어준다.
			slave->image.animation = KEYANIMANAGER->findAnimation("sBat_Left");		// 슬레이브의 애니메이션을 찾아서 넣어준다.

			break;
		}

	}




	void pos_Setting(SLAVE_INFO* slave, int idx, int idy)					// 슬레이브의 좌표 변수들을 만들어준다.
	{
		// 인덱스 초기화
		slave->pos.index.x = idx;
		slave->pos.index.y = idy;

		// 렉트 초기화
		slave->pos.rc = RectMake(idx * TILESIZE, idy * TILESIZE, TILESIZE, TILESIZE);

		// 중점 초기화
		slave->pos.center.x = (slave->pos.rc.left + slave->pos.rc.right) / 2;
		slave->pos.center.y = (slave->pos.rc.top + slave->pos.rc.bottom) / 2;
	}

};


