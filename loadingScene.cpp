#include "stdafx.h"
#include "loadingScene.h"
#include "progressBar.h"

loadingScene::loadingScene()
	: _background(nullptr),			//init보다 훨씬 앞선 초기화 개념인듯?
	_currentCount(0)
{
}


loadingScene::~loadingScene()
{
}

HRESULT loadingScene::init()
{
	_background = IMAGEMANAGER->addImage("로딩배경", "Intro_loading_start.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	CreateThread(
		NULL,			//스레드의 보안속성(자식윈도우가 있을때) 핸들로 자식인지 부모인지 파악
		NULL,			//스레드의 스택크기(NULL로 두면 메인쓰레드와 스택크기는 동일하다)
		threadFunction,	//스레드 사용할 함수 명
		this,			//스레드의 매개변수(this로하면 본 클래스)
		NULL,			//스레드의 특성(NULL로 두면 바로 실행한다)
		0				//스레드의 생성 후 스레드의 ID를 넘겨준다 보통은 NULL로 둠.
	);

	_addBossImage->add_BossImage();
	_addBossImage->add_BossAnimation();
	
	_addSlaveImage->add_SlaveImage();
	_addSlaveImage->add_SlaveAnimation();

	return S_OK;
}

void loadingScene::release()
{
}

void loadingScene::update()
{
	if (_currentCount == LOADINGMAX)							//로딩카운트가 맥스일 경우
	{
		_background = IMAGEMANAGER->findImage("intro_end");		//배경 이미지를 intro_end로 바꿔준다

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))				//키를 누르면
		{
			SCENEMANAGER->changeScene("Stage");					//스테이지로 넘어간다
		}
	}

}

void loadingScene::render()
{
	_background->render(getMemDC(), 0, 0);
}

DWORD CALLBACK threadFunction(LPVOID lpParameter)
{
	loadingScene* loadHealper = (loadingScene*)lpParameter;	//굳이 로딩씬 안에서 로딩씬클래스에 포인터를 사용한건
															//아마 스타틱함수 안에 넣기 위함일듯(전체적으로 공유하니까?)

	while (loadHealper->_currentCount != LOADINGMAX)		//로딩카운트가 맥스가 아닐 시
	{
		IMAGEMANAGER->addImage("intro_end", "Intro_loading_end.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));
		Sleep(1);											//지연시켜준다 Sleep함수의 1은 1ms = 0.001초를 말한다

		loadHealper->_currentCount++;						//로딩카운트를 올려준다.
	}


	return 0;
}

