#pragma once
#include"gameNode.h"
#include<vector>
#include"minion.h"
#include"boss.h"
#include"bullet.h"


class Player;


class enemymanager : public gameNode
{
private:
	typedef vector<enemy*> vEnemy;
	typedef vector<enemy*>::iterator viEnemy;
private:
	vEnemy _vEnemy;
	viEnemy _viEnemy;
	minionbullet* _minionbullet;
	minionbullet* _minionbullet2;
	bossBullet* _bossbullet;
	Player* _player;
	int count;
	int countt;
	int counttt;
	int countttt;
	int counttttt;
	int countttttt;
	int lifecount;
	STATE _state;
	BOSSMOVE _bossmv;
	float angle;
	float angle2;
	float angle3;
	float angle4;
	float _X, _Y;
	bool ison;

public:
	enemymanager() {};
	~enemymanager() {};
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void setEnemy();
	virtual void EnemyBullatFire();
	virtual void removeEnemy(int arrNum);
	virtual void collsion();
	virtual void stageClear();
	virtual void remove();


	
	vector<enemy*>getVEnemy() { return _vEnemy; }
	vector<enemy*>::iterator getViEnemy() { return _viEnemy; }
	inline  STATE getstate() { return _state; }
	void setPlayerMemortAddressLink(Player* player) { _player = player; }

};


