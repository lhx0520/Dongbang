#pragma once
#include"gameNode.h"
#include<vector>
#include <wincrypt.h>

enum STATE;


struct tagBullet
{
	image* bulletlmage;
	RECT rc;
	float x, y;
	float angle;
	float radius;
	float speed;
	float fireX, fireY;
	int count;
	int _currentFrameX, _currentFrameY;
	STATE _state;
	bool isFire;


};
class minionbullet : public gameNode
{
private:

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	int _bulletMax;
	float _range;
	const char* _imageName;


	//tagBullet _minionbullet;

public:
	minionbullet() {};
	~minionbullet() {};
	virtual HRESULT init(const char* imageName, int bulletMax, float range);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void fire(float x, float y, float angle, float speed, STATE state);
	virtual void fire2(float x, float y, float angle, float speed, STATE state);
	virtual void bossfire2(float x, float y, float angle, float speed, STATE state);
	virtual void bossfire3(float x, float y, float angle, float speed, STATE state);
	virtual void bossfire4(float x, float y, float angle, float speed, STATE state);
	virtual void move();
	virtual void remveBullet(int arrNum);
	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getViBullet() { return _viBullet; }

};


class playerbullet : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet> ::iterator _viBullet;
	int _bulletMax;
	float _range;
public:
	playerbullet() {};
	~playerbullet() {};

	virtual HRESULT init(int bulletMax, float range);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void fire(float x, float y, float angle);
	virtual void move();
	virtual void removeplayerbullet(int arrNum);

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getViBullet() { return _viBullet; }

};
enum BULLETMOVE
{
	BULLET_ISMOVE,
	BULLET_ISSTOP,
	BULLET_REMOVE
};
class bossBullet : public gameNode
{
private:
	vector<tagBullet>         _vBullet;
	vector<tagBullet>::iterator _viBullet;

	int _bulletMax;
	BULLETMOVE _bulletmove;
	int count;
public:
	bossBullet() {};
	~bossBullet() {};

	virtual HRESULT init(int bulletMax);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void fire3(float x, float y, float angle, float speed, STATE state);
	virtual void bulletstate();
	virtual void removebossbullet(int arrNum);

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVibullet() { return _viBullet; }
	inline BULLETMOVE getbulletmove() { return _bulletmove; }
};


