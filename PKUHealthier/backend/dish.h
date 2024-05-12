#include <QString>
#include <QTextStream>
#include <QThread>
#include <QtGlobal>
#ifndef DISH_H
#define DISH_H
#define DIM 8
class Dish
{
public:
    Dish();
    Dish(QStringList infos);
    static const double weight[DIM];
    int id;      //也许会需要把每道菜编号
    QString name;
    int type;    //0主食，1菜品，2点心，3套餐
    int energy;  //(1-5)
    int protein; //(1-5)
    int fat;     //(1-5)
    int sugar;   //(0-1)
    int pepper;  //(0-2) 毕竟有微辣，变态辣之分
    int all_veg; //(0-1) 是不是全素
    double money;//价格
    int scores;  //0永不推送，100满分
    QString save() const;
    void update(int user_score,int black); //user_score(1-5),black(0-1) 更新scores
    double get_value(int preference);
};
const double Dish::weight[] = {1,1,1,0,0,0,0,0};
#endif // DISH_H
