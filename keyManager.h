#pragma once
#include "singletonBase.h"
#include <bitset>

#define KEYMAX 256

using namespace std;

class keyManager : public singletonBase<keyManager>
{
private:
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;

public:
	keyManager();
	~keyManager();

	HRESULT init();
	void release();

	//키를 한 번 누르면
	bool isOnceKeyDown(int key);
	//키를 눌렀다 떼면
	bool isOnceKeyUp(int key);
	//키를 누르고 있으면
	bool isStayKeyDown(int key);
	//키를 토글하면
	bool isToggleKey(int key);

	bool isOncekeytwoDown(int one, int two);

	bitset<KEYMAX> getKeyUp() { return _keyUp; }
	bitset<KEYMAX> getKeyDown() { return _keyDown; }
	
	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setKeyTwoDown(int one,int two, bool state) 
	{ 
		_keyDown.set(one, state);
		_keyDown.set(two, state);
	}
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }

};

