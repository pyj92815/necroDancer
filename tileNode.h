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


//영주 MAPTOOL

#define TESTTILESIZE 52

//타일 갯수는 가로 100 / 세로 100
#define TILEX 40
#define TILEY 40

//타일 총 사이즈는 2080 X 2080
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//지형 타일 셋 범위(타일을 찍어올 팔레트 같은 역할)
#define TERRAINTILEX 6
#define TERRAINTILEY 6

//벽 타일 셋 범위(타일을 찍어올 팔레트 같은 역할)
#define WALLTILEX 16
#define WALLTILEY 4

//함정 타일 셋 범위(타일을 찍어올 팔레트 같은 역할)
#define TRAPTILEX 6
#define TRAPTILEY 7

//아이템 타일 셋 범위(타일을 찍어올 팔레트 같은 역할)
#define ITEMTILEX 4
#define ITEMTILEY 5

//아이템 타일 셋 범위(타일을 찍어올 팔레트 같은 역할)
#define CHARACTERTILEX 4
#define CHARACTERTILEY 4

#define ROBYSIZE 40 * 40
#define STAGESIZE 100 * 100
#define BOSSSTAGESIZE 40 * 80

//미니맵 타일 사이즈
#define MINTILESIZE 15

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
	W_DOOR,											//문. 토치, 불 기둥
	W_NONE											//나중에 지울용도
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

//아이템
enum ARMOR
{
	//방어구
	A_HELMET, A_SHOVEL,
	A_ARMOR_1, A_ARMOR_2, A_ARMOR_3, A_ARMOR_4,
	A_BOOTS,
	A_RING,
	A_TORCH_1, A_TORCH_2, A_TORCH_3, 
	A_NONE
};
enum WEAPON
{
	//무기
	WP_DAGGER_1, WP_DAGGER_2, WP_RAPIER, WP_BROAD_SWORD,
	WP_BOMB, WP_RIFLE, WP_SHOTGUN,
	WP_SPEAR, WP_MACE,WP_LONG_SWORD,
	WP_WHIP, WP_NINETAILS_WHIP,
	WP_BOW, WP_CROSS_BOW,
	WP_NONE
};

enum STUFF
{
	ST_DIAMOND,
	ST_ONE_COIN, ST_ONE_HALF_COIN,
	ST_COINS, ST_MORE_COINS,
	ST_APPLE, ST_CHEESE, ST_MEAT,
	ST_NONE,
};

enum OBJECT
{
	OBJ_WATER,										//바닦에 뿌려지는 오브젝트
	OBJ_FALLING_DOOR,								//떨어지는 바닦
};

enum CHARACTER
{
	CHAR_PLAYER,									//플레이어
	CHAR_BAT, 
	CHAR_SLIME_BLUE, CHAR_SLIME_ORANGE, 
	CHAR_GHOST, CHAR_WRAITH,
	CHAR_SKELETON, CHAR_SKELETON_YELLOW, CHAR_ZOMBIE,
	CHAR_MINO, CHAR_DRAGON, CHAR_BOSS,
	CHAR_NONE,
};

//position
enum POS
{
	POS_PLAYER
};

enum TYPE
{
	TYPE_TERRAIN,
	TYPE_WALL,
	TYPE_TRAP,
	TYPE_ITEM_ARMOR, TYPE_ITEM_WEAPON, TYPE_ITEM_STUFF,
	TYPE_OBJECT,
	TYPE_CHARACTER,
	TYPE_NONE
};

struct tagTile
{
	TYPE type;				//상태
	TERRAIN terrain;		//지형
	WALL wall;				//벽
	TRAP trap;				//함정
	ARMOR armor;				//방어구
	WEAPON weapon;			//무기
	OBJECT obj;				//오브젝트
	CHARACTER character;	//캐릭터
	STUFF stuff;			//소지품
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
	int armorFrameX;			//아이템 번호
	int armorFrameY;			//아이템 번호
	int weaponFrameX;			//아이템 번호
	int weaponFrameY;			//아이템 번호
	int stuffFrameX;			//아이템 번호
	int stuffFrameY;			//아이템 번호
	int characterFrameX;
	int characterFrameY;
	int trapFrameX;			//함정 번호
	int trapFrameY;			//함정 번호
	
	int alphaValue;			//시야 값 정하기 위한 알파 블랜더 변수
	bool alphaEyesight;		//플레이어 시야
	
	bool isRender;

	int idX;
	int idY;
	POINT XY;
};

//타일셋 
struct tagSetTile
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
	bool isClick;
};

struct tagMouse
{
	RECT rc;
	POINT XY;
};

// 락훈 추가
enum EFFECTTYPE
{
	TIMESLOW,// 시간이 지나면 사라짐				// 삽    
	SLOW,	 // 서서히 위로 올라가면서 사라짐		// 빗나감
	STOP,	 // 가만히 자리에서 사라짐			// 비트
	FRAMEIMAGE,
};

