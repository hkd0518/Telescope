#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QTcpServer>
#include <QTcpSocket>
#include <QPainter>
#include <QBitmap>
#include <QMouseEvent>
#include "ui_server.h"

namespace Ui {
    class Server;
}

class Server : public QDialog,private Ui::Server
{
    Q_OBJECT

public:
    Server(QWidget *parent = 0);
    void clearShowText();
signals:
    void showIMSignal();
protected:
    void paintEvent(QPaintEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
private slots:
    void newSocket();
    void receiveData();
    void sendData();

private:
    QPoint dragPoint;
    QTcpServer server;
    QTcpSocket *socket;
    QString talk,listen;
    QPen pen;
    Ui::Server *ui;
};

#endif // SERVER_H
