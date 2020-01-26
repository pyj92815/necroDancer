#pragma once
#include "boss.h"
#include "slave.h"

class deathMetal : public boss
{
private:
	ThrowShield _throwShield;					// 데스메탈의 실드를 던질때 이용할 실드 좌표 변수

public:
	HRESULT init(string bossName, int idx, int idy, int TILE_SIZEX, int TILE_SIZEY);
	void release();
	void update();
	void render();

	void clearThrowShield();					// 데스메탈 실드에 쓰일 변수들을 청소한다.

	void deathMetal_Animation_Setting();		// 데스메탈의 애니메이션 정보를 셋팅한다.
	void deathMetal_Animation_Test();			// 데스메탈의 애니메이션 테스트 함수.
	void deathMetal_ChangeAnimation();			// 데스메탈의 애니메이션 체인지 함수.

	void deathMetal_ChangePhase();				// 데스메탈의 페이즈 체인지 함수.
	void deathMetal_ShieldPosUpdate();			// 데스메탈의 실드 위치를 갱신해주는 함수.
	void deathMetal_ThrowShield();				// 데스메탈은 1페이즈가 끝나면 실드를 던진다.

};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 데스메탈 패턴
	// 기본으로 보호막이 달려있음.
	// 처음 슬레이브는 고스트 4마리
	// 고스트는 플레이어가 바라보면 투명해지면서 무적상태 이동하지 않음
	// 플레이어가 바라보고 있지 않으면 따라온다.
	// 고스트를 모두 죽이면 슬레이브 소환으로 박쥐가 나온다. 4마리
	// 박쥐는 랜덤으로 이동하고, 근처에 플레이어가 있으면 공격
	// 박쥐가 모두 죽고 슬레이브 소환으로 해골이 나온다. 2마리 소환
	// 해골은 플레이어를 a*로 따라오고, 손을 들고 그 다음에 공격을 한다.
	// 머리가 없어지면 플레이어에게 멀어지는 이동을 시작함
	// 데스메탈에 캐스팅 중에 피격을 당하면 캐스팅이 취소된다.
	// 데스메탈의 체력이 4칸으로 떨어지면 초록색 해골을 소환한다.
	// 데스메탈의 마법 공격에 적도 피해를 입는다. (팀킬 가능)
	// 체력 9칸
	// 보호막은 공격 2대에 깨짐
	// 보호막이 깨지기 전까지는 전방 공격에 데미지를 입지 않는다.
	// 보호막이 있을때는 보호막 들고 있는 이미지 4종류 (왼, 위, 오, 아래)
	// 보호막이 사라지면 데스메탈의 프레임 이미지는 2개 (대기, 손들기)
	// 일정 체력 이하에선 플레이어에게 맞았을때 텔레포트
	// 데스메탈은 손을 들면서 이상한 소리를 외치고 4틱 후에 내리면서 슬레이브를 소환한다.
	// 슬레이브는 랜덤? (유령, 해골)
	// 데스메탈은 손을 들면서 이상한 소리를 외치고 4틱 후에 파이어볼
	// 체력이 없을때는 플레이어에게서 멀어지면서 파이어볼만 쏨
	// 체력
	// 슬레이브 소환(고스트, 박쥐, 해골, 노란해골)
	// 보호막
	// 파이어볼
	// 텔레포트
	// 피격 시 캐스팅 취소
	// 

// 데스메탈 페이즈
	// HP 9 ~ 7 : 방패를 들고 세 박자마다 이동하면서 플레이어에게 다가간다.
	//            일반 무기로 방패를 든 상태의 데스 메탈을 정면에서 공격하면 뒤로 튕기게만 할 뿐이며, 동시에 박쥐가 소환된다.
	//            반드시 옆이나 뒤를 공격해야 한다. 다만 관통 효과가 있는 무기를 사용하면 정면에서도 공격할 수 있다.
	// HP 6 ~ 5 : 방패를 집어 던지고 두 박자마다 움직이면서 플레이어와 거리를 둔다. 이따금 "Come to me!"라고 외치며 손을 들어올리는데,
	//            직후 네 박자 동안 공격받지 않으면 1~3 마리의 해골을 소환한다. 이때부터는 공격받으면 반대편으로 순간 이동한다.
	// HP 4 ~ 3 : "End of the line!"을 외치며 노란 해골을 소환한다.
	// HP 2 ~ 1 : 한 박자마다 이동하기 시작하면서 왼쪽이나 오른쪽 벽에 붙는다. 그 후 세로축으로 플레이어를 따라가면서 네 박자마다
	//            "Bathe in fire!"을 외치며 양직선으로 파이어볼을 발사한다.

//  데스메탈 피격 사운드 3개
//  데스메탈 방패 피격 사운드 1개
//  데스메탈 방패 던지는 사운드 1개
//  박쥐 사망 사운드 1개
//  데스메탈 Come to me 사운드 1개
//  해골 사망 사운드 1개
//  해골 피격 사운드 있는지 찾아봐야함
//  데스메탈 End of the line 사운드 1개
//  데스메탈 welcome 사운드 1개

//  훈재가 찾은 비트에 맞게 움직이게 해야함
//  보스는 피격 당하면 체력 게이지가 머리 위에 표시가 된다.
//  A*
//  보스가 이동할때 시간에 맞게 이동하게 해야함
//  이동 시 살짝 점프 느낌?
//  슬레이브 소환 시 오브젝트와 곂치지 않게 랜덤 소환
//  이동 예외처리
//  파이어볼은 벽에는 그려지면 안된다. 
//  각 상황에 맞게 사운드 추가해야함
//  보스 스테이지 입장 할때 씬 이미지 나오게 해야함
//  보스 스테이지에서 플레이어 정보 연동 어떻게 해야할지 만들어야함
//  반대로 보스 정보를 플레이어에게 전달하는 방법도 만들어야함
//  임시 플레이어를 만들까
