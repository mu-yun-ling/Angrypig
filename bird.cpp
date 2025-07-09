#include "bird.h"
#include<QTimer>
#include <QRandomGenerator>
bird::bird(const QString&faceA,const QString&faceB,int t,QGraphicsItem* parent) :
    normalimg(faceA),changeimg(faceB),type(t),QGraphicsPixmapItem(parent)
{
    setZValue(10);//指定层级
    setPixmap(normalimg);
    setOffset(-normalimg.width() / 2, -normalimg.height() / 2);
    timer_face=new QTimer(this);
    connect(timer_face,&QTimer::timeout,[=]()
            {
                if(!is_collision)   changeExpression();
            });
    int random= QRandomGenerator::global()->bounded(1200, 30000);
    timer_face->start(random);
}



QPainterPath bird::shape()const
{
    QPainterPath path;
    qreal r = normalimg.width() / 2.0;
    if(!is_collision)
    {
        path.addEllipse(-r, -r, r*2, r*2);
    }
    else
    {
        path.addEllipse(0, 0, 0, 0);
    }
    return path;
}

void bird::changeExpression()
{
    if(is_collision)return;
    setPixmap(is_facechange?normalimg:changeimg);
    is_facechange=!is_facechange;
}
