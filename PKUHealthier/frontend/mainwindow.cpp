#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget{parent}
{
    QWidget::setAttribute(Qt::WA_Hover, true);
    resize(1050,650);
    setMinimumSize(1000,620);
    setStyleSheet("background:rgb(242,243,244);");
    setWindowTitle("PKUHealthier-首页");
    setWindowIcon(QIcon(":/mainwindow/pku.png"));

    //检查是不是新的一周
    Man* man=new Man;
    man->load();
    man->reset();

    for (int i=0;i<7;i++)
        button[i]=new QPushButton;

    button[0]->setIcon(QIcon(":/mainwindow/home_icon.png"));
    button[1]->setIcon(QIcon(":/mainwindow/recommend_icon.png"));
    button[2]->setIcon(QIcon(":/mainwindow/dish_icon.png"));
    button[3]->setIcon(QIcon(":/mainwindow/sport_icon.png"));
    button[4]->setIcon(QIcon(":/mainwindow/record_icon.png"));
    button[5]->setIcon(QIcon(":/mainwindow/achive_icon.png"));
    button[6]->setIcon(QIcon(":/mainwindow/profile_icon.png"));

    for (int i=0;i<7;i++){
        button[i]->setFixedSize(60,60);
        button[i]->setIconSize(QSize(50,50));
        leftlist->addWidget(button[i]);
    }

    leftlist->setSpacing(10);
    leftlist->insertStretch(6,1);
    leftlist->setContentsMargins(10,5,0,10);
    finalLayout->addLayout(leftlist);

    connect(button[0],&QPushButton::clicked,this,&MainWindow::changePage0);
    connect(button[1],&QPushButton::clicked,this,&MainWindow::changePage1);
    connect(button[2],&QPushButton::clicked,this,&MainWindow::changePage2);
    connect(button[3],&QPushButton::clicked,this,&MainWindow::changePage3);
    connect(button[4],&QPushButton::clicked,this,&MainWindow::changePage4);
    connect(button[5],&QPushButton::clicked,this,&MainWindow::changePage5);
    connect(button[6],&QPushButton::clicked,this,&MainWindow::changePage6);

    rightpage->addWidget(w0);
    rightpage->addWidget(w1);
    rightpage->addWidget(w2);
    rightpage->addWidget(w3);
    rightpage->addWidget(w4);
    rightpage->addWidget(w5);
    rightpage->addWidget(w6);

    connect(w1->acceptButton,&QPushButton::clicked,this,&MainWindow::jumpMenu);

    finalLayout->addWidget(rightpage);
    setLayout(finalLayout);

    changePage0();

    //成就检查
    connect(w1,&Recommend::hasnewach,this,&MainWindow::notice);
    connect(w2,&Menu::hasnewach,this,&MainWindow::notice);
    connect(w3,&Sports::hasnewach,this,&MainWindow::notice);

}

void MainWindow::list_refresh(int n){
    button[n]->setStyleSheet("QPushButton{background-color:rgb(192,57,43);border:none;border-radius:7px;}"
                             "QPushButton:hover{background-color:rgb(192,57,43);}"
                             "QPushButton:pressed{background-color:rgb(192,57,43);}");
    for (int i=0;i<7;i++){
        if (i!=n)
            button[i]->setStyleSheet("QPushButton{background-color:rgb(242,243,244);border:none;border-radius:7px;}"
                                     "QPushButton:hover{background-color:rgb(241,148,138);}"
                                     "QPushButton:pressed{background-color:rgb(192,57,43);}");
    }
}

void MainWindow::changePage0(){
    list_refresh(0);
    setWindowTitle("PKUHealthier-主页");
    rightpage->removeWidget(w0);
    w0=new Home(this);
    rightpage->insertWidget(0,w0);
    rightpage->setCurrentIndex(0);
}

void MainWindow::changePage1(){
    list_refresh(1);
    setWindowTitle("PKUHealthier-食谱推荐");
    rightpage->setCurrentIndex(1);
}

void MainWindow::changePage2(){
    list_refresh(2);
    setWindowTitle("PKUHealthier-饮食记录和评价");
    rightpage->setCurrentIndex(2);
}

void MainWindow::changePage3(){
    list_refresh(3);
    setWindowTitle("PKUHealthier-运动打卡");
    rightpage->setCurrentIndex(3);
}

