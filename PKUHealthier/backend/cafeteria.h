#include <QString>
#include <QVector>
#include <QList>
#include "man.h"
#include "dish.h"
#include "meal.h"
#ifndef CAFETERIA_H
#define CAFETERIA_H

//代表所有的食堂
class Cafeteria
{
public:
    Cafeteria();
    QString names[15] = {"家园食堂一层","家园食堂二层","家园食堂三层","学一食堂","燕南食堂",
        "松林食堂","勺园食堂一层","勺园食堂二层","学五食堂","农园食堂一层","农园食堂二层","佟园食堂"};
    QString filenames[15] = {"jia1.csv","jia2.csv","jia3.csv","xue1.csv","yan.csv","song.csv",
        "shao1.csv","shao2.csv","xue5.csv","nong1.csv","nong2.csv","tong.csv"};
    QVector<Dish*> staple; //所有主食，用过立即清理
    QVector<Dish*> recipe; //所有菜品，用过立即清理
    QVector<Dish*> dessert;//所有甜点，用过立即清理
    QVector<Dish*> setmeal;//所有套餐，用过立即清理
    QList< QVector<Meal> > multi_meals;//所有组合起来的食谱，用过立即清理
    QVector<Meal> meals; //真正用于排序的meals，用过立即清理

    QVector<Dish>  dishes;//一个食堂全部菜品，保存一段时间
    bool save(int id);//成功返回1，失败返回0
    //推送时随机到哪一个食堂就读取哪一个食堂的菜品，避免爆内存
    void load(int id);
    //随机选择一个食堂，然后推荐菜品,前端会直接调用这个函数获取菜品
    //pname:输入时为NULL，返回时被指向推送的食堂名
    QVector<Meal> recommend(const Man &m,int seed,QString *pname);
};

#endif // CAFETERIA_H
