#pragma once
#include "gameNode.h"


class video:public gameNode
{
private:
	VideoCapture cap;		// opencv 비디오 관련 구조체 
	const char* _aviName;
	bool _play;				// BOOL 값(필요한지 안한지 판단할 예정)
public:

	video();
	~video();

	HRESULT init(const char* videoName);
	void release();
	void update();
	void render();

	void videoRecord();		// 저장하는 코드 아직 검증되지 않음(판단예정)

	// 혹시 몰라서 만들어 놓음 (삭제 예정)
	void setPlay();
	void setStop();
};

