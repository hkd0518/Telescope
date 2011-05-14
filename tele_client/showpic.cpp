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
    //painter.fillRect(this->rect(),QColor(0,0,0,255));
    if (!first && !isPainted)
    {
        qDebug()<<"Paint widget.\n";
        painter.drawPixmap(4, 0, pm);
        this->parentWidget()->resize(pm.width()+8,pm.height()+80);
        isPainted = true;
    }
}
