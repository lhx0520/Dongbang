#include "stdafx.h"
#include "bullet.h"
#include "enemy.h"

//미니언
HRESULT minionbullet::init(const char* imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;
	return S_OK;
}

void minionbullet::release()
{
}

void minionbullet::update()
{
	move();
}

void minionbullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
	{
		_viBullet->bulletlmage->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
}

void minionbullet::fire(float x, float y, float angle, float speed, STATE state)
{
	if (_bulletMax < _vBullet.size())return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletlmage = IMAGEMANAGER->addImage("minionbulelt", "몬스터 블렛 파랑1.bmp", 21, 21, true, RGB(255, 0, 255));
	bullet.angle = angle;
	bullet._state = state;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.speed = speed;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.bulletlmage->getWidth(), bullet.bulletlmage->getHeight());

	_vBullet.push_back(bullet);
}

void minionbullet::fire2(float x, float y, float angle, float speed, STATE state)
{
	if (_bulletMax < _vBullet.size())return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletlmage = IMAGEMANAGER->addImage("minionbulelt2", "몬스터 블렛 보라1.bmp", 21, 21, true, RGB(255, 0, 255));
	bullet.angle = angle;
	bullet._state = state;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.speed = speed;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.bulletlmage->getWidth(), bullet.bulletlmage->getHeight());

	_vBullet.push_back(bullet);

}

void minionbullet::bossfire2(float x, float y, float angle, float speed, STATE state)
{
	if (_bulletMax < _vBullet.size())return;
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletlmage = IMAGEMANAGER->addImage("bossbullet2", "보스 큰블렛.bmp", 62, 62, true, RGB(255, 0, 255));
	bullet.angle = angle;
	bullet._state = state;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.speed = speed;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.bulletlmage->getWidth(), bullet.bulletlmage->getHeight());
	_vBullet.push_back(bullet);
}

void minionbullet::bossfire3(float x, float y, float angle, float speed, STATE state)
{
	if (_bulletMax < _vBullet.size())return;
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletlmage = IMAGEMANAGER->addImage("bossbullet3", "보스블렛빨강.bmp", 14, 14, true, RGB(255, 0, 255));
	bullet.angle = angle;
	bullet._state = state;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.speed = speed;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.bulletlmage->getWidth(), bullet.bulletlmage->getHeight());
	_vBullet.push_back(bullet);
}

void minionbullet::bossfire4(float x, float y, float angle, float speed, STATE state)
{
	if (_bulletMax < _vBullet.size())return;
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletlmage = IMAGEMANAGER->addImage("bossbullet4", "보스얇은블렛2.bmp", 16, 8, true, RGB(255, 0, 255));
	bullet.angle = angle;
	bullet._state = state;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.speed = speed;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.bulletlmage->getWidth(), bullet.bulletlmage->getHeight());
	_vBullet.push_back(bullet);
}

void minionbullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->bulletlmage->getWidth(),
			_viBullet->bulletlmage->getHeight());

		//if (_range < getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY))
		//if (_range < _viBullet->rc.bottom)
		if (_viBullet->_state == STAGE_4 && 400 < getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY))
		{
			_viBullet->speed = 1;
		}
		if (_viBullet->rc.bottom > WINSIZEY || _viBullet->rc.top < 0 || _viBullet->rc.left < 0 || _viBullet->rc.right>800)
		{
			_viBullet = _vBullet.erase(_viBullet);
		}

		else _viBullet++;
	}

}

void minionbullet::remveBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}



//플레이어
HRESULT playerbullet::init(int bulletMax, float range)
{
	_bulletMax = bulletMax;
	_range = range;
	return S_OK;
}

void playerbullet::release()
{
}

void playerbullet::update()
{
	move();
}

void playerbullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
	{
		_viBullet->bulletlmage->alphaRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, 100);
	}
}

void playerbullet::fire(float x, float y, float angle)
{
	if (_bulletMax < _vBullet.size())return;
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletlmage = new image;
	bullet.bulletlmage->init("플레이어발사체.bmp", 20, 20, true, RGB(255, 0, 255));
	bullet.speed = 20.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.angle = angle;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletlmage->getWidth(),
		bullet.bulletlmage->getHeight());
	_vBullet.push_back(bullet);

}

void playerbullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletlmage->getWidth(),
			_viBullet->bulletlmage->getHeight());

		if (0 > _viBullet->rc.top || _viBullet->rc.right > 800)
		{
			SAFE_RELEASE(_viBullet->bulletlmage);
			SAFE_DELETE(_viBullet->bulletlmage);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else _viBullet++;
	}
}

void playerbullet::removeplayerbullet(int arrNum)
{
	SAFE_RELEASE(_vBullet[arrNum].bulletlmage);
	_vBullet.erase(_vBullet.begin() + arrNum);
}

HRESULT bossBullet::init(int bulletMax)
{
	_bulletMax = bulletMax;
	_bulletmove = BULLET_ISMOVE;

	return S_OK;
}

void bossBullet::release()
{
}

void bossBullet::update()
{
	bulletstate();
}

void bossBullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
	{
		_viBullet->bulletlmage->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
}

void bossBullet::fire3(float x, float y, float angle, float speed, STATE state)
{
	if (_bulletMax < _vBullet.size())return;
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletlmage = IMAGEMANAGER->addImage("minionbulelt2", "몬스터 블렛 보라1.bmp", 21, 21, true, RGB(255, 0, 255));
	bullet.angle = angle;
	bullet._state = state;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.speed = speed;

	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.bulletlmage->getWidth(), bullet.bulletlmage->getHeight());
	_vBullet.push_back(bullet);
}



void bossBullet::bulletstate()
{



	count++;

	switch (_bulletmove)
	{
	case BULLET_ISMOVE:
		for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
		{

			_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
			_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->bulletlmage->getWidth(),
				_viBullet->bulletlmage->getHeight());

			if (_viBullet->rc.bottom > WINSIZEY || _viBullet->rc.top < 0 || _viBullet->rc.left < 0 || _viBullet->rc.right>800)
			{
				_viBullet = _vBullet.erase(_viBullet);
			}

			else _viBullet++;
		}
		if (count > 300)
		{
			_bulletmove = BULLET_ISSTOP;
		}
		break;
	case BULLET_ISSTOP:
		for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
		{
			_viBullet->speed = 0;


		}
		if (count > 300 && count > 500)
		{
			_bulletmove = BULLET_REMOVE;
		}

		break;
	case BULLET_REMOVE:
		for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
		{
			_viBullet->speed = 3;
			_viBullet->angle = RND->getFromFloatTo(0, PI * 2);
			_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
			_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->bulletlmage->getWidth(),
				_viBullet->bulletlmage->getHeight());



			if (_viBullet->rc.bottom > WINSIZEY || _viBullet->rc.top < 0 || _viBullet->rc.left < 0 || _viBullet->rc.right>800)
			{
				_viBullet = _vBullet.erase(_viBullet);
			}

			else _viBullet++;
		}
		if (count > 600)
		{
			_bulletmove = BULLET_ISMOVE;
			count = 0;
		}

		break;
	default:
		break;
	}


}

void bossBullet::removebossbullet(int arrNum)
{
	SAFE_RELEASE(_vBullet[arrNum].bulletlmage);
	_vBullet.erase(_vBullet.begin() + arrNum);
}
