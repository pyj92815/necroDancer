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

	void addSlaveImage();			// �����̺��� �̹����� �߰��Ѵ�.
	void addSlaveAnimation();		// �����̺��� �ִϸ��̼��� �߰��Ѵ�.

};

// �����̺� �⺻ Ŭ���� 