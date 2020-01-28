#pragma once
#include "gameNode.h"
#include "addImage_Boss.h"

#define LOADINGMAX 1000										//�ε� ī��Ʈ �ƽ�ġ

class loadingScene : public gameNode
{
private:
	image* _background;										//�̹��� ����� ���� ������ְ�

	ADD_BOSS_IMAGE*   _addBossImage;
	ADD_SLAVE_IMAGE*  _addSlaveImage;

public:
	loadingScene();
	~loadingScene();

	int _currentCount;										//�ε� ī��Ʈ �����ġ

	HRESULT init();
	void release();
	void update();
	void render();
};

static DWORD CALLBACK threadFunction(LPVOID lpParameter);	//��𿡼��� �� �� �ְ� static �������
															//�ҷ������� CALLBACK�Լ�
															//�Ķ���Ͱ��� � �ڷ����� ���� �����ϰ� LPVOID
