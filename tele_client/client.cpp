#include "client.h"
#include "mainwindow.h"
#include <QtNetwork>
#include <QTime>

Client::Client(QString ip,QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    this->serverIp=ip;
    connectToServer();
    showText->setReadOnly(true);
    talk.clear();
    this->hide();

    connect(lineEdit,SIGNAL(returnPressed()),this,SLOT(sendData()));
    connect(&tcpSocket,SIGNAL(readyRead()),this,SLOT(receiveData()));

    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}

void Client::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.fillRect(rect(), QColor(8, 46, 84, 100));
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(7);
    pen.setColor(QColor("#DCDCDC"));
    p.setPen(pen);
    p.drawRoundedRect(rect(),10,10);
}

void Client::connectToServer()
{
    if(tcpSocket.state()!=tcpSocket.ConnectedState)
        tcpSocket.connectToHost(QHostAddress(this->serverIp),12346);
}

void Client::sendData()
{
    QString str="<font size=3 color=#E0FFFF>Client ";
    str.append(QTime::currentTime().toString());
    str.append("<br></font>");
    str.append("<font size=3 color=#E0FFFF>");
    str.append("&nbsp;&nbsp;&nbsp;&nbsp;");
    str.append(lineEdit->text());
    str.append("<br>");
    str.append("</font>");
    if(!talk.isEmpty()) talk.append("\n");
    talk.append(str);
    showText->append(str);
    lineEdit->clear();

    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_3);

    out<<talk;
    if(tcpSocket.state()!=tcpSocket.ConnectedState)
    {
        tcpSocket.connectToHost(QHostAddress("172.18.33.59"),12346);
        tcpSocket.write(block);
        if(tcpSocket.state()==tcpSocket.ConnectedState)
            talk.clear();
    }
    else
    {
        talk.clear();
        tcpSocket.write(block);
    }
}

void Client::receiveData()
{
    QDataStream in(&tcpSocket);
    in.setVersion(QDataStream::Qt_4_3);

    in>>listen;
    showText->append(listen);
    //this->show();
    if(this->isHidden())emit showIMSignal();
}

void Client::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton)
    {
        move(e->globalPos() - dragPoint);   //移动IM窗口
        this->parentWidget()->move(this->pos().x()-this->parentWidget()->width(),this->pos().y()-45); //主窗口跟随IM移动
        e->accept();
    }
}

void Client::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        dragPoint = e->globalPos() - frameGeometry().topLeft();
        e->accept();    //表示不用父类的事件响应函数运行了，相当于把事件截获
    }
}

void Client::clearShowText()
{
    showText->clear();
}
