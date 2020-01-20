#pragma once
#include "image.h"
//����۴� ������ �Ѱ��� ������ �Ǵ� �������� �����ô�
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

enum CTRL
{
	CTRL_SAVE,			//���̺� ��ư���� ���� ��
	CTRL_LOAD,			//�ε� ��ư���� ���� ��
	CTRL_OBJECT,		//������Ʈ���� �׸������� ��ư
	CTRL_TERRAINDRAW,	//���� �׸��� ��ư
	CTRL_FLOOR_OBJ,		//�ٴۿ� �ִ� ������Ʈ
	CTRL_WALLDRAW,		//�� �׸��� ��ư
	CTRL_PLAYER,		//�÷��̾� �׸��� ��ư
	CTRL_ENEMY,			//�� �׸��� ��ư
	CTRL_TRAP,			//���� �׸��� ��ư
	CTRL_PLAY,			//���� ������ �˸��� ��ư(������ ��ư�� �����)
	CTRL_ERASER,		//���찳 ��ư (�߸����� ������Ʈ���� ��������)
	CTRL_END
};

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;

public:
	gameNode();
	virtual ~gameNode();

	int _crtSelect;  // ���� ����� �� 

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual HRESULT init(bool managerInit);
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ���� �Լ�
	virtual void render();			//�׸��� ���� �Լ�


	//������� DC�޸� ���� ������
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

};

