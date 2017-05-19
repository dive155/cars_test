#ifndef CAR_H
#define CAR_H
#include <qpixmap.h>

class Car
{
public:
    Car();
    void accel();
    void brake();
    void think();
    void step();
    int getX();
    int getY();
    QPixmap pic();
    bool moving;
    bool isMoving();
    bool startMoving();

private:
    int speed;
    int desiredSpeed;
    int x;
    int y;
    bool spawned;

    QPixmap _pic;

};

#endif // CAR_H
