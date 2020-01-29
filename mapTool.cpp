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
	
	//������������������ ���� ����� ���� ���������������������������������������������
	_WINSIZEX = 1800;
	_WINSIZEY = 900;
	setWindowsSize(WINSTARTX, WINSTARTY, _WINSIZEX, _WINSIZEY);
	resizeWindow(WINNAME, _WINSIZEX, _WINSIZEY);
	_backBuffer->init(_WINSIZEX, _WINSIZEY);
	//������������������ Ÿ�� â���� �����ϰ� �ʻ� �׷��� ���������������������������������������������
	setup();
	//������������������ ���콺 Ŭ�� ���������������������������������������������
	_startL = 0;
	_startT = 0;
	_isClick = false;
	
	destroyAllWindows();
	//������������������ ȭ�� ������ ������������������
	CAMERAMANAGER->set_CameraMapTool_XY(0, 0);

	_left = RectMake(0, 0, 25, 900);
	_top = RectMake(0, 0, 1800, 25);
	_right = RectMake(1775, 0, 25, 900);
	_bottom = RectMake(0, 875, 1800, 25);

	return S_OK;
}

void mapTool::release()
{

}

void mapTool::update()
{
	if(!_isClick) palette_Click();			// �ȷ�Ʈ Ŭ�� �Լ�
	if(!_palette.isClick) tile_Click();		// ���콺 ���� Ŭ�� ����

	// ���� �̵� ��Ʈ�� ���콺�� �ִٸ�, ī�޶� ��ǥ�� �ش� �ӵ���ŭ �̵� �����ش�. 
	if (PtInRect(&_left, _ptMouse)) { CAMERAMANAGER->set_CameraPos_Update(CAMERAMANAGER->get_CameraX() - SCREENMOVESPEED, CAMERAMANAGER->get_CameraY()); }
	if (PtInRect(&_top, _ptMouse)) { CAMERAMANAGER->set_CameraPos_Update(CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY() - SCREENMOVESPEED); }
	if (PtInRect(&_right, _ptMouse)) { CAMERAMANAGER->set_CameraPos_Update(CAMERAMANAGER->get_CameraX() + SCREENMOVESPEED, CAMERAMANAGER->get_CameraY()); }
	if (PtInRect(&_bottom, _ptMouse)) { CAMERAMANAGER->set_CameraPos_Update(CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY() + SCREENMOVESPEED); }
	CAMERAMANAGER->CameraMapTool_Correction();
	// ���콺 ��ġ�� Ÿ���� ��Ʈ�� �����´�.
	mouseRectUpdate();
}

void mapTool::save()
{
	HANDLE file;
	DWORD write;
	// "SaveFile.map"
	//"Boss_SaveFile.map"
	//"Stage_SaveFile.map"
	file = CreateFile("Stage_SaveFile.map", GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);
	WriteFile(file, _pos, sizeof(int) * 2, &write, NULL);

	CloseHandle(file);

}

void mapTool::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("Stage_SaveFile.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	ReadFile(file, _pos, sizeof(int) * 2, &read, NULL);

	//���� �ҷο� ���� Ÿ���� �Ӽ��� �Ű��ش�


	CloseHandle(file);
}


