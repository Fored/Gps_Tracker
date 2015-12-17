#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGeoPositionInfoSource>
#include <QtSql>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

class gps : public QObject
{
    Q_OBJECT
public:
    explicit gps(QObject *parent = 0);

signals:
    void gotCoordinates(QString);
    void record_bd (double, double, QString);


public slots:
    void slotPositionUpdated(QGeoPositionInfo info);
    void slotPositionTimeout();
};

class my_bd : public QObject
{
    Q_OBJECT
public:
    explicit my_bd(QObject *parent = 0);
    QSqlDatabase db;
    QSqlQuery q;
    double shirota;
    double dolgota;
signals:
    void zapis (QString);
public slots:
    void record(double latitude, double longitude, QString cur_time);
};

#endif // MAINWINDOW_H
