#include <QLabel>
#include <QPen>
#include <QRect>
#include <QMouseEvent>


#include <QDebug>

#include "paintablelabel.h"

//explicit void PaintableLabel::PaintableLabel(QWidget *parent, Qt::WindowFlags f):QLabel(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags())
//{

//}

void PaintableLabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        startpoint = event->globalPos();
        startpoint = this->mapFromGlobal(startpoint);
        qDebug()<<startpoint<<endl;
        mousestatus = 1;
        x_start = startpoint.x();
        y_start = startpoint.y();
    }

    else
    {
        _list.clear();
        update();
    }
}

void PaintableLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        endpoint = event->globalPos();
        endpoint = this->mapFromGlobal(endpoint);
        qDebug()<<endpoint<<endl;
        x_end = endpoint.x();
        y_end = endpoint.y();
        qDebug()<<"mouse released"<<endl;
        //update();
        repaint();
        mousestatus = 0;
        if(mode)
        {
            _list.push_back(Region(cur_file_name,startpoint,endpoint));
        }
        else
        {
            _list.clear();
            _list.push_back(Region(cur_file_name,startpoint,endpoint));
        }
    }
}

void PaintableLabel::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        endpoint = event->globalPos();
        endpoint = this->mapFromGlobal(endpoint);
        qDebug()<<endpoint<<endl;
        update();
    }
}

void PaintableLabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);//先调用父类的paintEvent为了显示'背景'!!!

    qDebug()<<"painter"<<"  "<<mousestatus<<endl;
    if (mousestatus == 0)
        return;

    QPainter painter(this);
    painter.setPen(QPen(Qt::red,2));

    if(mode)
    {
        Region temp;
        foreach (temp, _list) {
            painter.drawRect(QRect(temp.start,temp.end));
        }
        painter.drawRect(QRect(startpoint,endpoint));
    }
    else
    {
        painter.drawRect(QRect(startpoint,endpoint));
    }
}

//QPoint & PaintableLabel:: startPoint()
//{
//    return startpoint;
//}

//QPoint & PaintableLabel:: endPoint()
//{
//    return endpoint;
//}

void PaintableLabel::clearRegion()
{
    _list.clear();
}
