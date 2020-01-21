#pragma once

#define TESTTILEX 30
#define TESTTILEY 30
//=========================================
//�� Ÿ���� ������� 32�� �Ѵ�. 32 X 32
#define TILESIZE 52

//Ÿ�ϼ� ����(Ÿ���� ���� �ȷ�Ʈ ���� ����)
#define SAMPLETILEX 20
#define SAMPLETILEY 9

//��� �� ���ϴ°͵����ε�, �ݸ����� �� ��Ʃ����� ���ٰ� ī����
//������ �޸� �뷮�� ������ �޸� �Ƴ��ٱ� ���� ����� ��Ʈ�ʵ�

#define ATTR_UNMOVE 0x00000001
#define ATTR_SWAMP  0x00000002
#define ATTR_POISON 0x00000004
#define ATTR_FROZEN 0x00000008

//��������Ʈ�Ҷ� �� �̳����� �Ӽ�ó���ص� �����ҵ�


//���� MAPTOOP 

#define TESTTILESIZE 52

//Ÿ�� ������ ���� 100 / ���� 100
#define TILEX 20
#define TILEY 20

//Ÿ�� �� ������� 640 X 640
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//����Ÿ�ϼ� ����(Ÿ���� ���� �ȷ�Ʈ ���� ����)
#define TERRAINTILEX 6
#define TERRAINTILEY 6

//��Ÿ�ϼ� ����(Ÿ���� ���� �ȷ�Ʈ ���� ����)
#define WALLTILEX 16
#define WALLTILEY 4

//Ÿ�ϼ� ����(Ÿ���� ���� �ȷ�Ʈ ���� ����)
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
//����
enum TERRAIN
{
	TR_BASIC_STAGE_TILE, TR_BASIC_COMBO_TILE,
	TR_BOSS_STAGE_TILE, TR_BOSS_COMBO_TILE,
	TR_STAIR, TR_SHOP,
	TR_NONE,
	TR_END,
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER
};

//�� 
enum WALL
{
	W_WALL, W_ITEM_WALL, W_WALL2, W_SHOP_WALL,		//�⺻ ��, �������� ����ִ� ��, 
	W_END_WALL, W_BOSS_WALL,						//�μ����� �ʴ� ��
	W_DOOR, W_TORCH, W_FIRE_WALL,					//��. ��ġ, �� ���
	W_NONE											//���߿� ����뵵
};

//������Ʈ
enum OBJECT
{
	OBJ_ENEMY,										//��
	OBJ_FLOOR_OBJECT,								//�ٴۿ� �ѷ����� ������Ʈ
	OBJ_WEAPON, W_ARMOR								//������(��)
};

enum TRAP
{
	TRAP_FAST_BEAT, TRAP_SLOW_BEAT, TRAP_MUTE,		//���� ���� ���� �� ���Ұ� ����
	TRAP_LT_JUMP, TRAP_T_JUMP, TRAP_RT_JUMP,		// �밢�� ���� �����¿� ���� ����
	TRAP_L_JUMP, TRAP_R_JUMP,
	TRAP_LB_JUMP, TRAP_B_JUMP, TRAP_RB_JUMP,
	TRAP_CONFUSE,									//ȥ�� ����
	TRAP_BOMB,										//��ź ����
	TRAP_NIDDLE,									//���� ����
	TRAP_SHADOW, TRAP_NIDDLE_SHADOW,				//���� �׸���
	TRAP_NONE
};

//position
enum POS
{
	POS_PLAYER
};

struct tagTile
{
	TERRAIN terrain;		//����
	WALL wall;				//��
	TRAP trap;				//����
	OBJECT obj;				//������Ʈ
	RECT rc;				//��Ʈ
	int terrainFrameX;		//�ͷ��� ��ȣ
	int terrainFrameY;		//�ͷ��� ��ȣ
	int wallFrameX;			//�� ��ȣ
	int wallFrameY;			//�� ��ȣ
	int charFrameX;			//ĳ���� ��ȣ
	int charFrameY;			//ĳ���� ��ȣ
	int enemyFrameX;		//�� ��ȣ
	int enemyFrameY;		//�� ��ȣ
	int	floorObjFrameX;		//�ٴ� ������Ʈ ��ȣ
	int floorObjFrameY;		//�ٴ� ������Ʈ ��ȣ
	int itemFrameX;			//������ ��ȣ
	int itemFrameY;			//������ ��ȣ
	int trapFrameX;			//���� ��ȣ
	int trapFrameY;			//���� ��ȣ
	
	int alphaValue;			//�þ� �� ���ϱ� ���� ���� ���� ����
	bool alphaEyesight;			//�÷��̾� �þ�
	
	bool isRender;

	int idX;
	int idY;
	POINT XY;
};

//Ÿ�ϼ� 
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};

//���� Ÿ�� == ���� Ŭ���� ����Ÿ�� ������ ������ ����ü
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