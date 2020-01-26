#pragma once
#include "singletonBase.h"
#include <map>

class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
public:
	typedef map<string, gameNode*>				mapSceneList;
	typedef map<string, gameNode*>::iterator	mapSceneIter;

private:
	static gameNode* _currentScene;
	mapSceneList _mSceneList;

	bool _videoPlay;

public:
	sceneManager();
	~sceneManager();

	HRESULT init();
	void release();
	void update();
	void render();

	gameNode* addScene(string sceneName, gameNode* scene);

	HRESULT changeScene(string sceneName);

	bool getVideoPlay() { return _videoPlay; }				// 비디오 플레이가 있는 씬인지 아닌지의 BOOL
	void setVideoPlay(bool value) { _videoPlay = value; }   // 비디오 플레이 값 수정하기 
};

