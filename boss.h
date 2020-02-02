#pragma once
#include "gameNode.h"
#include "bossLibrary.h"
#include "bossMove.h"

class boss : gameNode
{
protected:
	// 보스 스테이터스
	BOSSTYPE			type;					// 보스 타입
	BOSS_PHASESTATE		phase;					// 보스 페이즈 상태
	BOSS_DIRECTION		direction;				// 보스 방향
	int					hp;						// HP 포인트
	int					shield;					// 실드 포인트
	float				attack;					// 보스의 공격력
	float				magicAttack;			// 보스의 마법공격력

	// 보스 좌표
	RECT		rc;								// 보스의 렉트		  (타일의 left, bottom 기준으로 계산해서 만들것)
	POINTFLOAT	center;							// 보스의 중심 좌표	  (타일의 중심)
	POINT		index;							// 보스의 배열 인덱스	  (어느 타일에 있는지 인덱스)

	// 보스 이미지
	animation*  attack_Ani;						// 보스 공격 이펙트 애니메이션 정보
	image*		att_Image;						// 보스 공격 이미지를 담는다.
	POINTFLOAT	ani_Center;						// 이펙트 애니메이션을 뿌릴 좌표를 저장한다.

	animation*  ani;							// 보스의 에니메이션 정보
	image*		_image;							// 보스의 이미지를 담는다.

	// 자주 연산하는 값 저장하는 변수
	int			_tileSize_X, _tileSize_Y;		// 타일의 사이즈를 담아둔다.
	int			skill_Casting_Cnt;				// 스킬 캐스팅 시간
	bool		isMove;							// 보스가 움직였는지 여부
	bool		isJump;							// 보스가 이동을 할때 점프 여부
	bool		isChangeAni;					// 보스가 움직였다면 애니메이션을 바꿔줘야한다.
	bool		isCasting;						// 스킬 시전 유무를 저장
	bool		isClosePlayer;					// 플레이어가 근처에 있는지 저장
	bool		isThrowShield;					// 실드를 던졌는지 여부
	bool		isShield_Hit;					// 실드가 피격 당했다면 true

	float		angle;							// 보스가 이동할때 쓰일각도
	float       time;							// 보스가 다음 타일까지 이동할때 걸리는 시간
	float		speed;							// 보스가 다음 타일까지 이동하는 속도
	float		distance;						// 타일 사이즈
	float       worldTime;						// 월드 타임 
	bossMove	move;							// 보스 이동에 필요한 연산 함수
	tagBossJump jump;							// 보스 점프에 필요한 연산 함수
	int			move_Count;						// 보스가 이동 가능한 박자를 저장한다.

	BOSS_BOOL	boss_Bool;						// 보스에 사용하는 bool을 모아두었다.
	BOSS_SUMMONS_SKILL	slave_Summon;			// 슬레이브 소환 스킬
	BOSS_Magic_SKILL	boss_FireBall;			// 보스 파이어볼 스킬

	BOSS_DIRECTION save_Direction;				// 보스의 방향을 저장해둔다.
	bool		   change_Ani;					// 애니메이션 체인지가 가능한지 여부
	bool		   save_ClosePlayer;		    // 플레이어가 근처에 있는지 여부 세이브

	int			   save_HP;						// 보스의 현재 HP를 저장해둔다.
	int			   max_HP;						// 보스의 최대 HP

public:
	boss();
	~boss();

	virtual HRESULT init(string bossName, int _idx, int _idy, int _tileSizeX, int _tileSizeY);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void render(ThrowShield info);

	void findBossType(string bossname);																				// 보스 타입을 찾아준다.
	void findBossImage();																							// 타입 정보로 보스 이미지를 찾아 넣는다.
	void settingBossPos(int idx, int idy, int tileSizeX, int tileSizeY);											// 보스의 각종 좌표 변수 초기화
	void settingBossMoveVariable(int tileSizeX, int tileSizeY);														// 보스의 이동 변수 초기화
	void settingBossVariable();																						// 보스에서 사용할 변수 초기화
	void showBossHP();																								// 보스의 체력 이미지 표시
	void setBoss_isShield_Hit(bool shield_Hit) { isShield_Hit = shield_Hit; }										// 실드 정보를 수정한다.

	// 보스 정보 겟터 함수
	int getBoss_HP() { return hp; }																					// 보스의 HP를 받아온다.
	int getBoss_Shield() { return shield; }																			// 보스의 실드를 받아온다.
	float getBoss_Atk() { return attack; }																			// 보스의 공격력을 받아온다.
	float getBoss_MegicAtk() { return magicAttack; }
	BOSS_DIRECTION getBoss_Direction() { return direction; }														// 보스가 바라보는 방향을 받아온다.

