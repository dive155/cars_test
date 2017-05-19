#include "car.h"
#include <QDebug>

Car::Car()
{
    _speed = 1;
    desiredSpeed = 60 + (rand()%20);
    x = -3000;
    if (rand()%2 == 0)
        y= 92;
    else
        y = 129;
    _pic = QPixmap(":cars/car1.png");
    qDebug() << rand()%2 << rand()%2 << rand()%2 << rand()%2 << rand()%2 << rand()%2;
    moving = false;
    checked = false;
    busted = false;
}

void Car::step()
{
    if (busted == false)
    {
        if (moving == true)
        { //если движется, двигаем
            if (_speed<desiredSpeed)
                _speed = _speed+1;
            if (_speed>desiredSpeed)
                _speed = _speed-1;
            x=x+_speed;
        }
        if (x>6600)
        { //если уехала, останавливаем
            moving = false;
            checked = false;
            x = -3000;
            busted = false;
            if (rand()%2 == 0)
                y= 92;
            else
                y = 129;
        }
        if ((x>2000)&&(x<2500)&&(checked==false))
        {

            window->checkCar(this);
            checked = true;
        }
    }
    else
    {
        if (_speed<desiredSpeed)
            _speed = _speed+1;
        if (_speed>desiredSpeed)
            _speed = _speed-4;
        x=x+_speed;

        if (y<166)
        {
            y+=3;
        }
        if (y>=166)
        {
            desiredSpeed = 0;
        }

    }
}

int Car::getX()
{
    return x/10;
}

int Car::getY()
{
    return y;
}

QPixmap Car::pic()
{
    return _pic;
}

bool Car::isMoving()
{
    return moving;
}

void Car::startMoving()
{
    moving = true;
    desiredSpeed = 60 + (rand()%40);
}

void Car::setSource(MainWindow *source)
{
    window = source;
}

int Car::speed()
{
    return _speed;
}

int Car::id()
{
    return _id;
}

void Car::setId(int ind)
{
    _id = ind;
}

void Car::bust()
{
    busted = true;
}


