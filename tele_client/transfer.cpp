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

void Transfer::setUpTcpSocket(QString hostIP, QString hostPort, ShowPic *shPic)
{
    picWidget = shPic;
    clientTcp.connectToHost(hostIP, hostPort.toInt());
    connect(&clientTcp, SIGNAL(readyRead()), this, SLOT(recvFromServer()));
    connect(&clientTcp,SIGNAL(disconnected()),this,SLOT(closedUpTcpSocket()));
}

void Transfer::recvFromServer()
{
//    if ((byteToTransfer != 0) && (clientTcp.bytesAvailable() >= 3*byteToTransfer)){
//        clientTcp.read(byteToTransfer);
//        byteToTransfer = 0;
//        buffer.seek(0);
//        return;
//    }

    QByteArray dataBlock;

    if (byteToTransfer == 0)
    {
        QDataStream in(&clientTcp);

        byteTransfered = 0;
        buffer.seek(0);
        //dataBlock.resize(sizeof(qint64));

        transferSize = qMin(clientTcp.bytesAvailable(), blockSize);
        dataBlock.resize(transferSize);

        in >> byteToTransfer;
        qDebug()<< "data length:" << byteToTransfer;

    }
    else
    {
        //QDataStream in(&dataBlock, QIODevice::ReadOnly);
        //QDataStream in(&clientTcp);
        qint64 available = clientTcp.bytesAvailable();
        transferSize = qMin(available,qMin(byteToTransfer, blockSize));
        dataBlock.resize(transferSize);
        //qDebug()<<"pendingDatagramSize():"<<clientUdp.pendingDatagramSize();
        qDebug()<<"data available:"<<available;
        qDebug()<<"before read dataBlock:"<<transferSize;

//        if ((res = clientUdp.readDatagram(dataBlock.data(), dataBlock.size())) != dataBlock.size())
//        {
//            qDebug()<<"Failed Read...:" << res << dataBlock.size();

//        }
//        else
//        {
        if (available <= byteToTransfer)
            dataBlock = clientTcp.readAll();    //Read the datablock
        else
            dataBlock = clientTcp.read(transferSize);
        //in >> dataBlock;
//dataBlock = clientTcp.readAll();

        buffer.seek(byteTransfered);
        buffer.write(dataBlock);
        byteTransfered += dataBlock.size();
        byteToTransfer -= dataBlock.size();
        qDebug()<<"Successful Read:" << dataBlock.size();
        dataBlock.resize(0);

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

void Transfer::displayError(QAbstractSocket::SocketError e)
{
    QMessageBox::warning(parentWidget, tr("Socket Error"),
                         tr("Socket Error: %1.").arg(clientTcp.errorString())); //QUESTION!!!
    clientTcp.close();
}
void Transfer::closeUpTcpSocket()
{
    disconnect(&clientTcp,SIGNAL(disconnected()),this,SLOT(closedUpTcpSocket()));
    clientTcp.close();
    this->parentWidget->update();
}

void Transfer::closedUpTcpSocket()
{
    emit hideIMSignal();
    QMessageBox::warning(parentWidget, tr("Message:"),
                         tr("Sever Quit!"));
    disconnect(&clientTcp,SIGNAL(disconnected()),this,SLOT(closedUpTcpSocket()));
    clientTcp.close();

}

void Transfer::setParentWidget(QWidget* pw)
{
    parentWidget=pw;
}

void Transfer::disconnectSlot()
{
    disconnect(&clientTcp,SIGNAL(disconnected()),this,SLOT(closedUpTcpSocket()));
}

