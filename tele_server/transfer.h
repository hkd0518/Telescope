#ifndef TRANSFER_H
#define TRANSFER_H

#include <QObject>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QTcpServer>
#include <QPixmap>
#include <QByteArray>
#include <QBuffer>
#include <QMessageBox>
#include <QDataStream>
#include <QSystemTrayIcon>

struct ClientInfo
{
    QString ip;
    quint16 port;
    QString name;
    QTcpSocket *socket;

    ClientInfo()
    {
        name = "NULL";
    }
};


class Transfer : public QObject
{
    Q_OBJECT
public:
    Transfer(QObject *parent = 0);
    Transfer(QSystemTrayIcon *ti, QObject *parent = 0);
    //explicit Transfer(QString ip, QString port, QObject *parent = 0);

public:
    void setUpUdpSocket(QString ip, QString port);
    void setUpTcpSocket(QString port);
    void setUpTcpSocket();
    void sendPicToClient(QPixmap *);
    void sendFileToClient();
    void showNewConnection();
    void setTrayIcon(QSystemTrayIcon *);
    void closeConnection();
    void setParentWidget(QWidget* pw);

signals:
    void hideIMSignal();

protected slots:
    void displayError(QAbstractSocket::SocketError e);
    void acceptConnection();
    void recvFromClient();

public:
    bool hasClientConnection;
private:
    static qint64 blockSize;
    qint32 clientNum;
    QUdpSocket serverUdp;
    QTcpServer serverTcp;
    QTcpSocket *clientConnection;
    QList <ClientInfo> clientList;
    QWidget *parentWidget;
    QSystemTrayIcon *trayIcon;



};

#endif // TRANSFERPIC_H
