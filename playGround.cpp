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
	KEYANIMANAGER->update();		// �÷��̾� �ִϸ��̼� 
	_sm->update();

}



void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//===========================================================

	_sm->render();
	//===========================================================
	if(!SCENEMANAGER->getVideoPlay()) _backBuffer->render(getHDC(), 0, 0);

}
