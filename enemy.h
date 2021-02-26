#pragma once
#include"gameNode.h"

enum STATE
{
	STAGE_1,
	STAGE_2,
	STAGE_3,
	STAGE_4,
	STAGE_5,
	STAGE_BOSS

};
enum BOSSMOVE
{
	BOSS_IDLE,
	BOSS_LEFT_MOVE,
	BOSS_RIGHT_MOVE,
	BOSS_UP_MOVE,
	BOSS_DOWN_MOVE
};


class enemy : public gameNode
{
protected:
	image* _imageName;
	RECT _rc;
	int _indexX, _indexY;
	int _BindexX, _BindexY;
	int _count;
	int _counttt;
	int _countttt;
	float _X, _Y;
	float _angle;
	float _speed;
	int _HP;
	int _fireCount;
	int _rndFireCount;
	bool ison;
	STATE _state;
	int _countt;
	bool isan;
	BOSSMOVE _bossmv;
	RECT _bossobject;

public:
	enemy() {};
	~enemy() {};

	virtual HRESULT init(const char* imageName, POINT position, STATE state, int HP, float angle);
	virtual HRESULT init(const char* imageName, POINT position, STATE state, int HP, float angle, BOSSMOVE bossmv);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void move();
	virtual void draw();
	virtual void EnemyMove();
	virtual void moveHP(int hp);
	virtual bool bulletFire();
	virtual void xymove(float x, float y);
	virtual void bossmove();
	inline RECT getRect() { return _rc; }
	inline int getHP() { return _HP; }
	inline int getindex() { return _BindexX; }

};



