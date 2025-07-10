#include "musicplayer.h"
#include<QDebug>
MusicPlayer ::MusicPlayer (QObject *parent) : QObject(parent)
{

}
MusicPlayer ::~MusicPlayer ()
{
    stopSound();
    stopMusic();

}
void MusicPlayer ::SoundPlay(const QString str)
{

    QSoundEffect* player = new QSoundEffect(this);
    player->setSource(QUrl::fromLocalFile(str));
    player->setLoopCount(1);
    player->setVolume(0.6f);
    player->play();


    // 播放完成后自动清理
    connect(player, &QSoundEffect::playingChanged, [this,player]()
            {
                if (!player->isPlaying())
                {
                    sound .removeOne(player);
                    player->deleteLater();
                }
            });
    sound.append(player);
}

void MusicPlayer ::MusicPlay(const QString str)
{

    QSoundEffect* player = new QSoundEffect(this);
    player->setSource(QUrl::fromLocalFile(str));
    player->setLoopCount(QSoundEffect::Infinite);
    player->setVolume(0.4f);
    player->play();


    // 播放完成后自动清理
    connect(player, &QSoundEffect::playingChanged, [this,player]()
            {
                if (!player->isPlaying())
                {
                    music .removeOne(player);
                    player->deleteLater();
                }
            });
    music.append(player);
}



// 停止所有音效
void MusicPlayer::stopSound()
{
    for(auto player :sound)
    {
        player->stop();
        player->deleteLater();
    }
    sound.clear();
}

// 停止背景音乐
void MusicPlayer::stopMusic()
{    for(auto player :music)
    {
        player->stop();
        player->deleteLater();
    }
    music.clear();
}
