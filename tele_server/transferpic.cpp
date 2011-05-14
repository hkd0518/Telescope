#include "transferpic.h"

TransferPic::TransferPic(QString ip, QString port)
{
    server.bind(port.toInt(), QUdpSocket::DefaultForPlatform);
    connect(&server, SIGNAL(readyRead()), this, SLOT(receiveFromClient()));

}

void TransferPic::sendPicToClient(QPixmap *pm)
{
    int res;

    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);

    pm->save(&buffer);

    if ((res = server.writeDatagram(byteArray, QHostAddress("127.0.0.1"), 12345))
        != byteArray.length())
    {
        QMessageBox::warning(0 , tr("UDP Socket"), tr("Error while transfer!"));
    }

}

void TransferPic::receiveFromeClient()
{

}
