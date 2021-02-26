#include "stdafx.h"
#include "Player.h"
#include"enemymanager.h"
//#include<iostream>
//#pragma comment (linker, "/entry:WinMainCRTStartup /subsystem:console")
//using namespace std;


HRESULT Player::init()
{
	_player = IMAGEMANAGER->addFrameImage("Player", "ÇÃ·¹ÀÌ¾î ¿òÁ÷ÀÓ.bmp", 0, 0, 330, 86, 11, 2, true, RGB(255, 0, 255));
	_player->setX(800 / 2);
	_player->setY(WINSIZEY / 2 + 200);
	_indexX = _indexY = 0;
	_playermotion = PLAYER_IDLE;
	_playerpower = 0;
	_playerbullet = new playerbullet;
	_playerbullet->init(400, 0);
	_item = new item;
	_item->init(30);
	_rc = RectMakeCenter(_player->getCenterX(), _player->getCenterY(), 90, 100);
	_playerobject.playerimage = IMAGEMANAGER->addImage("Playerobject", "ÇÃ·¹ÀÌ¾î ±¸Ã¼.bmp", 16, 17, true, RGB(255, 0, 255));
	//_playerobject[i].rc = RectMakeCenter(_player->getCenterX() - 30, _player->getCenterY() + 20,16,17);
	_playersd.playerimage = IMAGEMANAGER->addFrameImage("Playersd", "ÇÃ·¹ÀÌ¾î½¯µå3.bmp", 0, 0, 2025, 225, 9, 1, true, RGB(255, 0, 255));
	_playersd.index = _playersd.indexY = 0;
	_playersd._count = 0;
	_playersd._sdcount = 0;
	alphaon = false;
	alpha = 255;
	_playerlife = 2;
	itemon = false;
	modeon = false;
	return S_OK;
}

void Player::release()
{
}

void Player::update()
{
	
	motion();
	control();
	collsion();
	itemcollsion();

	_playerbullet->update();
	_item->update();
	if (_player->getCenterY() > WINSIZEY)
	{
		alphaon = true;
	}
	if (alphaon)
	{
		alphacount++;
	}
	if (alphacount % 2 == 0)
	{
		alpha = 255;
	}
	if (alphacount % 5 == 0)
	{
		alpha = 100;
	}
	if (alphacount > 300)
	{
		alphaon = false;
	}
	if (!alphaon)
	{
		alpha = 255;
		alphacount = 0;
	}
}