void MainWindow::changePage4(){
    list_refresh(4);
    setWindowTitle("PKUHealthier-饮食和运动记录");
    rightpage->removeWidget(w4);
    w4=new Records(this);
    rightpage->insertWidget(4,w4);
    rightpage->setCurrentIndex(4);
}

void MainWindow::changePage5(){
    list_refresh(5);
    setWindowTitle("PKUHealthier-成就");
    w5->refresh();
    rightpage->setCurrentIndex(5);
}

void MainWindow::changePage6(){
    list_refresh(6);
    setWindowTitle("PKUHealthier-个人信息设置");
    w6->refresh();
    rightpage->setCurrentIndex(6);
}

void MainWindow::jumpMenu(){
    changePage2();
    int idx=w1->index%100;
    QVector<int> chosen=w1->chosenId;

    w2->cafeBox->setCurrentIndex(idx);
    Menu::SinglePage* pp=w2->page[idx];
    pp->cancelAll();

    for (int i=0;i<chosen.size();i++){
        switch(pp->cafe->dishes[chosen[i]-1].type){
        case 0:
            for (int j=0;j<pp->stapleDishes.size();j++){
                if (pp->stapleDishes[j]->dish->id==chosen[i]){
                    pp->stapleDishes[j]->selected_change();
                    break;
                }
            }
            break;
        case 1:
            for (int j=0;j<pp->recipeDishes.size();j++){
                if (pp->recipeDishes[j]->dish->id==chosen[i]){
                    pp->recipeDishes[j]->selected_change();
                    break;
                }
            }
            break;
        case 2:
            for (int j=0;j<pp->dessertDishes.size();j++){
                if (pp->dessertDishes[j]->dish->id==chosen[i]){
                    pp->dessertDishes[j]->selected_change();
                    break;
                }
            }
            break;
        case 3:
            for (int j=0;j<pp->setmealDishes.size();j++){
                if (pp->setmealDishes[j]->dish->id==chosen[i]){
                    pp->setmealDishes[j]->selected_change();
                    break;
                }
            }
            break;
        default:break;
        }
    }
}

void MainWindow::notice(QVector<QString> newach){

    QDialog* dialog=new QDialog;
    QVBoxLayout* layout = new QVBoxLayout(dialog);
    dialog->setWindowTitle("获得新成就！");
    dialog->setStyleSheet("background:rgb(242,243,244);");

    QLabel* label1=new QLabel("恭喜您获得新成就：");
    label1->setStyleSheet("QLabel{font-size:14px;}");
    layout->addWidget(label1);

    QLabel* achlabel[20];
    for (int i=0;i<newach.length();i++){
        achlabel[i]=new QLabel(newach[i]);
        achlabel[i]->setStyleSheet("QLabel{font-size:16px;font-weight:bold;}");
        achlabel[i]->setAlignment(Qt::AlignHCenter);
        layout->addWidget(achlabel[i]);
    }

    layout->addSpacing(15);
    QLabel* label2=new QLabel("点击“前往”可前往成就页查看~");
    label2->setStyleSheet("QLabel{font-size:14px;}");
    layout->addWidget(label2);

    QPushButton* acceptButton=new QPushButton("确认");
    acceptButton->setStyleSheet("QPushButton{font-size:14px;}");
    connect(acceptButton,&QPushButton::clicked,dialog,&QDialog::close);

    QPushButton* jumpButton=new QPushButton("前往");
    jumpButton->setStyleSheet("QPushButton{font-size:14px;}");
    connect(jumpButton,&QPushButton::clicked,dialog,&QDialog::close);
    connect(jumpButton,&QPushButton::clicked,this,&MainWindow::changePage5);

    QHBoxLayout* hhLayout=new QHBoxLayout;
    hhLayout->addStretch(1);
    hhLayout->addSpacing(250);
    hhLayout->addWidget(acceptButton);
    hhLayout->addSpacing(20);
    hhLayout->addWidget(jumpButton);

    layout->addSpacing(40);
    layout->addStretch(1);
    layout->addLayout(hhLayout);

    layout->setSpacing(10);
    layout->setContentsMargins(20,20,20,20);

    dialog->exec();

}
