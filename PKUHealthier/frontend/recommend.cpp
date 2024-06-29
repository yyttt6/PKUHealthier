#include "recommend.h"
#include "qeventloop.h"
#include "qrandom.h"
#include "qtimer.h"

void refreshTime(QLabel* label,bool newlyCreated=false){ //是否强制初始化（新对话）
    QString s=label->text();
    if(s.length()==0 || newlyCreated){
        std::time_t now = std::time(nullptr);
        std::tm* tm = std::localtime(&now);
        std::string str(ctime(&now));
        QString monthstr=QString::number(1+tm->tm_mon);
        if(monthstr.length()<=1)
            monthstr="0"+monthstr;
        QString timestr="刚刚 "+monthstr+"-"+QString::fromStdString(str.substr(8,2))
                          +" "+QString::fromStdString(str.substr(11,5));
        label->setText(timestr);
    }
    else{
        std::time_t now = std::time(nullptr);
        std::tm* tm = std::localtime(&now);
        QString thattime=s.mid(s.length()-12,12);
        QString thatmin_str=s.mid(s.length()-2,2);
        int thatmin=thatmin_str.toInt();
        int thismin=tm->tm_min;
        if(thismin<thatmin)
            thismin+=60;
        if(thismin>thatmin){
            QString finalstr=QString::number(thismin-thatmin)+"分钟前"+thattime;
            label->setText(finalstr);
        }
    }
}

void wait(int ms){
    QEventLoop eventloop;
    QTimer::singleShot(ms, &eventloop, SLOT(quit()));
    eventloop.exec();
}

