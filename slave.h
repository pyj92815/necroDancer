#pragma once
#include "gameNode.h"
#include "slaveLibrary.h"

class slave : public gameNode
{
protected:
	SLAVE_INFO		_slave;
	slaveLibrary	_library;

public:
	slave();
	~slave();

	virtual HRESULT init(SLAVE_TYPE type, int idx, int idy);
	virtual void release();
	virtual void update();
	virtual void render();

	// �����̺�, �÷��̾�, UI
	virtual void move(SLAVE_DIRECTION direction);				// �����̺��� ������ ����

	SLAVE_INFO* get_Slave() { return &_slave; }					// �����̺��� ���� �ּҸ� �޾ƿ´�.
	void slave_Pos_Setting();									// �����̺� ��ǥ ���� ����
};

// �����̺� �⺻ Ŭ���� 