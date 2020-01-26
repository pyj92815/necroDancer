#include "stdafx.h"
#include "bossStageTestTile.h"

bossStageTestTile::bossStageTestTile()
{
}

bossStageTestTile::~bossStageTestTile()
{
}

HRESULT bossStageTestTile::init()
{
	//setTile();	// 기본 타일 셋팅
	BossStageLoad();	// 보스맵을 불러와서 저장한다.

	return S_OK;
}

void bossStageTestTile::release()
{
}

void bossStageTestTile::update()
{
}

void bossStageTestTile::render()
{
	// 지금은 쓰지 않는다.
	//for (int i = 0; i < _vTotalList.size(); ++i)
	//{
	//	if ((_vTotalList[i]->getIdX() + _vTotalList[i]->getIdY()) % 2)
	//	{
	//		if ((int)TIMEMANAGER->getWorldTime() % 2)
	//			IMAGEMANAGER->findImage("Floor_Test")->frameRender(getMemDC(), _vTotalList[i]->getRect().left, _vTotalList[i]->getRect().top, 1, 1);
	//		else
	//			IMAGEMANAGER->findImage("Floor_Test")->frameRender(getMemDC(), _vTotalList[i]->getRect().left, _vTotalList[i]->getRect().top, 2, 1);
	//	}
	//	else
	//	{
	//		if((int)TIMEMANAGER->getWorldTime() % 2)
	//			IMAGEMANAGER->findImage("Floor_Test")->frameRender(getMemDC(), _vTotalList[i]->getRect().left, _vTotalList[i]->getRect().top, 2, 1);
	//		else
	//			IMAGEMANAGER->findImage("Floor_Test")->frameRender(getMemDC(), _vTotalList[i]->getRect().left, _vTotalList[i]->getRect().top, 1, 1);
	//	}
	//}


}

void bossStageTestTile::setTile()
{
	// 지금은 쓰지 않는 함수
	//
	//// 테스트용 이미지
	//IMAGEMANAGER->addFrameImage("Heart_Test", "./image/Enemy/boss/beat_heart_test.bmp", 164, 104, 2, 1, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("Floor_Test", "./image/Enemy/boss/floor_test.bmp", 156, 104, 3, 2, true, RGB(255, 0, 255));
	//
	//// 전체 타일 셋팅
	//for (int y = 0; y < TESTTILEY; ++y)
	//{
	//	for (int x = 0; x < TESTTILEX; ++x)
	//	{
	//		tile* node = new tile;
	//		node->init("floor", x, y, TESTTILESIZE, TESTTILESIZE);
	//		node->setAttribute("기본타일");
	//
	//		_vTotalList.push_back(node);
	//	}
	//}
}

void bossStageTestTile::BossStageLoad()
{
	// 보스 스테이지 맵을 불러와서 
	// _tiles에 담는다.
	HANDLE file;
	DWORD read;

	file = CreateFile("BossStageFile.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);

	int i = 0;

	while (_tiles[i] != NULL)
	{
		// 타일의 타입이 NONE이 아니라면 벡터에 담는다.
		if (_tiles[i]->type != TYPE_NONE)  _vTotalList.push_back(_tiles[i]);
		i++;
	}

	cout << _vTotalList.size() << endl;
}
