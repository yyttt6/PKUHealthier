#include "recommend.h"
#include "qeventloop.h"
#include "qrandom.h"
#include "qtimer.h"

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

    vLayout->addLayout(finalLayout1);
    vLayout->addStretch(1);
    vLayout->setContentsMargins(15,15,15,15);
    vLayout->setSpacing(15);

    frame->setLayout(vLayout);
    frame->setObjectName("ff");
    frame->setStyleSheet("QFrame#ff{background-image:url(:/recommend/background.jpg);border-radius:10px;}");

    finalLayout->addWidget(frame);
    finalLayout->setContentsMargins(20,10,15,15);
    setLayout(finalLayout);
}

void Recommend::pku1(){  //在mainwindow中调用

    QEventLoop eventloop;
    QTimer::singleShot(3000, &eventloop, SLOT(quit()));
    eventloop.exec();  //等候3秒

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

    vLayout->insertLayout(1,finalLayout2);

    //********************

    QTimer::singleShot(1000, &eventloop, SLOT(quit()));
    eventloop.exec();

    label11->setStyleSheet("QLabel{font-family:微软雅黑;font-size:14px;background-color:rgb(249,231,159);}");
    label22->setStyleSheet("QLabel{font-family:微软雅黑;font-size:14px;background-color:rgb(249,231,159);}");

    Cafeteria* cafe=new Cafeteria;
    for (int i=0;i<=12;i++)
        cafeChoose->addItem(cafe->names[i]);

    cafeChoose->setStyleSheet("QComboBox{font-family:微软雅黑;font-size:14px;}");
    cafeChoose->setFixedSize(QSize(140,20));
    cafeChoose->setFocusPolicy(Qt::NoFocus);

    hhLayout1->addStretch(1);
    hhLayout1->addWidget(label11);
    hhLayout1->addWidget(cafeChoose);
    hhLayout1->addStretch(1);
    hhLayout1->addWidget(chooseButton1);
    hhLayout1->addSpacing(10);

    hhLayout2->addStretch(1);
    hhLayout2->addWidget(label22);
    hhLayout2->addStretch(1);
    hhLayout2->addWidget(chooseButton2);
    hhLayout2->addSpacing(10);

    line->setFrameShape(QFrame::HLine);
    line->setFixedWidth(315);
    line->setStyleSheet("QFrame{background-color:rgb(212,172,13);}");

    vvLayout->addLayout(hhLayout1);
    vvLayout->addWidget(line);
    vvLayout->addLayout(hhLayout2);
    vvLayout->setContentsMargins(10,10,10,10);
    vvLayout->setStretch(0,1);
    vvLayout->setStretch(2,1);

    chooseFrame->setLayout(vvLayout);
    chooseFrame->setFixedSize(QSize(330,100));
    chooseFrame->setStyleSheet("QFrame{border-radius:10px;background-color:rgb(249,231,159);}");

    chooseLayout->addWidget(chooseFrame);

    vLayout->insertLayout(2,chooseLayout);

    connect(chooseButton1,&QPushButton::clicked,this,&Recommend::choose1);
    connect(chooseButton2,&QPushButton::clicked,this,&Recommend::choose2);

}

void Recommend::choose1(){
    index=cafeChoose->currentIndex();
    result();
}

void Recommend::choose2(){
    index=100;
    result();
}