void mapTool::render()
{
	PatBlt(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), _WINSIZEX, _WINSIZEY, BLACKNESS);
	//TextOut(getMemDC(), 700, 700, str,strlen(str)); 
	//����
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		//Rectangle(CAMERAMANAGER->getWorldDC(), _tiles[i].rc);
		if (_tiles[i].isRender == true)
		{
			_tiles[i].type = TYPE_TERRAIN;
			//Rectangle(CAMERAMANAGER->getWorldDC(), _tiles[i].rc);
			IMAGEMANAGER->frameRender("terrainTiles", CAMERAMANAGER->getWorldDC(),
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		}
	}
	//����
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tiles[i].trap == TRAP_NONE) continue;
		if (_tiles[i].isRender == true)
		{
			_tiles[i].type = TYPE_TRAP;
			//Rectangle(CAMERAMANAGER->getWorldDC(), _tiles[i].rc);
			IMAGEMANAGER->frameRender("trapTiles", CAMERAMANAGER->getWorldDC(),
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].trapFrameX, _tiles[i].trapFrameY);
		}
	}
	//��
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tiles[i].armor == A_NONE) continue;
		if (_tiles[i].isRender == true)
		{
			_tiles[i].type = TYPE_ITEM_ARMOR;
			//Rectangle(CAMERAMANAGER->getWorldDC(), _tiles[i].rc);
			IMAGEMANAGER->frameRender("armorTiles", CAMERAMANAGER->getWorldDC(),
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].armorFrameX, _tiles[i].armorFrameY);
		}
	}

	//����
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tiles[i].weapon == WP_NONE) continue;
		if (_tiles[i].isRender == true)
		{
			_tiles[i].type = TYPE_ITEM_WEAPON;
			//Rectangle(CAMERAMANAGER->getWorldDC(), _tiles[i].rc);
			IMAGEMANAGER->frameRender("weaponTiles", CAMERAMANAGER->getWorldDC(),
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].weaponFrameX, _tiles[i].weaponFrameY);
		}
	}

	//�� 
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tiles[i].wall == W_NONE) continue;
		if (_tiles[i].isRender == true)
		{
			_tiles[i].type = TYPE_WALL;
			//Rectangle(CAMERAMANAGER->getWorldDC(), _tiles[i].rc);
			IMAGEMANAGER->frameRender("wallTiles", CAMERAMANAGER->getWorldDC(),
				_tiles[i].rc.left, _tiles[i].rc.top - 30,
				_tiles[i].wallFrameX, _tiles[i].wallFrameY);
		}
	}
	
	CAMERAMANAGER->getWorldImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), 1800,900);
	
	if (_isClick)
	{
		Rectangle(getMemDC(), _startL, _startT, _endR, _endB);
	}
	
	//Rectangle(getMemDC(), _saveButton.rc);
	//Rectangle(getMemDC(), _loadButton.rc);
	//Rectangle(getMemDC(), _terrainButton.rc);
	//Rectangle(getMemDC(), _wallButton.rc);
	//Rectangle(getMemDC(), _trapButton.rc);
	//Rectangle(getMemDC(), _armorButton.rc);
	//Rectangle(getMemDC(), _weaponButton.rc);
	IMAGEMANAGER->findImage("save")->render(getMemDC(), _saveButton.rc.left, _saveButton.rc.top);
	IMAGEMANAGER->findImage("load")->render(getMemDC(), _loadButton.rc.left, _loadButton.rc.top);
	IMAGEMANAGER->findImage("terrain")->render(getMemDC(), _terrainButton.rc.left, _terrainButton.rc.top);
	IMAGEMANAGER->findImage("wall")->render(getMemDC(), _wallButton.rc.left, _wallButton.rc.top);
	IMAGEMANAGER->findImage("trap")->render(getMemDC(), _trapButton.rc.left, _trapButton.rc.top);
	IMAGEMANAGER->findImage("armor")->render(getMemDC(), _armorButton.rc.left, _armorButton.rc.top);
	IMAGEMANAGER->findImage("weapon")->render(getMemDC(), _weaponButton.rc.left, _weaponButton.rc.top);
	Rectangle(getMemDC(), _eraseButton.rc);


	//Rectangle(getMemDC(), _left);
	IMAGEMANAGER->findImage("left")->alphaRender(getMemDC(), _left.left, _left.top, 200);
	//Rectangle(getMemDC(), _top);
	IMAGEMANAGER->findImage("top")->alphaRender(getMemDC(), _top.left, _top.top, 200);
	//Rectangle(getMemDC(), _right);
	IMAGEMANAGER->findImage("right")->alphaRender(getMemDC(), _right.left, _right.top, 200);
	//Rectangle(getMemDC(), _bottom);
	IMAGEMANAGER->findImage("bottom")->alphaRender(getMemDC(), _bottom.left, _bottom.top, 200);

	//Rectangle(getMemDC(), _mouseEffect.mouseRect);

	if (_crtSelect == CTRL_TERRAINDRAW)
	{
		//IMAGEMANAGER->render("terrainTiles", getMemDC(), _WINSIZEX - IMAGEMANAGER->findImage("terrainTiles")->getWidth(), 0);
		/*for (int i = 0; i < TERRAINTILEX * TERRAINTILEY; ++i)
		{
			Rectangle(CAMERAMANAGER->getWorldDC(), _terrainTile[i].rcTile);
		}*/

		IMAGEMANAGER->findImage("terrainTiles")->alphaFrameRender(getMemDC(),
			_mouseEffect.mouseRect.left, _mouseEffect.mouseRect.top,
			_mouseEffect.frameX, _mouseEffect.frameY, 200);

		// ���� ��Ʈ ���
		//Rectangle(getMemDC(), _palette.terrainTile);
		IMAGEMANAGER->render("terrainPalette", getMemDC(), _palette.terrainTile.left - 24, _palette.terrainTile.top);
		

		// �ȷ�Ʈ ��Ʈ ���
		for (int i = 0; i < TERRAINTILEY; ++i)
		{
			for (int j = 0; j < TERRAINTILEX; ++j)
			{
				Rectangle(getMemDC(), _terrainTile[i * TERRAINTILEX + j].rcTile);

			}
		}
		
		// �ȷ�Ʈ �̹��� ���
		IMAGEMANAGER->render("terrainTiles", getMemDC(), _palette.terrainTile.left, _palette.terrainTile.top + 24);
	}

	if (_crtSelect == CTRL_ARMOR)
	{

		IMAGEMANAGER->findImage("armorTiles")->alphaFrameRender(getMemDC(),
			_mouseEffect.mouseRect.left, _mouseEffect.mouseRect.top,
			_mouseEffect.frameX, _mouseEffect.frameY, 200);

		// ���� ��Ʈ ���
		//Rectangle(getMemDC(), _palette.armorTile);
		IMAGEMANAGER->render("itemPalette", getMemDC(), _palette.armorTile.left - 26, _palette.armorTile.top);
		// �ȷ�Ʈ ��Ʈ ���
		for (int i = 0; i < ITEMTILEY; ++i)
		{
			for (int j = 0; j < ITEMTILEX; ++j)
			{
				Rectangle(getMemDC(), _armorTile[i * ITEMTILEX + j].rcTile);
			}
		}

		// �ȷ�Ʈ �̹��� ���
		IMAGEMANAGER->render("armorTiles", getMemDC(), _palette.armorTile.left, _palette.armorTile.top + 24);
	}

	if (_crtSelect == CTRL_WEAPON)
	{
		IMAGEMANAGER->findImage("weaponTiles")->alphaFrameRender(getMemDC(),
			_mouseEffect.mouseRect.left, _mouseEffect.mouseRect.top,
			_mouseEffect.frameX, _mouseEffect.frameY, 200);

		// ���� ��Ʈ ���
		//Rectangle(getMemDC(), _palette.weaponTile);
		IMAGEMANAGER->render("itemPalette", getMemDC(), _palette.weaponTile.left - 26, _palette.weaponTile.top);
		// �ȷ�Ʈ ��Ʈ ���
		for (int i = 0; i < ITEMTILEY; ++i)
		{
			for (int j = 0; j < ITEMTILEX; ++j)
			{
				Rectangle(getMemDC(), _weaponTile[i * ITEMTILEX + j].rcTile);
			}
		}

		// �ȷ�Ʈ �̹��� ���
		IMAGEMANAGER->render("weaponTiles", getMemDC(), _palette.weaponTile.left, _palette.weaponTile.top + 24);
	}

	if (_crtSelect == CTRL_TRAP)
	{
		/*for (int i = 0; i < TRAPTILEX * TRAPTILEY; ++i)
		{
			Rectangle(CAMERAMANAGER->getWorldDC(), _trapTile[i].rcTile);
		}*/
		IMAGEMANAGER->findImage("trapTiles")->alphaFrameRender(getMemDC(),
			_mouseEffect.mouseRect.left, _mouseEffect.mouseRect.top,
			_mouseEffect.frameX, _mouseEffect.frameY, 200);

		// ���� ��Ʈ ���
		//Rectangle(getMemDC(), _palette.trapTile);
		IMAGEMANAGER->render("trapPalette", getMemDC(), _palette.trapTile.left - 26, _palette.trapTile.top);
		// �ȷ�Ʈ ��Ʈ ���
		for (int i = 0; i < TRAPTILEY; ++i)
		{
			for (int j = 0; j < TRAPTILEX; ++j)
			{
				Rectangle(getMemDC(), _trapTile[i * TRAPTILEX + j].rcTile);
			}
		}
		// �ȷ�Ʈ �̹��� ���
		IMAGEMANAGER->render("trapTiles", getMemDC(), _palette.trapTile.left, _palette.trapTile.top + 24);
	}
	if (_crtSelect == CTRL_WALLDRAW)
	{
		/*for (int i = 0; i < WALLTILEX * WALLTILEY; ++i)
		{
			Rectangle(CAMERAMANAGER->getWorldDC(), _wallTile[i].rcTile);
		}*/
		/*	for (int i = 0; i < TILEX * TILEY; ++i)
			{
				Rectangle(getMemDC(), _wallTile[i].rcTile);
			}*/
		IMAGEMANAGER->findImage("wallTiles")->alphaFrameRender(getMemDC(),
			_mouseEffect.mouseRect.left, _mouseEffect.mouseRect.top - 32,
			_mouseEffect.frameX, _mouseEffect.frameY, 200);

		// ���� ��Ʈ ���
		//Rectangle(getMemDC(), _palette.wallTile);
		IMAGEMANAGER->render("wallPalette", getMemDC(), _palette.wallTile.left - 28, _palette.wallTile.top);
		// �ȷ�Ʈ ��Ʈ ���
		for (int i = 0; i < WALLTILEY; ++i)
		{
			for (int j = 0; j < WALLTILEX; ++j)
			{
				Rectangle(getMemDC(), _wallTile[i * WALLTILEX + j].rcTile);
			}
		}
		// �ȷ�Ʈ �̹��� ���
		IMAGEMANAGER->render("wallTiles", getMemDC(), _palette.wallTile.left, _palette.wallTile.top + 24);
	}
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
	_itemButton.rc = RectMake(210, 825, 52, 52);
	_armorButton.rc = RectMake(320, 825, 52, 52);
	_weaponButton.rc = RectMake(430, 825, 52, 52);
	_saveButton.rc = RectMake(1625, 825, 52, 52);
	_loadButton.rc = RectMake(1700, 825, 52, 52);
	_terrainButton.rc = RectMake(1100, 825, 52, 52);
	_wallButton.rc = RectMake(1210, 825, 52, 52);
	_trapButton.rc = RectMake(1320, 825, 52, 52);
	_eraseButton.rc = RectMake(1430, 825, 52, 52);
	
	// �ȷ�Ʈ �̵� â���� ����� ��Ʈ
	_palette.terrainTile = RectMake(_WINSIZEX - 25 - TERRAINTILEX * TILESIZE, 25, TERRAINTILEX * TILESIZE, 25);
	_palette.trapTile = RectMake(_WINSIZEX - 25 - TRAPTILEX * TILESIZE, 25, TRAPTILEX * TILESIZE, 25);
	_palette.armorTile = RectMake(_WINSIZEX - 25 - ITEMTILEX * TILESIZE, 25, ITEMTILEX * TILESIZE, 25);
	_palette.weaponTile = RectMake(_WINSIZEX - 25 - ITEMTILEX * TILESIZE, 25, ITEMTILEX * TILESIZE, 25);
	_palette.wallTile = RectMake(_WINSIZEX - 25 - WALLTILEX * TILESIZE, 25, WALLTILEX * TILESIZE, 25);
	_palette.isClick = false;
	_palette.pos_Start.x = _palette.pos_Start.y = _palette.pos_End.x = _palette.pos_End.y = NULL;

	//ó������ �������� �д�
	//_crtSelect = CTRL_WALLDRAW;

	//���� ������Ʈ Ÿ�ϼ��� (����Ÿ��)

	for (int i = 0; i < TERRAINTILEY; ++i)
	{
		for (int j = 0; j < TERRAINTILEX; ++j)
		{
			_terrainTile[i * TERRAINTILEX + j].terrainFrameX = j;
			_terrainTile[i * TERRAINTILEX + j].terrainFrameY = i;
			SetRect(&_terrainTile[i * TERRAINTILEX + j].rcTile,
				_palette.terrainTile.left + j * TILESIZE, _palette.terrainTile.bottom + i * TILESIZE,
				_palette.terrainTile.left + j * TILESIZE + TILESIZE, _palette.terrainTile.bottom + i * TILESIZE + TILESIZE);
		}
	}
	//�� Ÿ�� ����
	for (int i = 0; i < ITEMTILEY; ++i)
	{
		for (int j = 0; j < ITEMTILEX; ++j)
		{
			_armorTile[i * ITEMTILEX + j].terrainFrameX = j;
			_armorTile[i * ITEMTILEX + j].terrainFrameY = i;
			SetRect(&_armorTile[i * ITEMTILEX + j].rcTile,
				_palette.armorTile.left + j * TILESIZE, _palette.armorTile.bottom + i * TILESIZE,
				_palette.armorTile.left + j * TILESIZE + TILESIZE, _palette.armorTile.bottom + i * TILESIZE + TILESIZE);
		}
	}
	//���� Ÿ�� ����
	for (int i = 0; i < ITEMTILEY; ++i)
	{
		for (int j = 0; j < ITEMTILEX; ++j)
		{
			_weaponTile[i * ITEMTILEX + j].terrainFrameX = j;
			_weaponTile[i * ITEMTILEX + j].terrainFrameY = i;
			SetRect(&_weaponTile[i * ITEMTILEX + j].rcTile,
				_palette.weaponTile.left + j * TILESIZE, _palette.weaponTile.bottom + i * TILESIZE,
				_palette.weaponTile.left + j * TILESIZE + TILESIZE, _palette.weaponTile.bottom + i * TILESIZE + TILESIZE);
		}
	}
	//���� Ÿ�� ����
	for (int i = 0; i < TRAPTILEY; ++i)
	{
		for (int j = 0; j < TRAPTILEX; ++j)
		{
			_trapTile[i * TRAPTILEX + j].terrainFrameX = j;
			_trapTile[i * TRAPTILEX + j].terrainFrameY = i;

			SetRect(&_trapTile[i * TRAPTILEX + j].rcTile,
				_palette.trapTile.left + j * TILESIZE, _palette.trapTile.bottom + i * TILESIZE,
				_palette.trapTile.left + j * TILESIZE + TILESIZE, _palette.trapTile.bottom + i * TILESIZE + TILESIZE);
		}
	}
	//�� Ÿ�� ���� ���� ���� �ʿ��� 
	for (int i = 0; i < WALLTILEY; ++i)
	{
		for (int j = 0; j < WALLTILEX; ++j)
		{
			_wallTile[i * WALLTILEX + j].terrainFrameX = j;
			_wallTile[i * WALLTILEX + j].terrainFrameY = i;

			SetRect(&_wallTile[i * WALLTILEX + j].rcTile,
				_palette.wallTile.left + j * TILESIZE, _palette.wallTile.bottom + (i * 2) * TILESIZE,
				_palette.wallTile.left + j * TILESIZE + TILESIZE, _palette.wallTile.bottom + (i * 2) * TILESIZE + (TILESIZE * 2));
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
		_tiles[i].type = TYPE_NONE;
		_tiles[i].isRender = false;
		_tiles[i].terrainFrameX = 5;
		_tiles[i].terrainFrameY = 5;
		_tiles[i].armorFrameX = 3;
		_tiles[i].armorFrameY = 4;
		_tiles[i].weaponFrameX = 3;
		_tiles[i].weaponFrameY = 4;
		_tiles[i].trapFrameX = 5;
		_tiles[i].trapFrameY = 6;
		_tiles[i].wallFrameX = 15;
		_tiles[i].wallFrameY = 3;
		_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		_tiles[i].terrain = TR_NONE;
		_tiles[i].armor = A_NONE;
		_tiles[i].weapon = WP_NONE;
		_tiles[i].trap = TRAP_NONE;
		_tiles[i].wall = W_NONE;
		_tiles[i].alphaValue = 255; // 0~255 
	}
}

