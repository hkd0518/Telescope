#ifndef SHOWPIC_H
#define SHOWPIC_H

#include <QWidget>
#include <QTimer>
#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QMessageBox>

class ShowPic : public QWidget
{
    Q_OBJECT
public:
    explicit ShowPic(QWidget *parent = 0);
    void paintEvent(QPaintEvent *e);
};

#endif // SHOWPIC_H
