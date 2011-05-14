#include "transfer.h"

qint64 Transfer::blockSize = 1024*4;

Transfer::Transfer(QObject *parent) :
    QObject(parent)
{
    clientNum = 0;
    hasClientConnection = false;
}

Transfer::Transfer(QSystemTrayIcon *ti, QObject *parent) :
        QObject(parent)
{
    clientNum = 0;
    hasClientConnection = false;
    trayIcon = ti;
}

void Transfer::setTrayIcon(QSystemTrayIcon * ti)
{
    trayIcon = ti;
}

void Transfer::setUpUdpSocket(QString ip, QString port)
{
    serverUdp.bind(port.toInt(), QUdpSocket::DefaultForPlatform);
    connect(&serverUdp, SIGNAL(readyRead()), this, SLOT(receiveFromClient()));
    qDebug()<<"Setup UDP socket.\n";
}

void Transfer::setUpTcpSocket(QString port)
{
    if (!serverTcp.listen(QHostAddress::Any, port.toInt())) //Static port!!!To Modified!!!
    {
        QMessageBox::warning(0, tr("Socket Error"),
                                 tr("Socket Error: %1.").arg(serverTcp.errorString()));
    }
    connect(&serverTcp, SIGNAL(newConnection()), this, SLOT(acceptConnection())); //For new connection

}

void Transfer::acceptConnection()
{
    //ClientInfo client;
    clientConnection = serverTcp.nextPendingConnection();
    hasClientConnection = true;
    //clientNum++;
    //client.socket = clientConnection;
    //clientList.append(client);
//    QMessageBox::warning(0, tr("Socket Error"),
//                         tr("new connection"));
    showNewConnection();
    connect(clientConnection, SIGNAL(readyRead()), this, SLOT(recvFromClient()));
    connect(clientConnection, SIGNAL(error(QAbstractSocket::SocketError)),
            this , SLOT(displayError(QAbstractSocket::SocketError)));

}

void Transfer::showNewConnection()
{
    trayIcon->showMessage(tr("New Client"), tr("New Connection Accepted."));
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

    if (!clientConnection->isValid())
    {
        closeConnection();
        return;
    }

    qDebug()<<"start transfer";
    //get the pixmap
    if (!pm->save(&buffer, "jpg"))
        qDebug()<<"Pixmap save failed!";
    byteToTransfer = buffer.size();

    out << byteToTransfer;
    //if ((res = serverUdp.write(dataBlock)) != dataBlock.size())    //将图片长度发送出去
    if ((res = clientConnection->write(dataBlock)) != dataBlock.size())
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
        if ((res = clientConnection->write(dataBlock)) != transferSize)
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
        clientConnection->flush();
    }

    qDebug()<<"data length:"<<buffer.size();

}

void Transfer::recvFromClient()
{

}

void Transfer::closeConnection()
{
    clientConnection->close();
    hasClientConnection = false;
}

void Transfer::displayError(QAbstractSocket::SocketError e)
{
    emit hideIMSignal();
    QMessageBox::warning(parentWidget, tr("Message:"),
                         tr("Client Quit!")); //QUESTION!!!
    //serverTcp.close();
    clientConnection->close();
}

void Transfer::setParentWidget(QWidget* pw)
{
    parentWidget=pw;
}