Recommend::Recommend(QWidget *parent)
    : QWidget{parent}
{
    //先设置所有格式

    //******************** dz1

    numberLabel1->setStyleSheet("QLabel{font-family:Consolas;font-size:12px;color:gray;background-color:#f7f7f7;}");
    timeLabel1->setStyleSheet("QLabel{font-family:微软雅黑;font-size:12px;background-color:#f7f7f7;}");
    commentNumber->setStyleSheet("QLabel{font-family:微软雅黑;font-size:12px;background-color:#f7f7f7;}");
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
    hLayout1->addSpacing(2);
    hLayout1->addWidget(timeLabel1);
    hLayout1->addStretch(1);
    hLayout1->addWidget(commentNumber);
    hLayout1->addWidget(commentImage);
    hLayout1->addSpacing(5);
    hLayout1->addWidget(starNumber);
    hLayout1->addWidget(starImage);
    hLayout1->setSpacing(4);

    dzText1->setStyleSheet("QLabel{font-family:微软雅黑;font-size:15px;}");

    vLayout1->addLayout(hLayout1);
    vLayout1->addWidget(dzText1);
    vLayout1->setStretch(0,2);
    vLayout1->setStretch(1,3);
    vLayout1->addSpacing(3);

    frame1->setLayout(vLayout1);
    frame1->setFixedHeight(70);
    frame1->setStyleSheet("QFrame{border-color:#f7f7f7;border-radius:10px;background-color:#f7f7f7;}");

    finalLayout1->addWidget(frame1);

    frame->setLayout(vLayout);
    frame->setObjectName("ff");
    frame->setStyleSheet("QFrame#ff{background-image:url(:/recommend/background.jpg);border-radius:10px;}");

    finalLayout->addWidget(frame);
    finalLayout->setContentsMargins(20,10,15,15);
    setLayout(finalLayout);

    //******************** start

    startButton->setStyleSheet("QPushButton{font-family:微软雅黑;font-size:15px;background-color:#e7e7e7;border-radius:10px;padding-left:5px;}"
                               "QPushButton:hover{text-decoration:underline;background-color:#fafafa;}");
    startButton->setIconSize(QSize(23,23));
    startButton->setFixedSize(QSize(150,35));

    startLayout->addStretch(1);
    startLayout->addWidget(startButton);
    startLayout->addStretch(1);
    startLayout->setContentsMargins(0,5,0,0);

    connect(startButton,&QPushButton::clicked,this,&Recommend::start);

    //******************** pku1

    numberLabel2->setStyleSheet("QLabel{font-family:Consolas;font-size:12px;color:gray;background-color:rgb(171,235,198);}");
    timeLabel2->setStyleSheet("QLabel{font-family:微软雅黑;font-size:12px;background-color:rgb(171,235,198);}");

    hLayout2->addWidget(numberLabel2);
    hLayout2->addWidget(timeLabel2);
    hLayout2->addStretch(1);

    pkuText1->setStyleSheet("QLabel{font-family:微软雅黑;font-size:15px;background-color:rgb(171,235,198);}");

    vLayout2->addLayout(hLayout2);
    vLayout2->addWidget(pkuText1);
    vLayout2->setStretch(0,2);
    vLayout2->setStretch(1,3);
    vLayout2->addSpacing(3);

    frame2->setLayout(vLayout2);
    frame2->setFixedHeight(70);
    frame2->setStyleSheet("QFrame{border-color:rgb(171,235,198);border-radius:10px;background-color:rgb(171,235,198);}");

    finalLayout2->addWidget(frame2);

    //******************** cafechoose

    label11->setStyleSheet("QLabel{font-family:微软雅黑;font-size:15px;background-color:rgb(249,231,159);}");
    label22->setStyleSheet("QLabel{font-family:微软雅黑;font-size:15px;background-color:rgb(249,231,159);}");

    Cafeteria* cafe=new Cafeteria;
    for (int i=0;i<=12;i++)
        cafeChoose->addItem(cafe->names[i]);

    cafeChoose->setStyleSheet("QComboBox{font-family:微软雅黑;font-size:15px;}");
    cafeChoose->setFixedSize(QSize(140,25));
    cafeChoose->setFocusPolicy(Qt::NoFocus);

    chooseButton1->setStyleSheet("QPushButton{font-size:14px;}");
    chooseButton2->setStyleSheet("QPushButton{font-size:14px;}");

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
    line->setFixedWidth(310);
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

    connect(chooseButton1,&QPushButton::clicked,this,&Recommend::choose1);
    connect(chooseButton2,&QPushButton::clicked,this,&Recommend::choose2);

    //******************** dz2

    numberLabel3->setStyleSheet("QLabel{font-family:Consolas;font-size:12px;color:gray;background-color:#f7f7f7;}");
    timeLabel3->setStyleSheet("QLabel{font-family:微软雅黑;font-size:12px;background-color:#f7f7f7;}");

    hLayout3->addWidget(numberLabel3);
    hLayout3->addWidget(timeLabel3);
    hLayout3->addStretch(1);

    dzText2->setStyleSheet("QLabel{font-family:微软雅黑;font-size:15px;background-color:#f7f7f7;}");

    vLayout3->addLayout(hLayout3);
    vLayout3->addWidget(dzText2);
    vLayout3->setStretch(0,2);
    vLayout3->setStretch(1,3);
    vLayout3->addSpacing(3);

    frame3->setLayout(vLayout3);
    frame3->setFixedHeight(70);
    frame3->setStyleSheet("QFrame{border-color:#f7f7f7;border-radius:10px;background-color:#f7f7f7;}");

    finalLayout3->addWidget(frame3);

    //******************** pku2

    numberLabel4->setStyleSheet("QLabel{font-family:Consolas;font-size:12px;color:gray;background-color:rgb(171,235,198);}");
    timeLabel4->setStyleSheet("QLabel{font-family:微软雅黑;font-size:12px;background-color:rgb(171,235,198);}");

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
    vLayout4->setStretch(0,2);
    vLayout4->setStretch(1,3);
    vLayout4->addSpacing(3);

    frame4->setLayout(vLayout4);
    frame4->setFixedHeight(70);
    frame4->setStyleSheet("QFrame{border-color:rgb(171,235,198);border-radius:10px;background-color:rgb(171,235,198);}");

    finalLayout4->addWidget(frame4);

    //******************** pku3

    numberLabel5->setStyleSheet("QLabel{font-family:Consolas;font-size:12px;color:gray;background-color:rgb(171,235,198);}");
    timeLabel5->setStyleSheet("QLabel{font-family:微软雅黑;font-size:12px;background-color:rgb(171,235,198);}");

    hLayout5->addWidget(numberLabel5);
    hLayout5->addWidget(timeLabel5);
    hLayout5->addStretch(1);

    pkuText3->setStyleSheet("QLabel{font-family:微软雅黑;font-size:15px;background-color:rgb(171,235,198);}");
    dishText->setStyleSheet("QLabel{font-family:微软雅黑;font-size:15px;font-weight:bold;background-color:rgb(171,235,198);}");
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

    //******************** result

    acceptButton->setStyleSheet("QPushButton{font-family:Verdana;color:#0000ff;font-size:15px;}"
                                "QPushButton:hover{text-decoration:underline;}");
    denyButton->setStyleSheet("QPushButton{font-family:微软雅黑;color:#595959;font-size:15px;padding-left:5px;padding-right:1px;}"
                              "QPushButton:hover{text-decoration:underline;}");
    restartButton->setStyleSheet("QPushButton{font-family:微软雅黑;color:#595959;font-size:15px;padding-left:5px;padding-right:1px;}"
                                 "QPushButton:hover{text-decoration:underline;}");

    acceptButton->setFixedHeight(30);
    denyButton->setFixedHeight(30);
    restartButton->setFixedHeight(30);

    hhhLayout->addStretch(1);
    hhhLayout->addWidget(acceptButton);
    hhhLayout->addSpacing(7);
    hhhLayout->addWidget(denyButton);
    hhhLayout->addSpacing(7);
    hhhLayout->addWidget(restartButton);
    hhhLayout->addStretch(1);
    hhhLayout->setContentsMargins(10,10,10,10);

    resultFrame->setLayout(hhhLayout);
    resultFrame->setFixedWidth(390);
    resultFrame->setStyleSheet("QFrame{border-radius:10px;background-color:rgb(249,231,159);}");

    resultLayout->addWidget(resultFrame);

    //acceptButton在mainwindow里连接jumpmenu
    connect(denyButton,&QPushButton::clicked,this,&Recommend::deny);
    connect(restartButton,&QPushButton::clicked,this,&Recommend::restart);


    //******************** final

    vLayout->addStretch(1);
    vLayout->setContentsMargins(15,15,15,15);
    vLayout->setSpacing(15);

    vLayout->insertLayout(0,finalLayout1);
    frame1->setVisible(false);
    //startLayout
    vLayout->insertLayout(1,finalLayout2);
    frame2->setVisible(false);
    //chooseLayout
    vLayout->insertLayout(2,finalLayout3);
    frame3->setVisible(false);
    vLayout->insertLayout(3,finalLayout4);
    frame4->setVisible(false);
    vLayout->insertLayout(4,finalLayout5);
    frame5->setVisible(false);
    vLayout->insertLayout(5,resultLayout);
    resultFrame->setVisible(false);

    //******************** dz1

    refreshTime(timeLabel1,true);
    starNumber->setText("1");
    commentNumber->setVisible(false);
    commentImage->setVisible(false);
    frame1->setVisible(true);

    vLayout->insertLayout(1,startLayout);

}

