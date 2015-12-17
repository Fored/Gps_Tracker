#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGeoPositionInfoSource>
#include <stdio.h>
#include "sqlite3.h"
#include <QMessageBox>
#include <QtWidgets>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gps *GPS = new gps(this);
    connect(GPS, SIGNAL(gotCoordinates(QString)), ui->label, SLOT(setText(QString)));
    my_bd *MY_BD = new my_bd(this);
    connect(GPS, SIGNAL(record_bd(double, double, QString)),MY_BD, SLOT(record(double,double,QString)));
    connect(MY_BD, SIGNAL(zapis(QString)), ui->textEdit, SLOT(append(QString)));
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
    source->setUpdateInterval(5);
    source->startUpdates();    
}
// Обрабатываем полученные координаты и генерируем сигнал о получении новых координат
void gps::slotPositionUpdated(QGeoPositionInfo info)
{
    emit gotCoordinates((QString("latitude - %1  longitude - %2").arg(info.coordinate().latitude()).arg(info.coordinate().longitude())));

    emit record_bd(info.coordinate().latitude(), info.coordinate().longitude(), info.timestamp().toString("yyyy-MM-dd hh:mm:ss"));

}

// Слот обработки таймаута запроса
void gps::slotPositionTimeout()
{
    //qDebug() << "timeout";
}
my_bd::my_bd(QObject *parent) :
    QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE", "/storage/emulated/0/Download/my_gps.dblite");
    db.setDatabaseName("/storage/emulated/0/Download/my_gps.dblite");
    db.open();
    q = QSqlQuery("", db);
}

 void my_bd::record(double latitude, double longitude, QString cur_time)
 {
     if (fabs(latitude - shirota) >= 0.0002 or fabs(longitude - dolgota) >= 0.0002)
     {
         shirota = latitude;
         dolgota = longitude;
         q.prepare(QString("INSERT INTO coordinate (datatime, latitude, longitude)"
         "VALUES ('%1', %2, %3)").arg(cur_time).arg(latitude).arg(longitude)
                   );
         q.exec();
         emit zapis(QString("INSERT INTO coordinate (datatime, latitude, longitude)"
                            "VALUES ('%1', %2, %3)").arg(cur_time).arg(latitude).arg(longitude));
     }
 }