void mapTool::setMap()
{
		if (_crtSelect == CTRL_TERRAINDRAW)
		{
			//������ Ÿ�ϼ¿��� Ŭ���� �ָ� ���� Ÿ�Ϸ� �����Ѵ�.
			for (int i = 0; i < TERRAINTILEX * TERRAINTILEY; i++)
			{
				//����
				if (PtInRect(&_terrainTile[i].rcTile, _ptMouse))
				{
					_currentTile.x = _terrainTile[i].terrainFrameX;
					_currentTile.y = _terrainTile[i].terrainFrameY;

					// ���콺 ����Ʈ�� ���� ������ x, y�� �޾ƿ´�.
					_mouseEffect.frameX = _terrainTile[i].terrainFrameX;
					_mouseEffect.frameY = _terrainTile[i].terrainFrameY;
					break;
				}
			}
		}
		if (_crtSelect == CTRL_ARMOR)
		{
			for (int i = 0; i < ITEMTILEX * ITEMTILEY; i++)
			{
				//��
				if (PtInRect(&_armorTile[i].rcTile, _ptMouse))
				{
					_currentTile.x = _armorTile[i].terrainFrameX;
					_currentTile.y = _armorTile[i].terrainFrameY;

					_mouseEffect.frameX = _armorTile[i].terrainFrameX;
					_mouseEffect.frameY = _armorTile[i].terrainFrameY;
					break;
				}
			}
		}
		if (_crtSelect == CTRL_WEAPON)
		{
			for (int i = 0; i < ITEMTILEX * ITEMTILEY; i++)
			{
				//��
				if (PtInRect(&_weaponTile[i].rcTile, _ptMouse))
				{
					_currentTile.x = _weaponTile[i].terrainFrameX;
					_currentTile.y = _weaponTile[i].terrainFrameY;

					_mouseEffect.frameX = _weaponTile[i].terrainFrameX;
					_mouseEffect.frameY = _weaponTile[i].terrainFrameY;
					break;
				}
			}
		}
		if (_crtSelect == CTRL_TRAP)
		{
			for (int i = 0; i < TRAPTILEX * TRAPTILEY; i++)
			{
				//����
				if (PtInRect(&_trapTile[i].rcTile, _ptMouse))
				{
					_currentTile.x = _trapTile[i].terrainFrameX;
					_currentTile.y = _trapTile[i].terrainFrameY;

					_mouseEffect.frameX = _trapTile[i].terrainFrameX;
					_mouseEffect.frameY = _trapTile[i].terrainFrameY;
					break;
				}
			}
		}
		if (_crtSelect == CTRL_WALLDRAW)
		{
			for (int i = 0; i < WALLTILEX * WALLTILEY; i++)
			{
				//��
				if (PtInRect(&_wallTile[i].rcTile, _ptMouse))
				{
					_currentTile.x = _wallTile[i].terrainFrameX;
					_currentTile.y = _wallTile[i].terrainFrameY;

					_mouseEffect.frameX = _wallTile[i].terrainFrameX;
					_mouseEffect.frameY = _wallTile[i].terrainFrameY;
					break;
				}
			}
		}
	

		//���� Ŭ���Ͽ� ������ Ÿ���� �� �� �׷���
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			// �ȷ�Ʈ ���� �Ҷ� �ڿ� Ÿ���� ������ �ʰ� �ϱ� ���ؼ�
			if (using_Palette()) break;

			RECT temp;

			// ptMouse�� ��ǥ�� ���� ��ǥ�� �ٲ��ش�.
			POINT ptMouse_Temp;
			ptMouse_Temp.x = _ptMouse.x + CAMERAMANAGER->get_CameraX();
			ptMouse_Temp.y = _ptMouse.y + CAMERAMANAGER->get_CameraY();

			// �� Ÿ�ϸ� Ŭ�� �ϰų�, �巡�׸� ���� ��� ��θ� ó�� �Ѵ�.
			if (IntersectRect(&temp, &_tiles[i].rc, &_RectCreate.rc) || PtInRect(&_tiles[i].rc, ptMouse_Temp))
			{
				_tiles[i].isRender = true;

				if (_crtSelect == CTRL_TERRAINDRAW)
				{
					_tiles[i].type = TYPE_TERRAIN;
					_tiles[i].terrainFrameX = _currentTile.x;
					_tiles[i].terrainFrameY = _currentTile.y;

					_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
				}
				else if (_crtSelect == CTRL_ARMOR)
				{
					_tiles[i].type = TYPE_ITEM_ARMOR;
					_tiles[i].armorFrameX = _currentTile.x;
					_tiles[i].armorFrameY = _currentTile.y;

					_tiles[i].armor = armorSelect(_currentTile.x, _currentTile.y);
				}
				else if (_crtSelect == CTRL_WEAPON)
				{
					_tiles[i].type = TYPE_ITEM_WEAPON;
					_tiles[i].weaponFrameX = _currentTile.x;
					_tiles[i].weaponFrameY = _currentTile.y;

					_tiles[i].weapon = weaponSelect(_currentTile.x, _currentTile.y);
				}
				else if (_crtSelect == CTRL_TRAP)
				{
					_tiles[i].type = TYPE_TRAP;
					_tiles[i].trapFrameX = _currentTile.x;
					_tiles[i].trapFrameY = _currentTile.y;

					_tiles[i].trap = trapSelect(_currentTile.x, _currentTile.y);
				}
				else if (_crtSelect == CTRL_WALLDRAW)
				{
					_tiles[i].type = TYPE_WALL;
					_tiles[i].wallFrameX = _currentTile.x;
					_tiles[i].wallFrameY = _currentTile.y;

					_tiles[i].wall = wallSelect(_currentTile.x, _currentTile.y);
				}
				else if (_crtSelect == CTRL_ERASER)
				{
					_tiles[i].terrainFrameX = 5;
					_tiles[i].terrainFrameY = 5;
					_tiles[i].terrain = TR_NONE;
					_tiles[i].trapFrameX = NULL;
					_tiles[i].trapFrameY = NULL;
					_tiles[i].trap = TRAP_NONE;
					_tiles[i].armorFrameX = NULL;
					_tiles[i].armorFrameY = NULL;
					_tiles[i].armor = A_NONE;
					_tiles[i].weaponFrameX = NULL;
					_tiles[i].weaponFrameY = NULL;
					_tiles[i].weapon = WP_NONE;
					_tiles[i].wallFrameX = NULL;
					_tiles[i].wallFrameY = NULL;
					_tiles[i].wall = W_NONE;
				}

				InvalidateRect(_hWnd, NULL, false);
				//break;
			}
		}
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

	return TR_NONE;
}

