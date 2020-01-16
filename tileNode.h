#pragma once

//한 타일의 사이즈는 32로 한다. 32 X 32
#define TILESIZE 32

//타일 갯수는 가로 20 / 세로 20
#define TILEX 20
#define TILEY 20

//타일 총 사이즈는 640 X 640
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

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


//지형
enum TERRAIN
{
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_END
};

enum OBJECT
{
	OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS,	//벽돌 등 오브젝트
	OBJ_FLAG1, OBJ_FLAG2,				//각 진영의 깃발
	OBJ_TANK1, OBJ_TANK2,				//탱크 리스폰위치
	OBJ_NONE							//나중에 지울용도
};

//position
enum POS
{
	POS_FLAG1, POS_FLAG2,
	POS_TANK1, POS_TANK2
};

struct tagTile
{
	TERRAIN terrain;		//지형
	OBJECT obj;				//오브젝트
	RECT rc;				//렉트
	int terrainFrameX;		//터레인 번호
	int terrainFrameY;		//터레인 번호
	int objFrameX;			//ㅇㅂㅈㅌ 번호
	int objFrameY;			//ㅇㅂㅈㅌ 번호
};

//타일셋 
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};
