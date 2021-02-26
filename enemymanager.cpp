#include "stdafx.h"
#include "enemymanager.h"
#include "Player.h"

HRESULT enemymanager::init()
{
	_minionbullet = new minionbullet;
	_minionbullet->init("minionbullet", 1000, WINSIZEY);
	_bossbullet = new bossBullet;
	_bossbullet->init(100);
	_state = STATE::STAGE_1;
	angle = -PI / 2;
	angle2 = PI / 2;
	angle3 = -PI / 2;
	angle4 = 0;
	countttt = 0;
	_X = _Y = 0;
	ison = false;

	return S_OK;
}

void enemymanager::release()
{
}

void enemymanager::update()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); _viEnemy++)
	{
		(*_viEnemy)->update();

	}
	collsion();
	EnemyBullatFire();
	_minionbullet->update();
	_bossbullet->update();
	stageClear();
	remove();


}

void enemymanager::render()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); _viEnemy++)
	{
		(*_viEnemy)->render();
	}
	_minionbullet->render();
	_bossbullet->render();


	
}

void enemymanager::setEnemy()
{

	if (_state == STAGE_1)
	{
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				enemy* minion1;
				minion1 = new minion;
				minion1->init("minion1", PointMake(150 + j * 500, -20 + i * -50), _state, 100, PI * 2 - PI / 2);
				_vEnemy.push_back(minion1);

			}
		}

	}

	if (_state == STAGE_2)
	{
		for (int i = 0; i < 3; i++)
		{
			enemy* minion1;
			minion1 = new minion;
			minion1->init("minion2", PointMake(150 + i * 250, -50), _state, 100, 0);
			_vEnemy.push_back(minion1);
		}
	}

	if (_state == STAGE_3)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				enemy* minion1;
				minion1 = new minion;
				minion1->init("minion3", PointMake(300 + i * 200, -50 + j * -50), _state, 100, 0);
				_vEnemy.push_back(minion1);
			}
		}
	}
	if (_state == STAGE_4)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				enemy* minion1;
				minion1 = new minion;
				minion1->init("minion4", PointMake(-400 + j * 50, 50 + i * 50), _state, 2000, PI, _bossmv);
				_vEnemy.push_back(minion1);
			}
		}
	}

	if (_state == STAGE_BOSS)
	{
		enemy* BOSS;
		BOSS = new boss;
		BOSS->init("BOSS", PointMake(800 / 2, -50), _state, 10000, PI * 2 - PI / 2, _bossmv);
		_vEnemy.push_back(BOSS);
	}

}

