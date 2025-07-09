#include "playing.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QPen>
#include <QColor>
#include<QDebug>
#include "start.h"
playing::playing(QWidget *parent) : QWidget{parent}
{
    explode=QPixmap(":/birds/boom.png");
    lever=1;
    //标题+窗口大小
    this-> setWindowTitle("Angry Pig");
    this->setWindowIcon(QPixmap(":/start/label.png"));
    this->setGeometry(QRect(250, 30,1300,990));

    player=new MusicPlayer(this);
    player->SoundPlay(":/sound/shoot_before.WAV");

    //黑屏
    blackMask = new QGraphicsRectItem(0, 0, Scene->width(), Scene->height());
    blackMask->setBrush(Qt::black);  // 纯黑色
    blackMask->setPen(Qt::NoPen);     // 无边框
    Scene->addItem(blackMask);
     blackMask->setVisible(false);


    //创建场景和视图
    Scene=new QGraphicsScene(this);
    View=new QGraphicsView(Scene,this);
    View->setGeometry(0, 0, this->width(), this->height());// 确保视图尺寸与窗口一致
    View->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    View->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//强制拉伸

    //添加背景
    QPixmap background(":/pig/bord.jpg");
    QGraphicsPixmapItem *BackGround=new QGraphicsPixmapItem(background.scaled(this->width(),this->height()));
    Scene->addItem(BackGround);

    //添加bird
    for(int i=0;i<4;i++)Add_bird(":/birds/bird_blue1.png",":/birds/bird_blue2.png",1,QPointF(830 ,700-60*i));
    for(int i=0;i<4;i++)Add_bird(":/birds/bird_red1.png",":/birds/bird_red2.png",2,QPointF(900 ,700-70*i));
    for(int i=0;i<4;i++)Add_bird(":/birds/bird_yellow1.png",":/birds/bird_yellow2.png",3,QPointF(850-60*i,420-60*i));
    Add_bird(":/birds/bird_red1.png",":/birds/bird_red2.png",2,QPointF(600 ,180));
    for(int i=0;i<3;i++)Add_bird(":/birds/bird_yellow1.png",":/birds/bird_yellow2.png",3,QPointF(920+60*i,360-60*i));
    Add_bird(":/birds/bird_red1.png",":/birds/bird_red2.png",2,QPointF(1110 ,160));

    for(bird* b  : birds)
    {
        b ->setVisible(false);
    }//暂时不可见


    // 添加pig
    // pigs.push_back(new pig(":/pig/pig_king.png"));
    // pigs.last()->setPos(180, 710);
    // Scene->addItem(pigs.last());
    // //
    pigs.push_back(new pig(":/pig/pig_green1.png"));
    pigs.last()->setPos(180, 710);
    Scene->addItem(pigs.last());

    pigs.push_back(new pig(":/pig/pig_cap1.png"));
    pigs.last()->setPos(100, 710);
    Scene->addItem(pigs.last());
    count = pigs.size();

        //添加弹弓
    Add_slingshot( );

    //弹弓换绑
    judge=new QTimer(this);
    judge->start(100);
    connect(judge, &QTimer::timeout, [=]()
            {
                if (count >0 &&pigReady->is_fall&& pigReady->is_flying)
                {
                    for (pig* p : pigs)
                    {
                        if (!p->is_flying && !p->is_fall)
                        {
                            pigReady = p;
                            set_pig(pigReady);  // 绑定下一只猪
                            break;
                        }
                    }
                }
            });

    //碰撞检测
    timer_boom=new QTimer(this);
    timer_boom->start(30);
    connect(timer_boom,&QTimer::timeout,[=]()
            {
                checkCollision();
            });

    this->setMouseTracking(true);
    View->show();
    View->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    Nextlever(lever);
}
playing::~playing()
{
    delete newscene;

}

