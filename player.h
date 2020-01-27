#pragma once
#include "gameNode.h"
#include "animation.h"
#include "jump.h"
#include "action.h"			   // �������� �̵��Ҷ� ����ϱ� ���� 
#include "alphaImageEffect.h"  // ����Ʈ ���

class Enemy;

enum PLAYERSTATE	// (�̻��) ���� ���� ���� 
{
	PLAYERSTATE_UP,
	PLAYERSTATE_DOWN,
	PLAYERSTATE_RIGHT,
	PLAYERSTATE_LEFT
};

enum PLAYERDIRECTION
{
	PLAYERDIRECTION_UP,
	PLAYERDIRECTION_DOWN,
	PLAYERDIRECTION_RIGHT,
	PLAYERDIRECTION_LEFT
};

enum PLAYERWAEPON
{
	PLAYERWAEPON_DAGGER,
	PLAYERWAEPON_LONGSWORD,
	PLAYERWAEPON_BROADSWORD,
	PLAYERWAEPON_RAPIER,
	PLAYERWAEPON_SPEAR,
	PLAYERWAEPON_NONE,
};

struct tagPlayer
{
	animation* headAni;		// �Ӹ� �ִϸ��̼�
	animation* bodyAni;		// ��   �ִϸ��̼� 
	PLAYERSTATE state;		// �÷��̾��� ����
	PLAYERWAEPON weapon;
	PLAYERDIRECTION direction;	// �÷��̾��� ����    
	image* headImage;		// �Ӹ� �̹��� 
	image* bodyImage;		// ���� 
	RECT rc;				// RECT
	float x, y;				// ��ǥ X,Y  

	int idx, idy;			// Ÿ���� �ε��� ��ȣ 
	int count;				// ������ ī���� 
	int currnetFrameX, currnetFrameY;	// ������ X,Y
	int sight;				// �÷��̾��� �þ߰� �⺻ 5
};

class player : public gameNode
{
private:
	tagPlayer _player;	//  �Ӹ�
	jump* _jump;		// ���� 
	action* _action;    // ��������

	float _distance;	// Ÿ�� ���� �Ÿ� 
	float _time;		// �ð� 
	float _angle;		// ���� 
	float _worldTimeCount;	// ���� Ÿ�� 

	bool _isMoving;			// BOOL ���������̵�
	bool _isKeyPress;		// KEY �Է��� ��Ʈ �Ǵ� 
	bool _isKeyDown;		// KEY �Է� �Ǵ�

	alphaImageEffect* _effect;
	vector<alphaImageEffect*>		     _vEffect;  // ������ ����Ʈ 
	vector<alphaImageEffect*>::iterator _viEffect;

	//Ÿ�� ������ �ϱ� ���� Ÿ�ϰ�
	map<PLAYERDIRECTION, tagTile*>				_mPlayerTile;
	map<PLAYERDIRECTION, tagTile*>::iterator	_miPlayerTile;

	//���������� �ϱ� ���� Ÿ�� ��
	map<PLAYERDIRECTION, Enemy*>				_mPlayerAttackTile;
	map<PLAYERDIRECTION, Enemy*>::iterator	_miPlayerAttackTile;
public:
	player();
	~player();

	HRESULT init(int idx, int idy, int tileSizeX, int tileSizeY);
	void release();
	void update();
	void render();

	void playerMove();
	void playerMissEffect();					// ����Ʈ
	void playerShovelEffect(tagTile* tile);
	void playerAttackEffect(const char* imageName,tagTile* tile, int frameY);
	void playerAttackEffect(const char* imageName, float x, float y, int frameY);
	void playerAttackEffect(const char* imageName, int x, int y, int frameY);


	
	void keyControl();

	//������ 
	tagPlayer getPlayer() { return _player; }			// �÷��̾� �� ��ȯ 
	int getSight() { return _player.sight; }			// �þ� �� ��ȯ 
	PLAYERSTATE getState() { return _player.state; }	// �÷��̾��� ���� �� ��ȯ (HG�� �߰�����)
	PLAYERDIRECTION getDirection() { return _player.direction; }	

	bool getPlayerKey() { return _isKeyPress; }
	void setPlayerKey(bool value = false) {	_isKeyPress = value;}  // 
	void setPlayerKeyDown() { _isKeyDown = false; }

	float* getPlayerY() { return &_player.y; }

	//Ÿ�� ����
	void setPlayerTile(map<PLAYERDIRECTION, tagTile*> tile) { _mPlayerTile = tile; }
	void setPlayerAttackTile(map<PLAYERDIRECTION, Enemy*> tile) { _mPlayerAttackTile = tile; }

	//Ÿ�ϰ���
	void tileCheck();
	void StateMove();			//�̵� 
	void StateAttack();			//����
	void StateShovel();

};


// ���޵��� �Ѱ�
/*
1. ALPHAEFFECT ��ģ��
2. ��Ʈ ���͹� ������ �÷��̾� ���� �����ϰ� �Ѱ� 
3. �÷��̾� �������� 4���� �浹ó�� 


�ؾ��Ұ� 

1. ENEMY ����
2. ITEM ȹ�� �� ����ϴ°�



*/