#ifndef TRANSFER_H
#define TRANSFER_H

#include <QObject>
#include <QUdpSocket>
#include <QPixmap>
#include <QByteArray>
#include <QBuffer>
#include <QMessageBox>
#include <QDataStream>

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


class Transfer : public QObject
{
    Q_OBJECT
public:
    explicit Transfer(QObject *parent = 0);
    //explicit Transfer(QString ip, QString port, QObject *parent = 0);

public:
    void setUpUdpSocket(QString ip, QString port);
    void setUpTcpSocket();
    void sendPicToClient(QPixmap *);
    void sendFileToClient();

protected slots:
    void receiveFromClient();

private:
    static qint64 blockSize;
    QUdpSocket serverUdp;
    QList <ClientInfo> clientList;



};

#endif // TRANSFERPIC_H
