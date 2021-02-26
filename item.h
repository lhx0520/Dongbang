#pragma once
#include"gameNode.h"
#include<vector>

enum ITEMTYPE
{
	SCORE_ITEM,
	POWER_ITEM,
	SHIELD_ITEM

};

struct tagItem
{
	image* itemimage;
	float x, y;
	float fireX, fireY;
	float angle;
	float gravity;
	float jumppw;
	bool isfire;
	RECT rc;
	ITEMTYPE item;


};
class item : public gameNode
{
private:
	vector<tagItem> _vItem;
	vector<tagItem>::iterator _viItem;
	ITEMTYPE _itemtype;
	int _itemMax;

public:
	item() {};
	~item() {};

	virtual HRESULT init(int itemMax);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void fire(float x, float y);
	virtual void move();
	virtual void removeitem(int arrNum);

	vector<tagItem> getVItem() { return _vItem; }
	vector<tagItem>::iterator getViItem() { return _viItem; }

};

