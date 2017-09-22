#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>
#include <QPoint>

extern bool mode;
extern QString cur_file_name;

struct Region
{
    QString img_name;
    QPoint start;
    QPoint end;

    Region(QString & name,QPoint & startp,QPoint &endp)
    {
        img_name = name;
        start = startp;
        end = endp;
    }

    Region(){};
};

#endif // GLOBAL_H
