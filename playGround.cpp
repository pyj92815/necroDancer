#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);
	//¸ÊÅø ÆÈ·¹Æ® Æ²
	IMAGEMANAGER->addImage("terrainPalette", "./image/mapTool/icon/toolbar.bmp", 360, 360, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("wallPalette", "./image/mapTool/icon/walltoolbar.bmp", 884, 468, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("trapPalette", "./image/mapTool/icon/traptoolbar.bmp", 364, 416, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("itemPalette", "./image/mapTool/icon/itemtoolbar.bmp", 260, 312, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("left", "./image/mapTool/icon/left.bmp", 25, 900, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("right", "./image/mapTool/icon/right.bmp", 25, 900, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("top", "./image/mapTool/icon/top.bmp", 1800, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bottom", "./image/mapTool/icon/bottom.bmp", 1800, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("save", "./image/mapTool/icon/save.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("load", "./image/mapTool/icon/load.bmp", 52, 52, true, RGB(255, 0, 255));
	//ÆÈ·¹Æ®¿¡ »ç¿ëµÉ ÀÌ¹ÌÁöµé
	IMAGEMANAGER->addFrameImage("terrainTiles", "./image/mapTool/terrain/tile.bmp", 312, 312, TERRAINTILEX, TERRAINTILEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("wallTiles", "./image/mapTool/wall/wall.bmp", 832, 416, WALLTILEX, WALLTILEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("trapTiles", "./image/mapTool/trap/trap.bmp", 312, 364, TRAPTILEX, TRAPTILEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("armorTiles", "./image/mapTool/item/passive.bmp", 208, 260, ITEMTILEX, ITEMTILEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("weaponTiles", "./image/mapTool/item/weapon.bmp", 208, 260, ITEMTILEX, ITEMTILEY, true, RGB(255, 0, 255));

	/*multimap<string, int> mm;


	mm.insert(pair<string, int>("¼¼ÈÆ", 300));
	mm.insert(pair<string, int>("¶ôÈÆ", 200));
	mm.insert(pair<string, int>("Çü±æ", 100));


	multimap<string, int>::iterator miter;

	for (miter =mm.begin();miter != mm.end();miter++)
	{
		cout <<miter->first<<","<< miter->second << endl;
	}*/
	_sm = new scene_Manager;
	_sm->init();

	
	return S_OK;
}


void playGround::release()
{
	gameNode::release();
	_sm->release();
}


void playGround::update()
{
	gameNode::update();
	_sm->update();
}



void playGround::render()
{
	//PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	PatBlt(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY, BLACKNESS);
	//PatBlt(CAMERAMANAGER->getmapToolDC(), CAMERAMANAGER->get_CameraMapSize_X(), CAMERAMANAGER->get_CameraMapSize_Y(), WINSIZEX, WINSIZEY, BLACKNESS);

	//===========================================================
	
	_sm->render();

	//===========================================================
	if (!SCENEMANAGER->getVideoPlay()) _backBuffer->render(getHDC(), 0, 0);

}
