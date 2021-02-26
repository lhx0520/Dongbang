#include "stdafx.h"
#include "enemy.h"



HRESULT enemy::init(const char* imageName, POINT position, STATE state, int HP, float angle)
{

    _indexX = _indexY = 0;
    _BindexX = _BindexY = 0;
    _count = _fireCount = 0;
    _rndFireCount = RND->getFromIntTo(1, 800);
    _imageName = IMAGEMANAGER->findImage(imageName);
    _rc = RectMakeCenter(position.x, position.y,
        _imageName->getFrameWidth(),
        _imageName->getFrameHeight());
    _X = (_rc.left + _rc.right) / 2;
    _Y = (_rc.top + _rc.bottom) / 2;
    _angle = angle;
    _state = state;
    _speed = 2;
    _HP = HP;
    ison = false;
    isan = false;
    _countt = 0;
    _counttt = 0;


    return S_OK;
}

HRESULT enemy::init(const char* imageName, POINT position, STATE state, int HP, float angle, BOSSMOVE bossmv)
{
    _indexX = _indexY = 0;
    _BindexX = _BindexY = 0;
    _count = _fireCount = 0;
    _rndFireCount = RND->getFromIntTo(1, 800);
    _imageName = IMAGEMANAGER->findImage(imageName);
    _rc = RectMakeCenter(position.x, position.y,
        _imageName->getFrameWidth(),
        _imageName->getFrameHeight());
    _X = (_rc.left + _rc.right) / 2;
    _Y = (_rc.top + _rc.bottom) / 2;
    _angle = angle;
    _state = state;
    _speed = 2;
    _HP = HP;
    ison = false;
    isan = false;
    _countt = 0;
    _counttt = 0;
    _bossmv = bossmv;
    return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
    _count++;
    move();
    if (_count % 10 == 0 && _state != STAGE_BOSS)
    {
        if (_indexX >= _imageName->getMaxFrameX())_indexX = 0;

        _imageName->setFrameX(_indexX);
        _imageName->setFrameY(_indexY);
        _indexX++;
        _count = 0;
    }
    bossmove();

}

void enemy::render()
{
    draw();


}

void enemy::move()
{
    switch (_state)
    {
    case STAGE_1:
        // _countt++;
        // OffsetRect(&_rc, 0, 3);
        //xymove(0, 3);
        //if (_rc.bottom >= 320 && _rc.left < 800 / 2)
        //{
        //    //OffsetRect(&_rc, -2, 1);
        //    xymove(-2, 1);
        //}
        //if (_rc.bottom >= 320 && _rc.left > 800 / 2)
        //{
        //    //OffsetRect(&_rc, 2, 1);
        //    xymove(2, 1);
        //}
        _X += cosf(_angle) * _speed;
        _Y += -sinf(_angle) * _speed;

        if (_rc.bottom >= 300 && _rc.right < 800 / 2 && !ison)
        {
            isan = true;
        }
        if (isan)
        {

            _angle += 0.01f;
        }
        if (_rc.bottom >= 300 && _rc.left > 800 / 2 && !isan)
        {
            ison = true;
        }
        if (ison)
        {

            _angle -= 0.01f;
        }
        _rc = RectMakeCenter(_X, _Y, _imageName->getFrameWidth(),
            _imageName->getFrameHeight());
        break;
    case STAGE_2:
        if (!ison)
        {
            //OffsetRect(&_rc, 0, 1);
            xymove(0, 1);
        }
        if (_rc.bottom >= 300)
        {
            ison = true;
        }
        if (ison);
        {
            //OffsetRect(&_rc, 0, 0);
            xymove(0, -0.1);
        }
        break;
    case STAGE_3:
        xymove(0, 1);
        if (_rc.bottom >= 320 && _rc.left < 800 / 2)
        {
            //OffsetRect(&_rc, -2, 1);
            xymove(-0.5, 0);
        }
        if (_rc.bottom >= 320 && _rc.left > 800 / 2)
        {
            //OffsetRect(&_rc, 2, 1);
            xymove(0.5f, 0);
        }
        break;
    case STAGE_4:
        _speed = 2;
        if (_rc.left >800 / 2 - 10)
        {
            ison = true;
        }
        if (ison)
        {
            _angle += 0.03f;
        }
        _X -= cosf(_angle) * _speed;
        _Y += -sinf(_angle) * _speed;


        _rc = RectMakeCenter(_X, _Y, _imageName->getFrameWidth(),
            _imageName->getFrameHeight());
        break;

    case STAGE_BOSS:
        _countt++;
        if (_countt < 50)
        {
            _bossmv = BOSS_DOWN_MOVE;

        }
        if (_countt > 50 && _countt < 100)
        {
            _bossmv = BOSS_IDLE;

        }
        if (_countt > 100 && _countt < 150)
        {
            _bossmv = BOSS_LEFT_MOVE;

        }
        if (_countt > 150 && _countt < 200)
        {
            _bossmv = BOSS_IDLE;

        }
        if (_countt > 200 && _countt < 230)
        {
            _bossmv = BOSS_UP_MOVE;
        }
        if (_countt > 230 && _countt < 300)
        {
            _bossmv = BOSS_IDLE;
        }
        if (_countt > 300 && _countt < 350)
        {
            _bossmv = BOSS_RIGHT_MOVE;
        }
        if (_countt > 350 && _countt < 400)
        {
            _bossmv = BOSS_IDLE;
        }
        if (_countt > 400 && _countt < 450)
        {
            _bossmv = BOSS_RIGHT_MOVE;
        }
        if (_countt > 450 && _countt < 500)
        {
            _bossmv = BOSS_IDLE;
        }
        if (_countt > 500 && _countt < 530)
        {
            _bossmv = BOSS_DOWN_MOVE;
        }
        if (_countt > 530 && _countt < 600)
        {
            _bossmv = BOSS_IDLE;
        }
        if (_countt > 600 && _countt < 650)
        {
            _bossmv = BOSS_LEFT_MOVE;
        }
        if (_countt >= 650)
        {
            _countt = 50;
        }
        break;
    default:
        break;
    }



}

