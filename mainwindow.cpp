#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //scene.addText("Hello, world!");
    //scene.addEllipse(10,10,10,10);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    QBrush redBrush(Qt::red);
    QPen blackPen(Qt::black);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
    timer->start(20);

    amount = 10;
    initCars();
    time = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initCars()
{ //создать amount машинок
    Cars.clear();
    for (int i = 0; i<amount; i++)
    {
        Car car;
        Cars.append(car);
    }
}

void MainWindow::tick()
{
    time++;
    scene->clear();
    scene->addPixmap(QPixmap(":cars/backtest.png"));
    for (int i = 0; i<amount; i++)
    {//двигаем машинки
        Cars[i].step();
        QGraphicsPixmapItem *pm = scene->addPixmap( QPixmap(Cars[i].pic() ) );
        pm->setPos(Cars[i].getX(), Cars[i].getY());
    }
    if (time > 50+rand()%100)
    {
        qDebug() << "starting spawning at time" << time;
        time = 0;
        int val = rand()%(amount-1);
        while (Cars[val].isMoving() != 0)
        {
            val = rand()%(amount-1);
        }
        qDebug() << "seems like this car is not moving" << val;
        Cars[val].startMoving();
    }
}
