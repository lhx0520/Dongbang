#pragma once
#include"gameNode.h"
#include"Player.h"
#include"enemymanager.h"



class inGame : public gameNode
{
private:
	
	int loopx, loopy;
	Player* _py;
	enemymanager* _em;
	int _alpha;
	int _alpha2;
	bool isPause;
	RECT _rc;
public:
	inGame() {};
	~inGame() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void backgroundloop();
	virtual void setimage();
	virtual void callpause();
	inline RECT getRect() { return _rc; }
	inline bool getisPause() { return isPause; }
};



