#ifndef CAR_H
#define CAR_H
#include <qpixmap.h>
#include <mainwindow.h>
class MainWindow;

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
    void startMoving();
    void setSource(MainWindow* source);
    void radarPassed();
    int speed();
    int id();
    void setId(int ind);
    void bust();
    QString color();

private:
    int _speed;
    int desiredSpeed;
    int x;
    int y;
    bool checked;
    bool busted;
    int _id;
    QString _color;

    QPixmap _pic;

protected:
     MainWindow* window;
};

#endif // CAR_H