void Recommend::result(){
    vLayout->removeItem(chooseLayout);

    //********************

    numberLabel3->setStyleSheet("QLabel{font-family:Consolas;font-size:12px;color:gray;background-color:#f7f7f7;}");

    timeLabel3->setText(timeString());
    timeLabel3->setStyleSheet("QLabel{font-family:微软雅黑;font-size:12px;background-color:#f7f7f7;}");

    commentNumber->setText("2");

    hLayout3->addWidget(numberLabel3);
    hLayout3->addWidget(timeLabel3);
    hLayout3->addStretch(1);

    Cafeteria* cafe=new Cafeteria;
    if (index<50)
        dzText2->setText("[洞主] 那就"+cafe->names[index]+"吧~");
    else
        dzText2->setText("[洞主] 哪个食堂都行~");
    dzText2->setStyleSheet("QLabel{font-family:微软雅黑;font-size:15px;background-color:#f7f7f7;}");

    vLayout3->addLayout(hLayout3);
    vLayout3->addWidget(dzText2);
    vLayout3->setStretch(0,3);
    vLayout3->setStretch(1,5);

    frame3->setLayout(vLayout3);
    frame3->setFixedHeight(70);
    frame3->setStyleSheet("QFrame{border-color:#f7f7f7;border-radius:10px;background-color:#f7f7f7;}");

    finalLayout3->addWidget(frame3);

    vLayout->removeItem(chooseLayout);
    chooseFrame->setVisible(false);
    vLayout->insertLayout(2,finalLayout3);

    //********************

    QEventLoop eventloop;
    QTimer::singleShot(2000, &eventloop, SLOT(quit()));
    eventloop.exec();

    numberLabel4->setStyleSheet("QLabel{font-family:Consolas;font-size:12px;color:gray;background-color:rgb(171,235,198);}");

    timeLabel4->setText(timeString());
    timeLabel4->setStyleSheet("QLabel{font-family:微软雅黑;font-size:12px;background-color:rgb(171,235,198);}");

    commentNumber->setText("3");

    hLayout4->addWidget(numberLabel4);
    hLayout4->addWidget(timeLabel4);
    hLayout4->addStretch(1);

    Man* man=new Man;
    man->load();
    QString namestr="[PKUHealthier] 已开盒！是来自北京的"+QString(man->name[0]);
    if(man->gender==0)
        namestr+="小姐";
    else
        namestr+="先生";
    namestr+="吗^_^";
    pkuText2->setText(namestr);
    pkuText2->setStyleSheet("QLabel{font-family:微软雅黑;font-size:15px;background-color:rgb(171,235,198);}");

    vLayout4->addLayout(hLayout4);
    vLayout4->addWidget(pkuText2);
    vLayout4->setStretch(0,3);
    vLayout4->setStretch(1,5);

    frame4->setLayout(vLayout4);
    frame4->setFixedHeight(70);
    frame4->setStyleSheet("QFrame{border-color:rgb(171,235,198);border-radius:10px;background-color:rgb(171,235,198);}");

    finalLayout4->addWidget(frame4);

    vLayout->insertLayout(3,finalLayout4);

    //********************

    QTimer::singleShot(500, &eventloop, SLOT(quit()));
    eventloop.exec();

    numberLabel5->setStyleSheet("QLabel{font-family:Consolas;font-size:12px;color:gray;background-color:rgb(171,235,198);}");

    timeLabel5->setText(timeString());
    timeLabel5->setStyleSheet("QLabel{font-family:微软雅黑;font-size:12px;background-color:rgb(171,235,198);}");

    commentNumber->setText("4");

    hLayout5->addWidget(numberLabel5);
    hLayout5->addWidget(timeLabel5);
    hLayout5->addStretch(1);

    pkuText3->setStyleSheet("QLabel{font-family:微软雅黑;font-size:15px;background-color:rgb(171,235,198);}");

    QVector<Meal> ans;
    if(index<50){
        int seed=index;
        ans=cafe->recommend(*man,seed,&index);
    }
    else{
        std::time_t now = std::time(nullptr);
        std::tm* tm = std::localtime(&now);
        int seed=167+tm->tm_sec;
        QRandomGenerator prng(seed);
        do{
            int newseed = 123+prng.generate()%119;
            ans=cafe->recommend(*man,newseed,&index);
        }
        while(ans.empty());
        index+=100;
    }

    chosenId.clear();
    for (int i=0;i<ans[0].elements.size();i++){
        chosenId.append(ans[0].elements[i]->id);
    }

    cafe->load(index%100);
    dishstr="去"+cafe->names[index%100]+"吃——"+cafe->dishes[chosenId[0]-1].name;
    for (int i=1;i<chosenId.size();i++){
        dishstr+="、";
        dishstr+=cafe->dishes[chosenId[i]-1].name;
    }
    dishstr+="！";
    resultstr="预计摄入热量 "+QString::number(ans[0].energy)+" 千卡，"
                +"蛋白质 "+QString::number(ans[0].protein)+" 克，"
                +"脂肪 "+QString::number(ans[0].fat)+" 克，"
                +"共消费 "+QString::number(ans[0].money)+" 元~";

    dishText->setText(dishstr);
    dishText->setStyleSheet("QLabel{font-family:微软雅黑;font-size:15px;font-weight:bold;background-color:rgb(171,235,198);}");

    resultText->setText(resultstr);
    resultText->setStyleSheet("QLabel{font-family:微软雅黑;font-size:15px;font-weight:bold;background-color:rgb(171,235,198);}");

    vLayout5->addLayout(hLayout5);
    vLayout5->addWidget(pkuText3);
    vLayout5->addWidget(dishText);
    vLayout5->addWidget(resultText);
    vLayout5->addSpacing(5);
    vLayout5->setStretch(0,3);
    vLayout5->setStretch(1,4);
    vLayout5->setStretch(2,4);
    vLayout5->setStretch(3,4);

    frame5->setLayout(vLayout5);
    frame5->setFixedHeight(130);
    frame5->setStyleSheet("QFrame{border-color:rgb(171,235,198);border-radius:10px;background-color:rgb(171,235,198);}");

    finalLayout5->addWidget(frame5);

    vLayout->insertLayout(4,finalLayout5);

    //********************

    QTimer::singleShot(1000, &eventloop, SLOT(quit()));
    eventloop.exec();

    acceptButton->setStyleSheet("QPushButton{font-family:Verdana;color:#0000ff;font-size:15px;}");
    denyButton->setStyleSheet("QPushButton{font-family:微软雅黑;font-size:15px;}");

    hhhLayout->addStretch(1);
    hhhLayout->addWidget(acceptButton);
    hhhLayout->addSpacing(7);
    hhhLayout->addWidget(denyButton);
    hhhLayout->addStretch(1);
    hhhLayout->setContentsMargins(10,10,10,10);

    resultFrame->setLayout(hhhLayout);
    resultFrame->setFixedSize(QSize(340,55));
    resultFrame->setStyleSheet("QFrame{border-radius:10px;background-color:rgb(249,231,159);}");

    resultLayout->addWidget(resultFrame);

    vLayout->insertLayout(5,resultLayout);

    connect(denyButton,&QPushButton::clicked,this,&Recommend::deny);
}