void Player::render()
{
	//Rectangle(getMemDC(), _rc);
	if (_playersd.ison)
	{
		_playersd.playerimage->alphaFrameRender(getMemDC(), _player->getX() - 95, _player->getY() - 90, _playersd.index, _playersd.indexY, 100);
	}
	_player->alphaFrameRender(getMemDC(), _player->getX(), _player->getY(), _indexX, _indexY,alpha);

	if (_playerpower >= 3 && _playerpower < 6)
	{
		if(!modeon)
		{ 
		_playerobject.playerimage->render(getMemDC(), _player->getCenterX() - 30, _player->getCenterY() + 20);
		}
		IMAGEMANAGER->findImage("ÆÄ¿öº°")->render(getMemDC(), 940, 345);
	}
	if (_playerpower >= 6 && _playerpower < 9)
	{
		if(!modeon)
		{ 
		_playerobject.playerimage->render(getMemDC(), _player->getCenterX() - 30, _player->getCenterY() + 20);
		_playerobject.playerimage->render(getMemDC(), _player->getCenterX() + 15, _player->getCenterY() + 20);
		}
		IMAGEMANAGER->findImage("ÆÄ¿öº°")->render(getMemDC(), 940, 345);
		IMAGEMANAGER->findImage("ÆÄ¿öº°")->render(getMemDC(), 980, 345);
	}
	if (_playerpower >= 9 && _playerpower < 12)
	{
		if (!modeon)
		{
			_playerobject.playerimage->render(getMemDC(), _player->getCenterX() - 45, _player->getCenterY());
			_playerobject.playerimage->render(getMemDC(), _player->getCenterX() - 30, _player->getCenterY() + 20);
			_playerobject.playerimage->render(getMemDC(), _player->getCenterX() + 15, _player->getCenterY() + 20);
		}
		IMAGEMANAGER->findImage("ÆÄ¿öº°")->render(getMemDC(), 940, 345);
		IMAGEMANAGER->findImage("ÆÄ¿öº°")->render(getMemDC(), 980, 345);
		IMAGEMANAGER->findImage("ÆÄ¿öº°")->render(getMemDC(), 1020, 345);

	}
	if (_playerpower >= 12)
	{
		if (!modeon)
		{
			_playerobject.playerimage->render(getMemDC(), _player->getCenterX() - 45, _player->getCenterY());
			_playerobject.playerimage->render(getMemDC(), _player->getCenterX() - 30, _player->getCenterY() + 20);
			_playerobject.playerimage->render(getMemDC(), _player->getCenterX() + 15, _player->getCenterY() + 20);
			_playerobject.playerimage->render(getMemDC(), _player->getCenterX() + 30, _player->getCenterY());
		}
		IMAGEMANAGER->findImage("ÆÄ¿öº°")->render(getMemDC(), 940, 345);
		IMAGEMANAGER->findImage("ÆÄ¿öº°")->render(getMemDC(), 980, 345);
		IMAGEMANAGER->findImage("ÆÄ¿öº°")->render(getMemDC(), 1020, 345);
		IMAGEMANAGER->findImage("ÆÄ¿öº°")->render(getMemDC(), 1060, 345);

	}
	if (modeon&&_playerpower>=12)
	{
		_playerobject.playerimage->render(getMemDC(), _player->getCenterX() - 45, _player->getCenterY()-10);
		_playerobject.playerimage->render(getMemDC(), _player->getCenterX() - 30, _player->getCenterY() - 20);
		_playerobject.playerimage->render(getMemDC(), _player->getCenterX() + 15, _player->getCenterY() - 20);
		_playerobject.playerimage->render(getMemDC(), _player->getCenterX() + 30, _player->getCenterY()-10);
	}
	if (_playersd._sdcount == 1)
	{
		IMAGEMANAGER->findImage("½¯µåº°")->render(getMemDC(), 920, 270);
	}
	if (_playersd._sdcount == 2)
	{
		IMAGEMANAGER->findImage("½¯µåº°")->render(getMemDC(), 920, 270);
		IMAGEMANAGER->findImage("½¯µåº°")->render(getMemDC(), 960, 270);
	}
	if (_playersd._sdcount == 3)
	{
		IMAGEMANAGER->findImage("½¯µåº°")->render(getMemDC(), 920, 270);
		IMAGEMANAGER->findImage("½¯µåº°")->render(getMemDC(), 960, 270);
		IMAGEMANAGER->findImage("½¯µåº°")->render(getMemDC(), 1000, 270);
	}
	if (_playersd._sdcount == 4)
	{
		IMAGEMANAGER->findImage("½¯µåº°")->render(getMemDC(), 920, 270);
		IMAGEMANAGER->findImage("½¯µåº°")->render(getMemDC(), 960, 270);
		IMAGEMANAGER->findImage("½¯µåº°")->render(getMemDC(), 1000, 270);
		IMAGEMANAGER->findImage("½¯µåº°")->render(getMemDC(), 1040, 270);
	}
	if (_playersd._sdcount == 5)
	{
		IMAGEMANAGER->findImage("½¯µåº°")->render(getMemDC(), 920, 270);
		IMAGEMANAGER->findImage("½¯µåº°")->render(getMemDC(), 960, 270);
		IMAGEMANAGER->findImage("½¯µåº°")->render(getMemDC(), 1000, 270);
		IMAGEMANAGER->findImage("½¯µåº°")->render(getMemDC(), 1040, 270);
		IMAGEMANAGER->findImage("½¯µåº°")->render(getMemDC(), 1080, 270);
	}
	_playerbullet->render();
	_item->render();
	EFFECTMANAGER->render();
	
	if (_playerlife == 1)
	{

		IMAGEMANAGER->findImage("½¯µåº°")->render(getMemDC(), 920, 210);

	}
	if (_playerlife == 2)
	{

		IMAGEMANAGER->findImage("½¯µåº°")->render(getMemDC(), 920, 210);
		IMAGEMANAGER->findImage("½¯µåº°")->render(getMemDC(), 960, 210);

	}
	if (_playerlife == 3)
	{

		IMAGEMANAGER->findImage("½¯µåº°")->render(getMemDC(), 920, 210);
		IMAGEMANAGER->findImage("½¯µåº°")->render(getMemDC(), 960, 210);
		IMAGEMANAGER->findImage("½¯µåº°")->render(getMemDC(), 1000, 210);

	}
	if (_playerlife == 4)
	{

		IMAGEMANAGER->findImage("½¯µåº°")->render(getMemDC(), 920, 210);
		IMAGEMANAGER->findImage("½¯µåº°")->render(getMemDC(), 960, 210);
		IMAGEMANAGER->findImage("½¯µåº°")->render(getMemDC(), 1000, 210);
		IMAGEMANAGER->findImage("½¯µåº°")->render(getMemDC(), 1040, 210);
	}
}

