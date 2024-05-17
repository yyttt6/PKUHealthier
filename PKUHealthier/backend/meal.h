#include <QString>
#include <QTextStream>
#include <QThread>
#include "dish.h"
#include "man.h"
#ifndef MEAL_H
#define MEAL_H

class Meal
{
public:
    Meal();
    QVector<Dish*> elements;
    double energy=0;  //卡路里/份
    double protein=0; //蛋白质/份
    double fat=0;     //脂肪/份
    int sugar=0;      //0-1是否高糖
    int pepper=0;     //0-1是否狠辣（微辣0）
    int all_veg=0;    //是不是全素
    double money=0;   //价格
    double value=0;
    double scores=0;
    void get_value(const Man &man,int seed);
    void init();
};



#endif // MEAL_H
