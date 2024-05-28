#include "singledish.h"

SingleDish::SingleDish(QWidget *parent,Dish* d)
    : QWidget{parent}, dish(d)
{
    /*
    int id;         //也许会需要把每道菜编号
    QString name;
    int type;       //0主食，1菜品，2点心，3套餐
                    //如果是套餐，数值是内部所有饭菜的加和
    double energy;  //卡路里/份     //热量：千卡 蛋白质：克
    double protein; //蛋白质/份
    double fat;     //脂肪/份
    int sugar;      //0-1是否高糖
    int pepper;     //0-1是否狠辣（微辣0）
    int all_veg;    //是不是全素
    double money;   //价格
    int scores;
    */

    label1->setText(dish->name);
    label2->setText("热量："+QString::number(dish->energy)+"千卡");
    label3->setText("蛋白质："+QString::number(dish->protein)+"克");
    label4->setText("脂肪："+QString::number(dish->fat)+"克");
    label5->setText("¥"+QString::number(dish->money));

    hLayout1->addWidget(label1);
    hLayout1->addStretch(1);
    hLayout1->addWidget(likeButton);
    hLayout1->addWidget(blockButton);
    if(dish->sugar>0)
        hLayout2->addWidget(label6);
    if(dish->pepper>0)
        hLayout2->addWidget(label7);
    if(dish->all_veg>0)
        hLayout2->addWidget(label8);
    hLayout2->addStretch(1);
    hLayout3->addStretch(1);
    hLayout3->addWidget(label5);
    hLayout3->addWidget(chooseButton);

    vLayout->addLayout(hLayout1);
    vLayout->addWidget(label2);
    vLayout->addWidget(label3);
    vLayout->addWidget(label4);
    vLayout->addLayout(hLayout2);
    vLayout->addLayout(hLayout3);


    frame->setLayout(vLayout);
    frame->setFixedSize(QSize(220,160));
    frame->setObjectName("frameframe");
    frame->setStyleSheet("QFrame#frameframe{border-style:solid;border-width:2px;border-color:gray;border-radius:10px;}");

}

void SingleDish::refresh(){

}