	RECT getBoss_Rect() { return rc; }																				// 보스의 렉트를 받아온다.
	POINTFLOAT getBoss_Center() { return center; }																	// 보스의 중점을 받아온다.
	POINT getBoss_Index() { return index; }																			// 보스의 배열 인덱스를 받아온다.

	int getBoss_Move_Count_Value() { return move.get_BossMoveCount(); }
	int getBoss_Move_Count() { return move_Count; }

	bool getBoss_Beat() { return boss_Bool.get_Beat; }																// 보스가 비트를 받았는지 유무
	POINTFLOAT getBoss_BaseAttack_Pos() { return ani_Center; }														// 이펙트 애니메이션을 뿌릴 좌표
	image* getBoss_AttImage() { return att_Image; }
	BOSS_PHASESTATE getBoss_Phase() { return phase;	}																// 보스 페이즈 받아오기.
	bool getBoss_isShield_Hit() { return isShield_Hit; }															// 실드 피격 상태 받아오기.

	bool getBoss_Dead() { return boss_Bool.boss_Die; }																// 보스 죽었는지 여부
	bool getBoss_ClosePlayer() { return isClosePlayer; }
	BOSS_SUMMONS_SKILL getBoss_SummonSkill() { return slave_Summon; }												// 슬레이브 소환에 필요한 변수들 모음
	BOSS_SUMMONS_SKILL* boss_SummonSkill() { return &slave_Summon; }
	BOSS_Magic_SKILL* boss_FireBallSkill() { return &boss_FireBall; }
	BOSS_BOOL* getBoss_Bool() { return &boss_Bool; }


	// 보스 정보 셋터 함수
	void setBoss_HP(int _hp) { hp = _hp; if (hp > 9) hp = 9; if (hp < 0) hp = 0; }									// 보스의 HP를 수정한다. (hp가 최대치 최소치를 넘어가지 않게 예외처리)
	void setBoss_HP_Hit() { hp--; if (hp < 0) hp = 0; }																// 보스의 체력이 1 감소한다. (hp가 최소치를 넘어가지 않게 예외처리)
	void setBoss_HP_Hit(int damage) { hp -= damage; if (hp < 0) hp = 0; }	 										// 받아 온 수치만큼 보스의 체력이 감소한다. (hp가 최소치를 넘어가지 않게 예외처리)

	void setBoss_HP_Heal() { hp++; if (hp > 9) hp = 9; }															// 보스의 체력을 1 증가한다. (hp가 최대치를 넘어가지 않게 예외처리)
	void setBoss_HP_Heal(int heal) { hp += heal; if (hp > 9) hp = 9; }												// 받아 온 수치만큼 보스의 체력을 증가한다. (hp가 최대치를 넘어가지 않게 예외처리) 

	void setBoss_Shield(int _shield) { shield = _shield; if (shield > 2) shield = 2; if (shield < 0) shield = 0; }	// 실드의 값을 수정한다. (실드가 최대치 최소치를 넘어가지 않게 예외처리)
	void setBoss_Shield_Hit() { shield--; if (shield < 0) shield = 0; }												// 실드를 1 감소한다. (실드가 최소치를 넘어가지 않게 예외처리)
	void setBoss_Shield_Hit(int damage) { shield -= damage; if (shield < 0) shield = 0; }							// 1 이상의 데미지를 입은 만큼 실드를 감소한다. (실드가 최소치는 넘어가지 않게 예외처리)

	void setBoss_Shield_Heal() { shield++; if (shield > 2) shield = 2; }											// 실드를 1 증가한다. (실드가 최대치를 넘어가지 않게 예외처리)
	void setBoss_Shield_Heal(int heal) { shield += heal; if (shield > 2) shield = 2; }								// 받아 온 수치만큼 실드를 증가시킨다. (실드가 최대치를 넘어가지 않게 예외처리)

	void setBoss_Attack(float _atk) { attack = _atk; if (attack < 0) attack = 0; }									// 보스의 공격력을 수정한다. (공격력이 0 이하로 내려가지 않게 예외처리)
	void setBoss_Attack_Plus() { attack++; }																		// 보스의 공격력을 1 증가시킨다.
	void setBoss_Attack_Plus(float buff) { attack += buff; }														// 보스의 공격력을 해당 수치만큼 증가시킨다.

