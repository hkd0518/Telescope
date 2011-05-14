#ifndef CONNECTDLG_H
#define CONNECTDLG_H

#include <QDialog>
#include <QRegExp>

namespace Ui {
    class ConnectDlg;
}

class ConnectDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDlg(QWidget *parent = 0);
    ~ConnectDlg();

public: //！！！这里设置成public不太安全...但外部要访问..暂时先这样...
    Ui::ConnectDlg *ui;
};

#endif // CONNECTDLG_H
