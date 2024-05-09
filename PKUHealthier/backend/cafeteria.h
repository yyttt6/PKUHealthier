#include <QString>
#include "man.h"
#include "dish.h"
#ifndef CAFETERIA_H
#define CAFETERIA_H

//代表所有的食堂
class Cafeteria
{
private:
    Cafeteria();
    QString names[15] = {"家园食堂一层","家园食堂二层","家园食堂三层","学一食堂","燕南食堂",
        "松林食堂","勺园食堂一层","勺园食堂二层","学五食堂","农园食堂一层","农园食堂二层","佟园食堂"};
    QString filenames[15] = {"jia1.txt","jia2.txt","jia3.txt","xue1.txt","yan.txt","song.txt",
        "shao1.txt","shao2.txt","xue5.txt","nong1.txt","nong2.txt","tong.txt"};
    bool Save(QString filename);
    //推送时随机到哪一个食堂就读取哪一个食堂的菜品，避免爆内存
    Dish* load(QString filename);
public:
    //随机选择一个食堂，然后推荐菜品,前端会直接调用这个函数获取菜品
    //pname:输入时为NULL，返回时被指向推送的食堂名
    Dish* recommend(const Man &m,int seed,QString *pname);
};

#endif // CAFETERIA_H
