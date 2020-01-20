#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

// 사용법을 몰라서 주석처리함 
//#include <vfw.h>   // 동영상을 추가하기 위한 헤더파일 
//#pragma comment(lib,"vfw32.lib")

//영상처리를 하기 위한 OpenCV (open Source Computer Vision)
// C++ 기반
// 다양한 영상처리 알고리즘을 쉽게 사용 가능 
// MAT api 사용시 사용되는 이미지 정보가 저장되는 클래스 
// IplImage 이미지 정보가 저장되는 구조체 (지금 사용안됨)

#include <opencv2/highgui.hpp>  // 고급 GUI 
#include <opencv2/cvconfig.h>
#include "opencv2/opencv.hpp"	
#include <opencv2/highgui/highgui_c.h>

#pragma comment (lib,"opencv_world420d.lib")

// #include <opencv2/videoio.hpp> // 동영상 처리 
// 주요 함수 https://jangjy.tistory.com/18?category=625807
// 마우스 함수 https://cinema4dr12.tistory.com/809
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>

using namespace cv;
using namespace std;

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "utils.h"
#include "imageManager.h"
#include "timeManager.h"
#include "effectManager.h"
#include "txtData.h"
#include "soundManager.h"
#include "sceneManager.h"
#include "keyAniManager.h"
#include "iniDataManager.h"
#include "cameraManager.h"

using namespace SEVENTEEN_UTIL;

//=========================================
// ## 19.10.30 ## - 디파인문 -
//=========================================

#define WINNAME (LPCTSTR)(TEXT("SevenTeen Class"))
#define WINSTARTX 50
#define WINSTARTY 50
#define WINSIZEX 960
#define WINSIZEY 640
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define KEYANIMANAGER keyAniManager::getSingleton()
#define INIDATAMANAGER iniDataManager::getSingleton()
#define CAMERAMANAGER cameraManager::getSingleton()

#define SAFE_DELETE(p) {if(p) {delete(p); (p)=NULL;}}
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[](p); (p) = NULL;}}

//==========================================
// ## 19.10.31 ## Extern
//==========================================
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;
extern BOOL			_leftButtonDown;

//
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
