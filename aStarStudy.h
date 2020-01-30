#pragma once
#include "gameNode.h"
#include <vector>
#define MAX_X 500
#define MAX_Y 500
enum class NODESTATE
{
	NODE_START,
	NODE_END,
	NODE_EMPTY
};
class node
{
	//에이스타에서 기억해야 할 2가지
	//1. 비용(F, G, H)
	//2. 부모노드 포인터(이전노드의 포인터)
public:
	RECT rc;				//렉트
	int idx, idy;			//인덱스 x, y
	int F, G, H;			//F = G + H //G = 시작 to 현재 //H = 현재 to 종료
	node* parentNode;		//부모를 가리킬 노드(이전노드)
	NODESTATE nodeState;	//노드의 상태(시작, 종료, 벽, 빈노드)
	//노드 생성자
	node() {}
	//생성자 오버로딩을 통한 초기화
	node(int _idx, int _idy)
	{
		idx = _idx;
		idy = _idy;
		F = G = H = 0;
		nodeState = NODESTATE::NODE_EMPTY;
		parentNode = NULL;
	}
};
class aStarStudy:public gameNode
{
private:
	node* _totalNode[MAX_X][MAX_Y];
	node* _startNode;
	node* _endNode;
	node* _curNode;

	vector<node*> _openList;
	vector<node*> _closeList;
	vector<node*> _finalList;

	int _count;
	bool _isFind;

public:
	HRESULT init();
	void release();
	void update();

	void setStart(int idx, int idy);
	void setEnd(int idx, int idy);

	/*중요함수*/
	//길찾기 함수
	void pathFinding();
	//오픈리스트에 추가 함수
	void addOpenList(int idx, int idy);
	//오픈리스트 삭제
	void delOpenList(int index);

	vector<node*> getFinalList() { return _finalList; }

	aStarStudy() : _startNode(NULL), _endNode(NULL) {}
	~aStarStudy() {}
};

