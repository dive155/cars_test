#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->spinBox, SIGNAL(valueChanged(int)),
            this, SLOT(checkSpin(int)));

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
    timer->start(20); //создаём время

    amount = 10; //кол-во машин
    initCars(); //создаем их
    time = 0;
    speedLimit = 85; //ограничение скорости
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initCars()
{ //создать amount машинок
    Cars.clear(); //чистим массив
    for (int i = 0; i<amount; i++)
    {
        Car car; //создаем тачку
        car.setId(i);
        car.setSource(this);
        Cars.append(car); //добавляем в массив
    }
}

void MainWindow::checkCar(Car *car)
{ //проверяем машину
    if (car->speed() > speedLimit)
    { //если превышает
        car->bust(); //арестовываем
        ui->textEdit->append(QString("%1: %2 км/ч. Ограничение: (%3) км/ч. НАРУШЕНИЕ.").arg(car->color()).arg(car->speed()).arg(speedLimit));
    }
    else
    {
        ui->textEdit->append(QString("%1: %2 км/ч. Ограничение: (%3) км/ч. Нет нарушения.").arg(car->color()).arg(car->speed()).arg(speedLimit));
    }
}

void MainWindow::tick()
{ //вызывается каждый тик
    time++; //движим время
    scene->clear(); //готовим сцену
    scene->addPixmap(QPixmap(":cars/backtest.png"));
    for (int i = 0; i<amount; i++)
    {//двигаем машинки
        Cars[i].step(); //сдвигаем машину, потом рисуем её
        QGraphicsPixmapItem *pm = scene->addPixmap( QPixmap(Cars[i].pic() ) );
        pm->setPos(Cars[i].getX(), Cars[i].getY());
    }
    if (time > 60+rand()%100)
    { //если настало время создать новое авто (переместить существующее в начало)
        time = 0; //обнуляем время
        int val = rand()%(amount-1);
        while (Cars[val].isMoving() != 0)
        { //ищем уехавшую машину
            val = rand()%(amount-1);
        }
        Cars[val].startMoving(); //запускаем её
    }
    scene->addPixmap(QPixmap(":cars/police.png")); //рисуем полицейский участок
}

void MainWindow::checkSpin(int spin)
{
    speedLimit=spin;
    ui->textEdit->append(QString("Новое ограничение скорости: %1.").arg(speedLimit));
}