void enemymanager::EnemyBullatFire()
{
	count++;
	countt++;
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		if (_state == STAGE_1)
		{
			if ((*_viEnemy)->bulletFire())
			{
				for (int i = 0; i < 6; i++)
				{
					RECT rc = (*_viEnemy)->getRect();

					_minionbullet->fire((rc.right + rc.left) / 2, rc.bottom + 5,
						getAngle((rc.right + rc.left) / 2, rc.bottom + 5,
							_player->getPlayeimage()->getCenterX(),
							_player->getPlayeimage()->getY()), 4.0f + (i * 0.5f), _state);
				}
			}
		}
		if (_state == STAGE_2)
		{


			RECT rc = (*_viEnemy)->getRect();
			if ((*_viEnemy)->getRect().left < 800 / 2 && (*_viEnemy)->getRect().right>800 / 2)
			{
				if (countt % 2 == 0)
				{
					angle += 0.1f;
					//RECT rc = (*_viEnemy)->getRect();
					_minionbullet->fire2((rc.right + rc.left) / 2, rc.bottom + 5,
						angle, 6.0f, _state);
					countt = 0;
				}
			}
			else
			{
				if (count % 50 == 0)
				{
					for (int i = 0; i < 44; i++)
					{
						//RECT rc = (*_viEnemy)->getRect();

						_minionbullet->fire((rc.right + rc.left) / 2, rc.bottom + 5,
							(PI / 2) + i, 4.0f, _state);
						count = 0;
					}
				}
			}
		}
		if (_state == STAGE_3)
		{
			if (count % 100 == 0)
			{
				RECT rc = (*_viEnemy)->getRect();
				for (int i = 0; i < 8; i++)
				{
					_minionbullet->fire((rc.right + rc.left) / 2, rc.bottom + 5,
						getAngle((rc.right + rc.left) / 2, rc.bottom + 5,
							_player->getPlayeimage()->getCenterX(), _player->getPlayeimage()->getY()) - 0.3 + (i * 0.1), 4.0f, _state);
				}
			}
		}
		if (_state == STAGE_4)
		{
			if (count % 400 == 0)
			{
				RECT rc = (*_viEnemy)->getRect();
				for (int i = 0; i < 14; i++)
				{
					_minionbullet->fire((rc.right + rc.left) / 2, rc.bottom + 5,
						getAngle((rc.right + rc.left) / 2, rc.bottom + 5,
							_player->getPlayeimage()->getCenterX(), _player->getPlayeimage()->getY()) - 1 + (i * 0.145f), 4.0f, _state);
				}
			}
		}
		if (_state == STAGE_BOSS && (*_viEnemy)->getindex() < 4 && (*_viEnemy)->getHP() > 5000)
		{
			counttt++;
			if (counttt % 20 == 0)
			{
				RECT rc = (*_viEnemy)->getRect();
				for (int i = 0; i < 44; i++)
				{
					_minionbullet->fire((rc.right + rc.left) / 2, rc.bottom + 5,
						(PI / 2) + i, 5.0f, _state);


				}
				//for (int i = 0; i < 44; i++)
				//{
				//	_minionbullet->fire2((rc.right + rc.left) / 2, rc.bottom + 5,
				//		(PI / 2) + i - 0.1, 5.0f, _state);
				//}
				//for(int i = 0;i<3;i++)
				//{ 
				//	_minionbullet->bossfire2((rc.right + rc.left) / 2, rc.bottom + 5,
				//		getAngle((rc.right + rc.left) / 2, rc.bottom + 5,
				//			_player->getPlayeimage()->getCenterX(), _player->getPlayeimage()->getY()) -0.4 + (i*0.4), 8, _state);
				//}
			}
			if (counttt % 30 == 0)
			{
				RECT rc = (*_viEnemy)->getRect();
				for (int i = 0; i < 44; i++)
				{
					_minionbullet->fire2((rc.right + rc.left) / 2, rc.bottom + 5,
						(PI / 2) + i - 0.2f, 5.0f, _state);
					counttt = 10;
				}
			}
			if (counttt % 10 == 0)
			{
				for (int i = 0; i < 3; i++)
				{
					RECT rc = (*_viEnemy)->getRect();
					_minionbullet->bossfire2((rc.right + rc.left) / 2, rc.bottom + 5,
						getAngle((rc.right + rc.left) / 2, rc.bottom + 5,
							_player->getPlayeimage()->getCenterX(), _player->getPlayeimage()->getY()) - 0.4 + (i * 0.4), 5, _state);
				}
			}
		}
		if (_state == STAGE_BOSS && (*_viEnemy)->getHP() <= 5000 && (*_viEnemy)->getHP() > 2000)
		{


			countttt++;
			counttttt++;
			if (countttt < 50)
			{
				angle += 1;
			}
			if (countttt > 50)
			{
				angle -= 1;
			}
			if (countttt > 100)
			{
				countttt = 0;
			}

			angle3--;
			_Y = WINSIZEY / 2;


			_minionbullet->fire2(800 / 2 + 50, WINSIZEY / 2, angle, 2.6f, _state);
			_minionbullet->fire(800 / 2 + 50, WINSIZEY / 2, angle - 0.5f, 2.6f, _state);
			//_minionbullet->bossfire2(800 / 2 + 50, WINSIZEY / 2, angle2--, 3, _state);
			//_minionbullet->fire(800 / 2 + 50, WINSIZEY / 2, angle3, 5, _state);
			//_minionbullet->fire(800 / 2 + 50, WINSIZEY / 2, angle3, 5, _state);

			if (counttttt == 400 || counttttt == 440)
			{
				for (int i = 0; i < 44; i++)
				{


					_minionbullet->bossfire3(800 / 4, WINSIZEY / 2,
						(PI / 2) + i, 4.0f, _state);

				}
			}
			if (counttttt == 500 || counttttt == 540)
			{
				for (int i = 0; i < 44; i++)
				{


					_minionbullet->bossfire3(800 / 2 + 800 / 3, WINSIZEY / 2,
						(PI / 2) + i, 4.0f, _state);

				}

			}
			if (counttttt > 550)
			{
				counttttt = 0;
			}




		}
		if (_state == STAGE_BOSS && (*_viEnemy)->getHP() <= 2000)
		{
			RECT rc = (*_viEnemy)->getRect();

			if (_bossbullet->getbulletmove() == 0)
			{



				_bossbullet->fire3((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2, RND->getFromFloatTo(PI + PI / 4, PI * 2), 5, _state);
			}
			if (count % 5 == 0 && _bossbullet->getbulletmove() == 1)
			{
				for (int i = 0; i < 3; i++)
				{
					RECT rc = (*_viEnemy)->getRect();
					_minionbullet->bossfire2((rc.right + rc.left) / 2, rc.bottom + 5,
						getAngle((rc.right + rc.left) / 2, rc.bottom + 5,
							_player->getPlayeimage()->getCenterX(), _player->getPlayeimage()->getY()) - 0.25f + (i * 0.25f), 9, _state);
				}
			}
			if (count == 400 || count == 440)
			{
				for (int i = 0; i < 44; i++)
				{


					_minionbullet->bossfire3(800 / 4, WINSIZEY / 2,
						(PI / 2) + i, 2.0f, _state);

				}
			}
			if (count == 500 || count == 540)
			{
				for (int i = 0; i < 44; i++)
				{


					_minionbullet->bossfire3(800 / 2 + 800 / 3, WINSIZEY / 2,
						(PI / 2) + i, 2.0f, _state);

				}

			}
			if (count > 550)
			{
				count = 0;
			}




			if (count % 4 == 0 && _bossbullet->getbulletmove() != 0)
			{
				_minionbullet->fire(800 - 20, 300, PI, 7, _state);						//1
				_minionbullet->fire(20, 300, -PI / 2 + 0.92, 7, _state);						//2
				_minionbullet->fire(800 - 20, WINSIZEY - 20, PI / 2 + 0.4, 7, _state);	//3
				_minionbullet->fire(800 / 2, 20, -PI / 2 - 0.43, 7, _state);			//4
				_minionbullet->fire(20, WINSIZEY - 20, PI / 2 - 0.92, 7, _state);				//5

			}


		}
	}

}

