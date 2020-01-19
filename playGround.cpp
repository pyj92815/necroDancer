#include "stdafx.h"
#include "playGround.h"
#include <map>

playGround::playGround()
{
}


playGround::~playGround()
{
}


HRESULT playGround::init()
{
	gameNode::init(true);
	
	/*multimap<string, int> mm;


	mm.insert(pair<string, int>("세훈", 300));
	mm.insert(pair<string, int>("락훈", 200));
	mm.insert(pair<string, int>("형길", 100));


	multimap<string, int>::iterator miter;

	for (miter =mm.begin();miter != mm.end();miter++)
	{
		cout <<miter->first<<","<< miter->second << endl;
	}*/
	_pm = new playerManager;
	_pm->init();
	//
	_em = new EnemyManager;
	_em->init();

	_bss = new bossStageScene;
	_bss->init();
	
	return S_OK;
}


void playGround::release()
{
	gameNode::release();

}


void playGround::update()
{
	gameNode::update();
	KEYANIMANAGER->update();		// 플레이어 애니매이션 
	_pm->update();
	_em->update();
	_bss->update();

}



void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//===========================================================
	_pm->render();
	_em->render();
	//ENEMYMANAGER->render(getMemDC());
	_bss->render();
	//===========================================================
	_backBuffer->render(getHDC(), 0, 0);
}
