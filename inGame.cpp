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

	IMAGEMANAGER->findImage("배경")->loopRender(getMemDC(), &RectMake(0, 0, 800, WINSIZEY), loopx, loopy);
	//IMAGEMANAGER->findImage("안개")->loopRender(getMemDC(), & RectMake(0, 0, WINSIZEX, WINSIZEY), loopx, loopy);
	IMAGEMANAGER->findImage("안개")->alphaRender(getMemDC(), 50);

	IMAGEMANAGER->findImage("보스전")->alphaRender(getMemDC(), _alpha);
	if (_em->getstate() == STAGE_5)
	{
		IMAGEMANAGER->findImage("보스이미지")->alphaRender(getMemDC(), 500, 200, _alpha2);
	}
	
	IMAGEMANAGER->findImage("점수판")->render(getMemDC(), WINSIZEX - 400, 0);
	_em->render();
	_py->render();
	if (_py->getHP() < 0)
	{
		IMAGEMANAGER->findImage("게임오버")->render(getMemDC());
	}
	if (isPause)
	{
		IMAGEMANAGER->findImage("퍼즈")->alphaRender(getMemDC(), 150);
		IMAGEMANAGER->findImage("퍼즈1")->render(getMemDC(), WINSIZEX / 3 + 20, WINSIZEY / 4);
		
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
	IMAGEMANAGER->addImage("배경", "준포폴 배경.bmp", 800, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("안개", "안개.bmp", 800, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("점수판", "점수판.bmp", 400, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보스전", "보스배경.bmp", 800, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보스이미지", "보스이미지.bmp", 300, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("minion1", "몬스터1.bmp", 0, 0, 368, 54, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("minion2", "몬스터2.bmp", 0, 0, 368, 54, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("minion3", "몬스터3.bmp", 0, 0, 368, 54, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("minion4", "몬스터4.bmp", 0, 0, 368, 54, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BOSS", "보스움직임.bmp", 0, 0, 440, 77, 8, 1, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("적폭발", "이펙트.bmp", 1600, 60, true, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("이펙트", "이펙트.bmp", 1600, 60, 50, 60, 1.0f, 1.0f, 500);
	IMAGEMANAGER->addImage("파워별", "파워별.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("쉴드별", "쉴드별.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("파워", "아이템 파워.bmp", 15, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("쉴드", "아이템 쉴드.bmp", 15, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("점수", "아이템 점수.bmp", 15, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("퍼즈", "퍼즈배경.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("퍼즈1", "퍼즈.bmp", 100, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("퍼즈나가기1", "퍼즈나가기1.bmp", 80, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("퍼즈나가기2", "퍼즈나가기2.bmp", 80, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("다시시작1", "다시시작1.bmp", 120, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("다시시작2", "다시시작2.bmp", 120, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("게임오버", "게임오버.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
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