WALL mapTool::wallSelect(int frameX, int frameY)
{
	for (int i = 0; i < 16; i++) { if (frameX == i && frameY == 0) return W_WALL; }
	for (int i = 0; i < 12; i++)
	{
		if (frameX == i && frameY == 1) return W_ITEM_WALL;
	}
	if (frameX == 12 && frameY == 1) return W_WALL2;
	for (int i = 0; i < 13; i++)
	{
		if (frameX == i && frameY == 2) return W_BOSS_WALL;
	}
	for (int i = 0; i < 2; i++) { if (frameX == i && frameY == 3) return W_SHOP_WALL; }
	if (frameX == 2 && frameY == 3) return W_END_WALL;
	for (int i = 0; i < 2; i++) { if (frameX == i + 3 && frameY == 3) return W_DOOR; }
	

	for (int i = 0; i < 3; i++)
	{
		if (frameX == i + 13 && frameY == 1) return W_NONE;
		if (frameX == i + 13 && frameY == 2) return W_NONE;
	}
	for (int i = 0; i < 11; i++)
	{
		if (frameX == i + 5 && frameY == 3) return W_NONE;
	}
	return W_NONE;
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

	return TRAP_NONE;
}

ARMOR mapTool::armorSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0) return A_HELMET;
	if (frameX == 0 && frameY == 1) return A_ARMOR_1;
	if (frameX == 1 && frameY == 1) return A_ARMOR_2;
	if (frameX == 2 && frameY == 1) return A_ARMOR_3;
	if (frameX == 3 && frameY == 1) return A_ARMOR_4;
	if (frameX == 0 && frameY == 2) return A_BOOTS;
	if (frameX == 0 && frameY == 3) return A_RING;
	if (frameX == 0 && frameY == 4) return A_TORCH_1;
	if (frameX == 1 && frameY == 4) return A_TORCH_2;
	if (frameX == 2 && frameY == 4) return A_TORCH_3;
	if (frameX == 3 && frameY == 4) return A_NONE;
	for (int i = 0; i < 3; i++)
	{
		if (frameX == i + 1 && frameY == 0) return A_NONE;
		if (frameX == i + 1 && frameY == 2) return A_NONE;
		if (frameX == i + 1 && frameY == 3) return A_NONE;
	}

	return A_NONE;
}

