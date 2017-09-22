#ifndef PAINTABLELABEL_H
#define PAINTABLELABEL_H

#include <QLabel>
#include <QPainter>
#include <QList>
#include "global.h"

//#include <QWidget>
class PaintableLabel:public QLabel
{
Q_OBJECT

public:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
//    QPoint & startPoint();
//    QPoint & endPoint();
    void clearRegion();
    QList<Region> & returnList(){return _list;}

//    PaintableLabel():QLabel(){painter = new QPainter(this);painter->setPen(QPen(Qt::red,2));};
//    ~PaintableLabel(){delete painter;};
    //explicit PaintableLabel(QWidget *parent, Qt::WindowFlags f):QLabel(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());

private:

    int x_start;
    int y_start;
    int x_end;
    int y_end;

    int h;
    int w;

    int mousestatus = 0;

    QPainter * painter;
    QPoint startpoint;
    QPoint endpoint;
    QList<Region> _list;
};

#endif // PAINTABLELABEL_H
