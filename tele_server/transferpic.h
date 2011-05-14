#ifndef TRANSFERPIC_H
#define TRANSFERPIC_H

#include <QObject>
#include <QUdpSocket>
#include <QPixmap>
#include <QByteArray>
#include <QBuffer>
#include <QMessageBox>

struct ClientInfo
{
    QString ip;
    quint16 port;
    QString name;

    ClientInfo()
    {
        name = "NULL";
    }
};


class TransferPic : public QObject
{
    Q_OBJECT
public:
    //TransferPic();
    TransferPic(QString ip, QString port);

public:
    void sendPicToClient(QPixmap *);
    void sendFileToClient();

protected slots:
    void receiveFromeClient();

private:
    QUdpSocket server;
    QList <ClientInfo> clientList;

};

#endif // TRANSFERPIC_H
