#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGeoPositionInfoSource>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gps *GPS = new gps(this);
    connect(GPS, SIGNAL(gotCoordinates(QString)), ui->label, SLOT(setText(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

gps::gps(QObject *parent) :
    QObject(parent)
{
    // 1. Создаем новый экземпляр класса
    QGeoPositionInfoSource *source = QGeoPositionInfoSource::createDefaultSource(this);
    // 2. Соединяем необходимые сигналы и слоты
    connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)), this, SLOT(slotPositionUpdated(QGeoPositionInfo)));
    connect(source, SIGNAL(updateTimeout()), this, SLOT(slotPositionTimeout()));
    // 3. Задаем интервал запросов на получение координат.
    // Если задать 0, то частота запросов будет автоматически регулироваться классом
    source->setUpdateInterval(3000);
    source->startUpdates();
}
// Обрабатываем полученные координаты и генерируем сигнал о получении новых координат
void gps::slotPositionUpdated(QGeoPositionInfo info)
{
//    QGeoCoordinate coordinate = info.coordinate();
    emit gotCoordinates((QString("latitude - %1  longitude - %2").arg(info.coordinate().latitude()).arg(info.coordinate().longitude())));
}
// Слот обработки таймаута запроса
void gps::slotPositionTimeout()
{
    //qDebug() << "timeout";
}
