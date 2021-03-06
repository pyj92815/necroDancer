#pragma once
#include "gameNode.h"

class tile : public gameNode
{
private:
	image* _image;		 // 플레이어 테스트 

	int _idX;
	int _idY;

	POINT _center;
	RECT _rc;

	//F = G + H
	float _totalCost;		//총 비용
	float _costFromStart;	//시작위치로부터 현재 노드
	float _costToGoal;		//현재 노드로부터 도착점까지 경로비용

	bool _isOpen;

	tile* _parentNode;		//현재 타일(상위에서 계산되고있는)

	COLORREF _color;
	HBRUSH _brush;
	HPEN _pen;

	const char* _attribute;	//타일속성

	int _alphaValue;		// 알파블랜더 값 

public:
	tile();
	~tile();

	HRESULT init(int idX, int idY);
	HRESULT init(const char* imageName, int idX, int idY, int tileWidth, int tileHeight);  // 플레이어 테스트 
	void release();
	void update();
	void render();
	void render(HDC hdc);  // 플레이어 테스트 렌더

	int getIdX() { return _idX; }
	int getIdY() { return _idY; }

	int getAlphaValue() { return _alphaValue; }
	void setAlphaValue(int value) { _alphaValue = value; }

	void setColor(COLORREF color)
	{
		DeleteObject(_brush);
		_color = color;
		_brush = CreateSolidBrush(_color);
	}

	RECT getRect() { return _rc; }

	//================= 접근자 & 설정자 ==================

	void setCenter(POINT center) { _center = center; }
	POINT getCenter() { return _center; }

	void setAttribute(const char* str) { _attribute = str; }
	const char* getAttribute() { return _attribute; }

	void setTotalCost(float totalCost) { _totalCost = totalCost; }
	float getTotalCost() { return _totalCost; }

	void setCostFromStart(float costFromStart) { _costFromStart = costFromStart; }
	float getCostFromStart() { return _costFromStart; }

	void setCostToGoal(float costToGoal) { _costToGoal = costToGoal; }
	float getCostToGoal() { return _costToGoal; }

	void setParentNode(tile* t) { _parentNode = t; }
	tile* getParentNode() { return _parentNode; }

	void setIsOpen(bool isOpen) { _isOpen = isOpen; }
	bool getIsOpen() { return _isOpen; }




};

