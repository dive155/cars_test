#include "car.h"
#include <QDebug>

Car::Car()
{
    desiredSpeed = 60 + (rand()%20);
    _speed = desiredSpeed;
    x = -2000; //ставим слева от экрана
    if (rand()%2 == 0) //в рандомную полосу
        y= 30;
    else
        y = 65;
    int picin = rand()%4;
    if (picin==0)
    { //рандомная картинка
        _pic = QPixmap(":cars/car1.png");
        _color = QString("Зеленый:");
    }
    if (picin==1)
    {
        _pic = QPixmap(":cars/car2.png");
        _color = QString("Синий:    ");
    }
    if (picin==2)
    {
        _pic = QPixmap(":cars/car3.png");
        _color = QString("Красный:");
    }
    if (picin==3)
    {
        _pic = QPixmap(":cars/car4.png");
        _color = QString("Желтый: ");
    }
    //не едет, не проверена, не арестована
    moving = false;
    checked = false;
    busted = false;
}

void Car::step()
{ //сдвинуть
    if (busted == false)
    { //если не арестована
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
            x = -2000;
            busted = false;
            if (rand()%2 == 0)
                y= 30; //ставим в рандомную полосу
            else
                y = 65;
        }
        if ((x>1500)&&(x<2000)&&(checked==false))
        { //если проезжает радар, проверяем
            window->checkCar(this);
            checked = true;
        }
    }
    else
    { //если арестовываем
        if (_speed<desiredSpeed)
            _speed = _speed+1;
        if (_speed>desiredSpeed)
            _speed = _speed-2;
        x=x+_speed; //машина всё ещё едет

        if (y<100)
        { //перестраиваемся вправо
            y+=2;
        }
        if ((y>=100))
        {
            desiredSpeed = 30; //тормозим
            //desiredSpeed = -0.01125*x + 77;
        }
        if (x>6600)
        { //если уехала, останавливаем
            moving = false;
            checked = false;
            x = -2000;
            busted = false;
            if (rand()%2 == 0)
                y= 30; //ставим в рандомную полосу
            else
                y = 65;
        }

    }
}

int Car::getX()
{ //получить х
    return x/10;
}

int Car::getY()
{ //получить y
    return y;
}

QPixmap Car::pic()
{ //получить пик
    return _pic;
}

bool Car::isMoving()
{ //едет ли
    return moving;
}

void Car::startMoving()
{ //начать двигаться
    moving = true;
    desiredSpeed = 60 + (rand()%40); //рандомная скорость
    _speed = desiredSpeed;
}

void Car::setSource(MainWindow *source)
{ //запоминаем мейнвиндоу
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
{ //арестовываем
    busted = true;
    desiredSpeed = 60; //снижай скорость
}

QString Car::color()
{
    return _color;
}


