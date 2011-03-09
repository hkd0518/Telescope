#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>

#include "showpic.h"
#include "connectdlg.h"
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

protected slots:
    void getConnectInfo();

//private:
public:
    Ui::MainWindow *ui;
    ShowPic *shPic;
    Transfer net;
    QString serverIp;
    QString serverPort;
    bool isConnected;
};

#endif // MAINWINDOW_H
