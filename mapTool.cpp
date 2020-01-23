#include "stdafx.h"
#include "mapTool.h"

mapTool::mapTool()
{
}


mapTool::~mapTool()
{
}

void setWindowsSize(int x, int y, int width, int height);

HRESULT mapTool::init()
{
	// 맵툴 사이즈를 정의 
	_WINSIZEX = 1800;
	_WINSIZEY = 900;
	setWindowsSize(WINSTARTX, WINSTARTY, _WINSIZEX, _WINSIZEY);
	resizeWindow(WINNAME, _WINSIZEX, _WINSIZEY);
	_backBuffer->init(_WINSIZEX, _WINSIZEY);
	setup();
	_startL = 0;
	_startT = 0;
	_isClick = false;
	//락훈 수정 ======================
	_mapDirection = 0;
	for (int i = 0;i < 3;i++)
	{
		for (int j = 0;j < 3;j++)
		{
			SetRect(&_map[i*3+j].rc, _WINSIZEX - 200 + (j * 30), _WINSIZEY - 100 + (i * 30),
				_WINSIZEX - 170 + (j * 30), _WINSIZEY - 80 + (i * 30));
			_map[i].XY.x = _WINSIZEX - 100;
			_map[i].XY.y = _WINSIZEY - 100;
			_map[i * 3 + j].isClick = false;
		}
	}
	return S_OK;
}

void mapTool::release()
{

}


void mapTool::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0;i < 9;i++)
		{
			if (PtInRect(&_map[i].rc, _ptMouse))
			{
				_map[i].isClick = true;
				_mapDirection = i;
			}
		}
		for (int i = 0;i < 9;i++)
		{
			if (_mapDirection == i) continue;
			_map[i].isClick = false;

		}
	}


	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
	
		setMap();
		
		if (PtInRect(&_terrainButton.rc, _ptMouse))	{ _crtSelect = CTRL_TERRAINDRAW; }
		if (PtInRect(&_wallButton.rc, _ptMouse)) { _crtSelect = CTRL_WALLDRAW; }
		if (PtInRect(&_trapButton.rc, _ptMouse)) { _crtSelect = CTRL_TRAP; }
		if (PtInRect(&_saveButton.rc, _ptMouse))
		{
			_crtSelect = CTRL_SAVE;
			save();
		}
		if (PtInRect(&_loadButton.rc, _ptMouse))
		{
			_crtSelect = CTRL_LOAD;
			load();
		}
	
	}
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		if (!_isClick)
		{
			_startL = _ptMouse.x;
			_startT = _ptMouse.y;
			_isClick = true;
		}
		if (_isClick == true)
		{
			_endR = _ptMouse.x;
			_endB = _ptMouse.y;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON))
	{
		_isClick = false;
	}
}



