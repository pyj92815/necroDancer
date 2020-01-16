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


	mm.insert(pair<string, int>("¼¼ÈÆ", 300));
	mm.insert(pair<string, int>("¶ôÈÆ", 200));
	mm.insert(pair<string, int>("Çü±æ", 100));


	multimap<string, int>::iterator miter;

	for (miter =mm.begin();miter != mm.end();miter++)
	{
		cout <<miter->first<<","<< miter->second << endl;
	}*/

	_pm = new playerManager;
	_pm->init();

	_em = new EnemyManager;
	_em->init();

	
	return S_OK;
}


void playGround::release()
{
	gameNode::release();


}


void playGround::update()
{
	gameNode::update();

	_pm->update();
	_em->update();

}



void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//===========================================================
	_pm->render();
	_em->render();
	//ENEMYMANAGER->render(getMemDC());
	//===========================================================
	_backBuffer->render(getHDC(), 0, 0);
}
