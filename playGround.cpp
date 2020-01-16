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


	mm.insert(pair<string, int>("����", 300));
	mm.insert(pair<string, int>("����", 200));
	mm.insert(pair<string, int>("����", 100));


	multimap<string, int>::iterator miter;

	for (miter =mm.begin();miter != mm.end();miter++)
	{
		cout <<miter->first<<","<< miter->second << endl;
	}*/

	_pm = new playerManager;
	_pm->init();
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
	

}



void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//===========================================================
	_pm->render();
	//===========================================================
	_backBuffer->render(getHDC(), 0, 0);
}
