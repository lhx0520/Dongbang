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


	SCENEMANAGER->addScene("���θ޴�", new Menu);
	SCENEMANAGER->addScene("�ΰ���", new inGame);


	SCENEMANAGER->changeScene("���θ޴�");
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
	//================ ���� �ǵ��� ���� ==============================


	SCENEMANAGER->render();
	//TIMEMANAGER->render(getMemDC());
	//================= �Ʒ��� �ǵ��� ���� ==============================
	_backBuffer->render(getHDC());
}