void Player::control()
{
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		itemon = true;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _player->getX() > 0)
	{
		_player->setX(_player->getX() - 5);
		_playermotion = PLAYER_LEFT_MOVE;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_playermotion = PLAYER_IDLE;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _player->getX() < 770)
	{
		_player->setX(_player->getX() + 5);
		_playermotion = PLAYER_RIGHT_MOVE;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_playermotion = PLAYER_IDLE;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _player->getY() > 0)
	{
		_player->setY(_player->getY() - 5);

	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _player->getY() < WINSIZEY - 50)
	{
		_player->setY(_player->getY() + 5);

	}
	if (_player->getCenterY() > WINSIZEY-50)
	{
		countt++;
		if(countt<200)
		{ 
			_player->setY(_player->getY() -5);
			countt = 0;
		}
	}
	count++;
	if (KEYMANAGER->isStayKeyDown(VK_SPACE) && count % 7 == 0)
	{
		playerskill(SKILL1);

	}

	if (KEYMANAGER->isStayKeyDown('C') && count % 5 == 0&&_playerpower>=12)
	{
		playerskill(SKILL2);
		modeon = true;
	}
	if (KEYMANAGER->isOnceKeyUp('C'))
	{
		modeon = false;
	}
	if (KEYMANAGER->isOnceKeyDown('X') && _playersd._sdcount > 0 && !_playersd.ison)
	{
		_playersd.ison = true;
		_playersd._sdcount -= 1;

	}
	if (_playersd.ison)
	{
		_playersd._count++;
	}
	if (_playersd._count > 200)
	{
		_playersd.ison = false;
		_playersd._count = 0;
	}
	if (_playersd.ison)
	{
		if (count % 10 == 0)
		{
			if (_playersd.index > 7)_playersd.index = 0;
			_playersd.playerimage->setFrameX(_playersd.index);
			_playersd.playerimage->setFrameY(_playersd.indexY);
			_playersd.index++;
		}
	}
	_rc = RectMakeCenter(_player->getCenterX(), _player->getCenterY(), 90, 100);
	motion();


}

void Player::collsion()
{
	for (int i = 0; i < _playerbullet->getVBullet().size(); i++)
	{
		for (int j = 0; j < _em->getVEnemy().size(); j++)
		{
			RECT temp;
			if (IntersectRect(&temp, &_playerbullet->getVBullet()[i].rc, &_em->getVEnemy()[j]->getRect()))
			{
				_playerbullet->removeplayerbullet(i);
				_em->getVEnemy()[j]->moveHP(30);
				if (_playerpower > 20)
				{
					_em->getVEnemy()[j]->moveHP(50);
				}
				if (_em->getVEnemy()[j]->getHP() <= 0)
				{

					EFFECTMANAGER->play("ÀÌÆåÆ®", (_em->getVEnemy()[j]->getRect().left + _em->getVEnemy()[j]->getRect().right) / 2, (_em->getVEnemy()[j]->getRect().top + _em->getVEnemy()[j]->getRect().bottom) / 2);


					_item->fire((_em->getVEnemy()[j]->getRect().left + _em->getVEnemy()[j]->getRect().right) / 2,
						(_em->getVEnemy()[j]->getRect().top + _em->getVEnemy()[j]->getRect().bottom) / 2);
					
					_em->removeEnemy(j);

				}
				break;
			}
		}
	}
	


	//for (int j = 0; j < _em->getVEnemy().size(); j++)
	//{
	//	if (_em->getVEnemy()[j]->getRect().left<0 || _em->getVEnemy()[j]->getRect().right>800)
	//	{
	//		_em->removeEnemy(j);
	//		break;
	//	}
	//}
}

