#include "sports.h"
#include "./backend/man.h"
#include <ctime>

double params[10]={12.25, 9.8, 8.6, 9.8, 7.35, 9.8, 4.9, 4.9, 6.126, 9.8};

Sports::SingleSport::SingleSport(QWidget *parent, int index)
    : QWidget{parent}, idx(index)
{
    switch(idx){
    case 0:movie=new QMovie(":/sports/running.gif");break;
    case 1:movie=new QMovie(":/sports/riding.gif");break;
    case 2:movie=new QMovie(":/sports/swimming.gif");break;
    case 3:movie=new QMovie(":/sports/climbing.gif");break;
    case 4:movie=new QMovie(":/sports/basketball.gif");break;
    case 5:movie=new QMovie(":/sports/football.gif");break;
    case 6:movie=new QMovie(":/sports/volleyball.png");break;
    case 7:movie=new QMovie(":/sports/pingpong.png");break;
    case 8:movie=new QMovie(":/sports/badminton.png");break;
    case 9:movie=new QMovie(":/sports/tennis.png");break;
    default:break;
    }

    switch(idx){
    case 0:nameLabel->setText("跑步");break;
    case 1:nameLabel->setText("骑行");break;
    case 2:nameLabel->setText("游泳");break;
    case 3:nameLabel->setText("攀岩");break;
    case 4:nameLabel->setText("篮球");break;
    case 5:nameLabel->setText("足球");break;
    case 6:nameLabel->setText("排球");break;
    case 7:nameLabel->setText("乒乓球");break;
    case 8:nameLabel->setText("羽毛球");break;
    case 9:nameLabel->setText("网球");break;
    default:break;
    }

    nameLabel->setStyleSheet("QLabel{font-size:18px;font-family:楷体;font-weight:bold;}");

    param=params[idx];

    movieLabel->setMovie(movie);
    if (idx<=3)
        movieLabel->setFixedSize(QSize(120,120));
    else
        movieLabel->setFixedSize(QSize(100,100));
    movieLabel->setScaledContents(true);

    spinBox->setRange(0, 600);
    spinBox->setFixedSize(QSize(100,30));

    hhLayout->addWidget(textLabel);
    hhLayout->addWidget(spinBox);

    recordLayout->addStretch(1);
    recordLayout->addWidget(recordButton);

    calcLayout->addWidget(nameLabel);
    calcLayout->addLayout(hhLayout);
    calcLayout->addWidget(autoCalc);
    calcLayout->addSpacing(10);
    calcLayout->addLayout(recordLayout);

    hLayout->addWidget(movieLabel);
    hLayout->addStretch(1);
    hLayout->addLayout(calcLayout);
    if(idx<=3)
        hLayout->setContentsMargins(15,20,20,20);
    else
        hLayout->setContentsMargins(25,20,20,20);

    frame->setLayout(hLayout);
    frame->setFixedSize(QSize(400,160));
    frame->setObjectName("frameframe");
    frame->setStyleSheet("QFrame#frameframe{border-style:solid;border-width:2px;border-color:rgb(52,152,219);border-radius:10px;}");

    finalLayout->addWidget(frame);
    setLayout(finalLayout);

    movie->start();
    movie->stop();

    connect(spinBox,&QSpinBox::valueChanged,this,&SingleSport::refresh);
    connect(recordButton,&QPushButton::clicked,this,&SingleSport::save);
    connect(movie,&QMovie::finished,this,&SingleSport::notice);

    refresh();
}

void Sports::SingleSport::refresh(){
    autoCalc->setText("（约消耗 "+QString::number(param*spinBox->value())+" 千卡能量）");
    if (spinBox->value()==0){
        recordButton->setEnabled(false);
        recordButton->setStyleSheet("color:gray;");
    }
    else{
        recordButton->setEnabled(true);
        recordButton->setStyleSheet("color:black;");
    }
}

QString _getTimeString(){
    std::time_t now = std::time(nullptr);
    std::tm* tm = std::localtime(&now);
    std::string str(ctime(&now));
    QString timestr= QString::number(1900+tm->tm_year)+"年"
                      +QString::number(1+tm->tm_mon)+"月"
                      +QString::number(tm->tm_mday)+"日"
                      +QString::fromStdString(str.substr(11,8));
    return timestr;
}

