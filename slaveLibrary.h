#pragma once

// 슬레이브 종류
enum SLAVE_TYPE
{
	SLAVE_BAT,
	SLAVE_GHOST,
	SLAVE_SKELETON,
	SLAVE_SKELETON_YELLOW,
	SLAVE_NONE
};

// 슬레이브 방향
enum SLAVE_DIRECTION
{
	SD_LEFT,
	SD_UP,
	SD_RIGHT,
	SD_DOWN,
	SD_NONE
};

// 슬레이브의 상태
enum SLAVE_STATE
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
	image*				image;						// 슬레이브의 이미지를 담는다.
};

// 슬레이브의 연산 변수
struct SLAVE_OPERATION
{
	// 타일 사이즈
	int					tile_SizeX, tile_SizeY;		// 타일의 사이즈를 담아둔다.

	// 이동
	float				angle;						// 이동에 쓰일 각도
	int					move_Count;					// 이동 카운트 (몇 박자마다 움직이는지)
	float				move_Tile;					// 다음 타일까지 이동에 걸리는 시간
	float				move_Speed;					// 다음 타일까지 이동하는 속도
	float				move_Distance;				// 다음 타일까지의 거리
	float				worldTile;					// 월드 타임

};



//// 슬레이브의 함수
//struct SLAVE_FUNC
//{
//	void slave_Setting(SLAVE_INFO* slave);
//
//};

// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 슬레이브의 정보 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
struct SLAVE_INFO
{
	SLAVE_STATUS		status;						// 슬레이브 스테이터스
	SLAVE_POS			pos;						// 슬레이브 좌표
	SLAVE_IMAGE			image;						// 슬레이브 이미지
	SLAVE_OPERATION		operation;					// 슬레이브 연산

	//SLAVE_FUNC			func;						// 슬레이브의 함수
};




//// 슬레이브 함수 정의
//void SLAVE_FUNC::slave_Setting(SLAVE_INFO* slave)
//{
//	// 스테이터스 초기화
//	slave->status.type = SLAVE_NONE;
//	slave->status.direction = SD_NONE;
//	slave->status.hp = 1;							// 기본 체력은 1 이다.
//	slave->status.attack = 1.f;						// 기본 공격력은 0.5f 이다.
//	
//	// 좌표 초기화
//	slave->pos.index.x = slave->pos.index.y = 0;		// 기본 인덱스는 0이다.
//	slave->pos.center.x = slave->pos.center.y = 0;	// 기본 중점은 0이다.
//	slave->pos.rc = RectMake(0, 0, 0, 0);			// 기본 렉트는 0이다.
//
//	// 이미지 초기화
//	slave->image.animation = new animation;			// 애니메이션 공간 할당
//	slave->image.image = new image;					// 이미지 공간 할당
//}