void Player::motion()
{
	count++;
	if (count % 10 == 0)
	{
		switch (_playermotion)
		{
		case PLAYER_IDLE:
			if (_indexX >= 3)_indexX = 0;
			_indexY = 0;
			_player->setFrameX(_indexX);
			_player->setFrameY(_indexY);
			_indexX++;
			break;
		case PLAYER_LEFT_MOVE:
			if (_indexX <= 3)_indexX = 4;

			_indexY = 0;
			_player->setFrameX(_indexX);
			_player->setFrameY(_indexY);
			if (_indexX > 3 && _indexX < 10)
			{
				_indexX++;
			}
			else {
				_indexX = 10;
			}

			break;
		case PLAYER_RIGHT_MOVE:
			if (_indexX >= 7)_indexX = 6;
			_indexY = 1;
			_player->setFrameX(_indexX);
			_player->setFrameY(_indexY);
			if (_indexX >= 1)
			{
				_indexX--;
			}
			else
			{
				_indexX = 0;
			}

			break;
		}
		count = 0;
	}

}

void Player::playerskill(PLAYERBULLET playerskill)
{
	_playerskill = playerskill;
	switch (_playerskill)
	{
	case SKILL1:
		if (_playerpower >= 0 && _playerpower < 3)
		{
			_playerbullet->fire(_player->getCenterX() - 13, _player->getY() - 20, PI / 2);
			_playerbullet->fire(_player->getCenterX() + 13, _player->getY() - 20, PI / 2);
		}
		if (_playerpower >= 3 && _playerpower < 6)
		{
			_playerbullet->fire(_player->getCenterX() - 13, _player->getY() - 20, PI / 2);
			_playerbullet->fire(_player->getCenterX() + 13, _player->getY() - 20, PI / 2);
			_playerbullet->fire(_player->getCenterX() - 35, _player->getY() - 10, PI / 2);
			_playerbullet->fire(_player->getCenterX() + 35, _player->getY() - 10, PI / 2);
		}
		if (_playerpower >= 6 && _playerpower < 9)
		{
			_playerbullet->fire(_player->getCenterX() - 13, _player->getY() - 20, PI / 2);
			_playerbullet->fire(_player->getCenterX() + 13, _player->getY() - 20, PI / 2);
			_playerbullet->fire(_player->getCenterX() - 35, _player->getY() - 10, PI / 2);
			_playerbullet->fire(_player->getCenterX() + 35, _player->getY() - 10, PI / 2);
			_playerbullet->fire(_player->getCenterX() - 35, _player->getY() - 10, PI / 2 + 0.2);
			_playerbullet->fire(_player->getCenterX() + 35, _player->getY() - 10, PI / 2 - 0.2);
		}
		if (_playerpower >= 9)
		{
			_playerbullet->fire(_player->getCenterX() - 13, _player->getY() - 20, PI / 2);
			_playerbullet->fire(_player->getCenterX() + 13, _player->getY() - 20, PI / 2);
			_playerbullet->fire(_player->getCenterX() - 35, _player->getY() - 10, PI / 2);
			_playerbullet->fire(_player->getCenterX() + 35, _player->getY() - 10, PI / 2);
			_playerbullet->fire(_player->getCenterX() - 35, _player->getY() - 10, PI / 2 + 0.2);
			_playerbullet->fire(_player->getCenterX() + 35, _player->getY() - 10, PI / 2 - 0.2);
			_playerbullet->fire(_player->getCenterX() - 35, _player->getY() - 10, PI / 2 + 0.4);
			_playerbullet->fire(_player->getCenterX() + 35, _player->getY() - 10, PI / 2 - 0.4);
		}
		break;
	case SKILL2:
		_playerbullet->fire(_player->getCenterX() - 13, _player->getY() - 20, PI / 2);
		_playerbullet->fire(_player->getCenterX() + 13, _player->getY() - 20, PI / 2);
		_playerbullet->fire(_player->getCenterX() - 35, _player->getY() - 10, PI / 2);
		_playerbullet->fire(_player->getCenterX() + 35, _player->getY() - 10, PI / 2);
		break;
	}
}

void Player::itemcollsion()
{
	for (int i = 0; i < _item->getVItem().size(); i++)
	{

		RECT temp;
		if (IntersectRect(&temp, &_rc, &_item->getVItem()[i].rc))
		{
			if (_item->getVItem()[i].item == POWER_ITEM)
			{
				_playerpower += 1;
			}
			if (_item->getVItem()[i].item == SHIELD_ITEM)
			{
				_playersd._sdcount += 1;
				if (_playersd._sdcount >= 5)
				{
					_playersd._sdcount = 5;
				}
			}
			_item->removeitem(i);
			break;
		}
	}
}

void Player::playerLife(int Num)
{
	_playerlife -= Num;
}
