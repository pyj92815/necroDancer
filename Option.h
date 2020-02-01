#pragma once
#include "singletonBase.h"

/*
enum OPTION_STATE
{
	OPTION_TITLE, OPTION_LOBBY, OPTION_DUNGEON
};
*/
enum OPTION
{
	OPTION_STOP,
	OPTION_PLAYERDIE,
};

class Option : public singletonBase<Option>
{
private:
	bool isOpen;
	bool _isDead; // 플레이어 죽을 때
	int keyId;

	int _isDeadDirection;
	int _frameY[3]; // 

public:
	Option();
	~Option();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	bool CheckOptionOpen(OPTION option) { return isOpen; }
	void SetOptionOpen() 
	{
		if (isOpen)
		{
			isOpen = false; 
		}
		else isOpen = true;
	}

	int CheckKeyID() { return keyId; }
	void SetKeyID(int _keyId) { keyId = _keyId; }

	// 플레이어 죽음
	void setPlayerDie(bool value) { _isDead = value; }
	bool getplayerDie() { return _isDead; }
	void playerDirection();
	int getDirection() { return _isDeadDirection;}

};