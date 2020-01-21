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
	// ���� ����� ���� 
	_WINSIZEX = 1880;
	_WINSIZEY = 900;
	setWindowsSize(WINSTARTX, WINSTARTY, _WINSIZEX, _WINSIZEY);
	resizeWindow(WINNAME, _WINSIZEX, _WINSIZEY);
	_backBuffer->init(_WINSIZEX, _WINSIZEY);
	setup();

	return S_OK;
}

void mapTool::release()
{

}


void mapTool::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		setMap();
	}
}



void mapTool::render()
{
	//PatBlt(CAMERAMANAGER->getWorldDC(), 0, 0, _WINSIZEX, _WINSIZEY, WHITENESS);
	//TextOut(getMemDC(), 700, 700, str,strlen(str));
	//����
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		Rectangle(CAMERAMANAGER->getWorldDC(), _tiles[i].rc);
		IMAGEMANAGER->frameRender("terrainTiles", CAMERAMANAGER->getWorldDC(),
			_tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	}
	//�� 
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tiles[i].wall == W_NONE) continue;

		IMAGEMANAGER->frameRender("wallTiles", CAMERAMANAGER->getWorldDC(),
			_tiles[i].rc.left, _tiles[i].rc.top - 32,
			_tiles[i].wallFrameX, _tiles[i].wallFrameY);
	}
	//����
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tiles[i].trap == TRAP_NONE) continue;

		IMAGEMANAGER->frameRender("trapTiles", CAMERAMANAGER->getWorldDC(),
			_tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].trapFrameX, _tiles[i].trapFrameY);
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

	CAMERAMANAGER->getWorldImage()->render(getMemDC());
	// ī�޶� �ڿ� �׷��� 
	/*_btnSave = CreateWindow("button", "����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1100, 500, 100, 30, _hWnd, HMENU(0), _hInstance, NULL);
	_btnLoad = CreateWindow("button", "�ҷ�����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON , 1200, 500, 100, 30, _hWnd, HMENU(1), _hInstance, NULL);
	_btnObjectDraw = CreateWindow("button", "������Ʈ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1100, 700, 100, 30, _hWnd, HMENU(2), _hInstance, NULL);
	_btnTerrainDraw = CreateWindow("button", "����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1200, 700, 100, 30, _hWnd, HMENU(3), _hInstance, NULL);
	_btnWallDraw = CreateWindow("button", "��", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1300, 700, 100, 30, _hWnd, HMENU(5), _hInstance, NULL);
	_btnTrap = CreateWindow("button", "����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1400, 700, 100, 30, _hWnd, HMENU(8), _hInstance, NULL);
	_btnEraser = CreateWindow("button", "���찳", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1500, 700, 100, 30, _hWnd, HMENU(10), _hInstance, NULL);
	_btnPlay = CreateWindow("button", "���� â", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1600, 700, 100, 30, _hWnd, HMENU(9), _hInstance, NULL);*/
	//===========================================================
	//_backBuffer->render(getHDC(), 0, 0);
}

void mapTool::setup()
{
	_saveButton.rc = RectMake(1100, 500, 100, 30);
	_loadButton.rc = RectMake(1210, 500, 100, 30);
	_terrainButton.rc = RectMake(1100, WINSIZEY - 20, 100, 30);
	_wallButton.rc = RectMake(1210, WINSIZEY - 20, 100, 30);
	//ó������ �������� �д�
	_crtSelect = CTRL_WALLDRAW;

	//���� ������Ʈ Ÿ�ϼ��� (����Ÿ��)
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
	//���� Ÿ�� ����
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

	//�� Ÿ�� ���� ���� ���� �ʿ��� 
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
	//Ÿ�� ��������
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			SetRect(&_tiles[i * TILEX + j].rc,
				j * TILESIZE,
				i * TILESIZE,
				j * TILESIZE + TILESIZE,
				i * TILESIZE + TILESIZE);
			//x / y ��
			_tiles[i * TILEX + j].XY.x = j * 52;
			_tiles[i * TILEX + j].XY.y = i * 52;
			//�ε��� x / y��ǥ ��
			_tiles[i * TILEX + j].idX = _tiles[i * TILEX + j].XY.x / 52;
			_tiles[i * TILEX + j].idY = _tiles[i * TILEX + j].XY.y / 52;
		}
	}

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
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
		//������ Ÿ�ϼ¿��� Ŭ���� �ָ� ���� Ÿ�Ϸ� �����Ѵ�.
		for (int i = 0; i < TERRAINTILEX * TERRAINTILEY; i++)
		{//����
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
		{//��
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
		{//����
			if (PtInRect(&_trapTile[i].rcTile, _ptMouse))
			{
				_currentTile.x = _trapTile[i].terrainFrameX;
				_currentTile.y = _trapTile[i].terrainFrameY;

				break;
			}
		}
	}

	//���� Ŭ���Ͽ� ������ Ÿ���� �� �� �׷���
	for (int i = 0; i < TILEX * TILEY; i++)
	{

		if (PtInRect(&_tiles[i].rc, _ptMouse))
		{
			if (_crtSelect == CTRL_TERRAINDRAW)
			{
				_tiles[i].terrainFrameX = _currentTile.x;
				_tiles[i].terrainFrameY = _currentTile.y;

				_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
			}
			else if (_crtSelect == CTRL_WALLDRAW)
			{
				_tiles[i].wallFrameX = _currentTile.x;
				_tiles[i].wallFrameY = _currentTile.y;

				_tiles[i].wall = wallSelect(_currentTile.x, _currentTile.y);
			}
			else if (_crtSelect == CTRL_TRAP)
			{
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

	//���� �ҷο� ���� Ÿ���� �Ӽ��� �Ű��ش�


	CloseHandle(file);
}

//void mapTool::clickLeft()
//{
//	setMap()
//}

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
	//if (frameX == 5 && frameY == 5) return TR_NONE;

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
		//if (frameX == i + 13 && frameY == 1) return W_NONE;
		//if (frameX == i + 13 && frameY == 2) return W_NONE;
	}
	for (int i = 0; i < 5; i++)
	{
		//if (frameX == i + 11 && frameY == 3) return W_NONE;
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
		//if (frameX == i + 3 && frameY == 6) return TRAP_NONE;
	}

	return TRAP_SLOW_BEAT;
}

