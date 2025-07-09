#ifndef PIG_H
#define PIG_H
#include<QApplication>
#include<QPixmap>
#include<QTimer>
#include<QObject>
#include <QGraphicsPixmapItem>
#include <QString>

class pig : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:

    QTimer *timer_flying;//发射之后调整轨迹
    qreal m_Vx=0,m_Vy=0,m_Ff=0,m_g=9.8;//数值设定
    qreal current_angle = 0.0;
    //qreal  浮点数
public:
    bool is_flying=false;
    bool is_fall=false;//落地且速度为0就s？
public:
    pig(const QString &img,QGraphicsItem* parent = nullptr);
    ~pig(){ }
    QPainterPath shape() const override;

    void port (qreal Vx,qreal Vy,qreal Ff,qreal a);//运动数据初始化
    void calculatepos();//更新位置
    void check_boundary();
};
#endif // PIG_H
