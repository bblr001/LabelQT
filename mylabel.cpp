#include "mylabel.h"
#include<QPainter>
#include<QDebug>
MyLabel::MyLabel(QWidget *parent):QLabel (parent)
{
    isPressed = false;
    m_vec.clear();
    isCtrlPressed = false;
    dtype = noinfo;
}

void MyLabel::paintEvent(QPaintEvent *event){
    QLabel::paintEvent(event);
    QPainter painter(this);

    if(dtype == rect0)
    {
        painter.setPen(QPen(Qt::red, 2));
        painter.drawRect(QRect(x,y,w,h));
    }
    if(dtype != noinfo)
    {
        for(int i = 0; i<m_vec.size(); i++)
        {
            DrawData dd = m_vec.at(i);
            if(dd.dt == rect0)
            {
                painter.setPen(QPen(Qt::red, 2));
                painter.drawRect(QRect(dd.x,dd.y,dd.w,dd.h));
            }
            else{
                painter.setPen(QPen(Qt::blue, 2));
                painter.drawEllipse(dd.x-5, dd.y-5, 10, 10);
            }
        }
    }
    if(isCtrlPressed)
    {
        //绘制文字信息
        painter.setPen(QPen(Qt::red,2));
        QRect rect(coursx-10, coursy-10, 50, 20);
        QString txt;
        txt =  txt.asprintf("%d,%d", coursx, coursy);
        qDebug()<<txt<<"\n";
        painter.drawText(rect, txt);
    }

    update();
}

void MyLabel::mousePressEvent(QMouseEvent *event)
{
    isPressed = true;
    if(dtype == noinfo){
        return;
    }else
    {
        x  = event->pos().x();
        y  = event->pos().y();
        int x1 = event->x();
        int y1 = event->y();

        qDebug()<<"x="<<x<<"\t"
               <<"y="<<y<<"\t"
              <<"x1="<<x1<<"\t"
             <<"y1="<<y1<<"\n";
        w = 0;
        h = 0;
    }
}

void MyLabel::mouseReleaseEvent(QMouseEvent *event)
{
    w = event->x() - x;
    h = event->y() - y;
    isPressed = false;
    if(dtype == noinfo)
        return;
    DrawData tmp;
    if(dtype == rect0)
    {
        tmp.x = x;
        tmp.y = y;
        tmp.w = w;
        tmp.h = h;
        tmp.dt = rect0;
        m_vec.push_back(tmp);
    }else if(dtype ==pointA ){
        tmp.x = x;
        tmp.y = y;
        tmp.w = 0;
        tmp.h = 0;
        tmp.dt = pointA;
        m_vec.push_back(tmp);
    }else if(dtype ==pointB)
    {
        tmp.x = x;
        tmp.y = y;
        tmp.w = 0;
        tmp.h = 0;
        tmp.dt = pointB;
        m_vec.push_back(tmp);
    }else if(dtype ==pointC)
    {
        tmp.x = x;
        tmp.y = y;
        tmp.w = 0;
        tmp.h = 0;
        tmp.dt = pointC;
        m_vec.push_back(tmp);
    }else if(dtype ==pointD){
        tmp.x = x;
        tmp.y = y;
        tmp.w = 0;
        tmp.h = 0;
        tmp.dt = pointD;
        m_vec.push_back(tmp);
    }else if(dtype ==pointE){
        tmp.x = x;
        tmp.y = y;
        tmp.w = 0;
        tmp.h = 0;
        tmp.dt = pointE;
        m_vec.push_back(tmp);
    }
}

void MyLabel::mouseMoveEvent(QMouseEvent *event)
{
    if(isPressed){
        w = event->x() - x;
        h = event->y() - y;
    }
    else{
        coursx = event->x();
        coursy = event->y();
    }
}

void MyLabel::keyPressEvent(QKeyEvent *ev)
{
    if(ev->modifiers() == Qt::ControlModifier){
        qDebug()<<"ctrl pressed";
        isCtrlPressed = true;
    }else{
        isCtrlPressed = false;
        qDebug()<<"ctrl not pressed";
    }
}

void MyLabel::mouseDoubleClickEvent(QMouseEvent *event){
    int mx = event->x();
    int my = event->y();
    qDebug()<<"mx:"<<mx<<"\t"<<"my:"<<my<<"\n";
}
