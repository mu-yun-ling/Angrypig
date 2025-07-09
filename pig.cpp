#include "pig.h"
#include<QPainter>
#include<QLine>
pig::pig(const QString &img,QGraphicsItem* parent) : QGraphicsPixmapItem(parent)
{
    QPixmap pix_pig(img);
    pix_pig=pix_pig.scaled(pix_pig.width()*0.8,pix_pig.height()*0.8, Qt::KeepAspectRatio,Qt::SmoothTransformation);
    this->setZValue(10);
    setPixmap(pix_pig);
    setOffset(-pix_pig.width() / 2, -pix_pig.height() / 2);
    timer_flying=new QTimer(this);

    connect(timer_flying,&QTimer::timeout,[=]()
            {
                if(is_flying)
                {
                    this->calculatepos();
                }
            });
    timer_flying->start(50);
}
QPainterPath pig::shape() const
{
    QPainterPath path;

    qreal r = pixmap().width() / 2.0;
    path.addEllipse(-r, -r, r*2, r*2);
    return path;
}
void pig::port (qreal Vx,qreal Vy,qreal Ff,qreal a)
{
    current_angle=qRadiansToDegrees(qAtan2(-Vy,Vx));
    m_Vx=Vx*1.3;
    m_Vy=Vy*1.3;
    m_Ff=Ff;
    m_g=a;

}
void pig::calculatepos()
{
    if(!is_flying)return;

    //水平方向
    qreal ax=-m_Ff*qAbs(m_Vx);//空气阻力产生的变化加速度
    m_Vx+=ax*0.1;
    //竖直方向
    if(m_Vy<0)//向上运动
    {
        m_Vy+=m_g*0.9+2;

    }
    else
    {
        m_Vy+=m_g*0.9+1.5;
    }
    //更新位置

    check_boundary();

    QPointF newPos=pos()+QPointF(m_Vx*0.05,m_Vy*0.05);
    QLineF line=QLineF(pos(),newPos);
    setPos(newPos);

    // //调整角度
    // qreal temp_angle=qRadiansToDegrees(qAtan2(-m_Vy,m_Vx));
    // qreal diff = temp_angle - current_angle;
    // // 确保差值在 -45 到 45 度之间
    // while (diff > 45.0) diff -= 90.0;
    // while (diff < -45.0) diff += 90.0;
    // //平滑过渡
    // current_angle += diff * 0.05;
    // setRotation(temp_angle);

        //停止运动，关闭计时器
    if ( pos().y() >= 705&& pos().y() <= 715&&line.length()<5)
    {
        timer_flying->stop();
        is_fall=true;
    }
}
void pig::check_boundary()
{

    if (pos().x() > 1300|| pos().x() < 0   )
    {
        m_Vx=-m_Vx*0.8;
        m_Vy *= 0.9;
    }
    if ( pos().y() > 710)
    {
        m_Vy=-m_Vy*0.6;
        m_Vx *= 0.8;
    }
}
