#include "showpic.h"

ShowPic::ShowPic(QWidget *parent) :
    QWidget(parent)
{
    pm = NULL;
    isPainted = false;
    first = true;
}

void ShowPic::setPm(QPixmap p)
{
    pm = p;
    isPainted = false;
    first = false;
}

void ShowPic::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    //QPixmap pm;
//    if (pm->load(":/resource/image/test.jpg") == false)
//        QMessageBox::warning(this, "error", "no load");
    if (!first && !isPainted)
    {
        qDebug()<<"Paint widget.\n";
        painter.drawPixmap(0, 0, pm);
        isPainted = true;
    }
}
