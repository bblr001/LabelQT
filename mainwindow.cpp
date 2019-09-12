#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QStringList>
#include <QPainter>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Label1 = new MyLabel(this);
    Label1->setGeometry(QRect(0, 0, 800, 600));
    //Label1->setAlignment(Qt::AlignCenter);
    Label1->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    Label1->setFrameStyle(2);
    Label1->setStyleSheet("background-color:black");
    ui->listWidget->clear();

    connect(ui->pButton_ImgList, SIGNAL(clicked(bool)),this, SLOT(lookdir()));
    connect(ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(doubleclicked(QListWidgetItem*)));
    connect(ui->listWidget, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(doubleclicked(QListWidgetItem*)));
    connect(ui->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(itemrowchanged(int)));

    // draw button connect
    connect(ui->rectButton, SIGNAL(clicked(bool)), this, SLOT(rectDraw()));
    connect(ui->AButton, SIGNAL(clicked(bool)), this, SLOT(ptADraw()));
    connect(ui->BButton, SIGNAL(clicked(bool)), this, SLOT(ptBDraw()));
    connect(ui->CButton, SIGNAL(clicked(bool)), this, SLOT(ptCDraw()));
    connect(ui->DButton, SIGNAL(clicked(bool)), this, SLOT(ptDDraw()));
    connect(ui->EButton, SIGNAL(clicked(bool)), this, SLOT(ptEDraw()));

    //other
    connect(ui->saveButton, SIGNAL(clicked(bool)), this, SLOT(looksavedir()));
    connect(ui->skipButton, SIGNAL(clicked(bool)), this, SLOT(skipfile()));
    connect(ui->doneButton, SIGNAL(clicked(bool)), this, SLOT(donefile()));

    //
    savePath = "";
//    float w = (float)1620/(float)800;
//    float h = (float)1236/(float)600;
//    qDebug()<<"w ="<<w<<"\t"<<"h ="<<h<<endl;
//    if(w>h)
//        qDebug()<<w;
//    else
//        qDebug()<<h;
}

void MainWindow::ShowImage(QString path)
{
    QImage *img = new QImage;
    img->load(path);
    int lw = Label1->width();
    int lh = Label1->height();
    int iw = img->width();
    int ih = img->height();
    w_r = (float)iw/(float)lw;
    h_r = (float)ih/(float)lh;
    qDebug()<<"lw:"<<lw<<" lh:"<<lh<<endl;
    qDebug()<<"iw:"<<iw<<" ih:"<<ih<<endl;
    qDebug()<<"w_r:"<<w_r<<" h_r:"<<h_r;
    aspectr = w_r>h_r?w_r:h_r;
    qDebug()<<"aspectr:"<<aspectr;
    QImage scaledimg=img->scaled(lw,lh,Qt::KeepAspectRatio);
    Label1->setPixmap(QPixmap::fromImage(scaledimg));
    delete img;
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::lookdir(){
    ui->listWidget->clear();
    imglist.clear();

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Image Directory"),
                                                      "D:\\",
                                                      QFileDialog::ShowDirsOnly
                                                      | QFileDialog::DontResolveSymlinks);
    qDebug()<<dir;
    imgdir = dir;
    QDir dirs(dir);
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.png";
    QStringList files = dirs.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    qDebug()<<"imglist's size = "<<imglist.size();
    QListWidgetItem * item = new QListWidgetItem;
    item->setText("ImageFileName");
    ui->listWidget->addItem(item);
    delete item;
    for(int i = 0; i<files.size();i++){
        qDebug()<<files.at(i);
        imglist.push_back(files.at(i));
        QListWidgetItem * item = new QListWidgetItem;
        item ->setText(files.at(i));
        ui->listWidget->insertItem(i, item);
        //delete item;
    }
    ui->listWidget->setCurrentRow(0);
    ui->listWidget->setFocus();
    imgname = ui->listWidget->item(0)->text();
    qDebug()<<"imglist's size = "<<imglist.size();
}

void MainWindow::looksavedir()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Image Directory"),
                                                      "D:\\",
                                                      QFileDialog::ShowDirsOnly
                                                      | QFileDialog::DontResolveSymlinks);
    qDebug()<<dir;
    savePath = dir;
}

void MainWindow::doubleclicked(QListWidgetItem* item)
{
    Label1->clear();
    QString tx = item->text();
    QString fullpath = imgdir + "\\" + tx;
    ShowImage(fullpath);
    imgname = tx;
    Label1->setDrawType(noinfo);
}

void MainWindow::itemrowchanged(int row)
{
    Label1->clear();
    QListWidgetItem * item = ui->listWidget->item(row);
    QString fullpath = imgdir + "\\" + item->text();
    ShowImage(fullpath);
    imgname = item->text();
    Label1->setDrawType(noinfo);
}



void MainWindow::rectDraw()
{
    Label1->setDrawType(rect0);
}

void MainWindow::ptADraw(){
    Label1->setDrawType(pointA);
}

void MainWindow::ptBDraw(){
    Label1->setDrawType(pointB);
}

void MainWindow::ptCDraw(){
    Label1->setDrawType(pointC);
}

void MainWindow::ptDDraw(){
    Label1->setDrawType(pointD);
}

void MainWindow::ptEDraw(){
    Label1->setDrawType(pointE);
}

void MainWindow::skipfile()
{
    int n = ui->listWidget->currentRow();
    QListWidgetItem *item = ui->listWidget->item(n+1);
    QString fullpath = imgdir + "\\" + item->text();
    ShowImage(fullpath);
    ui->listWidget->setCurrentRow(n+1);
    imgname = ui->listWidget->item(n+1)->text();
    Label1->setDrawType(noinfo);
}

void MainWindow::donefile()
{
    if(savePath == "")
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("warning");
          msgBox.setText("savePath is NULL.");
          msgBox.exec();
          return;
    }
    QStringList ls = imgname.split('.');
    QString name = ls[0];
    QString filename = name + ".txt";
    QString path = savePath + "\\" + filename;
    QFile file(path);
      if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
          return;

      QTextStream out(&file);
      out <<imgname<<" ";
      QVector<DrawData> qdd = Label1->getVec();
      for(int i =0; i< qdd.size(); i++)
      {
          if(qdd.at(i).dt == rect0)
            out<<int(qdd.at(i).x*aspectr)<<" "<<int(qdd.at(i).y*aspectr)<<" "<<int(qdd.at(i).x*aspectr + qdd.at(i).w*aspectr)<<" "<<int(qdd.at(i).y*aspectr + qdd.at(i).h*aspectr)<<" ";
          else
              out<<int(qdd.at(i).x*aspectr)<<" "<<int(qdd.at(i).y*aspectr)<<" ";
      }
      out<<"\n";
      Label1->setDrawType(noinfo);
}
