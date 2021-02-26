#pragma once
#include"gameNode.h"
#include"bullet.h"
#include"item.h"

class enemymanager;
enum PLAYERMOTION
{
	PLAYER_IDLE,
	PLAYER_LEFT_MOVE,
	PLAYER_RIGHT_MOVE
};
enum PLAYERBULLET
{
	SKILL1,
	SKILL2

};
struct tagPlayerobject
{
	RECT rc;
	image* playerimage;
	bool ison;
	int index, indexY;
	int _count;
	int _sdcount;

};
class Player : public gameNode
{
private:
	image* _player;
	int _playerpower;
	
	RECT _rc;
	int _indexX, _indexY;

	PLAYERMOTION _playermotion;
	PLAYERBULLET _playerskill;
	int count;
	tagPlayerobject _playerobject;
	tagPlayerobject _playersd;
	playerbullet* _playerbullet;
	item* _item;
	int countt;
	enemymanager* _em;
	bool alphaon;
	int alpha;
	int alphacount;
	int _playerlife;
	bool itemon;
	bool modeon;
public:

	Player() {};
	~Player() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void control();
	virtual void collsion();
	virtual void motion();
	virtual void playerskill(PLAYERBULLET playerskill);
	virtual void itemcollsion();
	virtual void playerLife(int Num);
	virtual void setEnemyMemoryaddressLink(enemymanager* em) { _em = em; }
	image* getPlayeimage() { return _player; }
	tagPlayerobject getPlayerSD() { return _playersd; }
	inline int getHP() { return _playerlife; }
};


