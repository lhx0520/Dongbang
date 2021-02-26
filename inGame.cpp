#include "stdafx.h"
#include "inGame.h"

HRESULT inGame::init()
{

	setimage();
	loopx = loopy = 0;

	_py = new Player;
	_py->init();

	_em = new enemymanager;
	_em->init();
	_em->setEnemy();

	_py->setEnemyMemoryaddressLink(_em);
	_em->setPlayerMemortAddressLink(_py);
	_alpha = 0;
	_alpha2 = 0;
	
	_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 3, 50, 50);

	return S_OK;
}

void inGame::release()
{
	SAFE_DELETE(_py);
	SAFE_DELETE(_em);
}

void inGame::update()
{
	backgroundloop();
	callpause();
}

void inGame::render()
{

	IMAGEMANAGER->findImage("���")->loopRender(getMemDC(), &RectMake(0, 0, 800, WINSIZEY), loopx, loopy);
	//IMAGEMANAGER->findImage("�Ȱ�")->loopRender(getMemDC(), & RectMake(0, 0, WINSIZEX, WINSIZEY), loopx, loopy);
	IMAGEMANAGER->findImage("�Ȱ�")->alphaRender(getMemDC(), 50);

	IMAGEMANAGER->findImage("������")->alphaRender(getMemDC(), _alpha);
	if (_em->getstate() == STAGE_5)
	{
		IMAGEMANAGER->findImage("�����̹���")->alphaRender(getMemDC(), 500, 200, _alpha2);
	}
	
	IMAGEMANAGER->findImage("������")->render(getMemDC(), WINSIZEX - 400, 0);
	_em->render();
	_py->render();
	if (_py->getHP() < 0)
	{
		IMAGEMANAGER->findImage("���ӿ���")->render(getMemDC());
	}
	if (isPause)
	{
		IMAGEMANAGER->findImage("����")->alphaRender(getMemDC(), 150);
		IMAGEMANAGER->findImage("����1")->render(getMemDC(), WINSIZEX / 3 + 20, WINSIZEY / 4);
		
	}
	//Rectangle(getMemDC(), _rc);
}

void inGame::backgroundloop()
{
	if (!isPause)
	{
		loopy -= 2;
		if (_em->getstate() == STAGE_BOSS)
		{
			_alpha += 1;
			if (_alpha >= 255)
			{
				_alpha = 255;
			}
		}
		if (_em->getstate() == STAGE_5)
		{
			_alpha2 += 1;
			if (_alpha2 >= 150)
			{
				_alpha2 = 150;
			}
		}
	}
}

void inGame::setimage()
{
	IMAGEMANAGER->addImage("���", "������ ���.bmp", 800, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ȱ�", "�Ȱ�.bmp", 800, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "������.bmp", 400, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "�������.bmp", 800, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����̹���", "�����̹���.bmp", 300, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("minion1", "����1.bmp", 0, 0, 368, 54, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("minion2", "����2.bmp", 0, 0, 368, 54, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("minion3", "����3.bmp", 0, 0, 368, 54, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("minion4", "����4.bmp", 0, 0, 368, 54, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BOSS", "����������.bmp", 0, 0, 440, 77, 8, 1, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("������", "����Ʈ.bmp", 1600, 60, true, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("����Ʈ", "����Ʈ.bmp", 1600, 60, 50, 60, 1.0f, 1.0f, 500);
	IMAGEMANAGER->addImage("�Ŀ���", "�Ŀ���.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���庰", "���庰.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ŀ�", "������ �Ŀ�.bmp", 15, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "������ ����.bmp", 15, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "������ ����.bmp", 15, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "������.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����1", "����.bmp", 100, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�������1", "�������1.bmp", 80, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�������2", "�������2.bmp", 80, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ٽý���1", "�ٽý���1.bmp", 120, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ٽý���2", "�ٽý���2.bmp", 120, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ӿ���", "���ӿ���.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
}

void inGame::callpause()
{
	if (KEYMANAGER->isOnceKeyDown('M'))
	{
		isPause = true;
	}
	
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN) && isPause)
	{
		_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 3 + 500, 50, 50);
		

	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP) && isPause)
	{
		_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 3, 50, 50);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _rc.bottom < WINSIZEY / 2)
	{
		isPause = false;
		
	}
	if (!isPause)
	{

		_em->update();
		_py->update();
	}
	
}


