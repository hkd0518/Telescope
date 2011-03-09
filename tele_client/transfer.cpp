#include "transfer.h"

qint64 Transfer::blockSize = 1024*4;

Transfer::Transfer(QObject *parent) :
    QObject(parent)
{
    buffer.setBuffer(&byteArray);
    buffer.open(QIODevice::ReadWrite);
    byteToTransfer = 0;
}

void Transfer::setUpUdpSocket(QString ip, QString port, ShowPic *shPic)
{
    picWidget = shPic;
    if (clientUdp.bind(port.toInt(), QUdpSocket::DefaultForPlatform))
        qDebug()<<"\nBind successfully!\n";
    if (connect(&clientUdp, SIGNAL(readyRead()), this, SLOT(recvFromServer())))
        qDebug()<<" Connect successfully!.\n";
}

void Transfer::recvFromServer()
{
    /*
    byteTransfered = 0;

    //QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::ReadWrite);
    QByteArray dataBlock;
    QDataStream in(&dataBlock, QIODevice::ReadOnly);

    dataBlock.resize(sizeof(qint64));
    if ((res = clientUdp.readDatagram(dataBlock.data(), dataBlock.size())) != dataBlock.size())
    {
        qDebug()<<"Failed Read length...";
    }
    else
    {
        qDebug()<<"Successful Read length!"<<res;
    }

    in >> byteToTransfer;
    qDebug()<< "data length:" << byteToTransfer;

    dataBlock.resize(0);
    buffer.seek(0);
    do{
        clientUdp.waitForReadyRead();//等待新的数据
        transferSize = qMin(clientUdp.pendingDatagramSize(),qMin(byteToTransfer, blockSize));
        dataBlock.resize(transferSize);
        qDebug()<<"pendingDatagramSize():"<<clientUdp.pendingDatagramSize();
        qDebug()<<"dataBlock:"<<dataBlock.size();
        if ((res = clientUdp.readDatagram(dataBlock.data(), dataBlock.size())) != dataBlock.size())
        {
            qDebug()<<"Failed Read...:" << res << dataBlock.size();

        }
        else
        {
            buffer.seek(byteTransfered);
            buffer.write(dataBlock);
            byteTransfered += res;
            byteToTransfer -= res;
            qDebug()<<"Successful Read:" << res;
            dataBlock.resize(0);
        }

    }while ((byteToTransfer != 0) && clientUdp.hasPendingDatagrams());


    qDebug()<<"receive data from server:"<<byteArray.size() << byteToTransfer;

   */
    QByteArray dataBlock;
    QDataStream in(&dataBlock, QIODevice::ReadOnly);

    if (byteToTransfer == 0)
    {
        byteTransfered = 0;
        buffer.seek(0);
        //dataBlock.resize(sizeof(qint64));

        transferSize = qMin(clientUdp.pendingDatagramSize(), blockSize);
        dataBlock.resize(transferSize);

        if ((res = clientUdp.readDatagram(dataBlock.data(), dataBlock.size())) != dataBlock.size())
        {
            qDebug()<<"Failed Read length...";
        }
        else
        {
            qDebug()<<"Successful Read length!"<<res;
        }

        in >> byteToTransfer;
        qDebug()<< "data length:" << byteToTransfer;

        dataBlock.resize(0);
    }
    else
    {
        transferSize = qMin(clientUdp.pendingDatagramSize(),qMin(byteToTransfer, blockSize));
        dataBlock.resize(transferSize);
        qDebug()<<"pendingDatagramSize():"<<clientUdp.pendingDatagramSize();
        qDebug()<<"dataBlock:"<<dataBlock.size();
        if ((res = clientUdp.readDatagram(dataBlock.data(), dataBlock.size())) != dataBlock.size())
        {
            qDebug()<<"Failed Read...:" << res << dataBlock.size();

        }
        else
        {
            buffer.seek(byteTransfered);
            buffer.write(dataBlock);
            byteTransfered += res;
            byteToTransfer -= res;
            qDebug()<<"Successful Read:" << res;
            dataBlock.resize(0);
        }
        if (byteToTransfer == 0) setPixmap();
    }

    //setPixmap();

}

void Transfer::setPixmap()
{
    QPixmap pm;
    if (pm.loadFromData(byteArray))
    {
        //qDebug()<<"Load Successfully!\n";
        picWidget->setPm(pm);
        picWidget->update();
    }
    else
        qDebug()<<"Load Failed!\n";
}