void mapTool::render()
{
	PatBlt(CAMERAMANAGER->getWorldDC(), 0, 0, _WINSIZEX, _WINSIZEY, BLACKNESS);
	//TextOut(getMemDC(), 700, 700, str,strlen(str)); 
	//지형
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tiles[i].isRender == true)
		{
			_tiles[i].type = TYPE_TERRAIN;
			Rectangle(CAMERAMANAGER->getWorldDC(), _tiles[i].rc);
			IMAGEMANAGER->frameRender("terrainTiles", CAMERAMANAGER->getWorldDC(),
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		}
	}
	//벽 
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tiles[i].wall == W_NONE) continue;
		if (_tiles[i].isRender == true)
		{
			_tiles[i].type = TYPE_WALL;
			IMAGEMANAGER->frameRender("wallTiles", CAMERAMANAGER->getWorldDC(),
				_tiles[i].rc.left, _tiles[i].rc.top - 32,
				_tiles[i].wallFrameX, _tiles[i].wallFrameY);
		}
	}
	//함정
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tiles[i].trap == TRAP_NONE) continue;
		if (_tiles[i].isRender == true)
		{
			_tiles[i].type = TYPE_TRAP;
			IMAGEMANAGER->frameRender("trapTiles", CAMERAMANAGER->getWorldDC(),
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].trapFrameX, _tiles[i].trapFrameY);
		}
	}
	if (_crtSelect == CTRL_TERRAINDRAW)
	{
		IMAGEMANAGER->render("terrainTiles", CAMERAMANAGER->getWorldDC(), _WINSIZEX - IMAGEMANAGER->findImage("terrainTiles")->getWidth(), 0);
		/*for (int i = 0; i < TERRAINTILEX * TERRAINTILEY; ++i)
		{
			Rectangle(CAMERAMANAGER->getWorldDC(), _terrainTile[i].rcTile);
		}*/
	}
	
	if (_crtSelect == CTRL_TRAP)
	{
		/*for (int i = 0; i < TRAPTILEX * TRAPTILEY; ++i)
		{
			Rectangle(CAMERAMANAGER->getWorldDC(), _trapTile[i].rcTile);
		}*/
		IMAGEMANAGER->render("trapTiles", CAMERAMANAGER->getWorldDC(), _WINSIZEX - IMAGEMANAGER->findImage("trapTiles")->getWidth(), 0);
	}

	if (_crtSelect == CTRL_WALLDRAW)
	{
		IMAGEMANAGER->render("wallTiles", CAMERAMANAGER->getWorldDC(), _WINSIZEX - IMAGEMANAGER->findImage("wallTiles")->getWidth(), 0);
		/*for (int i = 0; i < WALLTILEX * WALLTILEY; ++i)
		{
			Rectangle(CAMERAMANAGER->getWorldDC(), _wallTile[i].rcTile);
		}*/
		/*	for (int i = 0; i < TILEX * TILEY; ++i)
			{
				Rectangle(getMemDC(), _wallTile[i].rcTile);
			}*/
	}
	
	Rectangle(CAMERAMANAGER->getWorldDC(), _saveButton.rc);
	Rectangle(CAMERAMANAGER->getWorldDC(), _loadButton.rc);
	Rectangle(CAMERAMANAGER->getWorldDC(), _terrainButton.rc);
	Rectangle(CAMERAMANAGER->getWorldDC(), _wallButton.rc); 
	Rectangle(CAMERAMANAGER->getWorldDC(), _trapButton.rc);

	if (_isClick == true)
	{
		Rectangle(CAMERAMANAGER->getWorldDC(), _startL, _startT, _endR, _endB);
	}
	//락훈 수정사항
	for (int i = 0;i < 9;i++)
	{
		if (!_map[i].isClick)
		{
			Rectangle(CAMERAMANAGER->getWorldDC(), _map[i].rc);
		}
		else
		{
			HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
			HBRUSH oldBrush = (HBRUSH)SelectObject(CAMERAMANAGER->getWorldDC(), brush);
			Rectangle(CAMERAMANAGER->getWorldDC(), _map[i].rc);
			SelectObject(CAMERAMANAGER->getWorldDC(), oldBrush);
			DeleteObject(brush);
		}
	}
	CAMERAMANAGER->getWorldImage()->render(getMemDC());
	// 카메라 뒤에 그려줌 
	/*_btnSave = CreateWindow("button", "저장", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1100, 500, 100, 30, _hWnd, HMENU(0), _hInstance, NULL);
	_btnLoad = CreateWindow("button", "불러오기", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON , 1200, 500, 100, 30, _hWnd, HMENU(1), _hInstance, NULL);
	_btnObjectDraw = CreateWindow("button", "오브젝트", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1100, 700, 100, 30, _hWnd, HMENU(2), _hInstance, NULL);
	_btnTerrainDraw = CreateWindow("button", "지형", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1200, 700, 100, 30, _hWnd, HMENU(3), _hInstance, NULL);
	_btnWallDraw = CreateWindow("button", "벽", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1300, 700, 100, 30, _hWnd, HMENU(5), _hInstance, NULL);
	_btnTrap = CreateWindow("button", "함정", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1400, 700, 100, 30, _hWnd, HMENU(8), _hInstance, NULL);
	_btnEraser = CreateWindow("button", "지우개", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1500, 700, 100, 30, _hWnd, HMENU(10), _hInstance, NULL);
	_btnPlay = CreateWindow("button", "게임 창", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1600, 700, 100, 30, _hWnd, HMENU(9), _hInstance, NULL);*/


	//===========================================================
	//_backBuffer->render(getHDC(), 0, 0);
}

