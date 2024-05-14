#include <QString>
#include <QTextStream>
#include <QThread>
#include "dish.h"
#ifndef MEAL_H
#define MEAL_H

class Meal
{
public:
    Meal();
    static const double weight[DIM];
    QVector<Dish*> elements;
    double energy;  //卡路里/份
    double protein; //蛋白质/份
    double fat;     //脂肪/份
    int sugar;      //0-1是否高糖
    int pepper;     //0-1是否狠辣（微辣0）
    int all_veg;    //是不是全素
    double money;   //价格
    double get_value(int preference);
    double value=0;
};
const double Meal::weight[] = {1,1,1,0,0,0,0,0};

bool Meal_cmp(Meal a,Meal b){
    return a.value < b.value;
}

#endif // MEAL_H
