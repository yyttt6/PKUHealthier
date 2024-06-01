#include "records.h"

Records::SingleFoodRecord::SingleFoodRecord(QWidget *parent, QPair<QString,Meal> mealPair)
    : QWidget{parent}
{
    //tempLayout->addWidget(new QLabel(mealPair.first)); （这个QString是时间）
    //可能若干个 tempLayout->addWidget(new QLabel(mealPair.second.elements[i]->name));
    //然后总共摄入多少蛋白质脂肪等等
    //可以直接参考Menu::SinglePage::save()的Dialog部分

    frame->setLayout(tempLayout);

    frame->setFixedSize(QSize(400,160));
    frame->setObjectName("frameframe");
    frame->setStyleSheet("QFrame#frameframe{border-style:solid;border-width:2px;border-color:rgb(52,152,219);border-radius:10px;}");

    finalLayout->addWidget(frame);
    setLayout(finalLayout);
}

Records::SingleSportRecord::SingleSportRecord(QWidget *parent, QPair<QString,int> sportPair, int sportType)
    : QWidget{parent}
{
    //同上，这里主要是要switch(sportType){......}来确定是哪个运动
    //然后QLabel展示记录时间、运动名称、运动时长

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

    vLayout->setSpacing(20);
    vLayout->setContentsMargins(0,0,10,20);
    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);
    finalLayout->addWidget(scrollArea);
    finalLayout->setContentsMargins(25,20,15,20);

}

void Records::refresh(){

}
