#include "car.h"
#include <QDebug>

Car::Car()
{
    _speed = 1;
    desiredSpeed = 60 + (rand()%20);
    x = -3000;
    if (rand()%2 == 0)
        y= 28;
    else
        y = 65;
    int picin = rand()%4;
    if (picin==0) _pic = QPixmap(":cars/car1.png");
    if (picin==1) _pic = QPixmap(":cars/car2.png");
    if (picin==2) _pic = QPixmap(":cars/car3.png");
    if (picin==3) _pic = QPixmap(":cars/car4.png");

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
                y= 28;
            else
                y = 65;
        }
        if ((x>1500)&&(x<2000)&&(checked==false))
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

        if (y<102)
        {
            y+=3;
        }
        if ((y>=102))
        {
            desiredSpeed = 30;
            //desiredSpeed = -0.01125*x + 77;
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
    desiredSpeed = 60;
}


