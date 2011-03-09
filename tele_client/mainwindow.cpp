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

    //For menu File
    ui->actionExit->setIcon(QIcon(":/resource/icon/exit.png"));
    ui->actionExit->setStatusTip(tr("Exit from Telescope."));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));

    //For menu Tool
    ui->actionConnect->setIcon(QIcon(":/resource/icon/connect.png"));
    ui->actionConnect->setStatusTip(tr("Set up connection."));
    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(getConnectInfo()));

    ui->actionIM->setIcon(QIcon(":/resource/icon/im.png"));
    ui->actionIM->setStatusTip(tr("Open the IM Dialog."));

    //For ToolBar
    ui->mainToolBar->addAction(ui->actionConnect);
    ui->mainToolBar->addAction(ui->actionIM);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actionExit);

    //For MainWindow

    //For central Widget
    shPic = new ShowPic(this);
    this->setCentralWidget(shPic);

    net.setUpUdpSocket(QString("127.0.0.1"), QString("12345"), shPic);
    //qDebug()<<"Mainwindow constructor over\n";

}

MainWindow::~MainWindow()
{
    delete ui;
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
        qDebug()<<"before net\n";
        //net = new Transfer(this->serverIp, this->serverPort, shPic, this);
        qDebug()<<"after net\n";
    }

    delete(conDlg);
}
