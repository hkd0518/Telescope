#include "connectdlg.h"
#include "ui_connectdlg.h"

ConnectDlg::ConnectDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDlg)
{
    ui->setupUi(this);

    QRegExp ipRegExp("^((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)$");
    ui->ipEdit->setValidator(new QRegExpValidator(ipRegExp, this));

}

ConnectDlg::~ConnectDlg()
{
    delete ui;
}
