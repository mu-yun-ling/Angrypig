#ifndef BIRD_H
#define BIRD_H
#include<QApplication>
#include <QGraphicsPixmapItem>
#include<QPixmap>
#include<QString>
#include<QObject>
class bird:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    QPixmap normalimg;
    QPixmap changeimg;
    QPixmap boomimg;
    QTimer*timer_face;//表情切换
    int type;
public:
    int Type(){return type;}

public:
    bool is_facechange=false;//对应普通表情
    bool is_collision=false;//碰撞检测

public:
    bird(const QString &faceA,const QString &faceB,int t,QGraphicsItem *parent=nullptr);
    ~bird(){}


    QPainterPath shape()const override;//自定义图形项的形状，从而实现精确检测

    void changeExpression();
};
#endif // BIRD_H

