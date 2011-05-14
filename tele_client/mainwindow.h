#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QBitmap>
#include <QMouseEvent>
#include <QErrorMessage>

#include "showpic.h"
#include "connectdlg.h"
#include "transfer.h"
#include "client.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void getConnectInfo();
    void closeConnect();
    void showIM();
    void paintEvent(QPaintEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void resizeEvent(QResizeEvent *e);
    void closeClient();
    void hideIM();
private:
    QPoint dragPoint;
    QImage background;     //Ö÷´°¿Ú±³¾°    
public:
    Ui::MainWindow *ui;
    ShowPic *shPic;
    Transfer net;
    QString serverIp;
    QString serverPort;
    QPen pen;
    bool isConnected;
    bool hostIsSet;
    Client *client;

};


#endif // MAINWINDOW_H
