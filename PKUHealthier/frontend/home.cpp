#include "home.h"
#include <ctime>
#include <QDebug>

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

    sportChart->setTitle("本周运动");
    sportChart->setAnimationOptions(QChart::SeriesAnimations);
    sportView->setRenderHint(QPainter::Antialiasing);

    foodChart->setTitle("本周饮食");
    foodChart->setAnimationOptions(QChart::SeriesAnimations);
    foodView->setRenderHint(QPainter::Antialiasing);

    sportTimeSet();
    foodKindSet();

    sportSerie->append(sportTime);
    foodKindSerie->append(foodSet);

    sportChart->removeAllSeries();
    sportChart->addSeries(sportSerie);
    foodChart->removeAllSeries();
    foodChart->addSeries(foodKindSerie);

    QStringList sportAxisText, foodAxisText;
    sportAxisText << "羽毛球";
    sportAxisText << "乒乓球";
    sportAxisText << "网球";
    sportAxisText << "篮球";
    sportAxisText << "排球";
    sportAxisText << "足球";
    sportAxisText << "跑步";
    sportAxisText << "骑行";
    sportAxisText << "爬山";
    foodAxisText << "按时吃饭";
    foodAxisText << "素食";
    foodAxisText << "吃辣";

    sportAxisX->append(sportAxisText);
    foodKindAxisX->append(foodAxisText);

    sportChart->setAxisX(sportAxisX, sportSerie);
    foodChart->setAxisX(foodKindAxisX, foodKindSerie);

    sportAxisX->setRange(sportAxisText.at(0), sportAxisText.at(sportAxisText.count() - 1));
    foodKindAxisX->setRange(foodAxisText.at(0), foodAxisText.at(foodAxisText.count() - 1));

    sportAxisY->setRange(0, 10);
    sportAxisY->setTitleText("时间/小时");
    sportAxisY->setTickCount(6);
    sportAxisY->setLabelFormat("%.2f");
    foodAxisY->setRange(0, 25);
    foodAxisY->setTitleText("数量");
    foodAxisY->setTickCount(6);
    foodAxisY->setLabelFormat("%d");

    sportChart->setAxisY(sportAxisY, sportSerie);
    foodChart->setAxisY(foodAxisY, foodKindSerie);

    sportChart->legend()->setVisible(true);
    sportChart->legend()->setAlignment(Qt::AlignBottom);
    foodChart->legend()->setVisible(true);
    foodChart->legend()->setAlignment(Qt::AlignBottom);

    helloLayout->addWidget(photoLabel);
    helloLayout->addWidget(helloLabel);

    chartsLayout->addWidget(sportView);
    chartsLayout->addWidget(foodView);

    mainLayout->addLayout(helloLayout, 0, 0);
    mainLayout->addLayout(chartsLayout, 1, 0);
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
    foodKindRefresh();
}

void Home::sportTimeSet() {
    sportTime->append(User->sptRec.week_badminton_time);
    sportTime->append(User->sptRec.week_pingpong_time);
    sportTime->append(User->sptRec.week_tennis_time);
    sportTime->append(User->sptRec.week_basketball_time);
    sportTime->append(User->sptRec.week_volleyball_time);
    sportTime->append(User->sptRec.week_football_time);
    sportTime->append(User->sptRec.week_running_time);
    sportTime->append(User->sptRec.week_riding_time);
    sportTime->append(User->sptRec.week_climbing_time);
}

void Home::foodKindSet() {
    foodSet->append(User->foodRec.number);
    foodSet->append(User->foodRec.veg_number);
    foodSet->append(User->foodRec.hot_number);
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

void Home::foodKindRefresh() {
    foodSet->replace(0, User->foodRec.number);
    foodSet->replace(1, User->foodRec.veg_number);
    foodSet->replace(2, User->foodRec.hot_number);
}
