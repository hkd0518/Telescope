#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPoint>
#include <QTimer>
#include <QRect>
#include <QMenu>
#include <QAction>
#include <QMouseEvent>
#include <QSystemTrayIcon>
#include <QBitmap>

#include "showpic.h"
#include "transfer.h"
#include "server.h"

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

    void resizeEvent(QResizeEvent *e);

    void creatTrayIcon();


protected slots:
    void screenShot();
    void showIM();
    void switchMode();
    void hideIM();
private:
    Ui::MainWindow *ui;
    ShowPic *shPic;
    Transfer net;
    QPoint dragPoint;
    QPoint topLeftPoint;
    QRect winSize;
    QTimer *timer;
    QSystemTrayIcon trayIcon;
    QMenu *trayIconMenu;
    QAction *actionMax;
    QAction *actionMin;
    QAction *actionNormal;
    QImage background;     //主窗口背景
    QPen pen;              //画笔
    bool moveModel;        //移动模式
    Server *server;        //IM

};

#endif // MAINWINDOW_H
