#include "mainwindow.h"
#include <string>


MainWindow::MainWindow(QWidget *parent)
    : QWidget{parent}
{
    QWidget::setAttribute(Qt::WA_Hover, true);
    resize(900,600);
    setMinimumSize(700,500);
    setStyleSheet("background:rgb(242,243,244);");

    leftlist->addItem(icon0);
    leftlist->addItem(icon1);
    leftlist->addItem(icon2);
    leftlist->addItem(icon3);
    leftlist->addItem(icon4);
    leftlist->addItem(icon5);
    leftlist->addItem(icon6);

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
        case 0:w0->refresh();break;
        case 1:w1->refresh();break;
        case 2:w2->refresh();break;
        case 3:w3->refresh();break;
        case 4:w4->refresh();break;
        case 5:w5->refresh();break;
        case 6:w6->refresh();break;
        default:break;
    }
    rightpage->setCurrentIndex(n);
}
