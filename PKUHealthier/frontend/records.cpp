#include <algorithm>
#include "records.h"

double sportenergy[10]={12.25, 9.8, 8.6, 9.8, 7.35, 9.8, 4.9, 4.9, 6.126, 9.8};

Records::SingleRecord::SingleRecord(QWidget *parent, bool type, QString s1, QString s2, QString s3)
    : QWidget{parent}
{
    label1->setText(s1);
    if(!type)
        label1->setStyleSheet("QLabel{font-size:16px;color:rgb(40,116,166);font-weight:bold;background-color:transparent;}");
    else
        label1->setStyleSheet("QLabel{font-size:16px;color:rgb(30,132,73);font-weight:bold;background-color:transparent;}");

    label2->setText(s2);
    label2->setStyleSheet("QLabel{font-size:16px;background-color:transparent;}");

    label3->setText(s3);
    label3->setStyleSheet("QLabel{font-size:16px;background-color:transparent;}");

    tempLayout->addWidget(label1);
    tempLayout->addWidget(label2);
    tempLayout->addWidget(label3);
    tempLayout->setContentsMargins(70,10,70,20);

    frame->setLayout(tempLayout);
    frame->setFixedSize(QSize(800,140));
    frame->setObjectName("frameframe");
    frame->setStyleSheet("QFrame#frameframe{border-image:url(:/records/body.png) 4 4 4 4 stretch stretch;}"
                         "QFrame{border-bottom:1px solid #784212;padding-bottom:5px;}");

    finalLayout->addWidget(frame);
    finalLayout->setContentsMargins(0,0,0,0);
    setLayout(finalLayout);
}

Records::Records(QWidget *parent)
    : QWidget{parent}
{
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

    headframe->setFixedSize(QSize(800,100));
    headframe->setStyleSheet("QFrame{border-image:url(:/records/head.png) 4 4 4 4 stretch stretch;}");
    itemLayout->addWidget(headframe);

    for (auto &x : recVec) {
        x.time.replace("日","日 ");
        if (!x.type){
            Cafeteria* cafe=new Cafeteria;
            int idx=x.mealItem.elements[0]->sugar;
            QString s1=x.time+"    饮食记录";
            QString s2="在"+cafe->names[idx]+"吃了"+x.mealItem.elements[0]->name;
            for (int i=1;i<x.mealItem.elements.size();i++)
                s2=s2+"、"+x.mealItem.elements[i]->name;
            s2+="，";
            if(s2.length()>41){
                QString tempstr=s2.mid(0,39);
                int tempindex=tempstr.lastIndexOf("、");
                s2=s2.mid(0,tempindex)+"……";
            }
            QString s3="共计摄入热量 "+QString::number(x.mealItem.energy)+" 千卡，蛋白质 "
                        +QString::number(x.mealItem.protein)+" 克，脂肪 "
                        +QString::number(x.mealItem.fat)+" 克，消费 "
                        +QString::number(x.mealItem.money)+" 元。";
            itemLayout->addWidget(new SingleRecord(this,0,s1,s2,s3));
        }
        else{
            QString s1=x.time+"    运动记录";
            QString s2;
            switch(x.sportType) {
            case 0: s2 = "跑步 "; break;
            case 1: s2 = "骑行 "; break;
            case 2: s2 = "游泳 "; break;
            case 3: s2 = "登山 "; break;
            case 4: s2 = "打篮球 "; break;
            case 5: s2 = "踢足球 "; break;
            case 6: s2 = "打排球 "; break;
            case 7: s2 = "打乒乓球 "; break;
            case 8: s2 = "打羽毛球 "; break;
            case 9: s2 = "打网球 ";break;
            default:break;
            }
            s2=s2+QString::number(x.sportItem)+" 分钟，";
            QString s3="约消耗 "+QString::number(sportenergy[x.sportType]*x.sportItem)+" 千卡能量。";
            itemLayout->addWidget(new SingleRecord(this,1,s1,s2,s3));
        }
    }

    tailframe->setFixedSize(QSize(800,100));
    tailframe->setStyleSheet("QFrame{border-image:url(:/records/tail.png) 4 4 4 4 stretch stretch;}");
    itemLayout->addWidget(tailframe);

    itemLayout->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
    itemLayout->setSpacing(0);
    itemLayout->setContentsMargins(0,5,10,20);
    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);
    finalLayout->addWidget(scrollArea);
    finalLayout->setContentsMargins(10,20,15,20);

    setLayout(finalLayout);
}
