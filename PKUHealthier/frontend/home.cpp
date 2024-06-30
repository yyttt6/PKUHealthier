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
    helloLabel->setText(helloText + " " + User->name);

    sportChart->setTitle("本周运动时长前三");
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

    sportAxisY->setRange(0, 600);
    sportAxisY->setTitleText("时间/分钟");
    sportAxisY->setTickCount(7);
    sportAxisY->setLabelFormat("%.2f");
    costAxisY->setRange(0, 1200);
    costAxisY->setTitleText("能量/大卡");
    costAxisY->setTickCount(7);
    engAxisY->setRange(0, 1200);
    engAxisY->setTitleText("能量/大卡");
    engAxisY->setTickCount(7);
    otherAxisY->setRange(0, 120);
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
    helloLayout->addWidget(helloLabel);

    fdPrfText->setStyleSheet("font-family:华文新魏;font-size:24px;color:#FFFFFF");
    sptPrfText->setStyleSheet("font-family:华文中宋;font-size:24px;");

    setBestDish();
    fdPrfText->setAlignment(Qt::AlignCenter);
    foodPrefer->addWidget(fdPrfText);
    foodFrame->setLayout(foodPrefer);

    sptPrfText->setAlignment(Qt::AlignCenter);
    sportPrefer->addWidget(sptPrfText);
    sportFrame->setLayout(sportPrefer);

    foodFrame->setStyleSheet("border-image:url(:/home/prefer.png) 4 4 4 4 stretch stretch;");
    sportFrame->setStyleSheet("border-image:url(:/home/sport_prefer.jpg) 2 2 4 4 stretch stretch;");

    mainLayout->addLayout(helloLayout, 0, 0);
    mainLayout->addWidget(foodFrame, 1, 0);
    mainLayout->addWidget(foodView, 1, 1);
    mainLayout->addWidget(sportView, 2, 0);
    mainLayout->addWidget(sportFrame, 2, 1);
    setLayout(mainLayout);
}

void Home::refresh(){
    User->load();

    photo->load("../../data/photo.png");
    photoLabel->setPixmap(*photo);

    std::time_t now = std::time(nullptr);
    std::tm* now_tm = std::localtime(&now);
    QString helloText = timeString(now_tm);
    helloLabel->setText(helloText + " " + User->name);

    sportTimeRefresh();
    foodLineSet();

    setBestDish();
}

bool cmp(const WeekSpt & a, const WeekSpt & b) {
    return a.time > b.time;
}

void Home::sportTimeSet() {
    QVector<WeekSpt> vec;
    vec.append(WeekSpt("羽毛球", User->sptRec.week_badminton_time, costenergy[8]));
    vec.append(WeekSpt("乒乓球", User->sptRec.week_pingpong_time, costenergy[7]));
    vec.append(WeekSpt("网球", User->sptRec.week_tennis_time, costenergy[9]));
    vec.append(WeekSpt("篮球", User->sptRec.week_basketball_time, costenergy[4]));
    vec.append(WeekSpt("排球", User->sptRec.week_volleyball_time, costenergy[6]));
    vec.append(WeekSpt("足球", User->sptRec.week_football_time, costenergy[5]));
    vec.append(WeekSpt("跑步", User->sptRec.week_running_time, costenergy[0]));
    vec.append(WeekSpt("骑行", User->sptRec.week_riding_time, costenergy[1]));
    vec.append(WeekSpt("登山", User->sptRec.week_climbing_time, costenergy[3]));
    vec.append(WeekSpt("游泳", User->sptRec.week_swimming_time, costenergy[2]));
    std::sort(vec.begin(), vec.end(), cmp);
    sportAxisText.clear();
    for (int i = 0; i < 3; ++i) {
        sportTime->append(vec[i].time);
        energyCost->append(vec[i].cost * vec[i].time);
        sportAxisText << vec[i].name;
    }
    double week_tot = 0, tot = 0;
    for (auto &x : vec)
        week_tot += x.time;
    tot = User->sptRec.badminton_time + User->sptRec.pingpong_time + User->sptRec.tennis_time
          + User->sptRec.basketball_time + User->sptRec.volleyball_time + User->sptRec.football_time
          + User->sptRec.running_time + User->sptRec.riding_time + User->sptRec.climbing_time
          + User->sptRec.swimming_time;
    sptPrfText->setText("本周运动时长：" + QString::number(week_tot) + " 分钟\n\n总运动时长：" + QString::number(tot) + " 分钟");

}

void Home::sportTimeRefresh() {
    sportTime->replace(0, User->sptRec.week_badminton_time);
    sportTime->replace(1, User->sptRec.week_pingpong_time);
    sportTime->replace(2, User->sptRec.week_tennis_time);
    sportTime->replace(3, User->sptRec.week_basketball_time);
    sportTime->replace(4, User->sptRec.week_volleyball_time);
    sportTime->replace(5, User->sptRec.week_football_time);
    sportTime->replace(6, User->sptRec.week_running_time);
    sportTime->replace(7, User->sptRec.week_riding_time);
    sportTime->replace(8, User->sptRec.week_climbing_time);
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
    QString max_name;
    for (auto &x : mp)
        if (x.second > max_time) {
            max_time = x.second;
            max_name = x.first;
        }
    fdPrfText->setText("本周最爱菜品：" + max_name + "\n\n选择次数：" + QString::number(max_time));
}