void playing::Add_bird(const QString &faceA,const QString &faceB,int t,QPointF pos)
{
    bird*newbird=new bird(faceA,faceB,t);
    newbird->setPos(pos);
    Scene->addItem(newbird);
    birds.push_back(newbird);
}
void playing::Add_slingshot( )
{
    //弹弓图
    left_sling= QPixmap(":/pig/slingshot1.png");
    right_sling= QPixmap(":/pig/slingshot2.png");
    left_sling=left_sling.scaled(220,300,Qt::KeepAspectRatio);
    right_sling=right_sling.scaled(220,300,Qt::KeepAspectRatio);
    QGraphicsPixmapItem*left_shot=new  QGraphicsPixmapItem(left_sling);
    QGraphicsPixmapItem* right_shot=new  QGraphicsPixmapItem( right_sling);

    left_shot->setPos(98,528);
    right_shot->setPos(307,534);
    left_shot-> setZValue(15);//设置层级
    right_shot-> setZValue(5);//设置层级

    //左右锚点+发射器位置
    leftpos=QPointF(290,569);
    rightpos=QPointF(336,570);
    launchpos=(rightpos+leftpos)/2;
    //橡皮
    //绳子样式
    QPen pen(QColor(0x311706));
    pen.setWidthF(10.0);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::RoundJoin);
        //连接
    leftLine=new QGraphicsLineItem(QLineF(leftpos,launchpos));
    rightLine=new QGraphicsLineItem(QLineF(rightpos,launchpos));
    rightLine->setPen(pen);
    leftLine->setPen(pen);
    rightLine-> setZValue(8);//设置层级
    leftLine-> setZValue(16);//设置层级

    //发射器
    launchItem=new QGraphicsEllipseItem(QRectF(launchpos-QPointF(8,8),launchpos+QPointF(8,8)));
    launchItem->setPen(pen);
    launchItem->setBrush(QColor(pen.color()));
    launchItem-> setZValue(12);//设置层级

    //添加
    Scene->addItem(left_shot);
    Scene->addItem(right_shot);

    Scene->addItem(rightLine);
    Scene->addItem(leftLine);

    Scene->addItem(launchItem);

}
void playing::set_pig(pig*ptr)//放置pig到发射器
{

    if(!is_empty)
    {
        pigReady=ptr;
        is_pull=false;
        //发射准备
        pigReady->setPos(launchpos);
        pigReady->setFlag(QGraphicsItem::ItemIsMovable, false);
    }
}
void playing::mousePressEvent(QMouseEvent* event)//鼠标按下
{
    QPointF posing=View->mapToScene(event->pos());//获取当前位置信息
    if(event->buttons() & Qt::LeftButton &&launchItem->shape().contains(posing)&&!is_empty)//点击发射器，拉动绳子
    {
        is_pull=true;
        distance=posing-launchpos;
        pigReady->setFlag(QGraphicsItem::ItemIsMovable, true);//移动
    }

}

void playing::mouseMoveEvent(QMouseEvent* event)//鼠标移动
{

    if (event->buttons() & Qt::LeftButton &&is_pull)//鼠标左键，按下拖拽移动
    {
        setCursor(Qt::ClosedHandCursor);//设置鼠标指针为闭合的手形

        QPointF scenePos = View->mapToScene(event->pos());
        QPointF newposing = scenePos - distance;//新位置
        line=QLineF((leftpos+rightpos)/2,newposing);//判断是否超出范围
        if(line.length()>140)
        {
            newposing=(leftpos+rightpos)/2+(line.unitVector().p2() - line.unitVector().p1())*140;
        }
        //更新 绳子 发射器操作范围  猪的位置
        launchpos=newposing;


        leftLine->setLine(QLineF(leftpos,launchpos));
        rightLine->setLine(QLineF(rightpos,launchpos));
        launchItem->setRect(QRectF(launchpos-QPointF(8,8),launchpos+QPointF(8,8)));


        pigReady->setPos(launchpos);
        pigReady->setRotation(90+line.angle());//调整位置角度

        Scene->update();
    }

}