WEAPON mapTool::weaponSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0) return WP_DAGGER_1;
	if (frameX == 1 && frameY == 0) return WP_DAGGER_2;
	if (frameX == 2 && frameY == 0) return WP_SWORD;
	if (frameX == 3 && frameY == 0) return WP_LONG_SWORD;
	if (frameX == 0 && frameY == 1) return WP_BOMB;
	if (frameX == 1 && frameY == 1) return WP_RIFLE;
	if (frameX == 2 && frameY == 1) return WP_SHOTGUN;
	if (frameX == 3 && frameY == 1) return WP_NONE;
	if (frameX == 0 && frameY == 2) return WP_SPEAR;
	if (frameX == 1 && frameY == 2) return WP_MACE;
	if (frameX == 0 && frameY == 3) return WP_WHIP;
	if (frameX == 1 && frameY == 3) return WP_NINETAILS_WHIP;
	if (frameX == 0 && frameY == 4) return WP_BOW;
	if (frameX == 1 && frameY == 4) return WP_CROSS_BOW;
	for (int i = 0; i < 2; i++)
	{
		if (frameX == i + 2 && frameY == 2) return WP_NONE;
		if (frameX == i + 2 && frameY == 3) return WP_NONE;
		if (frameX == i + 2 && frameY == 4) return WP_NONE;
	}
	return WP_NONE;
}

void mapTool::tile_Click()
{
	if (!_isClick)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			// Ŭ���� ��ġ�� �����صд�.
			_startL = _ptMouse.x;
			_startT = _ptMouse.y;
			_isClick = true;
		}
	}

	if (_isClick)
	{
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			_isClick = false;
		}
	}

	if (_isClick)
	{
		// ���콺 ���� ��ư Ŭ���� �����ϰ� ������ (â �̵��� �ϰ� �������� ���� �ϸ� �ȵ�)
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			// ������ ��ġ�� �����صд�.
			_endR = _ptMouse.x;
			_endB = _ptMouse.y;

			// ��ŸƮ, ���带 �̿��Ͽ� ��Ʈ�� ���� ���ش�. (�̰��� Ÿ�� �浹�� ��Ʈ�̴�.)
			rectCreate_Update();

			// 1. �޴� ����
			menu_Choice();

			// 2. ��� ����
			setMap();
		}
	}

	//cout << "x : " << _ptMouse.x << endl;
	//cout << "y : " << _ptMouse.y << endl;
	//cout << "startx : " << _startL << endl;
	//cout << "starty : " << _startT << endl;
	//cout << "endR : " << _endR << endl;
	//cout << "endB : " << _endB << endl;
	//cout << _isClick << endl;
	//cout << "cameraX : " << CAMERAMANAGER->get_CameraX() << endl;
	//cout << "cameraY : " << CAMERAMANAGER->get_CameraY() << endl;
}

