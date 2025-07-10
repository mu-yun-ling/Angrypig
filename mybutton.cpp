#include "mybutton.h"
#include "QTimer"
#include<QPainter>
//设置按钮
mybutton::mybutton(QString normalimg,QString changeimg)
    : normalpath(normalimg),changepath(changeimg)
{
    QPixmap pix;
    if(!pix.load(normalimg))return;
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
}
void mybutton::jump()
{
    QPropertyAnimation*animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    //通过起始变换做弹起效果
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y() ,this->width(),this->height()));

    animation->setEasingCurve(QEasingCurve::OutBounce);//缓和曲线
    animation->start();
}
void mybutton::setText(const QString &t ) {
    text = t   ;
    update();
}
void mybutton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setPen(QColor(0, 0, 0)); // 定义字体
    QFont font;
    font.setPointSize(30);
    font.setBold(true);
    painter.setFont(font);

    painter.drawPixmap(rect(),normalpath);
    painter.drawText(rect(), Qt::AlignCenter, text);

}
void mybutton::mousePressEvent(QMouseEvent*e)
{
    if(changepath!=" ")
    {
        QPixmap pix;
        if(!pix.load(changepath))return;
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mousePressEvent(e);
}
void mybutton::mouseReleaseEvent(QMouseEvent*e)
{
    if(changepath!=" ")
    {
        QPixmap pix;
        if(!pix.load(changepath))return;
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

    }

    return QPushButton::mouseReleaseEvent(e);
}
