#pragma once
#include "gameNode.h"
#include"inGame.h"
#include"Menu.h"




class playGround : public gameNode
{
private:
	Menu* _mn;
	inGame* _gm;

public:
	playGround();
	~playGround();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

};

