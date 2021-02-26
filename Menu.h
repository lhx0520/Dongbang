#pragma once
#include"gameNode.h"

class Menu : public gameNode
{
private:
	RECT _rc;
	float _x, _y;
	

public:
	Menu() {};
	~Menu() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	inline RECT getRect() { return _rc; }
	
};
