#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPoint>
#include <QTimer>
#include <QRect>
#include <QMouseEvent>

#include "showpic.h"
#include "transfer.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *e);

    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);

    void keyPressEvent(QKeyEvent *e);

    void moveEvent(QMoveEvent *e);

protected slots:
    void screenShot();

private:
    Ui::MainWindow *ui;
    ShowPic *shPic;
    Transfer net;
    QPoint dragPoint;
    QPoint topLeftPoint;
    QRect winSize;
    QTimer *timer;
    bool moveModel;

};

#endif // MAINWINDOW_H
