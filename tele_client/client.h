#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QTcpSocket>
#include "ui_client.h"

class Client : public QDialog,private Ui::Client
{
    Q_OBJECT

public:
    Client(QString ip,QWidget *parent = 0);
    void clearShowText();
signals:
    void showIMSignal();
private slots:
    void sendData();
    void receiveData();

protected:
    void paintEvent(QPaintEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
private:
    void connectToServer();
    QPoint dragPoint;
    QTcpSocket tcpSocket;
    QString talk,listen;
    QString serverIp;
    QPen pen;
};

#endif // CLIENT_H