void mapTool::setup()
{
	_saveButton.rc = RectMake(1100, 500, 100, 30);
	_loadButton.rc = RectMake(1210, 500, 100, 30);
	_terrainButton.rc = RectMake(1100, _WINSIZEY - 50, 100, 30);
	_wallButton.rc = RectMake(1210, _WINSIZEY - 50, 100, 30);
	_trapButton.rc = RectMake(1320, _WINSIZEY - 50, 100, 30);
	//처음에는 지형으로 둔다
	//_crtSelect = CTRL_WALLDRAW;

	//지형 오브젝트 타일셋팅 (샘플타일)
	for (int i = 0; i < TERRAINTILEY; ++i)
	{
		for (int j = 0; j < TERRAINTILEX; ++j)
		{
			_terrainTile[i * TERRAINTILEX + j].terrainFrameX = j;
			_terrainTile[i * TERRAINTILEX + j].terrainFrameY = i;

			//RectMake -> SetRect()
			SetRect(&_terrainTile[i * TERRAINTILEX + j].rcTile,
				(_WINSIZEX - IMAGEMANAGER->findImage("terrainTiles")->getWidth()) + j * TILESIZE,
				i * TILESIZE,
				(_WINSIZEX - IMAGEMANAGER->findImage("terrainTiles")->getWidth()) + j * TILESIZE + TILESIZE,
				i * TILESIZE + TILESIZE);
		}
	}
	//함정 타일 셋팅
	for (int i = 0; i < TRAPTILEY; ++i)
	{
		for (int j = 0; j < TRAPTILEX; ++j)
		{
			_trapTile[i * TRAPTILEX + j].terrainFrameX = j;
			_trapTile[i * TRAPTILEX + j].terrainFrameY = i;

			//RectMake -> SetRect()
			SetRect(&_trapTile[i * TRAPTILEX + j].rcTile,
				(_WINSIZEX - IMAGEMANAGER->findImage("trapTiles")->getWidth()) + j * TILESIZE,
				i * TILESIZE,
				(_WINSIZEX - IMAGEMANAGER->findImage("trapTiles")->getWidth()) + j * TILESIZE + TILESIZE,
				i * TILESIZE + TILESIZE);
		}
	}

	//벽 타일 셋팅 추후 수정 필요함 
	for (int i = 0; i < WALLTILEY; ++i)
	{
		for (int j = 0; j < WALLTILEX; ++j)
		{
			_wallTile[i * WALLTILEX + j].terrainFrameX = j;
			_wallTile[i * WALLTILEX + j].terrainFrameY = i;

			//RectMake -> SetRect()
			SetRect(&_wallTile[i * WALLTILEX + j].rcTile,
				(_WINSIZEX - IMAGEMANAGER->findImage("wallTiles")->getWidth()) + j * TILESIZE,
				(i*2) * TILESIZE,
				(_WINSIZEX - IMAGEMANAGER->findImage("wallTiles")->getWidth()) + j * TILESIZE + TILESIZE,
				(i*2) * TILESIZE + (TILESIZE*2));
		}
	}
	//타일 영역셋팅
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			SetRect(&_tiles[i * TILEX + j].rc,
				j * TILESIZE,
				i * TILESIZE,
				j * TILESIZE + TILESIZE,
				i * TILESIZE + TILESIZE);
			//x / y 값
			_tiles[i * TILEX + j].XY.x = j * 52;
			_tiles[i * TILEX + j].XY.y = i * 52;
			//인덱스 x / y좌표 값
			_tiles[i * TILEX + j].idX = _tiles[i * TILEX + j].XY.x / 52;
			_tiles[i * TILEX + j].idY = _tiles[i * TILEX + j].XY.y / 52;
		}
	}

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		_tiles[i].type = TYPE_NONE;
		_tiles[i].isRender = false;
		_tiles[i].terrainFrameX = 5;
		_tiles[i].terrainFrameY = 5;
		_tiles[i].wallFrameX = 0;
		_tiles[i].wallFrameY = 0;
		_tiles[i].trapFrameX = 0;
		_tiles[i].trapFrameY = 0;
		_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		_tiles[i].terrain = TR_NONE;
		_tiles[i].wall = W_NONE;
		_tiles[i].trap = TRAP_NONE;
	}
}

