#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGeoPositionInfoSource>

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

public slots:
    void slotPositionUpdated(QGeoPositionInfo info);
    void slotPositionTimeout();
};

#endif // MAINWINDOW_H
