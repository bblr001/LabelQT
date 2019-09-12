#ifndef MYLABEL_H
#define MYLABEL_H
#include<QLabel>
#include<QPaintEvent>
#include <QObject>
#include <QPainter>
#include <QPoint>
#include <QColor>
#include <QPen>
#include <QMouseEvent>
#include <vector>
#include <QVector>
#include <QKeyEvent>
typedef enum{
    noinfo = -1,
    rect0 = 0,
    pointA,
    pointB,
    pointC,
    pointD,
    pointE
}DrawType;

typedef struct{
    int x;
    int y;
    int w;
    int h;
    DrawType dt;
}DrawData;
class MyLabel : public QLabel
{
    Q_OBJECT
public:
    MyLabel(QWidget *parent);
    void setDrawType(DrawType dt){
        dtype = dt;
    }

    void clear(){m_vec.clear();}
    QVector<DrawData> getVec(){return m_vec;}
protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *ev);
private:
    int x;
    int y;
    int w;
    int h;
    bool isPressed;
    DrawType dtype;
    QVector<DrawData> m_vec;
    bool isCtrlPressed;
    int coursx;
    int coursy;
};

#endif // MYLABEL_H
