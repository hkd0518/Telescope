#ifndef SHOWPIC_H
#define SHOWPIC_H

#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QMessageBox>

class ShowPic : public QWidget
{
    Q_OBJECT
public:
    explicit ShowPic(QWidget *parent = 0);

    void paintEvent(QPaintEvent *);
    void setPm(QPixmap p);
signals:

public slots:

private:
    QPixmap pm;
    bool isPainted;
    bool first;

};

#endif // SHOWPIC_H
