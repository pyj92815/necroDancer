#pragma once

class Enemy;

enum PLAYERDIRECTION			// 플레이어의 방향
{
	PLAYERDIRECTION_UP,		
	PLAYERDIRECTION_DOWN,
	PLAYERDIRECTION_LEFT,
	PLAYERDIRECTION_RIGHT
};

enum PLAYERWAEPON				// 플레이어의 무기
{
	PLAYERWAEPON_NONE,			// 무기없음
	PLAYERWAEPON_SPEAR,			// 롱스피어
	PLAYERWAEPON_DAGGER,		// 단검
	PLAYERWAEPON_RAPIER,		// 레이피어
	PLAYERWAEPON_LONGSWORD,		// 롱소드
	PLAYERWAEPON_BROADSWORD,	// 브로드소드
};

struct tagPlayer				//플레이어의 정보
{
	PLAYERDIRECTION direction;	// 방향   
	PLAYERWAEPON weapon;		// 무기 
	animation* headAni;			// 머리 애니매이션
	animation* bodyAni;			// 몸   애니매이션 
	image* headImage;			//	    이미지 
	image* bodyImage;			//      이미지 
	RECT rc;					// RECT
	float x, y;					// 좌표 값(X,Y)  
	float maxHp;				// 최대 HP
	float hp;					// hp
	float armor;				// 방어
	int idx, idy;				// 인덱스 (idx,idy)
	int sight;					// 시야값
};