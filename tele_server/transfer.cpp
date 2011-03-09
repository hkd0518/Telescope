#include "transfer.h"

qint64 Transfer::blockSize = 1024*4;

Transfer::Transfer(QObject *parent) :
    QObject(parent)
{

}

void Transfer::setUpUdpSocket(QString ip, QString port)
{
    serverUdp.bind(port.toInt(), QUdpSocket::DefaultForPlatform);
    connect(&serverUdp, SIGNAL(readyRead()), this, SLOT(receiveFromClient()));
    qDebug()<<"Setup UDP socket.\n";
}

void Transfer::sendPicToClient(QPixmap *pm)
{
    qint64 byteToTransfer;
    qint64 byteTransfered = 0;
    qint64 transferSize;
    qint64 res;

    QByteArray dataBlock;
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    QDataStream out(&dataBlock, QIODevice::WriteOnly);

    buffer.open(QIODevice::ReadWrite);

    qDebug()<<"start transfer";
    //get the pixmap
    if (!pm->save(&buffer, "jpg"))
        qDebug()<<"Pixmap save failed!";
    byteToTransfer = buffer.size();

    out << byteToTransfer;
    //if ((res = serverUdp.write(dataBlock)) != dataBlock.size())    //将图片长度发送出去
    if ((res = serverUdp.writeDatagram(dataBlock, QHostAddress::LocalHost, 12345))
        != dataBlock.size())
    {
        qDebug()<<"length transfer error:"<<res;
    }
    else
    {
        qDebug()<<"length transfer:"<<res;
    }
    dataBlock.resize(0);    //重置dataBlock

    while (byteToTransfer > 0)
    {
        transferSize = qMin(byteToTransfer, blockSize);

        //qDebug()<<"curSend:"<<curSend;
        buffer.seek(byteTransfered);    //必须对buffer进行重定位
        dataBlock = buffer.read(transferSize);
        //qDebug()<<"sendBlock:"<<sendBlock.length();
        if ((res = serverUdp.writeDatagram(dataBlock, QHostAddress::LocalHost, 12345))
            != transferSize)
        {
            //QMessageBox::warning(0 , tr("UDP Socket"), tr("Error while transfer!"));
            qDebug()<<"failed res:"<<res;
        }
        else
        {
            qDebug()<<"successful res:"<<res;
            byteToTransfer -= res;
            byteTransfered += res;
        }
    }

    qDebug()<<"data length:"<<buffer.size();

}

void Transfer::receiveFromClient()
{

}
