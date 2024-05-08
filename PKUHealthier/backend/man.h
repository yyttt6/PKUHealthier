#include <QString>
#include <Qvector>
#include "dish.h"
#ifndef MAN_H
#define MAN_H

class Man
{
public:
    Man();
    double weight;
    double BMI;
    QString name;
    QString password;
    int target; //0:均衡 1:减重 2:增肌
    int preference[5]; //0少糖1适中2多糖，0少辣1正常2多辣，0保守1默认2探索，保留，保留
    class SportRecord{
    public:
        //累计时长/里程
        double badminton_time;
        double pingpong_time;
        double tennis_time;
        double basketball_time;
        double volleyball_time;
        double football_time;
        double Running_mileage;
        double Riding_mileage;
        double climbing_mileage;
        //本周时长/里程
        double week_badminton_time;
        double week_pingpong_time;
        double week_tennis_time;
        double week_basketball_time;
        double week_volleyball_time;
        double week_football_time;
        double week_Running_mileage;
        double week_Riding_mileage;
        double week_climbing_mileage;
        void reset(); //每周更新
    };
    class FoodRecord{
        long long number; //累计吃了多少顿饭，暂时没想到更好的，害怕爆内存😇
        QVector<Dish*> week_record; //一周的饮食记录，每个指针指向一餐的内容
        void reset(); //每周更新，记得delete掉week_record里面指针指向的内容，避免内存泄露
    };
};

#endif // MAN_H
