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

    sportChart->removeAllSeries();
    sportChart->addSeries(sportSerie);
    foodChart->removeAllSeries();
    foodChart->addSeries(engLine);
    foodChart->addSeries(protLine);
    foodChart->addSeries(fatLine);

    QStringList sportAxisText;
    sportAxisText << "羽毛球";
    sportAxisText << "乒乓球";
    sportAxisText << "网球";
    sportAxisText << "篮球";
    sportAxisText << "排球";
    sportAxisText << "足球";
    sportAxisText << "跑步";
    sportAxisText << "骑行";
    sportAxisText << "登山";

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
    sportAxisY->setTickCount(6);
    sportAxisY->setLabelFormat("%.2f");
    engAxisY->setRange(0, 1200);
    engAxisY->setTitleText("能量/大卡");
    engAxisY->setTickCount(7);
    otherAxisY->setRange(0, 120);
    otherAxisY->setTitleText("质量/克");
    otherAxisY->setTickCount(7);

    sportChart->addAxis(sportAxisY, Qt::AlignLeft);
    foodChart->addAxis(engAxisY, Qt::AlignLeft);
    foodChart->addAxis(otherAxisY, Qt::AlignRight);

    sportSerie->attachAxis(sportAxisY);
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
    foodLineSet();
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
