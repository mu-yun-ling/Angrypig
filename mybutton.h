#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>
#include<QPixmap>
#include<QString>
#include <QPropertyAnimation>
#include <QEasingCurve>
class mybutton : public QPushButton
{
    Q_OBJECT
    QString normalpath;
    QString changepath;
    QString  text;
public:

    mybutton(QString normalimg,QString changeimg=" ");
    ~mybutton(){}

    //设置文本
    void setText(const QString &text);
    void paintEvent(QPaintEvent *event) override;

    void jump();

    //重写按下释放事件，不给隐性提示
    void mousePressEvent(QMouseEvent*e);
    void mouseReleaseEvent(QMouseEvent*e);
signals:
};
#endif // MYBUTTON_H
