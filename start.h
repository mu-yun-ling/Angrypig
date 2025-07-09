#ifndef START_H
#define START_H

#include <QMainWindow>
#include <QApplication>
#include<QIcon>
#include<QPainter>
#include<QPixmap>
#include <loading.h>
#include<mybutton.h>

#include<musicplayer.h>


class Start : public QMainWindow
{
    Q_OBJECT
private:
    MusicPlayer* player;
    loading*newscene=NULL;

public:
    Start(QWidget *parent = nullptr);
    ~Start();

    void paintEvent(QPaintEvent *ev);



};
#endif // START_H