void mapTool::setMap()
{
	if (_crtSelect == CTRL_TERRAINDRAW)
	{
		//지정한 타일셋에서 클릭한 애를 현재 타일로 저장한다.
		for (int i = 0; i < TERRAINTILEX * TERRAINTILEY; i++)
		{//지형
			if (PtInRect(&_terrainTile[i].rcTile, _ptMouse))
			{
				_currentTile.x = _terrainTile[i].terrainFrameX;
				_currentTile.y = _terrainTile[i].terrainFrameY;
				break;
			}
		}
	}

	if (_crtSelect == CTRL_WALLDRAW)
	{
		for (int i = 0; i < WALLTILEX * WALLTILEY; i++)
		{//벽
			if (PtInRect(&_wallTile[i].rcTile, _ptMouse))
			{
				_currentTile.x = _wallTile[i].terrainFrameX;
				_currentTile.y = _wallTile[i].terrainFrameY;
				break;
			}
		}
	}

	if (_crtSelect == CTRL_TRAP)
	{
		for (int i = 0; i < TRAPTILEX * TRAPTILEY; i++)
		{//함정
			if (PtInRect(&_trapTile[i].rcTile, _ptMouse))
			{
				_currentTile.x = _trapTile[i].terrainFrameX;
				_currentTile.y = _trapTile[i].terrainFrameY;

				break;
			}
		}
	}

	//위에 클릭하여 저장한 타일을 맵 상에 그려라
	for (int i = 0; i < TILEX * TILEY; i++)
	{


		if (PtInRect(&_tiles[i].rc, _ptMouse))
		{
			_tiles[i].isRender = true;
			if (_crtSelect == CTRL_TERRAINDRAW)
			{
				_tiles[i].type = TYPE_TERRAIN;
				_tiles[i].terrainFrameX = _currentTile.x;
				_tiles[i].terrainFrameY = _currentTile.y;

				_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
			}
			else if (_crtSelect == CTRL_WALLDRAW)
			{
				_tiles[i].type = TYPE_WALL;
				_tiles[i].wallFrameX = _currentTile.x;
				_tiles[i].wallFrameY = _currentTile.y;

				_tiles[i].wall = wallSelect(_currentTile.x, _currentTile.y);
			}
			else if (_crtSelect == CTRL_TRAP)
			{
				_tiles[i].type = TYPE_TRAP;
				_tiles[i].trapFrameX = _currentTile.x;
				_tiles[i].trapFrameY = _currentTile.y;

				_tiles[i].trap = trapSelect(_currentTile.x, _currentTile.y);
			}
			else if (_crtSelect == CTRL_ERASER)
			{
				_tiles[i].wallFrameX = NULL;
				_tiles[i].wallFrameY = NULL;
				_tiles[i].wall = W_NONE;
				_tiles[i].trapFrameX = NULL;
				_tiles[i].trapFrameY = NULL;
				_tiles[i].trap = TRAP_NONE;
			}

			InvalidateRect(_hWnd, NULL, false);
			break;
		}
	}
}

void mapTool::save()
{
	HANDLE file;
	DWORD write;
	// "SaveFile.map"
	// "BossStageFile.map"
	file = CreateFile("SaveFile.map", GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);
	WriteFile(file, _pos, sizeof(int) * 2, &write, NULL);

	CloseHandle(file);

}


