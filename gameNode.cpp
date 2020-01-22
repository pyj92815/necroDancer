#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == CV_EVENT_MOUSEMOVE)
	{
		//cout << "마우스 좌표" << "x:" << x << "y :" << y << endl;
		_ptMouse.x = x;
		_ptMouse.y = y;
	}
}

HRESULT gameNode::init()
{

	_hdc = GetDC(_hWnd);
	_managerInit = false;
	
	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (_managerInit)
	{
		
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TXTDATA->init();
		TIMEMANAGER->init();
		EFFECTMANAGER->init();
		SOUNDMANAGER->init();
		SCENEMANAGER->init();
		KEYANIMANAGER->init();
		INIDATAMANAGER->init();
		CAMERAMANAGER->init();
		BEATMANAGER->init();

	}

	return S_OK;
}

void gameNode::release()
{
	if (_managerInit)
	{
	
		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		TXTDATA->release();
		TXTDATA->releaseSingleton();
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();
		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		KEYANIMANAGER->release();
		KEYANIMANAGER->releaseSingleton();
		INIDATAMANAGER->release();
		INIDATAMANAGER->releaseSingleton();
		CAMERAMANAGER->release();
		CAMERAMANAGER->releaseSingleton();

	}

	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update()
{
	cvSetMouseCallback(WINNAME, CallBackFunc, NULL); // 위치 좌표를 넣기 위한 값 
	SOUNDMANAGER->update();
	KEYANIMANAGER->update();
}

void gameNode::render()
{
}

//void gameNode::loadSet(STAGE stage, int stageNum)
//{
//	HANDLE file;
//	DWORD read;
//
//	char str[256];
//	switch (stage)
//	{
//	case LOBY_STAGE:
//
//		sprintf_s(str, "SaveFile.map");
//		tagTile* tile;
//		tile = new tagTile;
//
//		load(str, tile);
//
//		break;
//	case BASIC_STAGE:
//		switch (stageNum)
//		{
//			case 1:
//				sprintf_s(str, "stage01Map.map");
//			break;
//			case 2:
//				sprintf_s(str, "stage02Map.map");
//				break;
//			case 3:
//				sprintf_s(str, "stage03Map.map");
//				break;
//		}
//		tagTile tile[STAGESIZE];
//		load(str, tile);
//		break;
//	case BOSSS_STAGE:
//		sprintf_s(str, "boss3Map.map");
//		tagTile tile[BOSSSTAGESIZE];
//		load(str, tile);
//		break;
//
//	}
//
//	//file = CreateFile(str, GENERIC_READ, 0, NULL,
//	//	OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//	//	//tagTile _tiles[40 * 40];
//	//ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
//	////ReadFile(file, _pos, sizeof(int) * 2, &read, NULL);
//
//	////맵을 불로온 직후 타일의 속성을 매겨준다
//
//
//	//CloseHandle(file);
//
//}
//
//void gameNode::load(char* str, tagTile* _tile)
//{
//	HANDLE file;
//	DWORD read;
//	
//
//	file = CreateFile(str, GENERIC_READ, 0, NULL,
//		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//	//tagTile _tiles[40 * 40];
//	ReadFile(file, _tile, sizeof(tagTile) * 1, &read, NULL);
//}


LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

	PAINTSTRUCT ps;
	HDC			hdc;

	switch (iMessage)
	{
		case WM_CREATE:
		
		break;

		//목이 아파서 잠시 주석으로 남김 감기조심해라
		//굳이 이렇게 하는 이유는 옛날에는 스테이지 기획을 기획자들이 하다보니
		//MFC 등으로 빠르게 맵툴을 만들어서 기획파트에 넘겨주는 일이 다반사였음
		//그래서 심미적요인을 빼고 빠르게 기능만 탑재해서 넘겼었음.
		//굳이 윈도우 메시지를 사용하지 않고 우리 평소에 하던대로 하면 
		//이런 난리는 안쳐도 됩니당
		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>(LOWORD(lParam));
			_ptMouse.y = static_cast<float>(HIWORD(lParam));
			cout << "마우스 좌표" << "x:" << _ptMouse.x << "y :" << _ptMouse.y << endl;
			
		break;
		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case VK_ESCAPE:
					PostQuitMessage(0);
				break;
			}
		}
		break;

		case WM_DESTROY:
			PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