void mapTool::palette_Click()
{
	if (!_palette.isClick)
	{
		switch (_crtSelect)
		{
		case CTRL_TERRAINDRAW:
			// �ȷ�Ʈ ��Ʈ�� ���콺�� Ŭ���ϰ� ������
			if (PtInRect(&_palette.terrainTile, _ptMouse))
			{
				palette_Click(true);
			}
			break;
		case CTRL_ARMOR:
			// �ȷ�Ʈ ��Ʈ�� ���콺�� Ŭ���ϰ� ������
			if (PtInRect(&_palette.armorTile, _ptMouse))
			{
				palette_Click(true);
			}
			break;
		case CTRL_WEAPON:
			// �ȷ�Ʈ ��Ʈ�� ���콺�� Ŭ���ϰ� ������
			if (PtInRect(&_palette.weaponTile, _ptMouse))
			{
				palette_Click(true);
			}
			break;

		case CTRL_TRAP:
			// �ȷ�Ʈ ��Ʈ�� ���콺�� Ŭ���ϰ� ������
			if (PtInRect(&_palette.trapTile, _ptMouse))
			{
				palette_Click(true);
			}
			break;
		case CTRL_WALLDRAW:
			// �ȷ�Ʈ ��Ʈ�� ���콺�� Ŭ���ϰ� ������
			if (PtInRect(&_palette.wallTile, _ptMouse))
			{
				palette_Click(true);
			}
			break;
		}
	}

	// Ŭ���� �� ���� ���� Ŭ���� ���� flase�� ������ �ٲ��ش�.
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _palette.isClick)
	{
		_palette.isClick = false;
	}


	// Ŭ���� �����ϴ� ���� ������ ���콺 ��ǥ�� ��� �������ش�.
	if (_palette.isClick)
	{
		_palette.pos_End.x = _ptMouse.x;
		_palette.pos_End.y = _ptMouse.y;
	}

	// Ŭ���� �ϰ� �����̴� ��ǥ��ŭ �ȷ�Ʈ ��Ʈ�� �ٽ� �׷��ش�.
	if (_palette.isClick) palette_Rect_Update();
}

void mapTool::palette_Click(bool start)
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && !_palette.isClick)
	{
		// Ŭ���� ������ ��ǥ�� �����Ѵ�.
		_palette.pos_Start.x = _ptMouse.x;
		_palette.pos_Start.y = _ptMouse.y;
		_palette.isClick = true;
	}
}

void mapTool::palette_Rect_Update()
{
	// TerrainDraw �ȷ�Ʈ ��Ʈ ����
	if (_crtSelect == CTRL_TERRAINDRAW)
	{
		palette_Move();
		
		for (int i = 0; i < TERRAINTILEY; ++i)
		{
			for (int j = 0; j < TERRAINTILEX; ++j)
			{
				SetRect(&_terrainTile[i * TERRAINTILEX + j].rcTile,
					_palette.terrainTile.left + j * TILESIZE, _palette.terrainTile.bottom + i * TILESIZE,
					_palette.terrainTile.left + j * TILESIZE + TILESIZE, _palette.terrainTile.bottom + i * TILESIZE + TILESIZE);
			}
		}
	}
	if (_crtSelect == CTRL_ARMOR)
	{
		palette_Move();

		for (int i = 0; i < ITEMTILEY; ++i)
		{
			for (int j = 0; j < ITEMTILEX; ++j)
			{
				SetRect(&_armorTile[i * ITEMTILEX + j].rcTile,
					_palette.armorTile.left + j * TILESIZE, _palette.armorTile.bottom + i * TILESIZE,
					_palette.armorTile.left + j * TILESIZE + TILESIZE, _palette.armorTile.bottom + i * TILESIZE + TILESIZE);
			}
		}
	}
	if (_crtSelect == CTRL_WEAPON)
	{
		palette_Move();

		for (int i = 0; i < ITEMTILEY; ++i)
		{
			for (int j = 0; j < ITEMTILEX; ++j)
			{
				SetRect(&_weaponTile[i * ITEMTILEX + j].rcTile,
					_palette.weaponTile.left + j * TILESIZE, _palette.weaponTile.bottom + i * TILESIZE,
					_palette.weaponTile.left + j * TILESIZE + TILESIZE, _palette.weaponTile.bottom + i * TILESIZE + TILESIZE);
			}
		}
	}
	// TrapDraw �ȷ�Ʈ ��Ʈ ����
	if (_crtSelect == CTRL_TRAP)
	{
		palette_Move();

		for (int i = 0; i < TRAPTILEY; ++i)
		{
			for (int j = 0; j < TRAPTILEX; ++j)
			{
				SetRect(&_trapTile[i * TRAPTILEX + j].rcTile,
					_palette.trapTile.left + j * TILESIZE, _palette.trapTile.bottom + i * TILESIZE,
					_palette.trapTile.left + j * TILESIZE + TILESIZE, _palette.trapTile.bottom + i * TILESIZE + TILESIZE);
			}
		}
	}

	// WallDraw �ȷ�Ʈ ��Ʈ ����
	if (_crtSelect == CTRL_WALLDRAW)
	{
		palette_Move();

		for (int i = 0; i < WALLTILEY; ++i)
		{
			for (int j = 0; j < WALLTILEX; ++j)
			{
				SetRect(&_wallTile[i * WALLTILEX + j].rcTile,
					_palette.wallTile.left + j * TILESIZE, _palette.wallTile.bottom + (i * 2) * TILESIZE,
					_palette.wallTile.left + j * TILESIZE + TILESIZE, _palette.wallTile.bottom + (i * 2) * TILESIZE + (TILESIZE * 2));
			}
		}
	}
}

