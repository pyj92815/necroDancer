#pragma once
#include "gameNode.h"


#define LOADINGMAX 100									//로딩 카운트 맥스치

class loadingScene : public gameNode
{
private:
	image* _background;										//이미지 빈공간 변수 만들어주고

public:
	loadingScene();
	~loadingScene();

	int _currentCount;										//로딩 카운트 현재수치

	HRESULT init();
	void release();
	void update();
	void render();
};

static DWORD CALLBACK threadFunction(LPVOID lpParameter);	//어디에서든 쓸 수 있게 static 멤버변수
															//불러오도록 CALLBACK함수
															//파라미터값은 어떤 자료형이 들어가든 가능하게 LPVOID
