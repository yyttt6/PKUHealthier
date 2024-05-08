#include <QString>
#ifndef DISH_H
#define DISH_H

class Dish
{
public:
    Dish();
    QString name;
    int id;      //也许会需要把每道菜编号
    int energy;  //(1-5)
    int protein; //(1-5)
    int fat;     //(1-5)
    int sugar;   //(0-1)
    int pepper;  //(0-2) 毕竟有微辣，变态辣之分
    int all_veg; //(0-1) 是不是全素
    int stars;   //(0-5) 默认1，用户“点赞”次数越多就越高，0代表加入黑名单，永不推送
    int scores;  //stars需要请确保数量越高增长越缓慢避免溢出,所以加上一个范围更大的scores便于实现非线性逻辑
    void update(int user_score,int black); //user_score(1-5),black(0-1) 更新星级
};

#endif // DISH_H