void mapTool::load()
{
	HANDLE file;
	DWORD read;
	
	file = CreateFile("SaveFile.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	ReadFile(file, _pos, sizeof(int) * 2, &read, NULL);

	//맵을 불로온 직후 타일의 속성을 매겨준다


	CloseHandle(file);
}



TERRAIN mapTool::terrainSelect(int frameX, int frameY)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (frameX == j && frameY == i) return TR_BASIC_STAGE_TILE;
			if (frameX == j + 3 && frameY == i) return TR_BASIC_COMBO_TILE;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (frameX == i && frameY == 4) return TR_BOSS_STAGE_TILE;
		if (frameX == i + 3 && frameY == 4) return TR_BOSS_COMBO_TILE;
	}
	for (int i = 0; i < 2; i++)
	{
		if (frameX == i && frameY == 5) return TR_STAIR;
	}
	if (frameX == 3 && frameY == 5) return TR_SHOP;
	if (frameX == 5 && frameY == 5) return TR_NONE;

	return TR_BASIC_STAGE_TILE;
}

WALL mapTool::wallSelect(int frameX, int frameY)
{
	for (int i = 0; i < 16; i++) { if (frameX == i && frameY == 0) return W_WALL; }
	for (int i = 0; i < 13; i++)
	{
		if (frameX == i && frameY == 1) return W_ITEM_WALL;
		if (frameX == i && frameY == 2) return W_BOSS_WALL;
	}
	if (frameX == 13 && frameY == 1) return W_WALL2;
	if (frameX == 13 && frameY == 1) return W_WALL2;
	if (frameX == 0 && frameY == 3) return W_TORCH;
	if (frameX == 4 && frameY == 3) return W_FIRE_WALL;
	for (int i = 0; i < 2; i++) { if (frameX == i + 6 && frameY == 3) return W_DOOR; }
	for (int i = 0; i < 2; i++) { if (frameX == i + 8 && frameY == 3) return W_SHOP_WALL; }
	if (frameX == 10 && frameY == 3) return W_DOOR;

	for (int i = 0; i < 3; i++)
	{
		if (frameX == i + 13 && frameY == 1) return W_NONE;
		if (frameX == i + 13 && frameY == 2) return W_NONE;
	}
	for (int i = 0; i < 5; i++)
	{
		if (frameX == i + 11 && frameY == 3) return W_NONE;
	}
	return W_WALL;
}

TRAP mapTool::trapSelect(int frameX, int frameY)
{
	for (int i = 0; i < 2; i++)
	{
		if (frameX == i && frameY == 0) return TRAP_SLOW_BEAT;
		if (frameX == i && frameY == 1) return TRAP_LT_JUMP;
		if (frameX == i && frameY == 2) return TRAP_L_JUMP;
		if (frameX == i && frameY == 3) return TRAP_LB_JUMP;
		if (frameX == i && frameY == 4) return TRAP_BOMB;

		if (frameX == i + 2 && frameY == 0) return TRAP_FAST_BEAT;
		if (frameX == i + 2 && frameY == 1) return TRAP_T_JUMP;
		if (frameX == i + 2 && frameY == 2) return TRAP_CONFUSE;
		if (frameX == i + 2 && frameY == 3) return TRAP_B_JUMP;
		if (frameX == i + 2 && frameY == 4) return TRAP_SHADOW;

		if (frameX == i + 4 && frameY == 0) return TRAP_MUTE;
		if (frameX == i + 4 && frameY == 1) return TRAP_RT_JUMP;
		if (frameX == i + 4 && frameY == 2) return TRAP_R_JUMP;
		if (frameX == i + 4 && frameY == 3) return TRAP_RB_JUMP;
		if (frameX == i + 4 && frameY == 4) return TRAP_NONE;

	}
	for (int i = 0; i < 3; i++)
	{
		if (frameX == i && frameY == 5) return TRAP_NIDDLE;
		if (frameX == i && frameY == 6) return TRAP_NIDDLE_SHADOW;
		if (frameX == i + 3 && frameY == 6) return TRAP_NONE;
	}

	return TRAP_SLOW_BEAT;
}

