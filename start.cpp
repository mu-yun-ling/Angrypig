#include "start.h"

#include<QTimer>
Start::Start(QWidget *parent)
    : QMainWindow(parent)
{

        //标题+窗口大小
    this-> setWindowTitle("Angry Pig");
    this->setWindowIcon(QPixmap(":/start/label.png"));
    this->setGeometry(QRect(250, 30,1300,990));

    player=new MusicPlayer(this);
    player->MusicPlay(":/sound/title_BGM.WAV");

    //按钮
    mybutton*start_false=new mybutton(":/start/begin_bar.png");
    start_false->setParent(this);
    start_false->move(this->width()*0.12,this->height()*0.4);
    connect(start_false,&mybutton::clicked,[=]()
            {start_false->jump();
                QTimer::singleShot(400,this,
                                   [=]()
                                   {                 //进入加载界面
                                       newscene=new loading();
                                       player->stopMusic();
                                       this->hide();
                                       newscene->show();
                                   });
            });
    mybutton*title=new mybutton(":/start/title1.png");
    title->setParent(this);
    title->move(this->width()*0.45,this->height()*0.1);
}

Start::~Start()
{
    delete newscene;
}

void Start::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);
    //开始界面
    QPixmap pix;
    pix.load(":/start/beginning.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