void Recommend::deny(){

    resultFrame->setVisible(false);
    frame5->setVisible(false);
    commentNumber->setText("3");

    QEventLoop eventloop;
    QTimer::singleShot(2000, &eventloop, SLOT(quit()));
    eventloop.exec();

    Cafeteria* cafe=new Cafeteria;
    Man* man=new Man;
    man->load();

    QVector<Meal> ans;
    if(index<50){
        int seed=index;
        ans=cafe->recommend(*man,seed,&index);
    }
    else{
        std::time_t now = std::time(nullptr);
        std::tm* tm = std::localtime(&now);
        int seed=167+tm->tm_sec;
        QRandomGenerator prng(seed);
        do{
            int newseed = 123+prng.generate()%119;
            ans=cafe->recommend(*man,newseed,&index);
        }
        while(ans.empty());
        index+=100;
    }

    chosenId.clear();
    for (int i=0;i<ans[0].elements.size();i++){
        chosenId.append(ans[0].elements[i]->id);
    }

    cafe->load(index%100);
    dishstr="去"+cafe->names[index%100]+"吃——"+cafe->dishes[chosenId[0]-1].name;
    for (int i=1;i<chosenId.size();i++){
        dishstr+="、";
        dishstr+=cafe->dishes[chosenId[i]-1].name;
    }
    dishstr+="！";
    resultstr="预计摄入热量 "+QString::number(ans[0].energy)+" 千卡，"
                +"蛋白质 "+QString::number(ans[0].protein)+" 克，"
                +"脂肪 "+QString::number(ans[0].fat)+" 克，"
                +"共消费 "+QString::number(ans[0].money)+" 元~";

    dishText->setText(dishstr);
    resultText->setText(resultstr);

    frame5->setVisible(true);
    commentNumber->setText("4");

    QTimer::singleShot(1000, &eventloop, SLOT(quit()));
    eventloop.exec();
    resultFrame->setVisible(true);

}






void Recommend::refresh(){

}
