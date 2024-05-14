#include <QString>
#include <QTextStream>
#include <QThread>
#ifndef DISH_H
#define DISH_H
#define DIM 8
class Dish
{
public:
    Dish();
    Dish(QStringList infos);
    int id;         //也许会需要把每道菜编号
    QString name;
    int type;       //0主食，1菜品，2点心，3套餐
                    //如果是套餐，数值是内部所有饭菜的加和
    double energy;  //卡路里/份
    double protein; //蛋白质/份
    double fat;     //脂肪/份
    int sugar;      //0-1是否高糖
    int pepper;     //0-1是否狠辣（微辣0）
    int all_veg;    //是不是全素
    double money;   //价格
    int scores;     //0永不推送，100满分
    QString save() const;
    void update(int user_score);//用户评分1-5颗星，更新scores
};
#endif // DISH_H
