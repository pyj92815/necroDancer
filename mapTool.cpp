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
	
	//■■■■■■■■■■■■■■■■■ 맵툴 사이즈를 정의 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	_WINSIZEX = 1800;
	_WINSIZEY = 900;
	setWindowsSize(WINSTARTX, WINSTARTY, _WINSIZEX, _WINSIZEY);
	resizeWindow(WINNAME, _WINSIZEX, _WINSIZEY);
	_backBuffer->init(_WINSIZEX, _WINSIZEY);
	//■■■■■■■■■■■■■■■■■ 타일 창에서 저장하고 맵상에 그려라 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	setup();
	//■■■■■■■■■■■■■■■■■ 마우스 클릭 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	_startL = 0;
	_startT = 0;
	_isClick = _isItemButtonClick = _isMapButtonClick = false;
	_isLobyButtonClick = _isStageButtonClick = _isBossButtonClick = false;
	
	destroyAllWindows();
	//■■■■■■■■■■■■■■■■■ 화면 움직임 ■■■■■■■■■■■■■■■■■
	CAMERAMANAGER->set_CameraMapTool_XY(0, 0);

	_left = RectMake(0, 0, 25, 900);
	_top = RectMake(0, 0, 1800, 25);
	_right = RectMake(1775, 0, 25, 900);
	_bottom = RectMake(0, 875, 1800, 25);
	_crtSelect == CTRL_LOBY;
	return S_OK;
}

void mapTool::release()
{

}

void mapTool::update()
{
	if(!_isClick) palette_Click();			// 팔렛트 클릭 함수
	if(!_palette.isClick) tile_Click();		// 마우스 왼쪽 클릭 연산

	// 만약 이동 렉트에 마우스가 있다면, 카메라 좌표를 해당 속도만큼 이동 시켜준다. 
	if (PtInRect(&_left, _ptMouse)) { CAMERAMANAGER->set_CameraPos_Update(CAMERAMANAGER->get_CameraX() - SCREENMOVESPEED, CAMERAMANAGER->get_CameraY()); }
	if (PtInRect(&_top, _ptMouse)) { CAMERAMANAGER->set_CameraPos_Update(CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY() - SCREENMOVESPEED); }
	if (PtInRect(&_right, _ptMouse)) { CAMERAMANAGER->set_CameraPos_Update(CAMERAMANAGER->get_CameraX() + SCREENMOVESPEED, CAMERAMANAGER->get_CameraY()); }
	if (PtInRect(&_bottom, _ptMouse)) { CAMERAMANAGER->set_CameraPos_Update(CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY() + SCREENMOVESPEED); }
	CAMERAMANAGER->CameraMapTool_Correction();

	if (_crtSelect == CTRL_ITEM) { _isItemButtonClick = true; }
	if (_crtSelect == CTRL_MAP) { _isMapButtonClick = true; }
	_itemButton.rc = RectMake(25, 25, 72, 72);
	if (_isItemButtonClick == true)
	{
		_stuffButton.rc = RectMake(100, 50, 52, 52);
		_armorButton.rc = RectMake(150, 50, 52, 52);
		_weaponButton.rc = RectMake(200, 50, 52, 52);
	}
	else if (!_isItemButtonClick)
	{
		_stuffButton.rc = RectMake(25, 50, 52, 52);
		_armorButton.rc = RectMake(25, 50, 52, 52);
		_weaponButton.rc = RectMake(25, 50, 52, 52);
	}
	_mapButton.rc = RectMake(25, 97, 72, 72);
	if (_isMapButtonClick == true)
	{

		_terrainButton.rc = RectMake(100, 122, 52, 52);
		_wallButton.rc = RectMake(150, 122, 52, 52);
		_trapButton.rc = RectMake(200, 122, 52, 52);
	}
	else if (_isMapButtonClick == false)
	{

		_terrainButton.rc = RectMake(25, 122, 52, 52);
		_wallButton.rc = RectMake(25, 122, 52, 52);
		_trapButton.rc = RectMake(25, 122, 52, 52);
	}
	_characterButton.rc = RectMake(25, 169, 72, 72);

	if (_crtSelect == CTRL_LOBY) { _isLobyButtonClick = true; }
	else if (_crtSelect == CTRL_STAGE) { _isStageButtonClick = true; }
	else if (_crtSelect == CTRL_BOSS_STAGE) { _isBossButtonClick = true; }
	
	_lobyButton.rc = RectMake(740, 25, 100, 27);
	_stageButton.rc = RectMake(850, 25, 100, 27);  
	_bossButton.rc = RectMake(960, 25, 100, 27);
	_eraseButton.rc = RectMake(1430, 825, 52, 52);

	_saveButton.rc = RectMake(1525, 825, 52, 52);
	_loadButton.rc = RectMake(1600, 825, 52, 52);

	_exitButton.rc = RectMake(1700, 830, 52, 52);

	// 마우스 위치의 타일의 렉트를 가져온다.
	mouseRectUpdate();
	//cout << "_crtSelect :" << _crtSelect << endl;
}

void mapTool::save()
{
	if (_isLobyButtonClick)
	{
		HANDLE file;
		DWORD write;
		//"Loby_SaveFile.mpa"
		//"SaveFile.map"
		//"Boss_SaveFile.map"
		//"Stage_SaveFile.map"
		file = CreateFile("Loby_SaveFile.map", GENERIC_WRITE, 0, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);
		WriteFile(file, _pos, sizeof(int) * 2, &write, NULL);

		CloseHandle(file);
	}
	else if (_isStageButtonClick)
	{
		HANDLE file;
		DWORD write;
		//"Loby_SaveFile.mpa"
		//"SaveFile.map"
		//"Boss_SaveFile.map"
		//"Stage_SaveFile.map"
		file = CreateFile("Stage_SaveFile.map", GENERIC_WRITE, 0, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);
		WriteFile(file, _pos, sizeof(int) * 2, &write, NULL);

		CloseHandle(file);
	}
	else if (_isBossButtonClick)
	{
		HANDLE file;
		DWORD write;
		//"Loby_SaveFile.mpa"
		//"SaveFile.map"
		//"Boss_SaveFile.map"
		//"Stage_SaveFile.map"
		file = CreateFile("Boss_SaveFile.map", GENERIC_WRITE, 0, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);
		WriteFile(file, _pos, sizeof(int) * 2, &write, NULL);

		CloseHandle(file);
	}

}

