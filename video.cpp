#include "stdafx.h"
#include "video.h"

video::video()
{
}

video::~video()
{
}

HRESULT video::init(const char* videoName, bool ending)
{
	if (ending)
	{
		cv::namedWindow(WINNAME);
		HWND cvWnd = (HWND)cvGetWindowHandle(WINNAME);
		if (!cvWnd) return false;
		HWND oldParent = ::GetParent(cvWnd);
		::SetParent(cvWnd, oldParent);
		//::ShowWindow(oldParent, SW_HIDE);
		// resizeWindow(WINNAME, WINSIZEX + 100, WINSIZEY+ 50); //동영상 크기라서 안됌 
		moveWindow(WINNAME, -74, -120);		// 이동시키기 
		::SetParent(oldParent, _hWnd);
	}
	//ShowWindow(_hWnd, NULL);

	SCENEMANAGER->setVideoPlay(true); // 비디오를 플레이 하니까 플레이 true로 
	_aviName = videoName;
	cap.open(videoName);		// 비디오 Name을 열어봄 

	if (!cap.isOpened())	// 비디오 파일이 아니면 오류 메시지를 띄움 
	{
		MessageBox(NULL, "동영상을 열수 없습니다.", "오류 메시지", MB_OK);		// 메시지 출력 
		SCENEMANAGER->setVideoPlay(false);
		SCENEMANAGER->changeScene("Stage");									// 혹시 모르니 스테이지로 
	}
	_play = true;	// BOOL 값 시작
	return S_OK;
}

void video::release()
{
}

void video::update()
{
}

void video::render()
{
	// 초기값이 시작 
	if (_play)
	{
		//
		if (cap.isOpened())
		{
			Mat frame;			     // opencv에서 사용하는 구조체  
			frame.setTo(Scalar(0));	 // 초기값 초기화 
			cap >> frame;			 // cap(동영상파일) -> frame이라는 구조체에 넣는다.		 
			//if (cap.get(CAP_PROP_POS_FRAMES) == cap.get(CAP_PROP_FRAME_COUNT)) ( 현재 프레임 == 최대 프레임 )  // 나중에 쓸수도 있으니 주석처리 
			// 만약 동영상이 비어있으면 
			if (frame.empty())
			{
				_play = false;
				SCENEMANAGER->setVideoPlay(false);  // 씬 매니저에 비디오 값을 수정해줌 
				cap.release();
				frame.release();
				destroyAllWindows();	// opencv 창해제 
				// 인트로 이면 
				if (_aviName == "intro.avi")
				{
					// 로딩씬으로 가기 
					SCENEMANAGER->changeScene("Loading");
				}
				else // endScene이면 스테이지로  
				{
					SCENEMANAGER->changeScene("Stage");
				}
				return;
			}
			Mat edges;
			// 빨리감으면 로딩씬으로 
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_play = false;
				SCENEMANAGER->setVideoPlay(false); // 씬 매니저에 비디오 값을 수정해줌 
				cap.release();
				frame.release();
				destroyAllWindows();			// opencv 창해제 
				if (_aviName == "intro.avi")
				{
					//로딩씬으로 
					SCENEMANAGER->changeScene("Loading");
				}
				else // endScene이면 스테이지로  
				{
					SCENEMANAGER->changeScene("Stage");
				}
				return;
			}
			imshow(WINNAME, frame);  // 윈도우창에 프레임을 띄운다 -> 실제로 동영상을 띄우는 코드 
		}
	}

}

// 나중에 혹시나 쓰일수 있으니 복사해둠 
void video::videoRecord()
{
	//	double fps = 15;
	//
	//	int fourcc = CV_FOURCC('X', 'V', 'I', 'D'); // codec
	//
	//	bool isColor = true;
	//
	//
	//
	//	VideoWriter* video = new VideoWriter;
	//
	//	if (!video->open("result.avi", fourcc, fps, Size(img_w, img_h), isColor)) {
	//
	//		delete video;
	//
	//		return;
	//
	//	}
	//
	//
	//
	//	Mat img;
	//
	//	while (1) {
	//
	//		// ...
	//
	//		*video << img;
	//
	//		// ...
	//
	//	}
	//
	//	delete video;
	//
	//
	//
	//출처: https://jangjy.tistory.com/21 [살다보니..]
}

void video::setPlay()
{
	_play = true;
}

void video::setStop()
{
	_play = false;
}

