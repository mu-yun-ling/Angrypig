#ifndef PLAYING_H
#define PLAYING_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include<QTimer>
#include<QVector2D>
#include <pig.h>
#include <bird.h>
#include <QGraphicsLineItem>
#include<musicplayer.h>
#include<QLine>

class Start;
class playing : public QWidget
{
    Q_OBJECT
private:
    int score=0;//
    QGraphicsScene *Scene;
    QGraphicsView *View;
    QGraphicsRectItem* blackMask = nullptr;  // 黑屏
    Start*newscene;
    int count;//猪的数量
    QTimer*judge;//判断弹弓是否需要上新
    QTimer*timer_boom;//碰撞检测

    MusicPlayer* player;

    //list
    QList<bird*>birds;
    QList<pig*> pigs;
    bird*safe;
    pig*pigReady=nullptr;//弹弓绑定的pig

    //判断
    bool is_empty=false;//判断是否还有剩余猪可用
    bool is_pull=false;//绳子是否拉动

    void checkCollision();
    void boom(bird*ptr);
    //弹弓

    QPixmap left_sling;
    QPixmap right_sling;
    QPixmap explode;
    //几个关键点
    QPointF rightpos;
    QPointF leftpos;//左右锚点
    QPointF launchpos;//发射器位置点
    QPointF distance;//位移
    QLineF line;//判断是否超出范围,直线位移
    //发射器，橡皮筋
    QGraphicsEllipseItem*launchItem=nullptr;
    QGraphicsLineItem*rightLine=nullptr;
    QGraphicsLineItem*leftLine=nullptr;

public:
    explicit playing(QWidget *parent = nullptr);
    ~playing();
    // void paintEvent(QPaintEvent *ev)override;

    void Add_bird(const QString &faceA,const QString &faceB,int t,QPointF pos);
    //弹弓
    void  Add_slingshot(pig*ptr);
    void set_pig(pig*ptr);

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    void   GameOver();

};
#endif // PLAYING_H