void mapTool::load()
{
	if (_isLobyButtonClick)
	{
		HANDLE file;
		DWORD read;

		file = CreateFile("Loby_SaveFile.map", GENERIC_READ, 0, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		//맵을 불로온 직후 타일의 속성을 매겨준다
		ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
		ReadFile(file, _pos, sizeof(int) * 2, &read, NULL);

		CloseHandle(file);
	}
	else if (_isStageButtonClick)
	{
		HANDLE file;
		DWORD read;

		file = CreateFile("Stage_SaveFile.map", GENERIC_READ, 0, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		//맵을 불로온 직후 타일의 속성을 매겨준다
		ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
		ReadFile(file, _pos, sizeof(int) * 2, &read, NULL);

		CloseHandle(file);
	}
	else if (_isBossButtonClick)
	{
		HANDLE file;
		DWORD read;

		file = CreateFile("Boss_SaveFile.map", GENERIC_READ, 0, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		//맵을 불로온 직후 타일의 속성을 매겨준다
		ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
		ReadFile(file, _pos, sizeof(int) * 2, &read, NULL);

		CloseHandle(file);
	}
}


void mapTool::render()
{
	PatBlt(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), _WINSIZEX, _WINSIZEY, BLACKNESS);
	//TextOut(getMemDC(), 700, 700, str,strlen(str)); 
	//지형
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		//Rectangle(CAMERAMANAGER->getWorldDC(), _tiles[i].rc);
		if (_tiles[i].terrain== TR_NONE) continue;
		if (_tiles[i].isRender == true)
		{
			_tiles[i].type = TYPE_TERRAIN;
			//Rectangle(CAMERAMANAGER->getWorldDC(), _tiles[i].rc);
			IMAGEMANAGER->frameRender("terrainTiles", CAMERAMANAGER->getWorldDC(),
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		}
	}
	//함정
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
	//소지품
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tiles[i].stuff == ST_NONE) continue;
		if (_tiles[i].isRender == true)
		{
			_tiles[i].type = TYPE_ITEM_STUFF;
			//Rectangle(CAMERAMANAGER->getWorldDC(), _tiles[i].rc);
			IMAGEMANAGER->frameRender("stuffTiles", CAMERAMANAGER->getWorldDC(),
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].stuffFrameX, _tiles[i].stuffFrameY);
		}
	}
	//방어구
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

	//무기
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
	//캐릭터
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tiles[i].character == CHAR_NONE) continue;
		if (_tiles[i].isRender == true)
		{
			_tiles[i].type = TYPE_CHARACTER;
			//Rectangle(CAMERAMANAGER->getWorldDC(), _tiles[i].rc);
			IMAGEMANAGER->frameRender("characterTiles", CAMERAMANAGER->getWorldDC(),
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].characterFrameX, _tiles[i].characterFrameY);
		}
	}
	//벽 
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
	//Rectangle(getMemDC(), _eraseButton.rc);
	IMAGEMANAGER->findImage("save")->render(getMemDC(), _saveButton.rc.left, _saveButton.rc.top);
	IMAGEMANAGER->findImage("load")->render(getMemDC(), _loadButton.rc.left, _loadButton.rc.top);
	IMAGEMANAGER->findImage("map")->render(getMemDC(), _mapButton.rc.left, _mapButton.rc.top);
	if (_crtSelect == CTRL_MAP)
	{
		IMAGEMANAGER->findImage("terrain")->render(getMemDC(), _terrainButton.rc.left, _terrainButton.rc.top);
		IMAGEMANAGER->findImage("wall")->render(getMemDC(), _wallButton.rc.left, _wallButton.rc.top);
		IMAGEMANAGER->findImage("trap")->render(getMemDC(), _trapButton.rc.left, _trapButton.rc.top);
	}
	if (_crtSelect == CTRL_ITEM)
	{
		IMAGEMANAGER->findImage("stuff")->render(getMemDC(), _stuffButton.rc.left, _stuffButton.rc.top);
		IMAGEMANAGER->findImage("armor")->render(getMemDC(), _armorButton.rc.left, _armorButton.rc.top);
		IMAGEMANAGER->findImage("weapon")->render(getMemDC(), _weaponButton.rc.left, _weaponButton.rc.top);
	}
	IMAGEMANAGER->findImage("character")->render(getMemDC(), _characterButton.rc.left, _characterButton.rc.top);
	IMAGEMANAGER->findImage("item")->render(getMemDC(), _itemButton.rc.left, _itemButton.rc.top);
	IMAGEMANAGER->findImage("eraser")->render(getMemDC(), _eraseButton.rc.left, _eraseButton.rc.top);
	IMAGEMANAGER->findImage("exit")->render(getMemDC(), _exitButton.rc.left, _exitButton.rc.top);



	//Rectangle(getMemDC(), _left);
	//Rectangle(getMemDC(), _top);
	//Rectangle(getMemDC(), _right);
	//Rectangle(getMemDC(), _bottom);
	IMAGEMANAGER->findImage("left")->alphaRender(getMemDC(), _left.left, _left.top);
	IMAGEMANAGER->findImage("top")->alphaRender(getMemDC(), _top.left, _top.top);
	IMAGEMANAGER->findImage("right")->alphaRender(getMemDC(), _right.left, _right.top);
	IMAGEMANAGER->findImage("bottom")->alphaRender(getMemDC(), _bottom.left, _bottom.top);

	//Rectangle(getMemDC(), _lobyButton.rc);
	//Rectangle(getMemDC(), _stageButton.rc);
	//Rectangle(getMemDC(), _bossButton.rc);
	if (_isLobyButtonClick == true && _isStageButtonClick == false && _isBossButtonClick == false)
	{
		IMAGEMANAGER->findImage("loby")->alphaRender(getMemDC(), _lobyButton.rc.left, _lobyButton.rc.top, 255);
		IMAGEMANAGER->findImage("stage")->alphaRender(getMemDC(), _stageButton.rc.left, _stageButton.rc.top, 100);
		IMAGEMANAGER->findImage("boss")->alphaRender(getMemDC(), _bossButton.rc.left, _bossButton.rc.top, 100);
	}
	else if (_isLobyButtonClick == false && _isStageButtonClick == true && _isBossButtonClick == false)
	{
		IMAGEMANAGER->findImage("loby")->alphaRender(getMemDC(), _lobyButton.rc.left, _lobyButton.rc.top, 100);
		IMAGEMANAGER->findImage("stage")->alphaRender(getMemDC(), _stageButton.rc.left, _stageButton.rc.top, 255);
		IMAGEMANAGER->findImage("boss")->alphaRender(getMemDC(), _bossButton.rc.left, _bossButton.rc.top, 100);
	}
	else if (_isLobyButtonClick == false && _isStageButtonClick == false && _isBossButtonClick == true)
	{
		IMAGEMANAGER->findImage("loby")->alphaRender(getMemDC(), _lobyButton.rc.left, _lobyButton.rc.top, 100);
		IMAGEMANAGER->findImage("stage")->alphaRender(getMemDC(), _stageButton.rc.left, _stageButton.rc.top, 100);
		IMAGEMANAGER->findImage("boss")->alphaRender(getMemDC(), _bossButton.rc.left, _bossButton.rc.top, 255);
	}
	else
	{
		IMAGEMANAGER->findImage("loby")->alphaRender(getMemDC(), _lobyButton.rc.left, _lobyButton.rc.top, 255);
		IMAGEMANAGER->findImage("stage")->alphaRender(getMemDC(), _stageButton.rc.left, _stageButton.rc.top, 255);
		IMAGEMANAGER->findImage("boss")->alphaRender(getMemDC(), _bossButton.rc.left, _bossButton.rc.top, 255);
	}

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

		// 무브 렉트 출력
		//Rectangle(getMemDC(), _palette.terrainTile);
		IMAGEMANAGER->render("terrainPalette", getMemDC(), _palette.terrainTile.left - 24, _palette.terrainTile.top);
		

		// 팔렛트 렉트 출력
		for (int i = 0; i < TERRAINTILEY; ++i)
		{
			for (int j = 0; j < TERRAINTILEX; ++j)
			{
				Rectangle(getMemDC(), _terrainTile[i * TERRAINTILEX + j].rcTile);

			}
		}
		
		// 팔렛트 이미지 출력
		IMAGEMANAGER->render("terrainTiles", getMemDC(), _palette.terrainTile.left, _palette.terrainTile.top + 24);
	}

	if (_crtSelect == CTRL_STUFF)
	{

		IMAGEMANAGER->findImage("stuffTiles")->alphaFrameRender(getMemDC(),
			_mouseEffect.mouseRect.left, _mouseEffect.mouseRect.top,
			_mouseEffect.frameX, _mouseEffect.frameY, 200);

		// 무브 렉트 출력
		//Rectangle(getMemDC(), _palette.armorTile);
		IMAGEMANAGER->render("itemPalette", getMemDC(), _palette.stuffTile.left - 26, _palette.stuffTile.top);
		// 팔렛트 렉트 출력
		for (int i = 0; i < ITEMTILEY; ++i)
		{
			for (int j = 0; j < ITEMTILEX; ++j)
			{
				Rectangle(getMemDC(), _stuffTile[i * ITEMTILEX + j].rcTile);
			}
		}

		// 팔렛트 이미지 출력
		IMAGEMANAGER->render("stuffTiles", getMemDC(), _palette.stuffTile.left, _palette.stuffTile.top + 24);
	}

	if (_crtSelect == CTRL_ARMOR)
	{

		IMAGEMANAGER->findImage("armorTiles")->alphaFrameRender(getMemDC(),
			_mouseEffect.mouseRect.left, _mouseEffect.mouseRect.top,
			_mouseEffect.frameX, _mouseEffect.frameY, 200);

		// 무브 렉트 출력
		//Rectangle(getMemDC(), _palette.armorTile);
		IMAGEMANAGER->render("itemPalette", getMemDC(), _palette.armorTile.left - 26, _palette.armorTile.top);
		// 팔렛트 렉트 출력
		for (int i = 0; i < ITEMTILEY; ++i)
		{
			for (int j = 0; j < ITEMTILEX; ++j)
			{
				Rectangle(getMemDC(), _armorTile[i * ITEMTILEX + j].rcTile);
			}
		}

		// 팔렛트 이미지 출력
		IMAGEMANAGER->render("armorTiles", getMemDC(), _palette.armorTile.left, _palette.armorTile.top + 24);
	}

	if (_crtSelect == CTRL_WEAPON)
	{
		IMAGEMANAGER->findImage("weaponTiles")->alphaFrameRender(getMemDC(),
			_mouseEffect.mouseRect.left, _mouseEffect.mouseRect.top,
			_mouseEffect.frameX, _mouseEffect.frameY, 200);

		// 무브 렉트 출력
		//Rectangle(getMemDC(), _palette.weaponTile);
		IMAGEMANAGER->render("itemPalette", getMemDC(), _palette.weaponTile.left - 26, _palette.weaponTile.top);
		// 팔렛트 렉트 출력
		for (int i = 0; i < ITEMTILEY; ++i)
		{
			for (int j = 0; j < ITEMTILEX; ++j)
			{
				Rectangle(getMemDC(), _weaponTile[i * ITEMTILEX + j].rcTile);
			}
		}

		// 팔렛트 이미지 출력
		IMAGEMANAGER->render("weaponTiles", getMemDC(), _palette.weaponTile.left, _palette.weaponTile.top + 24);
	}
	if (_crtSelect == CTRL_CHARACTER)
	{
		IMAGEMANAGER->findImage("characterTiles")->alphaFrameRender(getMemDC(),
			_mouseEffect.mouseRect.left, _mouseEffect.mouseRect.top,
			_mouseEffect.frameX, _mouseEffect.frameY, 200);

		// 무브 렉트 출력
		//Rectangle(getMemDC(), _palette.weaponTile);
		IMAGEMANAGER->render("itemPalette", getMemDC(), _palette.characterTile.left - 26, _palette.characterTile.top);
		// 팔렛트 렉트 출력
		for (int i = 0; i < CHARACTERTILEY; ++i)
		{
			for (int j = 0; j < CHARACTERTILEX; ++j)
			{
				Rectangle(getMemDC(), _characterTile[i * CHARACTERTILEX + j].rcTile);
			}
		}

		// 팔렛트 이미지 출력
		IMAGEMANAGER->render("characterTiles", getMemDC(), _palette.characterTile.left, _palette.characterTile.top + 24);
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

		// 무브 렉트 출력
		//Rectangle(getMemDC(), _palette.trapTile);
		IMAGEMANAGER->render("trapPalette", getMemDC(), _palette.trapTile.left - 26, _palette.trapTile.top);
		// 팔렛트 렉트 출력
		for (int i = 0; i < TRAPTILEY; ++i)
		{
			for (int j = 0; j < TRAPTILEX; ++j)
			{
				Rectangle(getMemDC(), _trapTile[i * TRAPTILEX + j].rcTile);
			}
		}
		// 팔렛트 이미지 출력
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

		// 무브 렉트 출력
		//Rectangle(getMemDC(), _palette.wallTile);
		IMAGEMANAGER->render("wallPalette", getMemDC(), _palette.wallTile.left - 28, _palette.wallTile.top);
		// 팔렛트 렉트 출력
		for (int i = 0; i < WALLTILEY; ++i)
		{
			for (int j = 0; j < WALLTILEX; ++j)
			{
				Rectangle(getMemDC(), _wallTile[i * WALLTILEX + j].rcTile);
			}
		}
		// 팔렛트 이미지 출력
		IMAGEMANAGER->render("wallTiles", getMemDC(), _palette.wallTile.left, _palette.wallTile.top + 24);
	}
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
	// 팔레트 이동 창으로 사용할 렉트
	_palette.terrainTile = RectMake(_WINSIZEX - 50 - TERRAINTILEX * TILESIZE, 25, TERRAINTILEX * TILESIZE, 25);
	_palette.trapTile = RectMake(_WINSIZEX - 50 - TRAPTILEX * TILESIZE, 25, TRAPTILEX * TILESIZE, 25);
	_palette.stuffTile = RectMake(_WINSIZEX - 50 - ITEMTILEX * TILESIZE, 25, ITEMTILEX * TILESIZE, 25);
	_palette.armorTile = RectMake(_WINSIZEX - 50 - ITEMTILEX * TILESIZE, 25, ITEMTILEX * TILESIZE, 25);
	_palette.weaponTile = RectMake(_WINSIZEX - 50 - ITEMTILEX * TILESIZE, 25, ITEMTILEX * TILESIZE, 25);
	_palette.wallTile = RectMake(_WINSIZEX - 50 - WALLTILEX * TILESIZE, 25, WALLTILEX * TILESIZE, 25);
	_palette.characterTile = RectMake(_WINSIZEX - 50 - CHARACTERTILEX * TILESIZE, 25, CHARACTERTILEY * TILESIZE, 25);
	_palette.isClick = false;
	_palette.pos_Start.x = _palette.pos_Start.y = _palette.pos_End.x = _palette.pos_End.y = NULL;

	//처음에는 지형으로 둔다
	//_crtSelect = CTRL_WALLDRAW;

	//지형 오브젝트 타일셋팅 (샘플타일)

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
	//소지품 타일 셋팅
	for (int i = 0; i < ITEMTILEY; ++i)
	{
		for (int j = 0; j < ITEMTILEX; ++j)
		{
			_stuffTile[i * ITEMTILEX + j].terrainFrameX = j;
			_stuffTile[i * ITEMTILEX + j].terrainFrameY = i;
			SetRect(&_stuffTile[i * ITEMTILEX + j].rcTile,
				_palette.stuffTile.left + j * TILESIZE, _palette.stuffTile.bottom + i * TILESIZE,
				_palette.stuffTile.left + j * TILESIZE + TILESIZE, _palette.stuffTile.bottom + i * TILESIZE + TILESIZE);
		}
	}
	//방어구 타일 셋팅
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
	//무기 타일 셋팅
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
	//캐릭터 타일 셋팅
	for (int i = 0; i < CHARACTERTILEY; ++i)
	{
		for (int j = 0; j < CHARACTERTILEX; ++j)
		{
			_characterTile[i * CHARACTERTILEX + j].terrainFrameX = j;
			_characterTile[i * CHARACTERTILEX + j].terrainFrameY = i;
			SetRect(&_characterTile[i * CHARACTERTILEX + j].rcTile,
				_palette.characterTile.left + j * TILESIZE, _palette.characterTile.bottom + i * TILESIZE,
				_palette.characterTile.left + j * TILESIZE + TILESIZE, _palette.characterTile.bottom + i * TILESIZE + TILESIZE);
		}
	}
	//함정 타일 셋팅
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
	//벽 타일 셋팅
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
		_tiles[i].stuffFrameX = 3;
		_tiles[i].stuffFrameY = 4;
		_tiles[i].armorFrameX = 3;
		_tiles[i].armorFrameY = 4;
		_tiles[i].weaponFrameX = 3;
		_tiles[i].weaponFrameY = 4;
		_tiles[i].trapFrameX = 5;
		_tiles[i].trapFrameY = 6;
		_tiles[i].wallFrameX = 15;
		_tiles[i].wallFrameY = 3;
		_tiles[i].characterFrameX = 3;
		_tiles[i].characterFrameY = 3;
		_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		_tiles[i].terrain = TR_NONE;
		_tiles[i].stuff = ST_NONE;
		_tiles[i].armor = A_NONE;
		_tiles[i].weapon = WP_NONE;
		_tiles[i].trap = TRAP_NONE;
		_tiles[i].wall = W_NONE;
		_tiles[i].character = CHAR_NONE;
		_tiles[i].alphaValue = 255; // 0~255 
	}
}

