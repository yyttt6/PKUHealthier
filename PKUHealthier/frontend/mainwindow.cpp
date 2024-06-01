#include "mainwindow.h"
#include <string>


MainWindow::MainWindow(QWidget *parent)
    : QWidget{parent}
{
    QWidget::setAttribute(Qt::WA_Hover, true);
    resize(1050,650);
    setMinimumSize(1000,600);
    setStyleSheet("background:rgb(242,243,244);");
    setWindowTitle("PKUHealthier-首页");
    setWindowIcon(*pkuIcon);

    leftlist->addItem(icon0);
    leftlist->addItem(icon1);
    leftlist->addItem(icon2);
    leftlist->addItem(icon3);
    leftlist->addItem(icon4);
    leftlist->addItem(icon5);
    leftlist->addItem(icon6);

    /*
    button->setStyleSheet(
        "QPushButton {background-color: #2196F3;color: white;border: none;padding: 10px 20px;}"
        "QPushButton:hover {background-color: #1976D2;}"
        "QPushButton:pressed {background-color: #0D47A1;}");
    */

    leftlist->setIconSize(QSize(50, 50));
    leftlist->setFixedWidth(60);
    leftlist->setFrameShape(QFrame::NoFrame);
    leftlist->setFocusPolicy(Qt::NoFocus);
    leftlist->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    leftlist->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    std::string stylestr = R"(
        QListWidget{background:rgb(242,243,244);}
        QListWidget::item{border-radius:7px;height:60px;padding-left:2;}
        QListWidget::item:hover{border-radius:7px;background:rgb(241, 148, 138);}
        QListWidget::item:selected{border-radius:7px;background:rgb(192, 57, 43);color:rgb(0,0,0);}
    )";
    leftlist->setStyleSheet(QString::fromStdString(stylestr));
    finalLayout->addWidget(leftlist);

    rightpage->addWidget(w0);
    rightpage->addWidget(w1);
    rightpage->addWidget(w2);
    rightpage->addWidget(w3);
    rightpage->addWidget(w4);
    rightpage->addWidget(w5);
    rightpage->addWidget(w6);

    finalLayout->addWidget(rightpage);
    connect(leftlist,SIGNAL(currentRowChanged(int)),this,SLOT(changePage(int)));
    setLayout(finalLayout);
}

void MainWindow::changePage(int n){
    switch(n){
    case 0:rightpage->removeWidget(w0);
        w0=new Home(this);
        rightpage->insertWidget(0,w0);
        setWindowTitle("PKUHealthier-首页");
        break;
    case 1:rightpage->removeWidget(w1);
        w1=new Recommend(this);
        rightpage->insertWidget(1,w1);
        setWindowTitle("PKUHealthier-食谱推荐");
        break;
    case 2:
        setWindowTitle("PKUHealthier-饮食记录和评价");
        break;
    case 3:
        setWindowTitle("PKUHealthier-运动打卡");
        break;
    case 4:rightpage->removeWidget(w4);
        w4=new Records(this);
        rightpage->insertWidget(4,w4);
        setWindowTitle("PKUHealthier-饮食和运动记录");
        break;
    case 5:rightpage->removeWidget(w5);
        w5=new AchievementWall(this);
        rightpage->insertWidget(5,w5);
        setWindowTitle("PKUHealthier-成就");
        break;
    case 6:
        w6->refresh();
        setWindowTitle("PKUHealthier-个人信息");
        break;
    default:break;
    }
    rightpage->setCurrentIndex(n);
}
