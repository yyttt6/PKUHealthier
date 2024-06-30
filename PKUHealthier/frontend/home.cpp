#include "home.h"
#include <ctime>
#include <QDebug>
#include <map>
#include <QVector2D>
#include <algorithm>

struct WeekSpt
{
    QString name;
    double time, cost;

    WeekSpt(QString _name, double _time, double _cost) : name(_name), time(_time), cost(_cost) {}
};

double costenergy[10]={12.25, 9.8, 8.6, 9.8, 7.35, 9.8, 4.9, 4.9, 6.126, 9.8};

QString timeString(std::tm* now_tm) {
    int hour = now_tm->tm_hour;
    if (hour >= 0 && hour <= 5) return "凌晨了，该休息了~";
    if (hour >= 6 && hour <= 8) return "早上好！";
    if (hour >= 9 && hour <= 11) return "上午好！";
    if (hour == 12) return "中午好！";
    if (hour >= 13 && hour <= 18) return "下午好！";
    return "晚上好~";
}

Home::Home(QWidget *parent)
    : QWidget{parent}
{
    User->load();

    photoLabel->setFrameStyle(QFrame::Box|QFrame::Sunken);
    photoLabel->setPixmap(*photo);
    photoLabel->setMaximumSize(QSize(50, 50));
    photoLabel->setScaledContents(true);
    photoLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    std::time_t now = std::time(nullptr);
    std::tm* now_tm = std::localtime(&now);
    QString helloText = timeString(now_tm);
    helloLabel->setText(helloText + User->name);
    helloLabel->setStyleSheet("font-size:14px;");

    sportChart->setTitle("本周时长前三的运动");
    sportChart->setAnimationOptions(QChart::SeriesAnimations);
    sportView->setRenderHint(QPainter::Antialiasing);

    foodChart->setTitle("最近五餐摄入");
    foodChart->setAnimationOptions(QChart::SeriesAnimations);
    foodView->setRenderHint(QPainter::Antialiasing);

    sportTimeSet();
    foodLineSet();

    QPen engPen = engLine->pen();
    QPen protPen = protLine->pen();
    QPen fatPen = fatLine->pen();
    engPen.setColor(Qt::red);
    protPen.setColor(Qt::blue);
    fatPen.setColor(Qt::green);

    sportSerie->append(sportTime);
    costSerie->append(energyCost);

    sportChart->removeAllSeries();
    sportChart->addSeries(sportSerie);
    sportChart->addSeries(costSerie);
    foodChart->removeAllSeries();
    foodChart->addSeries(engLine);
    foodChart->addSeries(protLine);
    foodChart->addSeries(fatLine);

    sportAxisX->append(sportAxisText);
    sportChart->addAxis(sportAxisX, Qt::AlignBottom);
    foodChart->addAxis(foodAxisX, Qt::AlignBottom);

    sportSerie->attachAxis(sportAxisX);
    engLine->attachAxis(foodAxisX);
    protLine->attachAxis(foodAxisX);
    fatLine->attachAxis(foodAxisX);

    sportAxisX->setRange(sportAxisText.at(0), sportAxisText.at(sportAxisText.count() - 1));
    foodAxisX->setRange(1, 5);
    foodAxisX->setTickCount(5);
    foodAxisX->setLabelFormat("%d");

    sportAxisY->setTitleText("时间/分钟");
    sportAxisY->setTickCount(7);
    sportAxisY->setLabelFormat("%d");
    costAxisY->setTitleText("能量/千卡");
    costAxisY->setTickCount(7);
    engAxisY->setRange(0, 1200);
    engAxisY->setTitleText("热量/千卡");
    engAxisY->setTickCount(7);
    otherAxisY->setRange(0, 90);
    otherAxisY->setTitleText("质量/克");
    otherAxisY->setTickCount(7);

    sportChart->addAxis(sportAxisY, Qt::AlignLeft);
    sportChart->addAxis(costAxisY, Qt::AlignRight);
    foodChart->addAxis(engAxisY, Qt::AlignLeft);
    foodChart->addAxis(otherAxisY, Qt::AlignRight);

    sportSerie->attachAxis(sportAxisY);
    costSerie->attachAxis(costAxisY);
    engLine->attachAxis(engAxisY);
    protLine->attachAxis(otherAxisY);
    fatLine->attachAxis(otherAxisY);

    sportChart->legend()->setVisible(true);
    sportChart->legend()->setAlignment(Qt::AlignBottom);
    foodChart->legend()->setVisible(true);
    foodChart->legend()->setAlignment(Qt::AlignBottom);

    helloLayout->addSpacing(10);
    helloLayout->addWidget(photoLabel);
    helloLayout->addSpacing(2);
    helloLayout->addWidget(helloLabel);

    setBestDish();
    fdPrfText1->setAlignment(Qt::AlignHCenter);
    fdPrfText1->setStyleSheet("font-size:20px;background:transparent;");
    fdPrfText2->setAlignment(Qt::AlignHCenter);
    fdPrfText2->setStyleSheet("font-size:20px;font-weight:bold;background:transparent;");
    cafePrfText1->setAlignment(Qt::AlignHCenter);
    cafePrfText1->setStyleSheet("font-size:20px;background:transparent;");
    cafePrfText2->setAlignment(Qt::AlignHCenter);
    cafePrfText2->setStyleSheet("font-size:20px;font-weight:bold;background:transparent;");

    foodPrefer->addStretch(5);
    foodPrefer->addWidget(fdPrfText1);
    foodPrefer->addStretch(1);
    foodPrefer->addWidget(fdPrfText2);
    foodPrefer->addStretch(2);
    foodPrefer->addWidget(cafePrfText1);
    foodPrefer->addStretch(1);
    foodPrefer->addWidget(cafePrfText2);
    foodPrefer->addStretch(5);

    foodFrame->setLayout(foodPrefer);
    foodFrame->setObjectName("ff");
    foodFrame->setStyleSheet("QFrame#ff{border:2px solid rgb(52,152,219);border-radius:10px;background-color:#D6EAF8;}");

    foodLayout->addWidget(foodFrame);
    foodLayout->setContentsMargins(10,10,10,10);

    sptPrfText1->setAlignment(Qt::AlignHCenter);
    sptPrfText1->setStyleSheet("font-size:20px;background:transparent;");
    sptPrfText2->setAlignment(Qt::AlignHCenter);
    sptPrfText2->setStyleSheet("font-size:20px;font-weight:bold;background:transparent;");
    sptPrfText3->setAlignment(Qt::AlignHCenter);
    sptPrfText3->setStyleSheet("font-size:20px;background:transparent;");
    sptPrfText4->setAlignment(Qt::AlignHCenter);
    sptPrfText4->setStyleSheet("font-size:20px;font-weight:bold;background:transparent;");

    sportPrefer->addStretch(5);
    sportPrefer->addWidget(sptPrfText1);
    sportPrefer->addStretch(1);
    sportPrefer->addWidget(sptPrfText2);
    sportPrefer->addStretch(2);
    sportPrefer->addWidget(sptPrfText3);
    sportPrefer->addStretch(1);
    sportPrefer->addWidget(sptPrfText4);
    sportPrefer->addStretch(5);

    sportFrame->setLayout(sportPrefer);
    sportFrame->setObjectName("ff");
    sportFrame->setStyleSheet("QFrame#ff{border:2px solid rgb(40,180,99);border-radius:10px;background-color:#d5f5e3;}");

    sportLayout->addWidget(sportFrame);
    sportLayout->setContentsMargins(10,10,10,10);

    achText->setText(" 最近完成成就：");
    achText->setAlignment(Qt::AlignHCenter);
    achText->setStyleSheet("font-family:华文中宋;font-size:20px;background:transparent;");
    achLayout->addWidget(achText);
    achLayout->addSpacing(5);

    for (int i=User->achRec.qu.length()-1;i>=0;i--){
        QLabel* label=new QLabel(User->achRec.qu[i]);
        label->setStyleSheet("font-family:华文中宋;font-size:20px;background:transparent;");
        achLayout->addWidget(label);
    }

    achLayout->addStretch(1);
    achLayout->setSpacing(10);
    achLayout->setContentsMargins(20,15,0,0);

    achFrame->setLayout(achLayout);
    achFrame->setObjectName("ff");
    achFrame->setStyleSheet("QFrame#ff{border-image:url(:/home/label.png) 4 4 4 4 stretch stretch;}");

    achLayout2->addWidget(achFrame);
    achLayout2->setContentsMargins(10,10,10,5);

    foodFrame->setMaximumWidth(380);
    hLayout1->addLayout(foodLayout);
    hLayout1->addWidget(foodView);
    hLayout1->setStretch(0,2);
    hLayout1->setStretch(1,3);
    hLayout1->setSpacing(10);

    sportView->setMinimumWidth(400);
    sportFrame->setMinimumWidth(190);
    hLayout2->addWidget(sportView);
    hLayout2->addLayout(sportLayout);
    hLayout2->addLayout(achLayout2);
    hLayout2->setStretch(0,3);
    hLayout2->setStretch(1,2);
    hLayout2->setStretch(2,2);
    hLayout2->setSpacing(10);

    mainLayout->addLayout(helloLayout);
    mainLayout->addLayout(hLayout1);
    mainLayout->addLayout(hLayout2);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(20,10,10,10);

    setLayout(mainLayout);
}

