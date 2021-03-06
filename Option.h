#pragma once
#include "singletonBase.h"

class gameNode; // 게임 노드와 전방 선언

/*
enum OPTION_STATE
{
	OPTION_TITLE, OPTION_LOBBY, OPTION_DUNGEON
};
*/

class Option : public singletonBase<Option>
{
private:
	bool isOpen;
	int keyId;

public:
	Option();
	~Option();

	HRESULT init();
	void release();
	void update();
	void render();

	bool CheckOptionOpen() { return isOpen; }
	void SetOptionOpen(bool _isOpen) { isOpen = _isOpen; }

	int CheckKeyID() { return keyId; }
	void SetKeyID(int _keyId) { keyId = _keyId; }
};