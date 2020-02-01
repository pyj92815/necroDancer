#pragma once
#include "gameNode.h"
#include "player.h"

enum HEARTSTATE							//��Ʈ HP����
{
	HEARTSTATE_FULL,
	HEARTSTATE_HALF,
	HEARTSTATE_NULL
};
enum HEARTTURN							//��Ʈ ������ ����
{
	TURN_ON,
	TURN_OFF
};
enum INVENSTATE							//�κ��丮 ����
{
	INVENSTATE_FULL,
	INVENSTATE_NULL
};

struct heartTag							//��Ʈ ����ü
{
	image* image;
	HEARTSTATE state;
	HEARTTURN turn;
	animation* anime;
};
struct invenTag							//�κ��丮 ����ü
{
	image* image;
	RECT rc;
	INVENSTATE state;
	float x;
	float y;
	bool open;

};

class UImanager : public gameNode
{

private:

private:
	vector<tagItem*>					_vInven;		//�κ��丮 ����
	vector<tagItem*>::iterator			_viInven;		//�κ��丮 ���ͷ�����
	player* _pm;										//�÷��̾� ������
	tagPlayer* _player;									//�÷��̾� ����ü ������

	//�κ��丮 ����ü
	invenTag _attackInven;								
	invenTag _shovelInven;
	invenTag _itemInven;
	invenTag _bombInven;
	invenTag _throwInven;
	invenTag _bodyInven;
	invenTag _headInven;
	invenTag _feetInven;
	invenTag _torchInven;
	invenTag _ringInven;
	invenTag _coinInven;
	invenTag _daiaInven;

	//���ڵ�
	invenTag _downLeft;
	invenTag _upDown;
	invenTag _upLeft;

	//��Ʈ
	heartTag _heart[3];

	animation* _FrameWork;
	image* _scoreNum;
	image* _scoreX;
	image* _daiaNum;

	int _coinvalue;				//���߿� �÷��̾ ���� �浹�� ���ڷ� �޾ƿ��� �Լ��� �ٲ��ָ� �ɵ�
	int _diavalue;

	int _hp;

	bool _heartinterval;
	int _heartBeatCnt;
	
	int _currentFrameSpeed;
	int _frameCount;

	float tx;

	//���� ������ ��ġ ��ǥ
	float _x1Slot , _y1Slot;
	float _x2Slot , _y2Slot;
	float _x3Slot , _y3Slot;
	float _x4Slot , _y4Slot;
	float _x5Slot;
	float _x6Slot;
	float _x7Slot;


public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	void set_HP() { _hp--; }

	void setInven(vector<tagItem*> inven) { _vInven = inven; }
	void setPlayerInfo(tagPlayer* player) { _player  = player; }
	

};

