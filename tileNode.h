#pragma once

#define TESTTILEX 30
#define TESTTILEY 30
//=========================================
//한 타일의 사이즈는 32로 한다. 32 X 32
#define TILESIZE 52

//타일셋 범위(타일을 찍어올 팔레트 같은 역할)
#define SAMPLETILEX 20
#define SAMPLETILEY 9

//요샌 잘 안하는것들중인데, 넷마블에서 몇몇개 스튜디오는 쓴다고 카더라
//예전에 메모리 용량이 작을때 메모리 아낀다구 쓰던 방식이 비트필드

#define ATTR_UNMOVE 0x00000001
#define ATTR_SWAMP  0x00000002
#define ATTR_POISON 0x00000004
#define ATTR_FROZEN 0x00000008

//팀프로젝트할땐 걍 이넘으로 속성처리해도 무방할듯


//영주 MAPTOOP 

#define TESTTILESIZE 52

//타일 갯수는 가로 100 / 세로 100
#define TILEX 20
#define TILEY 20

//타일 총 사이즈는 640 X 640
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//지형타일셋 범위(타일을 찍어올 팔레트 같은 역할)
#define TERRAINTILEX 6
#define TERRAINTILEY 6

//벽타일셋 범위(타일을 찍어올 팔레트 같은 역할)
#define WALLTILEX 16
#define WALLTILEY 4

//타일셋 범위(타일을 찍어올 팔레트 같은 역할)
#define TRAPTILEX 6
#define TRAPTILEY 7

#define ROBYSIZE 40 * 40
#define STAGESIZE 100 * 100
#define BOSSSTAGESIZE 40 * 80

enum STAGE
{
	LOBY_STAGE,
	BASIC_STAGE,
	BOSSS_STAGE
};
//지형
enum TERRAIN
{
	TR_BASIC_STAGE_TILE, TR_BASIC_COMBO_TILE,
	TR_BOSS_STAGE_TILE, TR_BOSS_COMBO_TILE,
	TR_STAIR, TR_SHOP,
	TR_NONE,
	TR_END,
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER
};

//벽 
enum WALL
{
	W_WALL, W_ITEM_WALL, W_WALL2, W_SHOP_WALL,		//기본 벽, 아이템이 들어있는 벽, 
	W_END_WALL, W_BOSS_WALL,						//부셔지지 않는 벽
	W_DOOR, W_TORCH, W_FIRE_WALL,					//문. 토치, 불 기둥
	W_NONE											//나중에 지울용도
};

//오브젝트
enum OBJECT
{
	OBJ_ENEMY,										//적
	OBJ_FLOOR_OBJECT,								//바닦에 뿌려지는 오브젝트
	OBJ_WEAPON, W_ARMOR								//아이탬(방어구)
};

enum TRAP
{
	TRAP_FAST_BEAT, TRAP_SLOW_BEAT, TRAP_MUTE,		//리듬 템포 함정 및 음소거 함정
	TRAP_LT_JUMP, TRAP_T_JUMP, TRAP_RT_JUMP,		// 대각선 포함 상하좌우 점프 함정
	TRAP_L_JUMP, TRAP_R_JUMP,
	TRAP_LB_JUMP, TRAP_B_JUMP, TRAP_RB_JUMP,
	TRAP_CONFUSE,									//혼란 함정
	TRAP_BOMB,										//폭탄 함정
	TRAP_NIDDLE,									//가시 함정
	TRAP_SHADOW, TRAP_NIDDLE_SHADOW,				//함정 그림자
	TRAP_NONE
};

//position
enum POS
{
	POS_PLAYER
};

struct tagTile
{
	TERRAIN terrain;		//지형
	WALL wall;				//벽
	TRAP trap;				//함정
	OBJECT obj;				//오브젝트
	RECT rc;				//렉트
	int terrainFrameX;		//터레인 번호
	int terrainFrameY;		//터레인 번호
	int wallFrameX;			//벽 번호
	int wallFrameY;			//벽 번호
	int charFrameX;			//캐릭터 번호
	int charFrameY;			//캐릭터 번호
	int enemyFrameX;		//적 번호
	int enemyFrameY;		//적 번호
	int	floorObjFrameX;		//바닦 오브젝트 번호
	int floorObjFrameY;		//바닦 오브젝트 번호
	int itemFrameX;			//아이템 번호
	int itemFrameY;			//아이템 번호
	int trapFrameX;			//함정 번호
	int trapFrameY;			//함정 번호
	
	int alphaValue;			//시야 값 정하기 위한 알파 블랜더 변수
	bool alphaEyesight;			//플레이어 시야
	
	bool isRender;

	int idX;
	int idY;
	POINT XY;
};

//타일셋 
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};

//현재 타일 == 내가 클릭한 현재타일 정보를 저장할 구조체
struct tagCurrentTile
{
	int x;
	int y;
};

struct tagButton
{
	RECT rc;
	POINT XY;
};