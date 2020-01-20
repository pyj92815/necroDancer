#pragma once
#include "gameNode.h"
#include "enemy.h"
#include "bossLibrary.h"
#include "bossMove.h"

class boss : gameNode
{
protected:
	// ���� �������ͽ�
	BOSSTYPE			type;					// ���� Ÿ��
	BOSS_PHASESTATE		phase;					// ���� ������ ����
	BOSS_DIRECTION		direction;				// ���� ����
	int					hp;						// HP ����Ʈ
	int					shield;					// �ǵ� ����Ʈ
	float				attack;					// ������ ���ݷ�
	float				magicAttack;			// ������ �������ݷ�

	// ���� ��ǥ
	RECT		rc;								// ������ ��Ʈ		  (Ÿ���� left, bottom �������� ����ؼ� �����)
	POINTFLOAT	center;							// ������ �߽� ��ǥ	  (Ÿ���� �߽�)
	POINT		index;							// ������ �迭 �ε���	  (��� Ÿ�Ͽ� �ִ��� �ε���)

	// ���� �̹���
	animation*  animation;						// ������ ���ϸ��̼� ����
	image*		image;							// ������ �̹����� ��´�.


	// ���� �����ϴ� �� �����ϴ� ����
	int			_tileSize_X, _tileSize_Y;		// Ÿ���� ����� ��Ƶд�.
	int			skill_Casting_Cnt;				// ��ų ĳ���� �ð�
	bool		isMove;							// ������ ���������� ����
	bool		isJump;							// ������ �̵��� �Ҷ� ���� ����
	bool		isChangeAni;					// ������ �������ٸ� �ִϸ��̼��� �ٲ�����Ѵ�.
	bool		isCasting;						// ��ų ���� ������ ����
	bool		isClosePlayer;					// �÷��̾ ��ó�� �ִ��� ����
	bool		isThrowShield;					// �ǵ带 �������� ����

	float		angle;							// ������ �̵��Ҷ� ���ϰ���
	float       time;							// ������ ���� Ÿ�ϱ��� �̵��Ҷ� �ɸ��� �ð�
	float		speed;							// ������ ���� Ÿ�ϱ��� �̵��ϴ� �ӵ�
	float		distance;						// Ÿ�� ������
	float       worldTime;						// ���� Ÿ�� 
	bossMove	move;							// ���� �̵��� �ʿ��� ���� �Լ�
	tagBossJump jump;							// ���� ������ �ʿ��� ���� �Լ�

public:
	boss();
	~boss();

	virtual HRESULT init(string bossName, int _idx, int _idy, int _tileSizeX, int _tileSizeY);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void render(ThrowShield info);

	void addBossImage();																							// �������� �ʿ��� �̹����� �߰��Ѵ�.
	void findBossType(string bossname);																				// ���� Ÿ���� ã���ش�.
	void findBossImage();																							// Ÿ�� ������ ���� �̹����� ã�� �ִ´�.
	void settingBossPos(int idx, int idy, int tileSizeX, int tileSizeY);											// ������ ���� ��ǥ ���� �ʱ�ȭ
	void settingBossMoveVariable(int tileSizeX, int tileSizeY);														// ������ �̵� ���� �ʱ�ȭ

	// ���� ���� ���� �Լ�
	int getBoss_HP() { return hp; }																					// ������ HP�� �޾ƿ´�.
	int getBoss_Shield() { return shield; }																			// ������ �ǵ带 �޾ƿ´�.
	float getBoss_Atk() { return attack; }																			// ������ ���ݷ��� �޾ƿ´�.
	float getBoss_MegicAtk() { return magicAttack; }

	RECT getBoss_Rect() { return rc; }																				// ������ ��Ʈ�� �޾ƿ´�.
	POINTFLOAT getBoss_Center() { return center; }																	// ������ ������ �޾ƿ´�.
	POINT getBoss_Index() { return index; }																			// ������ �迭 �ε����� �޾ƿ´�.

	// ���� ���� ���� �Լ�
	void setBoss_HP(int _hp) { hp = _hp; if (hp > 9) hp = 9; if (hp < 0) hp = 0; }									// ������ HP�� �����Ѵ�. (hp�� �ִ�ġ �ּ�ġ�� �Ѿ�� �ʰ� ����ó��)
	void setBoss_HP_Hit() { hp--; if (hp < 0) hp = 0; }																// ������ ü���� 1 �����Ѵ�. (hp�� �ּ�ġ�� �Ѿ�� �ʰ� ����ó��)
	void setBoss_HP_Hit(int damage) { hp -= damage; if (hp < 0) hp = 0; }											// �޾� �� ��ġ��ŭ ������ ü���� �����Ѵ�. (hp�� �ּ�ġ�� �Ѿ�� �ʰ� ����ó��)

