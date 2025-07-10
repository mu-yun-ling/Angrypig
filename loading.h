#ifndef LOADING_H
#define LOADING_H

#include <QWidget>

#include<musicplayer.h>
class playing;
class loading : public QWidget
{
    Q_OBJECT
private:
    MusicPlayer* player;
    playing*gameScene=NULL;
public:
    explicit loading(QWidget *parent = nullptr);
    ~loading();

    void paintEvent(QPaintEvent *event);

signals:
};
#endif // LOADING_H
