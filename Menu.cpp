#include "stdafx.h"
#include "Menu.h"

HRESULT Menu::init()
{
    IMAGEMANAGER->addImage("메뉴", "메뉴.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
    IMAGEMANAGER->addImage("시작", "시작1.bmp", 200, 100, true, RGB(255, 0, 255));
    IMAGEMANAGER->addImage("나가기", "나가기.bmp", 150, 100, true, RGB(255, 0, 255));
    IMAGEMANAGER->addImage("시작2", "시작2.bmp", 200, 100, true, RGB(255, 0, 255));
    IMAGEMANAGER->addImage("나가기2", "나가기2.bmp", 150, 100, true, RGB(255, 0, 255));

    _rc = RectMakeCenter(WINSIZEX / 3, WINSIZEY - 150, 200, 100);
    _x = (_rc.left + _rc.right) / 2;
    _y - (_rc.bottom + _rc.top) / 2;
    return S_OK;
}

void Menu::release()
{
}

void Menu::update()
{
    if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
    {
        _rc = RectMakeCenter(WINSIZEX / 2 + 175, WINSIZEY - 150, 150, 100);
    }
    if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
    {
        _rc = RectMakeCenter(WINSIZEX / 3, WINSIZEY - 150, 200, 100);
    }
   if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _x < WINSIZEX / 2)
   {
       SCENEMANAGER->changeScene("인게임");
   }
    _x = (_rc.left + _rc.right) / 2;
}

void Menu::render()
{
    IMAGEMANAGER->findImage("메뉴")->render(getMemDC());
    if (_x > WINSIZEX / 2)
    {
        IMAGEMANAGER->findImage("시작")->render(getMemDC(), WINSIZEX / 3 - 100, WINSIZEY - 200);
        IMAGEMANAGER->findImage("나가기2")->render(getMemDC(), WINSIZEX / 2 + 100, WINSIZEY - 200);
    }
    else
    {
        IMAGEMANAGER->findImage("나가기")->render(getMemDC(), WINSIZEX / 2 + 100, WINSIZEY - 200);
        IMAGEMANAGER->findImage("시작2")->render(getMemDC(), WINSIZEX / 3 - 100, WINSIZEY - 200);
    }



    //Rectangle(getMemDC(), _rc);
}
