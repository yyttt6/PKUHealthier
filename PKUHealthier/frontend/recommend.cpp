#include "recommend.h"

QString timeString(){
    std::time_t now = std::time(nullptr);
    std::tm* tm = std::localtime(&now);
    std::string str(ctime(&now));
    QString monthstr;
    if(tm->tm_mon<=8)
        monthstr="0"+QString::number(1+tm->tm_mon);
    else
        monthstr=QString::number(1+tm->tm_mon);
    QString timestr="刚刚 "+monthstr+"-"+QString::fromStdString(str.substr(8,2))
                      +" "+QString::fromStdString(str.substr(11,5));
    return timestr;
}


Recommend::Recommend(QWidget *parent)
    : QWidget{parent}
{
    numberLabel1->setStyleSheet("QLabel{font-family:Consolas;font-size:12px;color:gray;background-color:#f7f7f7;}");

    timeLabel1->setText(timeString());
    timeLabel1->setStyleSheet("QLabel{font-family:微软雅黑;font-size:12px;background-color:#f7f7f7;}");

    commentNumber->setText("1");
    commentNumber->setStyleSheet("QLabel{font-family:微软雅黑;font-size:12px;background-color:#f7f7f7;}");

    starNumber->setText("1");
    starNumber->setStyleSheet("QLabel{font-family:微软雅黑;font-size:12px;background-color:#f7f7f7;}");

    commentImage->setPixmap(*commentPixmap);
    commentImage->setFixedSize(QSize(16,16));
    commentImage->setScaledContents(true);
    commentImage->setStyleSheet("QLabel{background-color:#f7f7f7;}");

    starImage->setPixmap(*starPixmap);
    starImage->setFixedSize(QSize(16,16));
    starImage->setScaledContents(true);
    starImage->setStyleSheet("QLabel{background-color:#f7f7f7;}");

    hLayout1->addWidget(numberLabel1);
    hLayout1->addWidget(timeLabel1);
    hLayout1->addStretch(1);
    hLayout1->addWidget(commentNumber);
    hLayout1->addWidget(commentImage);
    hLayout1->addSpacing(5);
    hLayout1->addWidget(starNumber);
    hLayout1->addWidget(starImage);

    commentNumber->setVisible(false);
    commentImage->setVisible(false);

    dzText1->setStyleSheet("QLabel{font-family:微软雅黑;font-size:15px;}");

    vLayout1->addLayout(hLayout1);
    vLayout1->addWidget(dzText1);
    vLayout1->setStretch(0,3);
    vLayout1->setStretch(1,5);

    frame1->setLayout(vLayout1);
    frame1->setFixedHeight(70);
    frame1->setStyleSheet("QFrame{border-color:#f7f7f7;border-radius:10px;background-color:#f7f7f7;}");

    finalLayout1->addWidget(frame1);

    button1->setFixedSize(QSize(70,30));
    hhLayout->addStretch(1);
    hhLayout->addWidget(button1);
    hhLayout->addStretch(1);

    vLayout->addLayout(finalLayout1);
    vLayout->addLayout(hhLayout);
    vLayout->addStretch(1);
    vLayout->setContentsMargins(10,10,10,10);
    vLayout->setSpacing(15);
    frame->setLayout(vLayout);
    frame->setObjectName("ff");
    frame->setStyleSheet("QFrame#ff{background-image:url(:/recommend/background.jpg);border-radius:10px;}");
    finalLayout->addWidget(frame);
    finalLayout->setContentsMargins(20,10,15,15);
    setLayout(finalLayout);

    connect(button1,&QPushButton::clicked,this,&Recommend::pku1);
}

void Recommend::pku1(){


    numberLabel2->setStyleSheet("QLabel{font-family:Consolas;font-size:12px;color:gray;background-color:rgb(171,235,198);}");

    timeLabel2->setText(timeString());
    timeLabel2->setStyleSheet("QLabel{font-family:微软雅黑;font-size:12px;background-color:rgb(171,235,198);}");

    commentNumber->setVisible(true);
    commentImage->setVisible(true);

    starNumber->setText("2");

    hLayout2->addWidget(numberLabel2);
    hLayout2->addWidget(timeLabel2);
    hLayout2->addStretch(1);

    pkuText1->setStyleSheet("QLabel{font-family:微软雅黑;font-size:15px;background-color:rgb(171,235,198);}");

    vLayout2->addLayout(hLayout2);
    vLayout2->addWidget(pkuText1);
    vLayout2->setStretch(0,3);
    vLayout2->setStretch(1,5);

    frame2->setLayout(vLayout2);
    frame2->setFixedHeight(70);
    frame2->setStyleSheet("QFrame{border-color:rgb(171,235,198);border-radius:10px;background-color:rgb(171,235,198);}");

    finalLayout2->addWidget(frame2);
    vLayout->removeItem(hhLayout);
    vLayout->insertLayout(1,finalLayout2);

    //***********

    numberLabel3->setStyleSheet("QLabel{font-family:Consolas;font-size:12px;color:gray;background-color:rgb(171,235,198);}");

    timeLabel3->setText(timeString());
    timeLabel3->setStyleSheet("QLabel{font-family:微软雅黑;font-size:12px;background-color:rgb(171,235,198);}");

    commentNumber->setText("2");

    hLayout3->addWidget(numberLabel3);
    hLayout3->addWidget(timeLabel3);
    hLayout3->addStretch(1);

    /*
    Cafeteria* cafe=new Cafeteria;
    Man* man=new Man;
    man->load();
    QVector<Meal> ans;
    int index=0;
    do{
        ans=cafe->recommend(*man,0,&index);
    }
    while(ans.empty());
    */

    vLayout3->addLayout(hLayout3);
    vLayout3->setStretch(0,3);

    QLabel* label[100];
    label[0]=new QLabel("我推荐您去农园食堂一层吃：");
    label[0]->setStyleSheet("QLabel{font-family:微软雅黑;font-size:15px;background-color:rgb(171,235,198);}");
    vLayout3->addWidget(label[0]);
    vLayout3->setStretch(1,4);

    label[1]=new QLabel("       鸡汤馄饨面");
    label[1]->setStyleSheet("QLabel{font-family:微软雅黑;font-size:15px;background-color:rgb(171,235,198);}");
    vLayout3->addWidget(label[1]);
    vLayout3->setStretch(2,4);

    label[2]=new QLabel("       原味地道肠");
    label[2]->setStyleSheet("QLabel{font-family:微软雅黑;font-size:15px;background-color:rgb(171,235,198);}");
    vLayout3->addWidget(label[2]);
    vLayout3->setStretch(3,4);


    frame3->setLayout(vLayout3);
    frame3->setFixedHeight(120);
    frame3->setStyleSheet("QFrame{border-color:rgb(171,235,198);border-radius:10px;background-color:rgb(171,235,198);}");

    finalLayout3->addWidget(frame3);
    vLayout->insertLayout(2,finalLayout3);

}



void Recommend::refresh(){

}