void mapTool::setMap()
{
		if (_crtSelect == CTRL_TERRAINDRAW)
		{
			//지정한 타일셋에서 클릭한 애를 현재 타일로 저장한다.
			for (int i = 0; i < TERRAINTILEX * TERRAINTILEY; i++)
			{
				//지형
				if (PtInRect(&_terrainTile[i].rcTile, _ptMouse))
				{
					_currentTile.x = _terrainTile[i].terrainFrameX;
					_currentTile.y = _terrainTile[i].terrainFrameY;

					// 마우스 이펙트에 쓰일 프레임 x, y를 받아온다.
					_mouseEffect.frameX = _terrainTile[i].terrainFrameX;
					_mouseEffect.frameY = _terrainTile[i].terrainFrameY;
					break;
				}
			}
		}
		if (_crtSelect == CTRL_STUFF)
		{
			for (int i = 0; i < ITEMTILEX * ITEMTILEY; i++)
			{
				//방어구
				if (PtInRect(&_stuffTile[i].rcTile, _ptMouse))
				{
					_currentTile.x = _stuffTile[i].terrainFrameX;
					_currentTile.y = _stuffTile[i].terrainFrameY;

					_mouseEffect.frameX = _stuffTile[i].terrainFrameX;
					_mouseEffect.frameY = _stuffTile[i].terrainFrameY;
					break;
				}
			}
		}
		if (_crtSelect == CTRL_ARMOR)
		{
			for (int i = 0; i < ITEMTILEX * ITEMTILEY; i++)
			{
				//방어구
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
				//방어구
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
		if (_crtSelect == CTRL_CHARACTER)
		{
			for (int i = 0; i < CHARACTERTILEX * CHARACTERTILEY; i++)
			{
				//방어구
				if (PtInRect(&_characterTile[i].rcTile, _ptMouse))
				{
					_currentTile.x = _characterTile[i].terrainFrameX;
					_currentTile.y = _characterTile[i].terrainFrameY;

					_mouseEffect.frameX = _characterTile[i].terrainFrameX;
					_mouseEffect.frameY = _characterTile[i].terrainFrameY;
					break;
				}
			}
		}
		if (_crtSelect == CTRL_TRAP)
		{
			for (int i = 0; i < TRAPTILEX * TRAPTILEY; i++)
			{
				//함정
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
				//벽
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
	

		//위에 클릭하여 저장한 타일을 맵 상에 그려라
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			RECT temp;
			// 팔렛트 선택 할때 뒤에 타일이 찍히지 않게 하기 위해서
			if (using_Palette()) break;
			if ((PtInRect(&_itemButton.rc, _ptMouse)) ||
				(PtInRect(&_stuffButton.rc, _ptMouse)) ||
				(PtInRect(&_armorButton.rc, _ptMouse)) ||
				(PtInRect(&_weaponButton.rc, _ptMouse)) ||
				(PtInRect(&_terrainButton.rc, _ptMouse)) ||
				(PtInRect(&_wallButton.rc, _ptMouse)) ||
				(PtInRect(&_trapButton.rc, _ptMouse)) ||
				(PtInRect(&_eraseButton.rc, _ptMouse)) ||
				(PtInRect(&_saveButton.rc, _ptMouse)) ||
				(PtInRect(&_loadButton.rc, _ptMouse)) ||
				(PtInRect(&_characterButton.rc, _ptMouse)) ||
				(PtInRect(&_lobyButton.rc, _ptMouse)) ||
				(PtInRect(&_stageButton.rc, _ptMouse)) ||
				(PtInRect(&_bossButton.rc, _ptMouse)) ||
				(PtInRect(&_exitButton.rc, _ptMouse))) { break; }

			if ((IntersectRect(&temp, &_itemButton.rc, &_RectCreate.rc)) ||
				(IntersectRect(&temp, &_stuffButton.rc,  &_RectCreate.rc)) ||
				(IntersectRect(&temp, &_armorButton.rc,  &_RectCreate.rc)) ||
				(IntersectRect(&temp, &_weaponButton.rc, &_RectCreate.rc)) ||
				(IntersectRect(&temp, &_terrainButton.rc, &_RectCreate.rc)) ||
				(IntersectRect(&temp, &_wallButton.rc, &_RectCreate.rc)) ||
				(IntersectRect(&temp, &_trapButton.rc, &_RectCreate.rc)) ||
				(IntersectRect(&temp, &_eraseButton.rc, &_RectCreate.rc)) ||
				(IntersectRect(&temp, &_saveButton.rc, &_RectCreate.rc)) ||
				(IntersectRect(&temp, &_loadButton.rc, &_RectCreate.rc)) ||
				(IntersectRect(&temp, &_characterButton.rc, &_RectCreate.rc)) ||
				(IntersectRect(&temp, &_lobyButton.rc, &_RectCreate.rc)) ||
				(IntersectRect(&temp, &_stageButton.rc, &_RectCreate.rc)) ||
				(IntersectRect(&temp, &_bossButton.rc, &_RectCreate.rc)) ||
				(IntersectRect(&temp, &_exitButton.rc, &_RectCreate.rc))) { break; }
			// ptMouse의 좌표를 월드 좌표로 바꿔준다.
			POINT ptMouse_Temp;
			ptMouse_Temp.x = _ptMouse.x + CAMERAMANAGER->get_CameraX();
			ptMouse_Temp.y = _ptMouse.y + CAMERAMANAGER->get_CameraY();

			// 한 타일만 클릭 하거나, 드래그를 했을 경우 모두를 처리 한다.
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
				else if (_crtSelect == CTRL_STUFF)
				{
					_tiles[i].type = TYPE_ITEM_STUFF;
					_tiles[i].stuffFrameX = _currentTile.x;
					_tiles[i].stuffFrameY = _currentTile.y;

					_tiles[i].stuff = stuffSelect(_currentTile.x, _currentTile.y);
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
				else if (_crtSelect == CTRL_CHARACTER)
				{
					_tiles[i].type = TYPE_CHARACTER;
					_tiles[i].characterFrameX = _currentTile.x;
					_tiles[i].characterFrameY = _currentTile.y;

					_tiles[i].character = characterSelect(_currentTile.x, _currentTile.y);
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
					_tiles[i].stuffFrameX = NULL;
					_tiles[i].stuffFrameY = NULL;
					_tiles[i].stuff = ST_NONE;
					_tiles[i].armorFrameX = NULL;
					_tiles[i].armorFrameY = NULL;
					_tiles[i].armor = A_NONE;
					_tiles[i].weaponFrameX = NULL;
					_tiles[i].weaponFrameY = NULL;
					_tiles[i].weapon = WP_NONE;
					_tiles[i].wallFrameX = NULL;
					_tiles[i].wallFrameY = NULL;
					_tiles[i].wall = W_NONE;
					_tiles[i].characterFrameX = NULL;
					_tiles[i].characterFrameY = NULL;
					_tiles[i].character = CHAR_NONE;
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

STUFF mapTool::stuffSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0) return ST_DIAMOND;
	for (int i =0;i<3;i++) { if (frameX == i + 1 && frameY == 0) return ST_NONE; }
	if (frameX == 0 && frameY == 1) return ST_ONE_COIN;
	if (frameX == 1 && frameY == 1) return ST_ONE_HALF_COIN;
	if (frameX == 0 && frameY == 2) return ST_COINS;
	if (frameX == 1 && frameY == 2) return ST_MORE_COINS;
	for(int i=0; i<2;i++)
	{
		if (frameX == i + 2 && frameY == 1) return ST_NONE; 
		if (frameX == i + 2 && frameY == 2) return ST_NONE;
	}
	if (frameX == 0 && frameY == 3) return ST_APPLE;
	if (frameX == 1 && frameY == 3) return ST_CHEESE;
	if (frameX == 2 && frameY == 3) return ST_MEAT;
	if (frameX == 3 && frameY == 3) return ST_NONE;
	for (int i = 0; i < 5; i++){ if (frameX == i && frameY == 4) return ST_NONE;	}

	return ST_NONE;
}

ARMOR mapTool::armorSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0) return A_HELMET;
	if (frameX == 1 && frameY == 0) return A_SHOVEL;
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
	for (int i = 0; i < 2; i++)
	{
		if (frameX == i + 2 && frameY == 0) return A_NONE;
	}
	for (int i = 0; i < 3; i++)
	{
		if (frameX == i + 1 && frameY == 2) return A_NONE;
		if (frameX == i + 1 && frameY == 3) return A_NONE;
	}

	return A_NONE;
}

WEAPON mapTool::weaponSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0) return WP_DAGGER_1;
	if (frameX == 1 && frameY == 0) return WP_DAGGER_2;
	if (frameX == 2 && frameY == 0) return WP_RAPIER;
	if (frameX == 3 && frameY == 0) return WP_BROAD_SWORD;
	if (frameX == 0 && frameY == 1) return WP_BOMB;
	if (frameX == 1 && frameY == 1) return WP_RIFLE;
	if (frameX == 2 && frameY == 1) return WP_SHOTGUN;
	if (frameX == 3 && frameY == 1) return WP_NONE;
	if (frameX == 0 && frameY == 2) return WP_SPEAR;
	if (frameX == 1 && frameY == 2) return WP_MACE;
	if (frameX == 2 && frameY == 2) return WP_LONG_SWORD;
	if (frameX == 0 && frameY == 3) return WP_WHIP;
	if (frameX == 1 && frameY == 3) return WP_NINETAILS_WHIP;
	if (frameX == 0 && frameY == 4) return WP_BOW;
	if (frameX == 1 && frameY == 4) return WP_CROSS_BOW;
	if (frameX == 3 && frameY == 2) return WP_NONE;
	for (int i = 0; i < 2; i++)
	{
		if (frameX == i + 2 && frameY == 3) return WP_NONE;
		if (frameX == i + 2 && frameY == 4) return WP_NONE;
	}
	return WP_NONE;
}

CHARACTER mapTool::characterSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0) return CHAR_PLAYER;
	if (frameX == 1 && frameY == 0) return CHAR_SHOPKEEPER;
	if (frameX == 2 && frameY == 0) return CHAR_NONE;
	if (frameX == 3 && frameY == 0) return CHAR_NONE;
	if (frameX == 0 && frameY == 1) return CHAR_SLIME_BLUE;
	if (frameX == 1 && frameY == 1) return CHAR_SLIME_ORANGE;
	if (frameX == 2 && frameY == 1) return CHAR_BAT;
	if (frameX == 3 && frameY == 1) return CHAR_GHOST;
	if (frameX == 0 && frameY == 2) return CHAR_SKELETON;
	if (frameX == 1 && frameY == 2) return CHAR_SKELETON_YELLOW;
	if (frameX == 2 && frameY == 2) return CHAR_ZOMBIE;
	if (frameX == 3 && frameY == 2) return CHAR_WRAITH;
	if (frameX == 0 && frameY == 3) return CHAR_MINO;
	if (frameX == 1 && frameY == 3) return CHAR_DRAGON;
	if (frameX == 2 && frameY == 3) return CHAR_BOSS;
	if (frameX == 3 && frameY == 3) return CHAR_NONE;

	return CHAR_NONE;
}

