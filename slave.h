#pragma once
#include "gameNode.h"

class slave : public gameNode
{
protected:


public:
	slave();
	~slave();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void addSlaveImage();			// 슬레이브의 이미지를 추가한다.
	void addSlaveAnimation();		// 슬레이브의 애니메이션을 추가한다.

};

// 슬레이브 기본 클래스 