	void setBoss_MagicAttack(float _matk) { magicAttack = _matk; if (magicAttack < 0) magicAttack = 0; }			// 보스의 마법공격력을 수정한다. (마법공격력이0 이하로 넘어가지 않게 예외처리)
	void setBoss_MagicAttack_Plus() { magicAttack++; }																// 보스의 마법공격력을 1 증가시킨다.
	void setBoss_MagicAttack_Plus(float buff) { magicAttack += buff; }												// 보스의 마법공격력을 해당 수치만큼 증가시킨다.

	void setBoss_Rect(RECT _rc, int _RECT_SIZEX, int _RECT_SIZEY)													//보스 이미지를 출력할 렉트 위치를 구한다. 
	{
		// 보스의 이미지가 클 경우를 대비해서 바텀을 기준으로 이미지 크기만큼 빼서 Top을 구했다.
		rc = RectMake(_rc.left, (_rc.top + _RECT_SIZEY) - _image->getFrameWidth(), _image->getFrameWidth(), _image->getFrameHeight());
	}

	void setBoss_center(RECT _rc) { center.x = (_rc.left + _rc.right) / 2; center.y = (_rc.top + _rc.bottom) / 2; }	// 타일의 렉트를 받아와 중점을 구한다.

	void setBoss_Index(int idx, int idy) { index.x = idx; index.y = idy; }											// 타일의 인덱스를 받아와 저장한다.

	void setBoss_Image(string bossName) { _image = IMAGEMANAGER->findImage(bossName); }								// 보스의 이미지를 수정한다.

	void setBoss_Animation(string bossAni) { ani = KEYANIMANAGER->findAnimation(bossAni); }							// 보스의 애니메이션을 바꿔준다.

	void setBoss_ClosePlayer(bool close) { isClosePlayer = close; }													// 보스 근처에 플레이어가 있는지 없는지

	void ChangeAni() { isChangeAni = true; }

	void setBoss_Move_Count() { move_Count--; }																		// 보스의 무브 카운트를 감소 시킨다.
	void setBoss_Move_Count(int num) { move_Count = num; }

	void setBoss_Direction(BOSS_DIRECTION dir) { direction = dir; }													// 보스의 방향을 수정한다.

	void setBoss_WorldTime(float wTime) { worldTime = wTime; }														// 월드 타임을 수정한다.

	void setBoss_Move_BoolValue_Ture() { 
		/*isMove = isJump = isChangeAni = true;*/ isMove = isJump = isChangeAni = true;	}									// 무브에 필요한 bool값을 한번에 수정한다.

	void setBoss_Beat(bool value) { boss_Bool.get_Beat = value; }													// 비트를 받았는지 유무를 수정한다. (여러번 중복 받는것을 피하기 위해)

	void setBoss_BaseSkill(string skillName) { attack_Ani = KEYANIMANAGER->findAnimation(skillName); }				// 해당 애니메이션을 찾아서 넣어준다.

	void setBoss_BaseSkill_Image(string skillName) { att_Image = IMAGEMANAGER->findImage(skillName); }

	void setBoss_BaseAttack_Pos(float x, float y) { ani_Center.x = x; ani_Center.y = y; }							// 이펙트 애니메이션을 뿌릴 좌표를 셋팅한다.

	void setBoss_Shield_Hit_True() { isShield_Hit = true; }																// 실드가 피격 당하면 true

	void setBoss_Angle(float ang) { angle = ang; }

	void setBoss_SummonSkill(int num) { slave_Summon.rnd = num; }													// 랜덤값을 저장한다.

	void setBoss_isCasting(bool value) { isCasting = value; }														// 캐스팅 유무 설정

	void setBoss_HP_1() { hp = 1; }

	// 업데이트 함수
	void Info_Update();																								// 정보 갱신 함수
	void boss_Move();																								// 보스 이동 연산 함수
	void start_AttackAni() { attack_Ani->start(); }																	// 이펙트 애니메이션을 시작한다.

};

// 선형보간 (inear intetpolation)
// lerp() 럴프 함수
// lerp(min, max, 비율)을 해주면 min ~ max 사이에 원하는 비율의 값을 찾을 수 있는 함수
// 시작과 끝의 값을 알고 있을때 그 사이의 어떤 값도 선형적으로 찾을 수 있음
// 공식 : (max - min) * 비율 + min
// 
// 비율 공식 : 구하고자 하는 개수 - 1을 분모로 두고 분자에 1을 두면 비율을 찾을 수 있다.
// 