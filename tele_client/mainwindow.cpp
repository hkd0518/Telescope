#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_connectdlg.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/resource/icon/telescope.png"));
    this->setWindowTitle(tr("Telescope"));
    //For common initialization
    isConnected = false;
    hostIsSet = false;
    client= NULL;
    background=QImage(":/resource/image/colourback.jpg");
    net.setParentWidget(this);

    connect(&net,SIGNAL(hideIMSignal()),this,SLOT(hideIM()));

    //For exit Tool
    ui->actionExit->setIcon(QIcon(":/resource/icon/exit.png"));
    ui->actionExit->setStatusTip(tr("Exit from Telescope."));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(closeClient()));

    //For connect Tool
    ui->actionConnect->setIcon(QIcon(":/resource/icon/connect.png"));
    ui->actionConnect->setStatusTip(tr("Set up connection."));
    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(getConnectInfo()));

    //For IM Tool
    ui->actionIM->setIcon(QIcon(":/resource/icon/chat2.png"));
    ui->actionIM->setStatusTip(tr("Open the IM Dialog."));
    ui->actionIM->setCheckable(true);            //单击后保持按下状态
    connect(ui->actionIM,SIGNAL(triggered()),this,SLOT(showIM()));

    //For disconnect Tool
    ui->actionDisConnect->setIcon(QIcon(":/resource/icon/disconnect.png"));
    ui->actionDisConnect->setStatusTip(tr("Close up connection."));
    connect(ui->actionDisConnect, SIGNAL(triggered()), this, SLOT(closeConnect()));

    //For ToolBar
    ui->mainToolBar->setMovable(false);          //固定工具栏
    ui->mainToolBar->addAction(ui->actionConnect);
    ui->mainToolBar->addAction(ui->actionIM);
    ui->mainToolBar->addAction(ui->actionDisConnect);
    ui->mainToolBar->addAction(ui->actionExit);
    ui->mainToolBar->setIconSize(QSize(50,45));  //设置工具栏图标大小

    //For MainWindow
    setAttribute(Qt::WA_TranslucentBackground);   //窗口半透明
    setWindowFlags(Qt::Window |  Qt::FramelessWindowHint); //无边框窗口


    //For central Widget
    shPic = new ShowPic(this);
    //shPic->setMinimumSize(QSize(80, 60));
    this->setCentralWidget(shPic);
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter pb(&bmp);
    pb.setPen(Qt::NoPen);
    pb.setBrush(Qt::black);
    pb.drawRoundedRect(bmp.rect(),10,10);
    setMask(bmp);//设置窗体遮罩，形成圆角窗体效果

    pen.setStyle(Qt::SolidLine);
    pen.setWidth(7);
    pen.setColor(QColor("#DCDCDC"));
    p.setPen(pen);
    ui->mainToolBar->resize(ui->mainToolBar->width(),45);
    QRect mid(ui->mainToolBar->rect().bottomLeft(),rect().bottomRight());
    p.fillRect(mid,QColor(255,255,255,255));  //画背景色
    //ui->mainToolBar->setStyleSheet("");
    p.fillRect(ui->mainToolBar->rect(), QColor(190, 230, 251, 180));    //半透明靛青色
    //背景图片
    p.drawImage(mid.center().x()-background.width()/2,((mid.center().y()-background.height()/2)>45)?(mid.center().y()-background.height()/2):45,background);
    p.drawRoundedRect(rect(),10,10);   //画边框
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton)
    {
        move(e->globalPos() - dragPoint);   //移动主窗口
        if(client!=NULL)client->move(this->pos().x()+this->width(),this->pos().y()+45);  //IM跟随主窗口移动
        e->accept();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        dragPoint = e->globalPos() - frameGeometry().topLeft();
        e->accept();    //表示不用父类的事件响应函数运行了，相当于把事件截获
    }
}

void MainWindow::getConnectInfo()
{
    ConnectDlg *conDlg = NULL;
    qDebug()<<"into connectdlg\n";
    if (!conDlg)
        conDlg = new ConnectDlg(this);

    if (conDlg->exec() == QDialog::Accepted)
    {
        this->serverIp = conDlg->ui->ipEdit->text();
        this->serverPort = conDlg->ui->portEdit->text();
        hostIsSet = true;
        client=new Client(this->serverIp,this); //建立IM客户端
        connect(client,SIGNAL(showIMSignal()),this,SLOT(showIM()));
        net.setUpTcpSocket(serverIp, serverPort, shPic);
    }

    delete(conDlg);
}

void MainWindow::showIM()
{
    if(client==NULL)
    {
       QMessageBox::warning(this, tr("Stupid"),tr("You have to connect to Server first!"));
           ui->actionIM->setChecked(false);
       return;
    }
    client->move(this->pos().x()+this->width(),this->pos().y()+45);  //IM跟随主窗口移动
    if(client->isHidden()){client->show();ui->actionIM->setChecked(true);}
    else client->hide();
}

void MainWindow::closeConnect()
{
    if(client==NULL)
    {
        QMessageBox::warning(this, tr("Stupid"),tr("You have to connect to Server first!"));
            ui->actionDisConnect->setChecked(false);
        return;
    }
    net.closeUpTcpSocket();
    client->hide();
    client=NULL;
    ui->actionIM->setChecked(false);
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    if(client!=NULL)client->move(this->pos().x()+this->width(),this->pos().y()+45);  //IM跟随主窗口移动
}

void MainWindow::closeClient()
{
    net.disconnectSlot();
    close();
}

void MainWindow::hideIM()
{
    client->clearShowText();
    client->hide();
    client=NULL;
    ui->actionIM->setChecked(false);
}