void enemy::draw()
{
    if (_state != STAGE_BOSS)
    {
        _imageName->frameRender(getMemDC(), _rc.left, _rc.top,
            _indexX, _indexY);
    }
    else
    {
        _imageName->frameRender(getMemDC(), _rc.left, _rc.top,
            _BindexX, _BindexY);
    }

}

void enemy::EnemyMove()
{


}

void enemy::moveHP(int hp)
{
    _HP -= hp;
}

bool enemy::bulletFire()
{
    _fireCount++;
    if (_fireCount > 10 && _rc.bottom > 300 && _rc.bottom < 320 && _state == STAGE_1)
    {
        _fireCount = 0;

        return true;
    }

    return false;
}

void enemy::xymove(float x, float y)
{

    _X += x;
    _Y += y;

    _rc = RectMakeCenter(_X, _Y, _imageName->getFrameWidth(),
        _imageName->getFrameHeight());
}

void enemy::bossmove()
{
    _counttt++;
    if (_state == STAGE_BOSS)
    {
        switch (_bossmv)
        {
        case BOSS_IDLE:
            _bossmv = BOSS_IDLE;
            xymove(0, 0);
            if (_counttt % 5 == 0)
            {
                if (_BindexX > 2)_BindexX = 0;
                _imageName->setFrameX(_BindexX);
                _imageName->setFrameY(_BindexY);
                _BindexX++;
                _counttt = 0;
            }
            break;
        case BOSS_LEFT_MOVE:
            _bossmv = BOSS_LEFT_MOVE;
            xymove(-6, 0);
            if (_counttt % 1 == 0)
            {
                if (_BindexX < 7 && _BindexX>7)_BindexX = 6;
                _imageName->setFrameX(_BindexX);
                _imageName->setFrameY(_BindexY);
                if (_BindexX < 7)
                {
                    _BindexX++;
                }
                _counttt = 0;
            }

            break;
        case BOSS_RIGHT_MOVE:
            _bossmv = BOSS_RIGHT_MOVE;
            xymove(6, 0);
            if (_counttt % 1 == 0)
            {
                if (_BindexX < 4 && _BindexX > 5)_BindexX = 4;
                _imageName->setFrameX(_BindexX);
                _imageName->setFrameY(_BindexY);
                if (_BindexX < 5)
                {
                    _BindexX++;
                }
                _counttt = 0;
            }

            break;
        case BOSS_UP_MOVE:
            _bossmv = BOSS_UP_MOVE;
            xymove(0, -5);
            if (_counttt % 1 == 0)
            {
                if (_BindexX < 7 && _BindexX>7)_BindexX = 6;
                _imageName->setFrameX(_BindexX);
                _imageName->setFrameY(_BindexY);
                if (_BindexX < 7)
                {
                    _BindexX++;
                }
                _counttt = 0;
            }
            break;
        case BOSS_DOWN_MOVE:
            _bossmv = BOSS_DOWN_MOVE;
            xymove(0, 5);
            if (_counttt % 1 == 0)
            {
                if (_BindexX < 4 && _BindexX > 5)_BindexX = 4;
                _imageName->setFrameX(_BindexX);
                _imageName->setFrameY(_BindexY);
                if (_BindexX < 5)
                {
                    _BindexX++;
                }
                _counttt = 0;
            }
            break;
        default:
            break;
        }
    }
}