bool cmp(const WeekSpt & a, const WeekSpt & b) {
    return a.time > b.time;
}

void Home::sportTimeSet() {
    QVector<WeekSpt> vec;
    vec.append(WeekSpt("跑步", User->sptRec.week_running_time, costenergy[0]));
    vec.append(WeekSpt("骑行", User->sptRec.week_riding_time, costenergy[1]));
    vec.append(WeekSpt("游泳", User->sptRec.week_swimming_time, costenergy[2]));
    vec.append(WeekSpt("登山", User->sptRec.week_climbing_time, costenergy[3]));
    vec.append(WeekSpt("篮球", User->sptRec.week_basketball_time, costenergy[4]));
    vec.append(WeekSpt("足球", User->sptRec.week_football_time, costenergy[5]));
    vec.append(WeekSpt("排球", User->sptRec.week_volleyball_time, costenergy[6]));
    vec.append(WeekSpt("乒乓球", User->sptRec.week_pingpong_time, costenergy[7]));
    vec.append(WeekSpt("羽毛球", User->sptRec.week_badminton_time, costenergy[8]));
    vec.append(WeekSpt("网球", User->sptRec.week_tennis_time, costenergy[9]));

    std::sort(vec.begin(), vec.end(), cmp);
    sportAxisText.clear();
    for (int i = 0; i < 3; ++i) {
        sportTime->append(vec[i].time);
        energyCost->append(vec[i].cost * vec[i].time);
        sportAxisText << vec[i].name;
    }
    double week_tot = 0, week_energy=0,maxtime=0,maxenergy=0;
    for (auto &x : vec){
        week_tot += x.time;
        week_energy += x.time * x.cost;
        maxtime=std::max(maxtime,x.time);
        maxenergy=std::max(maxenergy,x.time * x.cost);
    }

    int timeup=ceil(maxtime/60.0)*60+60;
    int energyup=ceil(maxenergy/300.0)*300+300;

    sportAxisY->setRange(0, timeup);
    costAxisY->setRange(0, energyup);

    sptPrfText1->setText("本周运动时长：");
    sptPrfText2->setText(QString::number(week_tot) + " 分钟");
    sptPrfText3->setText("约消耗能量：");
    sptPrfText4->setText(QString::number(week_energy) + " 千卡");

}

