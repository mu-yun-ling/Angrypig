#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H
#include <QObject>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QVector>
#include <QString>

class MusicPlayer: public QObject
{
    Q_OBJECT

private:
    QVector<QSoundEffect*>  sound ;    //音效
    QVector<QSoundEffect*>music  ; //音乐


public:
    explicit MusicPlayer(QObject *parent = nullptr);
    ~MusicPlayer();

    void SoundPlay(const QString str);            // 播放单次音效
    void MusicPlay(const QString str);       // 播放循环背景音乐

    // 停止所有音效
    void stopSound();

    // 停止背景音乐
    void stopMusic();
};

#endif // MUSICPLAYER_H
