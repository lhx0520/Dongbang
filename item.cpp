#include "stdafx.h"
#include "item.h"


HRESULT item::init(int itemMax)
{

	_itemMax = itemMax;

	return S_OK;
}

void item::release()
{
}

void item::update()
{
	move();


}

void item::render()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); _viItem++)
	{
		_viItem->itemimage->render(getMemDC(), _viItem->rc.left, _viItem->rc.top);

	}

}

void item::fire(float x, float y)
{

	if (_itemMax < _vItem.size())return;

	tagItem item;
	ZeroMemory(&item, sizeof(tagItem));
	_itemtype = (ITEMTYPE)RND->getInt(3);
	switch (_itemtype)
	{
	case SCORE_ITEM:
		item.item = SCORE_ITEM;
		item.itemimage = IMAGEMANAGER->findImage("점수");
		break;
	case POWER_ITEM:
		item.item = POWER_ITEM;
		item.itemimage = IMAGEMANAGER->findImage("파워");
		break;
	case SHIELD_ITEM:
		item.item = SHIELD_ITEM;
		item.itemimage = IMAGEMANAGER->findImage("쉴드");
		break;
	default:
		break;
	}


	item.jumppw = 4;
	item.gravity = 0;
	item.angle = PI / 2;
	item.x = item.fireX = x;
	item.y = item.fireY = y;
	item.rc = RectMakeCenter(item.x, item.y,
		item.itemimage->getWidth(),
		item.itemimage->getHeight());

	_vItem.push_back(item);
}

void item::move()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end();)
	{
		_viItem->gravity += 0.09f;
		_viItem->x += cosf(_viItem->angle) * _viItem->jumppw;
		_viItem->y += -sinf(_viItem->angle) * _viItem->jumppw + _viItem->gravity;
		if (_viItem->gravity > 10)
		{
			_viItem->gravity = 10;
		}
		_viItem->rc = RectMakeCenter(_viItem->x, _viItem->y,
			_viItem->itemimage->getWidth(),
			_viItem->itemimage->getHeight());
		if (_viItem->rc.bottom > WINSIZEY)
		{
			_viItem = _vItem.erase(_viItem);
		}
		else ++_viItem;

	}


}

void item::removeitem(int arrNum)
{

	_vItem.erase(_vItem.begin() + arrNum);
}