void playing::mouseReleaseEvent(QMouseEvent* event)//松开发射
{
    if (is_pull )
    {
        setCursor(Qt::OpenHandCursor);//鼠标指针还原
        is_pull=false;
        line=QLineF((leftpos+rightpos)/2,launchpos);
        QVector2D v = QVector2D(line.p1()-line.p2()) * 4;//初速度设置  与拉伸长度（矢量）成比例

        pigReady->setFlag(QGraphicsItem::ItemIsMovable, false); // 发射后禁止移动

        //发出信号
        pigReady->is_flying=true;
        if(count==2) player->SoundPlay(":/sound/shoot1.WAV");
        if(count==1)player->SoundPlay(":/sound/shoot2.WAV");

        pigReady->port (v.x(),v.y(),0.2,9.8);
        count--;//可用猪数量-1

        if (count == 0)
        {
            is_empty = true;
        }

        launchpos=(rightpos+leftpos)/2;
        launchItem->setRect(QRectF(launchpos-QPointF(8,8),launchpos+QPointF(8,8)));
        leftLine->setLine(QLineF(leftpos,launchpos));
        rightLine->setLine(QLineF(rightpos,launchpos));

        Scene->update();
    }
}
void playing::checkCollision()
{
    for (bird* b : birds)
    {
        for (pig* p : pigs)
        {
            if (b->collidesWithItem(p))
            {
                b->is_collision = true;
                boom(b);
                if(b->Type()==1)  player->SoundPlay(":/sound/die1.WAV");
                if(b->Type()==2)player->SoundPlay(":/sound/die2.WAV");
                if(b->Type()==3)player->SoundPlay(":/sound/die3.WAV");
                break;
            }
        }
    }

    //判断是否胜利
    if(count>=0&&birds.isEmpty()&&pigReady->is_fall)//胜利  暂时没作特殊显示
    {
        player->SoundPlay(":/sound/title_BGM.WAV");
        lever++;
        Nextlever(lever);

    }
    else if(count==0&&pigReady->is_fall)
    {
        player->SoundPlay(":/sound/game_complete.WAV");
        GameOver();


    }

    // QTimer::singleShot(3000,this,[this]()
    //                    {
    //     for (bird* b : birds)
    //     {
    //          b->is_collision = true;
    //         boom(b);
    //     }
    //                    });

}
void playing::Nextlever(int i)
{
    count=pigs.size();
    for(int t=0;t<i*2;t++)
    {
        birds.at(t)->setVisible(true);

    }

    for (pig* p : pigs)
    {
        p->is_flying=false;
        p->is_fall=false;
     }
    set_pig(pigs.first());
   pigs.last()->setPos(100, 710);

   blackMask->setVisible(true);
     QTimer::singleShot(4000,this,[this](){blackMask->setVisible(false);});
}

void playing:: GameOver()
{

    judge->stop();
    timer_boom->stop();
    QTimer::singleShot(4000,this,[this]()
                       {
                            blackMask->setVisible(true);


                           QPainter painter(this);
                           painter.setPen(QColor(43, 141, 167));
                           // 定义字体（如字号 24，加粗）
                           QFont font;
                           font.setPointSize(40);
                           font.setBold(true);
                           painter.setFont(font);
                           // 绘制文字（指定矩形区域、对齐方式、文字内容）
                           painter.drawText(
                               QRect(150, 200, 600, 400), // 矩形区域（x, y, 宽, 高）
                               "游戏结束"   // 实际显示的文字内容

                               );

                       });
    QTimer::singleShot(5000,this,[this]()
                       {
                          newscene=new Start();
                          player->stopMusic();
                          player->stopSound();
                          this->hide();
                          newscene->show();

                       });

}

void playing::boom(bird*ptr)
{
    if( !ptr->is_collision)return;//防止多次爆炸

    QGraphicsPixmapItem*booming=new QGraphicsPixmapItem(explode);
    booming->setZValue(20);
    booming->setPos(ptr->pos());
    Scene->addItem(booming);
    ptr->setVisible(false);
    Scene->update();

    QTimer::singleShot(300,this,[this,booming]()
                       {
                          Scene->removeItem(booming);
                          delete booming;

                       });
        //指定的时间间隔
}
