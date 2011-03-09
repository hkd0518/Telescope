#ifndef TRANSFER_H
#define TRANSFER_H

#include <QObject>
#include <QUdpSocket>
#include <QPixmap>
#include <QByteArray>
#include <QBuffer>
#include <QMessageBox>

#include "showpic.h"

class Transfer : public QObject
{
    Q_OBJECT
public:
    explicit Transfer(QObject *parent = 0);

public:
    void setUpUdpSocket(QString ip, QString port, ShowPic *shPic);
    void setUpTcpSocket();

signals:

public slots:
    void recvFromServer();   //以后此处构架要改，先有个分配器，对数据进行分析，再分配给各个处理函数
    void setPixmap();

protected:
    void recvPicFromServer();

private:
    static qint64 blockSize;
    QUdpSocket clientUdp;
    ShowPic *picWidget;
    QByteArray byteArray;
    QBuffer buffer;
    qint64 byteToTransfer;
    qint64 byteTransfered;
    qint64 transferSize;
    qint64 res;
};

#endif // TRANSFER_H