void Home::foodLineSet() {
    engLine->clear(); engLine->setName("能量");
    protLine->clear();  protLine->setName("蛋白质");
    fatLine->clear();   fatLine->setName("脂肪");
    int begin = User->foodRec.week_record.size() - 5, cnt = 1;
    if (begin < 0) begin = 0;
    for (int i = begin; i < User->foodRec.week_record.size(); ++i) {
        engLine->append(cnt, User->foodRec.week_record[i].second.energy);
        protLine->append(cnt, User->foodRec.week_record[i].second.protein);
        fatLine->append(cnt, User->foodRec.week_record[i].second.fat);
        ++cnt;
    }
    while (cnt <= 5) {
        engLine->append(cnt, 0);
        protLine->append(cnt, 0);
        fatLine->append(cnt, 0);
        ++cnt;
    }
}

void Home::setBestDish() {
    std::map<QString, int> mp;
    for (auto &x : User->foodRec.week_record)
        for (auto &y : x.second.elements)
            ++mp[y->name];
    int max_time = 0;
    QString max_name = "无";
    for (auto &x : mp)
        if (x.second > max_time) {
            max_time = x.second;
            max_name = x.first;
        }

    QString names[15] = {"家园食堂一层","家园食堂二层","家园食堂三层","学一食堂","燕南食堂",
                 "松林食堂","勺园食堂一层","勺园食堂二层","学五食堂","农园食堂一层","农园食堂二层","佟园食堂"};
    int cnt[15]={0};
    for (auto &x : User->foodRec.week_record)
        cnt[x.second.elements[0]->sugar]++;
    int cafe_cnt = 0;
    QString cafe_name = "无";
    for (int i=0;i<15;i++)
        if (cnt[i] > cafe_cnt) {
            cafe_cnt = cnt[i];
            cafe_name = names[i];
        }

    fdPrfText1->setText("本周最爱菜品：");
    fdPrfText2->setText(max_name + "（" + QString::number(max_time) + " 次）");
    cafePrfText1->setText("本周最爱食堂：");
    cafePrfText2->setText(cafe_name + "（" + QString::number(cafe_cnt) +" 次）");
}
