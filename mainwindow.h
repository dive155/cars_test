#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include "car.h"
#include <qvector.h>

class Car;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initCars();

public slots:
    void tick();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    //QGraphicsRectItem *rect;
    QPixmap *rect;
    QTimer *timer;
    QVector<Car> Cars;
    Car* car1;
    int amount;
    int time;
};

#endif // MAINWINDOW_H