void mapTool::palette_Move()
{
	// ��ŸƮ���� ������� �󸶳� �̵��ߴ��� �����ϰ�,
	// �� ���� �̿��Ͽ� ��Ʈ ��ġ�� �Ȱ��ش�.
	int moveX, moveY;
	moveX = moveY = 0;

	switch (_crtSelect)
	{
		case CTRL_TERRAINDRAW:

			// ���� ����� ���´ٸ� �̵� ������ ������ �Ǿ�� �Ѵ�.
			if (_palette.pos_Start.x - _palette.pos_End.x > 0)
			{
				moveX = _palette.pos_Start.x - _palette.pos_End.x;

				_palette.terrainTile.left -= moveX;
				_palette.terrainTile.right -= moveX;
			}

			// ���� ����� ���´ٸ� �̵� ������ ������ �Ǿ�� �Ѵ�.
			if (_palette.pos_Start.y - _palette.pos_End.y > 0)
			{
				moveY = _palette.pos_Start.y - _palette.pos_End.y;

				_palette.terrainTile.top -= moveY;
				_palette.terrainTile.bottom -= moveY;
			}

			// ���� ������ ���´ٸ� �̵� ������ �������� �Ǿ�� �Ѵ�.
			if (_palette.pos_Start.x - _palette.pos_End.x < 0)
			{
				moveX = _palette.pos_End.x - _palette.pos_Start.x;

				_palette.terrainTile.left += moveX;
				_palette.terrainTile.right += moveX;
			}

			// ���� ������ ���´ٸ� �̵� ������ �Ʒ����� �Ǿ�� �Ѵ�.
			if (_palette.pos_Start.y - _palette.pos_End.y < 0)
			{
				moveY = _palette.pos_End.y - _palette.pos_Start.y;

				_palette.terrainTile.top += moveY;
				_palette.terrainTile.bottom += moveY;
			}

			break;

		case CTRL_ARMOR:
			//��
			// ���� ����� ���´ٸ� �̵� ������ ������ �Ǿ�� �Ѵ�.
			if (_palette.pos_Start.x - _palette.pos_End.x > 0)
			{
				moveX = _palette.pos_Start.x - _palette.pos_End.x;

				_palette.armorTile.left -= moveX;
				_palette.armorTile.right -= moveX;
			}

			// ���� ����� ���´ٸ� �̵� ������ ������ �Ǿ�� �Ѵ�.
			if (_palette.pos_Start.y - _palette.pos_End.y > 0)
			{
				moveY = _palette.pos_Start.y - _palette.pos_End.y;

				_palette.armorTile.top -= moveY;
				_palette.armorTile.bottom -= moveY;
			}

			// ���� ������ ���´ٸ� �̵� ������ �������� �Ǿ�� �Ѵ�.
			if (_palette.pos_Start.x - _palette.pos_End.x < 0)
			{
				moveX = _palette.pos_End.x - _palette.pos_Start.x;

				_palette.armorTile.left += moveX;
				_palette.armorTile.right += moveX;
			}

			// ���� ������ ���´ٸ� �̵� ������ �Ʒ����� �Ǿ�� �Ѵ�.
			if (_palette.pos_Start.y - _palette.pos_End.y < 0)
			{
				moveY = _palette.pos_End.y - _palette.pos_Start.y;

				_palette.armorTile.top += moveY;
				_palette.armorTile.bottom += moveY;
			}
			break;
		case CTRL_WEAPON:
			//����
			// ���� ����� ���´ٸ� �̵� ������ ������ �Ǿ�� �Ѵ�.
			if (_palette.pos_Start.x - _palette.pos_End.x > 0)
			{
				moveX = _palette.pos_Start.x - _palette.pos_End.x;

				_palette.weaponTile.left -= moveX;
				_palette.weaponTile.right -= moveX;
			}

			// ���� ����� ���´ٸ� �̵� ������ ������ �Ǿ�� �Ѵ�.
			if (_palette.pos_Start.y - _palette.pos_End.y > 0)
			{
				moveY = _palette.pos_Start.y - _palette.pos_End.y;

				_palette.weaponTile.top -= moveY;
				_palette.weaponTile.bottom -= moveY;
			}

			// ���� ������ ���´ٸ� �̵� ������ �������� �Ǿ�� �Ѵ�.
			if (_palette.pos_Start.x - _palette.pos_End.x < 0)
			{
				moveX = _palette.pos_End.x - _palette.pos_Start.x;

				_palette.weaponTile.left += moveX;
				_palette.weaponTile.right += moveX;
			}

			// ���� ������ ���´ٸ� �̵� ������ �Ʒ����� �Ǿ�� �Ѵ�.
			if (_palette.pos_Start.y - _palette.pos_End.y < 0)
			{
				moveY = _palette.pos_End.y - _palette.pos_Start.y;

				_palette.weaponTile.top += moveY;
				_palette.weaponTile.bottom += moveY;
			}
			break;
		case CTRL_TRAP:

			// ���� ����� ���´ٸ� �̵� ������ ������ �Ǿ�� �Ѵ�.
			if (_palette.pos_Start.x - _palette.pos_End.x > 0)
			{
				moveX = _palette.pos_Start.x - _palette.pos_End.x;

				_palette.trapTile.left -= moveX;
				_palette.trapTile.right -= moveX;
			}

			// ���� ����� ���´ٸ� �̵� ������ ������ �Ǿ�� �Ѵ�.
			if (_palette.pos_Start.y - _palette.pos_End.y > 0)
			{
				moveY = _palette.pos_Start.y - _palette.pos_End.y;

				_palette.trapTile.top -= moveY;
				_palette.trapTile.bottom -= moveY;
			}

			// ���� ������ ���´ٸ� �̵� ������ �������� �Ǿ�� �Ѵ�.
			if (_palette.pos_Start.x - _palette.pos_End.x < 0)
			{
				moveX = _palette.pos_End.x - _palette.pos_Start.x;

				_palette.trapTile.left += moveX;
				_palette.trapTile.right += moveX;
			}

			// ���� ������ ���´ٸ� �̵� ������ �Ʒ����� �Ǿ�� �Ѵ�.
			if (_palette.pos_Start.y - _palette.pos_End.y < 0)
			{
				moveY = _palette.pos_End.y - _palette.pos_Start.y;

				_palette.trapTile.top += moveY;
				_palette.trapTile.bottom += moveY;
			}

			break;
		case CTRL_WALLDRAW:

			// ���� ����� ���´ٸ� �̵� ������ ������ �Ǿ�� �Ѵ�.
			if (_palette.pos_Start.x - _palette.pos_End.x > 0)
			{
				moveX = _palette.pos_Start.x - _palette.pos_End.x;

				_palette.wallTile.left -= moveX;
				_palette.wallTile.right -= moveX;
			}

			// ���� ����� ���´ٸ� �̵� ������ ������ �Ǿ�� �Ѵ�.
			if (_palette.pos_Start.y - _palette.pos_End.y > 0)
			{
				moveY = _palette.pos_Start.y - _palette.pos_End.y;

				_palette.wallTile.top -= moveY;
				_palette.wallTile.bottom -= moveY;
			}

			// ���� ������ ���´ٸ� �̵� ������ �������� �Ǿ�� �Ѵ�.
			if (_palette.pos_Start.x - _palette.pos_End.x < 0)
			{
				moveX = _palette.pos_End.x - _palette.pos_Start.x;

				_palette.wallTile.left += moveX;
				_palette.wallTile.right += moveX;
			}

			// ���� ������ ���´ٸ� �̵� ������ �Ʒ����� �Ǿ�� �Ѵ�.
			if (_palette.pos_Start.y - _palette.pos_End.y < 0)
			{
				moveY = _palette.pos_End.y - _palette.pos_Start.y;

				_palette.wallTile.top += moveY;
				_palette.wallTile.bottom += moveY;
			}

			break;
	}

	// ������ �����ٸ� ���� ��ǥ�� ������ ��ǥ�� �������ش�.
	_palette.pos_Start = _palette.pos_End;
}

