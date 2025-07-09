#include "loading.h"
#include"mybutton.h"
#include<QPainter>
#include<QPixmap>
#include<QTimer>
#include"playing.h"
loading::loading(QWidget *parent)  : QWidget(parent)
{
    //标题+窗口大小
    this-> setWindowTitle("Angry Pig");
    this->setWindowIcon(QPixmap(":/start/label.png"));
    this->setGeometry(QRect(250, 30,1300,990));

    player=new MusicPlayer(this);
    player->MusicPlay(":/sound/loading_BGM.WAV");


    QTimer::singleShot(5000,this,[this]()
                       {
                           gameScene=new playing();
                           player->stopMusic();
                           player->stopSound();
                           this->hide();
                           gameScene->show();
                       });


}
loading::~loading()
{
    delete gameScene;
}
void loading::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/start/loading.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

}

