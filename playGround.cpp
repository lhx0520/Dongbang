#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);


	_mn = new Menu;
	_mn->init();
	
	_gm = new inGame;
	_gm->init();


	SCENEMANAGER->addScene("매인메뉴", new Menu);
	SCENEMANAGER->addScene("인게임", new inGame);


	SCENEMANAGER->changeScene("매인메뉴");
	return S_OK;
}


void playGround::release()
{
	gameNode::release();


	SCENEMANAGER->release();
}

void playGround::update()
{


	gameNode::update();
	
	
	
	
	SCENEMANAGER->update();

	EFFECTMANAGER->update();
	
	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================


	SCENEMANAGER->render();
	//TIMEMANAGER->render(getMemDC());
	//================= 아래도 건들지 마라 ==============================
	_backBuffer->render(getHDC());
}

