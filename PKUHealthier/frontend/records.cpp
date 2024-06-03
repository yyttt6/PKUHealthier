#include <algorithm>
#include "records.h"

double cost[10]={12.25, 9.8, 8.6, 9.8, 7.35, 9.8, 4.9, 4.9, 6.126, 9.8};

Records::SingleFoodRecord::SingleFoodRecord(QWidget *parent, QPair<QString,Meal> mealPair)
    : QWidget{parent}
{
    //tempLayout->addWidget(new QLabel(mealPair.first)); （这个QString是时间）
    //可能若干个 tempLayout->addWidget(new QLabel(mealPair.second.elements[i]->name));
    //然后总共摄入多少蛋白质脂肪等等
    //可以直接参考Menu::SinglePage::save()的Dialog部分

    QString dishName = "菜品： ";
    for (auto x : mealPair.second.elements)
        dishName += x->name + " ";
    dishLabel->setText(dishName);
    dishLabel->setStyleSheet("QLabel{font-size:15px;font-family:楷体;font-weight:bold;}");

    QString intake = "总摄入： ";
    intake += "能量" + QString::number(mealPair.second.energy) + "千卡 ";
    intake += "蛋白质" + QString::number(mealPair.second.protein) + "克 ";
    intake += "脂肪" + QString::number(mealPair.second.fat) + "克 ";
    intakeLabel->setText(intake);
    intakeLabel->setStyleSheet("QLabel{font-size:15px;font-family:楷体;font-weight:bold;}");

    timeLabel->setText(mealPair.first);

    tempLayout->addWidget(nameLabel);
    tempLayout->addWidget(dishLabel);
    tempLayout->addWidget(intakeLabel);
    tempLayout->addWidget(timeLabel);

    frame->setLayout(tempLayout);

    frame->setFixedSize(QSize(400,160));
    frame->setObjectName("frameframe");
    frame->setStyleSheet("QFrame#frameframe{border-style:solid;border-width:2px;border-color:rgb(255,204,68);border-radius:10px;}");

    finalLayout->addWidget(frame);
    setLayout(finalLayout);
}

Records::SingleSportRecord::SingleSportRecord(QWidget *parent, QPair<QString,int> sportPair, int sportType)
    : QWidget{parent}
{
    //同上，这里主要是要switch(sportType){......}来确定是哪个运动
    //然后QLabel展示记录时间、运动名称、运动时长

    QString sport;
    switch(sportType) {
        case 0: sport += "跑步 "; break;
        case 1: sport += "骑行 "; break;
        case 2: sport += "游泳 "; break;
        case 3: sport += "登山 "; break;
        case 4: sport += "打篮球 "; break;
        case 5: sport += "踢足球 "; break;
        case 6: sport += "打排球 "; break;
        case 7: sport += "打乒乓球 "; break;
        case 8: sport += "打羽毛球 "; break;
        case 9: sport += "打网球 ";
    }
    sport += QString::number(sportPair.second);
    sport += "分钟   消耗 ";
    sport += QString::number(cost[sportType] * sportPair.second);
    sport += "千卡";
    sportLabel->setText(sport);
    sportLabel->setStyleSheet("QLabel{font-size:15px;font-family:楷体;font-weight:bold;}");

    timeLabel->setText(sportPair.first);

    tempLayout->addWidget(nameLabel);
    tempLayout->addWidget(sportLabel);
    tempLayout->addWidget(timeLabel);

    frame->setLayout(tempLayout);

    frame->setFixedSize(QSize(400,160));
    frame->setObjectName("frameframe");
    frame->setStyleSheet("QFrame#frameframe{border-style:solid;border-width:2px;border-color:rgb(52,152,219);border-radius:10px;}");

    finalLayout->addWidget(frame);
    setLayout(finalLayout);
}

Records::Records(QWidget *parent)
    : QWidget{parent}
{

    //man load 对 man->foodRec.week_record 和 man->sptRec里的所有week_***_vec 里的记录按时间从后到前排序
    //这个可能很麻烦qaq
    //然后依次vLayout->addWidget(new SingleFoodRecord(this,?))
    //或vLayout->addWidget(new SingleSportRecord(this,?,type))

    QVector<RecordItem> recVec;
    Man* User = new Man;
    User->load();
    for (auto &x : User->foodRec.week_record)
        recVec.append(RecordItem(x));
    for (auto &x : User->sptRec.week_run_vec)
        recVec.append(RecordItem(x, 0));
    for (auto &x : User->sptRec.week_rid_vec)
        recVec.append(RecordItem(x, 1));
    for (auto &x : User->sptRec.week_swi_vec)
        recVec.append(RecordItem(x, 2));
    for (auto &x : User->sptRec.week_cli_vec)
        recVec.append(RecordItem(x, 3));
    for (auto &x : User->sptRec.week_bas_vec)
        recVec.append(RecordItem(x, 4));
    for (auto &x : User->sptRec.week_foo_vec)
        recVec.append(RecordItem(x, 5));
    for (auto &x : User->sptRec.week_vol_vec)
        recVec.append(RecordItem(x, 6));
    for (auto &x : User->sptRec.week_pin_vec)
        recVec.append(RecordItem(x, 7));
    for (auto &x : User->sptRec.week_bad_vec)
        recVec.append(RecordItem(x, 8));
    for (auto &x : User->sptRec.week_ten_vec)
        recVec.append(RecordItem(x, 9));
    std::sort(recVec.begin(), recVec.end());
    int cnt = 0;
    for (auto &x : recVec) {
        if (!x.type)
            itemLayout->addWidget(new SingleFoodRecord(this, std::make_pair(x.time, x.mealItem)), cnt / 2, cnt % 2);
        else
            itemLayout->addWidget(new SingleSportRecord(this, std::make_pair(x.time, x.sportItem), x.sportType), cnt / 2, cnt % 2);
        ++cnt;
    }

    itemLayout->setSpacing(20);
    itemLayout->setContentsMargins(0,0,10,20);
    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);
    finalLayout->addWidget(scrollArea);
    finalLayout->setContentsMargins(25,20,15,20);

    setLayout(finalLayout);
}

void Records::refresh(){

}
