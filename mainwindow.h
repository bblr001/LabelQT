#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QVector>
#include <QString>
#include <QListWidgetItem>
#include <QMouseEvent>
#include "mylabel.h"
namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void ShowImage(QString path);
private:
    Ui::MainWindow *ui;
    MyLabel* Label1;
    QVector<QString> imglist;

    float w_r;
    float h_r;
    QPoint offset;
    DrawType m_drtype;

signals:
    void click();
public slots:
    void lookdir();
    void doubleclicked(QListWidgetItem* item);
    void itemrowchanged(int row);
    void rectDraw();
    void ptADraw();
    void ptBDraw();
    void ptCDraw();
    void ptDDraw();
    void ptEDraw();
    void looksavedir();
    void skipfile();
    void donefile();
protected:
//    void mouseDoubleClickEvent(QMouseEvent* event);
//    void paintEvent(QPaintEvent* event);
private:
    QString imgdir;    //图片路径
    QString  savePath; //保持路径
    QString  imgname;   //图像名称
    float aspectr;      //图像与控件的高宽比
};

#endif // MAINWINDOW_H