void Sports::SingleSport::save(){
    movie->start();
    Man* man=new Man;
    man->load();
    int t=spinBox->value();

    switch(idx){
    case 0:man->sptRec.week_run_vec.append(qMakePair(_getTimeString(),t));break;
    case 1:man->sptRec.week_rid_vec.append(qMakePair(_getTimeString(),t));break;
    case 2:man->sptRec.week_swi_vec.append(qMakePair(_getTimeString(),t));break;
    case 3:man->sptRec.week_cli_vec.append(qMakePair(_getTimeString(),t));break;
    case 4:man->sptRec.week_bas_vec.append(qMakePair(_getTimeString(),t));break;
    case 5:man->sptRec.week_foo_vec.append(qMakePair(_getTimeString(),t));break;
    case 6:man->sptRec.week_vol_vec.append(qMakePair(_getTimeString(),t));break;
    case 7:man->sptRec.week_pin_vec.append(qMakePair(_getTimeString(),t));break;
    case 8:man->sptRec.week_bad_vec.append(qMakePair(_getTimeString(),t));break;
    case 9:man->sptRec.week_ten_vec.append(qMakePair(_getTimeString(),t));break;
    default:break;
    }

    switch(idx){
    case 0:man->sptRec.week_running_time+=t;break;
    case 1:man->sptRec.week_riding_time+=t;break;
    case 2:man->sptRec.week_swimming_time+=t;break;
    case 3:man->sptRec.week_climbing_time+=t;break;
    case 4:man->sptRec.week_basketball_time+=t;break;
    case 5:man->sptRec.week_football_time+=t;break;
    case 6:man->sptRec.week_volleyball_time+=t;break;
    case 7:man->sptRec.week_pingpong_time+=t;break;
    case 8:man->sptRec.week_badminton_time+=t;break;
    case 9:man->sptRec.week_tennis_time+=t;break;
    default:break;
    }

    switch(idx){
    case 0:man->sptRec.running_time+=t;break;
    case 1:man->sptRec.riding_time+=t;break;
    case 2:man->sptRec.swimming_time+=t;break;
    case 3:man->sptRec.climbing_time+=t;break;
    case 4:man->sptRec.basketball_time+=t;break;
    case 5:man->sptRec.football_time+=t;break;
    case 6:man->sptRec.volleyball_time+=t;break;
    case 7:man->sptRec.pingpong_time+=t;break;
    case 8:man->sptRec.badminton_time+=t;break;
    case 9:man->sptRec.tennis_time+=t;break;
    default:break;
    }

    man->save();

}

void Sports::SingleSport::notice(){

    QDialog* dialog=new QDialog;
    QVBoxLayout* layout = new QVBoxLayout(dialog);
    dialog->setWindowTitle("记录成功！");
    dialog->setStyleSheet("background:rgb(242,243,244);");

    layout->addWidget(new QLabel("运动记录成功！"));
    layout->addWidget(new QLabel("本次您进行运动 “"+nameLabel->text()+"” "+QString::number(spinBox->value())+" 分钟，"));
    layout->addWidget(new QLabel("约消耗 "+QString::number(param*spinBox->value())+" 千卡能量~"));

    layout->addSpacing(40);

    QPushButton* Button=new QPushButton("确认");
    connect(Button,&QPushButton::clicked,dialog,&QDialog::close);
    QHBoxLayout* hhLayout=new QHBoxLayout;
    hhLayout->addSpacing(200);
    hhLayout->addWidget(Button);
    layout->addLayout(hhLayout);

    layout->setSpacing(10);
    dialog->setStyleSheet("QLabel{font-size:16px;}");
    layout->setContentsMargins(20,20,20,20);

    dialog->exec();

    spinBox->setValue(0);
    refresh();
}

Sports::Sports(QWidget *parent)
    : QWidget{parent}
{
    for(int i=0;i<10;i++)
        gLayout->addWidget(new SingleSport(this,i),i/2,i%2);
    gLayout->setVerticalSpacing(20);
    gLayout->setContentsMargins(0,0,10,20);
    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);
    finalLayout->addWidget(scrollArea);
    finalLayout->setContentsMargins(25,20,15,20);
}

void Sports::refresh(){

}
