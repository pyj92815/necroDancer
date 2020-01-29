#pragma once
#include "gameNode.h"
#include <string>
#include "mapTool_Library.h"
class mapTool: public gameNode
{

private:
	//HWND _btnPlay;				//플레이 버튼
	//HWND _btnSave;				//저장 버튼
	//HWND _btnLoad;				//불러오기 버튼
	//HWND _btnTerrainDraw;		//지형 그리기 버튼
	//HWND _btnWallDraw;			//벽 그리기 버튼
	//HWND _btnObjectDraw;		//오브젝트 그리기 버튼
	//HWND _btnTrap;				//함정 버튼
	//HWND _btnEraser;			//지우개 버튼

	tagCurrentTile _currentTile;
	tagSetTile _terrainTile[TERRAINTILEX * TERRAINTILEY];
	tagSetTile _wallTile[WALLTILEX * WALLTILEY];
	tagSetTile _trapTile[TRAPTILEX * TRAPTILEY];
	tagSetTile _armorTile[ITEMTILEX * ITEMTILEY];
	tagSetTile _weaponTile[ITEMTILEX * ITEMTILEY];
	tagSetTile _stuffTile[ITEMTILEX * ITEMTILEY];
	tagTile		 _tiles[TILEX * TILEY];

	float _WINSIZEX, _WINSIZEY;
	int _pos[2];

	//락훈 맵툴 수정 
	tagButton _map[9];
	int _mapDirection;
	mousePointRect _mouseEffect;
private:
	tagButton _saveButton;		//저장
	tagButton _loadButton;		//로드
	tagButton _terrainButton;	//지형
	tagButton _wallButton;		//벽
	tagButton _trapButton;		//함정
	tagButton _itemButton;		//아이템
	tagButton _armorButton;		//방어구
	tagButton _weaponButton;	//무기
	tagButton _stuffButton;		//소지품
	tagButton _eraseButton;		//지우개
	tagButton _exitButton;		//나가기
private:
	tagMouse _RectCreate;
	bool _isClick;
	int _startL, _startT, _endR, _endB;
	RECT _left, _top, _right, _bottom;
	MovePalette _palette;	// 창 이동으로 사용할 렉트
	tagMouse _mousePoint;
	int alpha;
public:
	mapTool();
	~mapTool();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setup();

	virtual void setMap();
	virtual void save();
	virtual void load();

	//virtual void clickLeft();

	//어떤 지형을 선택했는가?
	TERRAIN terrainSelect(int frameX, int frameY);
	//어떤 벽을 선택했는가?
	WALL wallSelect(int frameX, int frameY);
	//어떤 함정를 선택했는가?
	TRAP trapSelect(int frameX, int frameY);
	//어떤 아이템을 선택했는가?
	STUFF stuffSelect(int frameX, int frameY);
	ARMOR armorSelect(int frameX, int frameY);
	WEAPON weaponSelect(int frameX, int frameY);

	void setS(int num) { _crtSelect = num; }
	void tile_Click();

	void palette_Click();				// 어느 팔렛트를 클랙했는지 찾아주는 함수.
	void palette_Click(bool start);		// 팔렛트 클릭 시 계산을 위한 준비 함수.
	void palette_Rect_Update();			// 팔렛트의 렉트를 갱신해주는 함수.
	void palette_Move();				// 팔렛트의 이동 연산을 해주는 함수.
	void menu_Choice();					// 메뉴 선택 함수.
	void rectCreate_Update();			// 렉트크리에이트 갱신
	bool using_Palette();				// 팔렛트 사용 중에 타일이 찍히지 않게 하는 함수.
	void mouseRectUpdate();				// 마우스 렉트 업데이트 함수.

	void clickButton();
};

