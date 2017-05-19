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
    speedLimit = 85;
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
        car.setId(i);
        car.setSource(this);
        Cars.append(car);
    }
}

void MainWindow::checkCar(Car *car)
{
    qDebug () << "car" << car->id() << "passes at speed " << car->speed();
    if (car->speed() > speedLimit) car->bust();
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
        time = 0;
        int val = rand()%(amount-1);
        while (Cars[val].isMoving() != 0)
        {
            val = rand()%(amount-1);
        }
        Cars[val].startMoving();
    }
}