void mapTool::tile_Click()
{
	if (!_isClick)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			// 클릭한 위치를 저장해둔다.
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
		// 마우스 왼쪽 버튼 클릭을 유지하고 있을때 (창 이동을 하고 있을때는 실행 하면 안돼)
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			// 마지막 위치도 저장해둔다.
			_endR = _ptMouse.x;
			_endB = _ptMouse.y;

			// 스타트, 엔드를 이용하여 렉트를 갱신 해준다. (이것은 타일 충돌용 렉트이다.)
			rectCreate_Update();

			// 1. 메뉴 선택
			menu_Choice();

			// 2. 기능 선택
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
			// 팔렛트 렉트를 마우스로 클릭하고 있을때
			if (PtInRect(&_palette.terrainTile, _ptMouse))
			{
				palette_Click(true);
			}
			break;
		case CTRL_STUFF:
			// 팔렛트 렉트를 마우스로 클릭하고 있을때
			if (PtInRect(&_palette.stuffTile, _ptMouse))
			{
				palette_Click(true);
			}
			break;
		case CTRL_ARMOR:
			// 팔렛트 렉트를 마우스로 클릭하고 있을때
			if (PtInRect(&_palette.armorTile, _ptMouse))
			{
				palette_Click(true);
			}
			break;
		case CTRL_WEAPON:
			// 팔렛트 렉트를 마우스로 클릭하고 있을때
			if (PtInRect(&_palette.weaponTile, _ptMouse))
			{
				palette_Click(true);
			}
			break;
		case CTRL_CHARACTER:
			// 팔렛트 렉트를 마우스로 클릭하고 있을때
			if (PtInRect(&_palette.characterTile, _ptMouse))
			{
				palette_Click(true);
			}
			break;
		case CTRL_TRAP:
			// 팔렛트 렉트를 마우스로 클릭하고 있을때
			if (PtInRect(&_palette.trapTile, _ptMouse))
			{
				palette_Click(true);
			}
			break;
		case CTRL_WALLDRAW:
			// 팔렛트 렉트를 마우스로 클릭하고 있을때
			if (PtInRect(&_palette.wallTile, _ptMouse))
			{
				palette_Click(true);
			}
			break;
		}
	}

	// 클릭을 땐 순간 다음 클릭을 위해 flase의 값으로 바꿔준다.
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _palette.isClick)
	{
		_palette.isClick = false;
	}

	// 클릭을 지속하는 순간 순간의 마우스 좌표를 계속 저장해준다.
	if (_palette.isClick)
	{
		_palette.pos_End.x = _ptMouse.x;
		_palette.pos_End.y = _ptMouse.y;
	}

	// 클릭을 하고 움직이는 좌표만큼 팔렛트 렉트를 다시 그려준다.
	if (_palette.isClick) palette_Rect_Update();
}