void enemymanager::removeEnemy(int arrNum)
{
	SAFE_DELETE(_vEnemy[arrNum]);
	_vEnemy.erase(_vEnemy.begin() + arrNum);
}

void enemymanager::collsion()
{
	if(!ison)
	{ 
		for (int i = 0; i < _minionbullet->getVBullet().size(); i++)
		{
			RECT temp;
			
			
			if(_player->getHP() <=4 &&_player->getHP() >= 0)
			{ 
				if (IntersectRect(&temp, &_minionbullet->getVBullet()[i].rc,
					&RectMakeCenter(_player->getPlayeimage()->getCenterX(),
						_player->getPlayeimage()->getCenterY(),
						5,
						5)))
				{
					
					
					_minionbullet->remveBullet(i);
					_player->playerLife(1);
					_player->getPlayeimage()->setCenter(WINSIZEX / 2, WINSIZEY + 100);
					lifecount = 0;
					ison = true;
					break;
				}
			}
			
		}
	}
	if (ison)
	{
		lifecount++;
	}
	if (lifecount > 200)
	{
		ison = false;
	}




	for (int i = 0; i < _minionbullet->getVBullet().size(); i++)
	{
		if (_player->getPlayerSD().ison)
		{
			RECT temp;
			if (IntersectRect(&temp, &_minionbullet->getVBullet()[i].rc,
				&RectMakeCenter(_player->getPlayeimage()->getCenterX(),
					_player->getPlayeimage()->getCenterY(),
					200, 200)))
			{
				_minionbullet->remveBullet(i);
				break;

			}
		}

	}
}

void enemymanager::stageClear()
{
	switch (_state)
	{
	case STAGE_1:
		_state = STAGE_1;
		if (_vEnemy.empty())
		{
			_state = STAGE_2;
			setEnemy();
		}
		break;
	case STAGE_2:
		_state = STAGE_2;

		if (_vEnemy.empty())
		{
			_state = STAGE_3;
			setEnemy();
		}
		break;
	case STAGE_3:
		_state = STAGE_3;

		if (_vEnemy.empty())
		{
			_state = STAGE_4;
			setEnemy();
		}
		break;
	case STAGE_4:
		_state = STAGE_4;
		if (_vEnemy.empty())
		{
			_state = STAGE_5;

		}
		break;
	case STAGE_5:
		_state = STAGE_5;
		counttttt++;
		if (counttttt > 600)
		{
			_state = STAGE_BOSS;
			setEnemy();
		}
		break;
	case STAGE_BOSS:
		_state = STAGE_BOSS;
		break;
	}





}

void enemymanager::remove()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end();)
	{
		if ((*_viEnemy)->getRect().left<0 && (*_viEnemy)->getRect().bottom>WINSIZEY / 2 || (*_viEnemy)->getRect().right > 800 && (*_viEnemy)->getRect().bottom > WINSIZEY / 2)
		{
			_viEnemy = _vEnemy.erase(_viEnemy);
		}
		else ++_viEnemy;

	}
}



