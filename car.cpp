#include "car.h"
#include <QDebug>

Car::Car()
{
    speed = 1;
    desiredSpeed = 60 + (rand()%20);
    x = -1000;
    if (rand()%2 == 0)
        y= 92;
    else
        y = 127;
    _pic = QPixmap(":cars/car1.png");
    qDebug() << rand()%2 << rand()%2 << rand()%2 << rand()%2 << rand()%2 << rand()%2;
    moving = false;
}

void Car::step()
{
    if (moving == true)
    { //если движется, двигаем
        if (speed<desiredSpeed)
            speed = speed+1;
            x=x+speed;
    }
    if (x>6600)
    { //если уехала, останавливаем
        moving = false;
        x = -1000;
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

bool Car::startMoving()
{
    moving = true;
}