void mapTool::palette_Click(bool start)
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && !_palette.isClick)
	{
		// 클릭을 시작한 좌표를 저장한다.
		_palette.pos_Start.x = _ptMouse.x;
		_palette.pos_Start.y = _ptMouse.y;
		_palette.isClick = true;
	}
}

void mapTool::palette_Rect_Update()
{
	// TerrainDraw 팔렛트 렉트 갱신
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
	if (_crtSelect == CTRL_STUFF)
	{
		palette_Move();

		for (int i = 0; i < ITEMTILEY; ++i)
		{
			for (int j = 0; j < ITEMTILEX; ++j)
			{
				SetRect(&_stuffTile[i * ITEMTILEX + j].rcTile,
					_palette.stuffTile.left + j * TILESIZE, _palette.stuffTile.bottom + i * TILESIZE,
					_palette.stuffTile.left + j * TILESIZE + TILESIZE, _palette.stuffTile.bottom + i * TILESIZE + TILESIZE);
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
	if (_crtSelect == CTRL_CHARACTER)
	{
		palette_Move();

		for (int i = 0; i < CHARACTERTILEY; ++i)
		{
			for (int j = 0; j < CHARACTERTILEX; ++j)
			{
				SetRect(&_characterTile[i * CHARACTERTILEX + j].rcTile,
					_palette.characterTile.left + j * TILESIZE, _palette.characterTile.bottom + i * TILESIZE,
					_palette.characterTile.left + j * TILESIZE + TILESIZE, _palette.characterTile.bottom + i * TILESIZE + TILESIZE);
			}
		}
	}
	// TrapDraw 팔렛트 렉트 갱신
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

	// WallDraw 팔렛트 렉트 갱신
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
	// 스타트에서 엔드까지 얼마나 이동했는지 저장하고,
	// 그 값을 이용하여 렉트 위치를 옴겨준다.
	int moveX, moveY;
	moveX = moveY = 0;

	switch (_crtSelect)
	{
		case CTRL_TERRAINDRAW:

			// 만약 양수가 나온다면 이동 지점이 왼쪽이 되어야 한다.
			if (_palette.pos_Start.x - _palette.pos_End.x > 0)
			{
				moveX = _palette.pos_Start.x - _palette.pos_End.x;

				_palette.terrainTile.left -= moveX;
				_palette.terrainTile.right -= moveX;
			}

			// 만약 양수가 나온다면 이동 지점이 위쪽이 되어야 한다.
			if (_palette.pos_Start.y - _palette.pos_End.y > 0)
			{
				moveY = _palette.pos_Start.y - _palette.pos_End.y;

				_palette.terrainTile.top -= moveY;
				_palette.terrainTile.bottom -= moveY;
			}

			// 만약 음수가 나온다면 이동 지점이 오른쪽이 되어야 한다.
			if (_palette.pos_Start.x - _palette.pos_End.x < 0)
			{
				moveX = _palette.pos_End.x - _palette.pos_Start.x;

				_palette.terrainTile.left += moveX;
				_palette.terrainTile.right += moveX;
			}

			// 만약 음수가 나온다면 이동 지점이 아래쪽이 되어야 한다.
			if (_palette.pos_Start.y - _palette.pos_End.y < 0)
			{
				moveY = _palette.pos_End.y - _palette.pos_Start.y;

				_palette.terrainTile.top += moveY;
				_palette.terrainTile.bottom += moveY;
			}

			break;
		case CTRL_STUFF:
			//방어구
			// 만약 양수가 나온다면 이동 지점이 왼쪽이 되어야 한다.
			if (_palette.pos_Start.x - _palette.pos_End.x > 0)
			{
				moveX = _palette.pos_Start.x - _palette.pos_End.x;

				_palette.stuffTile.left -= moveX;
				_palette.stuffTile.right -= moveX;
			}

			// 만약 양수가 나온다면 이동 지점이 위쪽이 되어야 한다.
			if (_palette.pos_Start.y - _palette.pos_End.y > 0)
			{
				moveY = _palette.pos_Start.y - _palette.pos_End.y;

				_palette.stuffTile.top -= moveY;
				_palette.stuffTile.bottom -= moveY;
			}

			// 만약 음수가 나온다면 이동 지점이 오른쪽이 되어야 한다.
			if (_palette.pos_Start.x - _palette.pos_End.x < 0)
			{
				moveX = _palette.pos_End.x - _palette.pos_Start.x;

				_palette.stuffTile.left += moveX;
				_palette.stuffTile.right += moveX;
			}

			// 만약 음수가 나온다면 이동 지점이 아래쪽이 되어야 한다.
			if (_palette.pos_Start.y - _palette.pos_End.y < 0)
			{
				moveY = _palette.pos_End.y - _palette.pos_Start.y;

				_palette.stuffTile.top += moveY;
				_palette.stuffTile.bottom += moveY;
			}
			break;
		case CTRL_ARMOR:
			//방어구
			// 만약 양수가 나온다면 이동 지점이 왼쪽이 되어야 한다.
			if (_palette.pos_Start.x - _palette.pos_End.x > 0)
			{
				moveX = _palette.pos_Start.x - _palette.pos_End.x;

				_palette.armorTile.left -= moveX;
				_palette.armorTile.right -= moveX;
			}

			// 만약 양수가 나온다면 이동 지점이 위쪽이 되어야 한다.
			if (_palette.pos_Start.y - _palette.pos_End.y > 0)
			{
				moveY = _palette.pos_Start.y - _palette.pos_End.y;

				_palette.armorTile.top -= moveY;
				_palette.armorTile.bottom -= moveY;
			}

			// 만약 음수가 나온다면 이동 지점이 오른쪽이 되어야 한다.
			if (_palette.pos_Start.x - _palette.pos_End.x < 0)
			{
				moveX = _palette.pos_End.x - _palette.pos_Start.x;

				_palette.armorTile.left += moveX;
				_palette.armorTile.right += moveX;
			}

			// 만약 음수가 나온다면 이동 지점이 아래쪽이 되어야 한다.
			if (_palette.pos_Start.y - _palette.pos_End.y < 0)
			{
				moveY = _palette.pos_End.y - _palette.pos_Start.y;

				_palette.armorTile.top += moveY;
				_palette.armorTile.bottom += moveY;
			}
			break;
		case CTRL_WEAPON:
			//무기
			// 만약 양수가 나온다면 이동 지점이 왼쪽이 되어야 한다.
			if (_palette.pos_Start.x - _palette.pos_End.x > 0)
			{
				moveX = _palette.pos_Start.x - _palette.pos_End.x;

				_palette.weaponTile.left -= moveX;
				_palette.weaponTile.right -= moveX;
			}

			// 만약 양수가 나온다면 이동 지점이 위쪽이 되어야 한다.
			if (_palette.pos_Start.y - _palette.pos_End.y > 0)
			{
				moveY = _palette.pos_Start.y - _palette.pos_End.y;

				_palette.weaponTile.top -= moveY;
				_palette.weaponTile.bottom -= moveY;
			}

			// 만약 음수가 나온다면 이동 지점이 오른쪽이 되어야 한다.
			if (_palette.pos_Start.x - _palette.pos_End.x < 0)
			{
				moveX = _palette.pos_End.x - _palette.pos_Start.x;

				_palette.weaponTile.left += moveX;
				_palette.weaponTile.right += moveX;
			}

			// 만약 음수가 나온다면 이동 지점이 아래쪽이 되어야 한다.
			if (_palette.pos_Start.y - _palette.pos_End.y < 0)
			{
				moveY = _palette.pos_End.y - _palette.pos_Start.y;

				_palette.weaponTile.top += moveY;
				_palette.weaponTile.bottom += moveY;
			}
			break;
		case CTRL_CHARACTER:
			//무기
			// 만약 양수가 나온다면 이동 지점이 왼쪽이 되어야 한다.
			if (_palette.pos_Start.x - _palette.pos_End.x > 0)
			{
				moveX = _palette.pos_Start.x - _palette.pos_End.x;

				_palette.characterTile.left -= moveX;
				_palette.characterTile.right -= moveX;
			}

			// 만약 양수가 나온다면 이동 지점이 위쪽이 되어야 한다.
			if (_palette.pos_Start.y - _palette.pos_End.y > 0)
			{
				moveY = _palette.pos_Start.y - _palette.pos_End.y;

				_palette.characterTile.top -= moveY;
				_palette.characterTile.bottom -= moveY;
			}

			// 만약 음수가 나온다면 이동 지점이 오른쪽이 되어야 한다.
			if (_palette.pos_Start.x - _palette.pos_End.x < 0)
			{
				moveX = _palette.pos_End.x - _palette.pos_Start.x;

				_palette.characterTile.left += moveX;
				_palette.characterTile.right += moveX;
			}

			// 만약 음수가 나온다면 이동 지점이 아래쪽이 되어야 한다.
			if (_palette.pos_Start.y - _palette.pos_End.y < 0)
			{
				moveY = _palette.pos_End.y - _palette.pos_Start.y;

				_palette.characterTile.top += moveY;
				_palette.characterTile.bottom += moveY;
			}
			break;
		case CTRL_TRAP:

			// 만약 양수가 나온다면 이동 지점이 왼쪽이 되어야 한다.
			if (_palette.pos_Start.x - _palette.pos_End.x > 0)
			{
				moveX = _palette.pos_Start.x - _palette.pos_End.x;

				_palette.trapTile.left -= moveX;
				_palette.trapTile.right -= moveX;
			}

			// 만약 양수가 나온다면 이동 지점이 위쪽이 되어야 한다.
			if (_palette.pos_Start.y - _palette.pos_End.y > 0)
			{
				moveY = _palette.pos_Start.y - _palette.pos_End.y;

				_palette.trapTile.top -= moveY;
				_palette.trapTile.bottom -= moveY;
			}

			// 만약 음수가 나온다면 이동 지점이 오른쪽이 되어야 한다.
			if (_palette.pos_Start.x - _palette.pos_End.x < 0)
			{
				moveX = _palette.pos_End.x - _palette.pos_Start.x;

				_palette.trapTile.left += moveX;
				_palette.trapTile.right += moveX;
			}

			// 만약 음수가 나온다면 이동 지점이 아래쪽이 되어야 한다.
			if (_palette.pos_Start.y - _palette.pos_End.y < 0)
			{
				moveY = _palette.pos_End.y - _palette.pos_Start.y;

				_palette.trapTile.top += moveY;
				_palette.trapTile.bottom += moveY;
			}

			break;
		case CTRL_WALLDRAW:

			// 만약 양수가 나온다면 이동 지점이 왼쪽이 되어야 한다.
			if (_palette.pos_Start.x - _palette.pos_End.x > 0)
			{
				moveX = _palette.pos_Start.x - _palette.pos_End.x;

				_palette.wallTile.left -= moveX;
				_palette.wallTile.right -= moveX;
			}

			// 만약 양수가 나온다면 이동 지점이 위쪽이 되어야 한다.
			if (_palette.pos_Start.y - _palette.pos_End.y > 0)
			{
				moveY = _palette.pos_Start.y - _palette.pos_End.y;

				_palette.wallTile.top -= moveY;
				_palette.wallTile.bottom -= moveY;
			}

			// 만약 음수가 나온다면 이동 지점이 오른쪽이 되어야 한다.
			if (_palette.pos_Start.x - _palette.pos_End.x < 0)
			{
				moveX = _palette.pos_End.x - _palette.pos_Start.x;

				_palette.wallTile.left += moveX;
				_palette.wallTile.right += moveX;
			}

			// 만약 음수가 나온다면 이동 지점이 아래쪽이 되어야 한다.
			if (_palette.pos_Start.y - _palette.pos_End.y < 0)
			{
				moveY = _palette.pos_End.y - _palette.pos_Start.y;

				_palette.wallTile.top += moveY;
				_palette.wallTile.bottom += moveY;
			}

			break;
	}

	// 연산이 끝났다면 시작 좌표를 마지막 좌표로 갱신해준다.
	_palette.pos_Start = _palette.pos_End;
}

void mapTool::menu_Choice()
{
	if (PtInRect(&_itemButton.rc, _ptMouse)){ _crtSelect = CTRL_ITEM; }
	if (_isItemButtonClick == true)
	{
		if (PtInRect(&_stuffButton.rc, _ptMouse)) { _crtSelect = CTRL_STUFF; _isItemButtonClick = false; }
		if (PtInRect(&_armorButton.rc, _ptMouse)) { _crtSelect = CTRL_ARMOR; _isItemButtonClick = false; }
		if (PtInRect(&_weaponButton.rc, _ptMouse)) { _crtSelect = CTRL_WEAPON; _isItemButtonClick = false; }
	}
	if (PtInRect(&_mapButton.rc, _ptMouse)) { _crtSelect = CTRL_MAP; }
	if (_isMapButtonClick == true)
	{
		if (PtInRect(&_terrainButton.rc, _ptMouse)) { _crtSelect = CTRL_TERRAINDRAW; _isMapButtonClick = false; }
		if (PtInRect(&_trapButton.rc, _ptMouse)) { _crtSelect = CTRL_TRAP; _isMapButtonClick = false; }
		if (PtInRect(&_wallButton.rc, _ptMouse)) { _crtSelect = CTRL_WALLDRAW; _isMapButtonClick = false; }
	}
	if (PtInRect(&_eraseButton.rc, _ptMouse)) { _crtSelect = CTRL_ERASER; }
	if (PtInRect(&_characterButton.rc, _ptMouse)) { _crtSelect = CTRL_CHARACTER; }
	if (PtInRect(&_lobyButton.rc, _ptMouse)) 
	{ 
		_crtSelect = CTRL_LOBY; 
		_isStageButtonClick = false;
		_isBossButtonClick = false;
	}
	if (PtInRect(&_stageButton.rc, _ptMouse)) 
	{ 
		_crtSelect = CTRL_STAGE; 
		_isLobyButtonClick = false;
		_isBossButtonClick = false;
	}
	if (PtInRect(&_bossButton.rc, _ptMouse)) 
	{ 
		_crtSelect = CTRL_BOSS_STAGE; 
		_isLobyButtonClick = false;
		_isStageButtonClick = false;
	}
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
	if (PtInRect(&_exitButton.rc, _ptMouse))
	{
		_crtSelect = CTRL_EXIT;
		setWindowsSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);
		resizeWindow(WINNAME, WINSIZEX, WINSIZEY);
		_backBuffer->init(WINSIZEX, WINSIZEY);
		SCENEMANAGER->changeScene("Stage");
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

	// 마우스가 스타트 기점으로 5시 방향으로 그려지고 있는것
	if (_startL - _endR < 0 && _startT - _endB < 0)
	{
		sizeX = _endR - _startL;
		sizeY = _endB - _startT;

		_RectCreate.rc = RectMake(_startL + CAMERAMANAGER->get_CameraX(), _startT + CAMERAMANAGER->get_CameraY(), sizeX, sizeY);
	}

	// 마우스가 스타트 기점으로 7시 방향으로 그려지고 있는것
	if (_startL - _endR > 0 && _startT - _endB < 0)
	{
		sizeX = _startL - _endR;
		sizeY = _endB - _startT;

		_RectCreate.rc = RectMake(_startL - sizeX + CAMERAMANAGER->get_CameraX(), _startT + +CAMERAMANAGER->get_CameraY(), sizeX, sizeY);
	}

	// 마우스가 스타트 기점으로 10시 방향으로 그려지고 있는것
	if (_startL - _endR > 0 && _startT - _endB > 0)
	{
		sizeX = _startL - _endR;
		sizeY = _startT - _endB;

		_RectCreate.rc = RectMake(_startL - sizeX + CAMERAMANAGER->get_CameraX(), _startT - sizeY + +CAMERAMANAGER->get_CameraY(), sizeX, sizeY);
	}

	// 마우스가 스타트 기점으로 2시 방향으로 그려지고 있는것
	if (_startL - _endR < 0 && _startT - _endB > 0)
	{
		sizeX = _endR - _startL;
		sizeY = _startT - _endB;

		_RectCreate.rc = RectMake(_startL + CAMERAMANAGER->get_CameraX(), _startT - sizeY + +CAMERAMANAGER->get_CameraY(), sizeX, sizeY);
	}

}

bool mapTool::using_Palette()
{
	// 팔렛트 선택 중일때 true값을 리턴한다. (타일 찍는걸 막는다)
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
	if (_crtSelect == CTRL_STUFF)
	{
		for (int i = 0; i < ITEMTILEX * ITEMTILEY; i++)
		{
			if (PtInRect(&_stuffTile[i].rcTile, _ptMouse))
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
	if (_crtSelect == CTRL_CHARACTER)
	{
		for (int i = 0; i < CHARACTERTILEX * CHARACTERTILEY; i++)
		{
			if (PtInRect(&_characterTile[i].rcTile, _ptMouse))
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

	// false 값이 반환 된다면 문제 없다.
	return false;
}

void mapTool::mouseRectUpdate()
{
	// 현재 마우스가 어디 타일에 있는지 찾아준다.
	// 그리고 그 렉트의 정보를 담아온다.
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		// ptMouse의 좌표를 월드 좌표로 바꿔준다.
		//POINT ptMouse_Temp;
		//ptMouse_Temp.x = _ptMouse.x + CAMERAMANAGER->get_CameraX();
		//ptMouse_Temp.y = _ptMouse.y + CAMERAMANAGER->get_CameraY();

		// 만약 타일에 마우스 포인터가 위치 했다면 렉트 정보를 복사한다.
		if (PtInRect(&_tiles[i].rc, _ptMouse))
		{
			_mouseEffect.mouseRect = _tiles[i].rc;

			break;
		}
	}
}