void mapTool::menu_Choice()
{
	if (PtInRect(&_terrainButton.rc, _ptMouse)) { _crtSelect = CTRL_TERRAINDRAW; }
	if (PtInRect(&_itemButton.rc, _ptMouse)) { _crtSelect = CTRL_ITEM; }
	if (PtInRect(&_armorButton.rc, _ptMouse)) { _crtSelect = CTRL_ARMOR; }
	if (PtInRect(&_weaponButton.rc, _ptMouse)) { _crtSelect = CTRL_WEAPON; }
	if (PtInRect(&_trapButton.rc, _ptMouse)) { _crtSelect = CTRL_TRAP; }
	if (PtInRect(&_wallButton.rc, _ptMouse)) { _crtSelect = CTRL_WALLDRAW; }
	if (PtInRect(&_eraseButton.rc, _ptMouse)) { _crtSelect = CTRL_ERASER; }
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

void mapTool::rectCreate_Update()
{
	int sizeX, sizeY;
	sizeX = sizeY = 0;
	if (_startL - _endR > 0) sizeX = _startL - _endR;
	if (_startL - _endR < 0) sizeX = _endR - _startL;
	if (_startT - _endB > 0) sizeY = _startT - _endB;
	if (_startT - _endB < 0) sizeY = _endB - _startT;

	_RectCreate.rc = RectMake(_startL + CAMERAMANAGER->get_CameraX(), _startT + CAMERAMANAGER->get_CameraY(), sizeX, sizeY);

	// ���콺�� ��ŸƮ �������� 5�� �������� �׷����� �ִ°�
	if (_startL - _endR < 0 && _startT - _endB < 0)
	{
		sizeX = _endR - _startL;
		sizeY = _endB - _startT;

		_RectCreate.rc = RectMake(_startL + CAMERAMANAGER->get_CameraX(), _startT + CAMERAMANAGER->get_CameraY(), sizeX, sizeY);
	}

	// ���콺�� ��ŸƮ �������� 7�� �������� �׷����� �ִ°�
	if (_startL - _endR > 0 && _startT - _endB < 0)
	{
		sizeX = _startL - _endR;
		sizeY = _endB - _startT;

		_RectCreate.rc = RectMake(_startL - sizeX + CAMERAMANAGER->get_CameraX(), _startT + +CAMERAMANAGER->get_CameraY(), sizeX, sizeY);
	}

	// ���콺�� ��ŸƮ �������� 10�� �������� �׷����� �ִ°�
	if (_startL - _endR > 0 && _startT - _endB > 0)
	{
		sizeX = _startL - _endR;
		sizeY = _startT - _endB;

		_RectCreate.rc = RectMake(_startL - sizeX + CAMERAMANAGER->get_CameraX(), _startT - sizeY + +CAMERAMANAGER->get_CameraY(), sizeX, sizeY);
	}

	// ���콺�� ��ŸƮ �������� 2�� �������� �׷����� �ִ°�
	if (_startL - _endR < 0 && _startT - _endB > 0)
	{
		sizeX = _endR - _startL;
		sizeY = _startT - _endB;

		_RectCreate.rc = RectMake(_startL + CAMERAMANAGER->get_CameraX(), _startT - sizeY + sizeY + +CAMERAMANAGER->get_CameraY(), sizeX, sizeY);
	}

}

bool mapTool::using_Palette()
{
	// �ȷ�Ʈ ���� ���϶� true���� �����Ѵ�. (Ÿ�� ��°� ���´�)
	if (_crtSelect == CTRL_TERRAINDRAW)
	{
		for (int i = 0; i < TERRAINTILEX * TERRAINTILEY; i++)
		{
			if (PtInRect(&_terrainTile[i].rcTile, _ptMouse))
			{
				return true;
			}
		}
	}
	if (_crtSelect == CTRL_ARMOR)
	{
		for (int i = 0; i < ITEMTILEX * ITEMTILEY; i++)
		{
			if (PtInRect(&_armorTile[i].rcTile, _ptMouse))
			{
				return true;
			}
		}
	}
	if (_crtSelect == CTRL_WEAPON)
	{
		for (int i = 0; i < ITEMTILEX * ITEMTILEY; i++)
		{
			if (PtInRect(&_weaponTile[i].rcTile, _ptMouse))
			{
				return true;
			}
		}
	}
	if (_crtSelect == CTRL_TRAP)
	{
		for (int i = 0; i < TRAPTILEX * TRAPTILEY; i++)
		{
			if (PtInRect(&_trapTile[i].rcTile, _ptMouse))
			{
				return true;
			}
		}
	}
	if (_crtSelect == CTRL_WALLDRAW)
	{
		for (int i = 0; i < WALLTILEX * WALLTILEY; i++)
		{
			if (PtInRect(&_wallTile[i].rcTile, _ptMouse))
			{
				return true;
			}
		}
	}

	// false ���� ��ȯ �ȴٸ� ���� ����.
	return false;
}

void mapTool::mouseRectUpdate()
{
	// ���� ���콺�� ��� Ÿ�Ͽ� �ִ��� ã���ش�.
	// �׸��� �� ��Ʈ�� ������ ��ƿ´�.
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		// ptMouse�� ��ǥ�� ���� ��ǥ�� �ٲ��ش�.
		//POINT ptMouse_Temp;
		//ptMouse_Temp.x = _ptMouse.x + CAMERAMANAGER->get_CameraX();
		//ptMouse_Temp.y = _ptMouse.y + CAMERAMANAGER->get_CameraY();

		// ���� Ÿ�Ͽ� ���콺 �����Ͱ� ��ġ �ߴٸ� ��Ʈ ������ �����Ѵ�.
		if (PtInRect(&_tiles[i].rc, _ptMouse))
		{
			_mouseEffect.mouseRect = _tiles[i].rc;

			break;
		}
	}
}

void mapTool::clickButton()
{
}

