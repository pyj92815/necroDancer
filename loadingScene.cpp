#include "stdafx.h"
#include "loadingScene.h"
#include "progressBar.h"

loadingScene::loadingScene()
	: _background(nullptr),			//init���� �ξ� �ռ� �ʱ�ȭ �����ε�?
	_currentCount(0)
{
}


loadingScene::~loadingScene()
{
}

HRESULT loadingScene::init()
{
	_background = IMAGEMANAGER->addImage("�ε����", "Intro_loading_start.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	CreateThread(
		NULL,			//�������� ���ȼӼ�(�ڽ������찡 ������) �ڵ�� �ڽ����� �θ����� �ľ�
		NULL,			//�������� ����ũ��(NULL�� �θ� ���ξ������ ����ũ��� �����ϴ�)
		threadFunction,	//������ ����� �Լ� ��
		this,			//�������� �Ű�����(this���ϸ� �� Ŭ����)
		NULL,			//�������� Ư��(NULL�� �θ� �ٷ� �����Ѵ�)
		0				//�������� ���� �� �������� ID�� �Ѱ��ش� ������ NULL�� ��.
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
	if (_currentCount == LOADINGMAX)							//�ε�ī��Ʈ�� �ƽ��� ���
	{
		_background = IMAGEMANAGER->findImage("intro_end");		//��� �̹����� intro_end�� �ٲ��ش�

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))				//Ű�� ������
		{
			SCENEMANAGER->changeScene("Stage");					//���������� �Ѿ��
		}
	}

}

void loadingScene::render()
{
	_background->render(getMemDC(), 0, 0);
}

DWORD CALLBACK threadFunction(LPVOID lpParameter)
{
	loadingScene* loadHealper = (loadingScene*)lpParameter;	//���� �ε��� �ȿ��� �ε���Ŭ������ �����͸� ����Ѱ�
															//�Ƹ� ��Ÿƽ�Լ� �ȿ� �ֱ� �����ϵ�(��ü������ �����ϴϱ�?)

	while (loadHealper->_currentCount != LOADINGMAX)		//�ε�ī��Ʈ�� �ƽ��� �ƴ� ��
	{
		IMAGEMANAGER->addImage("intro_end", "Intro_loading_end.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));
		Sleep(1);											//���������ش� Sleep�Լ��� 1�� 1ms = 0.001�ʸ� ���Ѵ�

		loadHealper->_currentCount++;						//�ε�ī��Ʈ�� �÷��ش�.
	}


	return 0;
}

