#pragma once
#include "image.h"
//백버퍼는 어차피 한개만 있으면 되니 전역으로 빼봅시당
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

enum CTRL
{
	CTRL_SAVE,			//세이브 버튼에서 사용될 것
	CTRL_LOAD,			//로드 버튼에서 사용될 것
	CTRL_OBJECT,		//오브젝트들을 그리기위한 버튼
	CTRL_TERRAINDRAW,	//지형 그리기 버튼
	CTRL_FLOOR_OBJ,		//바닦에 있는 오브젝트
	CTRL_WALLDRAW,		//벽 그리기 버튼
	CTRL_PLAYER,		//플레이어 그리기 버튼
	CTRL_ENEMY,			//적 그리기 버튼
	CTRL_TRAP,			//함정 그리기 버튼
	CTRL_PLAY,			//게임 시작을 알리는 버튼(나머지 버튼이 사라짐)
	CTRL_ERASER,		//지우개 버튼 (잘못찍은 오브젝트등을 지움지움)
	CTRL_END
};

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;

public:
	gameNode();
	virtual ~gameNode();

	int _crtSelect;  // 맵툴 만드는 중 

	virtual HRESULT init();			//초기화 전용 함수
	virtual HRESULT init(bool managerInit);
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용 함수
	virtual void render();			//그리기 전용 함수


	//백버퍼의 DC메모리 영역 접근자
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

};