void Recommend::start(){

    startButton->setVisible(false);
    if(index==-1)
        vLayout->removeItem(startLayout);

    //******************** pku1

    wait(3000);

    refreshTime(timeLabel1);
    refreshTime(timeLabel2,true);
    starNumber->setText("2");
    commentNumber->setText("1");
    commentNumber->setVisible(true);
    commentImage->setVisible(true);
    frame2->setVisible(true);

    //******************** cafechoose

    wait(1000);

    if(index==-1)
        vLayout->insertLayout(2,chooseLayout);
    chooseFrame->setVisible(true);

}

void Recommend::choose1(){
    index=cafeChoose->currentIndex();
    chooseresult();
}

void Recommend::choose2(){
    index=100;
    chooseresult();
}

void Recommend::chooseresult(){

    chooseFrame->setVisible(false);
    if(index==-1)
        vLayout->removeItem(chooseLayout);

    //******************** dz2

    refreshTime(timeLabel1);
    refreshTime(timeLabel2);
    refreshTime(timeLabel3,true);
    commentNumber->setText("2");

    if (index<50){
        Cafeteria* cafe=new Cafeteria;
        dzText2->setText("[洞主] 那就"+cafe->names[index]+"吧~");
    }
    else
        dzText2->setText("[洞主] 暂时没有想好明确的食堂！");

    frame3->setVisible(true);

    //******************** pku2

    wait(2000);

    refreshTime(timeLabel1);
    refreshTime(timeLabel2);
    refreshTime(timeLabel3);
    refreshTime(timeLabel4,true);
    commentNumber->setText("3");

    frame4->setVisible(true);

    recommendresult();
}

void Recommend::recommendresult(){

    //******************** pku3

    wait(500);

    refreshTime(timeLabel1);
    refreshTime(timeLabel2);
    refreshTime(timeLabel3);
    refreshTime(timeLabel4);
    refreshTime(timeLabel5,true);
    commentNumber->setText("4");

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
    dishText->setText(dishstr);

    resultstr="预计摄入热量 "+QString::number(ans[0].energy)+" 千卡，"
                +"蛋白质 "+QString::number(ans[0].protein)+" 克，"
                +"脂肪 "+QString::number(ans[0].fat)+" 克，"
                +"共消费 "+QString::number(ans[0].money)+" 元~";
    resultText->setText(resultstr);

    frame5->setVisible(true);

    //******************** result

    wait(1000);

    resultFrame->setVisible(true);

    QVector<QString> newach=man->check_achievement();
    man->save();
    if(!newach.empty())
        emit hasnewach(newach);

}

void Recommend::deny(){
    Man* man=new Man;
    man->load();
    man->foodRec.reject_number++;
    man->save();

    frame5->setVisible(false);
    resultFrame->setVisible(false);

    commentNumber->setText("3");

    recommendresult();
}

void Recommend::restart(){
    refreshTime(timeLabel1,true);
    frame2->setVisible(false);
    frame3->setVisible(false);
    frame4->setVisible(false);
    frame5->setVisible(false);
    resultFrame->setVisible(false);

    starNumber->setText("1");
    commentNumber->setVisible(false);
    commentImage->setVisible(false);
    startButton->setVisible(true);
}