	void setBoss_HP_Heal() { hp++; if (hp > 9) hp = 9; }															// ������ ü���� 1 �����Ѵ�. (hp�� �ִ�ġ�� �Ѿ�� �ʰ� ����ó��)
	void setBoss_HP_Heal(int heal) { hp += heal; if (hp > 9) hp = 9; }												// �޾� �� ��ġ��ŭ ������ ü���� �����Ѵ�. (hp�� �ִ�ġ�� �Ѿ�� �ʰ� ����ó��) 

	void setBoss_Shield(int _shield) { shield = _shield; if (shield > 2) shield = 2; if (shield < 0) shield = 0; }	// �ǵ��� ���� �����Ѵ�. (�ǵ尡 �ִ�ġ �ּ�ġ�� �Ѿ�� �ʰ� ����ó��)
	void setBoss_Shield_Hit() { shield--; if (shield < 0) shield = 0; }												// �ǵ带 1 �����Ѵ�. (�ǵ尡 �ּ�ġ�� �Ѿ�� �ʰ� ����ó��)
	void setBoss_Shield_Hit(int damage) { shield -= damage; if (shield < 0) shield = 0; }							// 1 �̻��� �������� ���� ��ŭ �ǵ带 �����Ѵ�. (�ǵ尡 �ּ�ġ�� �Ѿ�� �ʰ� ����ó��)

	void setBoss_Shield_Heal() { shield++; if (shield > 2) shield = 2; }											// �ǵ带 1 �����Ѵ�. (�ǵ尡 �ִ�ġ�� �Ѿ�� �ʰ� ����ó��)
	void setBoss_Shield_Heal(int heal) { shield += heal; if (shield > 2) shield = 2; }								// �޾� �� ��ġ��ŭ �ǵ带 ������Ų��. (�ǵ尡 �ִ�ġ�� �Ѿ�� �ʰ� ����ó��)

	void setBoss_Attack(float _atk) { attack = _atk; if (attack < 0) attack = 0; }									// ������ ���ݷ��� �����Ѵ�. (���ݷ��� 0 ���Ϸ� �������� �ʰ� ����ó��)
	void setBoss_Attack_Plus() { attack++; }																		// ������ ���ݷ��� 1 ������Ų��.
	void setBoss_Attack_Plus(float buff) { attack += buff; }														// ������ ���ݷ��� �ش� ��ġ��ŭ ������Ų��.

	void setBoss_MagicAttack(float _matk) { magicAttack = _matk; if (magicAttack < 0) magicAttack = 0; }			// ������ �������ݷ��� �����Ѵ�. (�������ݷ���0 ���Ϸ� �Ѿ�� �ʰ� ����ó��)
	void setBoss_MagicAttack_Plus() { magicAttack++; }																// ������ �������ݷ��� 1 ������Ų��.
	void setBoss_MagicAttack_Plus(float buff) { magicAttack += buff; }												// ������ �������ݷ��� �ش� ��ġ��ŭ ������Ų��.

	void setBoss_Rect(RECT _rc, int _RECT_SIZEX, int _RECT_SIZEY)													//���� �̹����� ����� ��Ʈ ��ġ�� ���Ѵ�. 
	{
		// ������ �̹����� Ŭ ��츦 ����ؼ� ������ �������� �̹��� ũ�⸸ŭ ���� Top�� ���ߴ�.
		rc = RectMake(_rc.left, (_rc.top + _RECT_SIZEY) - image->getFrameWidth(), image->getFrameWidth(), image->getFrameHeight());
	}

	void setBoss_center(RECT _rc) { center.x = (_rc.left + _rc.right) / 2; center.y = (_rc.top + _rc.bottom) / 2; }	// Ÿ���� ��Ʈ�� �޾ƿ� ������ ���Ѵ�.

	void setBoss_Index(int idx, int idy) { index.x = idx; index.y = idy; }											// Ÿ���� �ε����� �޾ƿ� �����Ѵ�.

	void setBoss_Image(string bossName) { image = IMAGEMANAGER->findImage(bossName); }								// ������ �̹����� �����Ѵ�.

	// ������Ʈ �Լ�
	void Info_Update();																								// ���� ���� �Լ�
	void boss_Move();																								// ���� �̵� ���� �Լ�
};

// �������� (inear intetpolation)
// lerp() ���� �Լ�
// lerp(min, max, ����)�� ���ָ� min ~ max ���̿� ���ϴ� ������ ���� ã�� �� �ִ� �Լ�
// ���۰� ���� ���� �˰� ������ �� ������ � ���� ���������� ã�� �� ����
// ���� : (max - min) * ���� + min
// 
// ���� ���� : ���ϰ��� �ϴ� ���� - 1�� �и�� �ΰ� ���ڿ� 1�� �θ� ������ ã�� �� �ִ�.
// 