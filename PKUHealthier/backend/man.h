#include <QString>
#include <Qvector>
#include <QQueue>
#include <QHash>
#include "dish.h"
#include "../frontend/achievement.h"
#ifndef MAN_H
#define MAN_H

class Man
{
public:
    Man();
    ///////////////////////////////////////////////////////////
    //在注册界面需要的信息,前端直接修改
    double weight=0;    //kg
    double height=0;    //cm
    int age=0;
    int gender=0;       //0女性1男性
    QString name;
    QString password;
    int target=0;       //0减重;1平衡不锻炼;2平衡适度锻炼;3增肌中度锻炼;4增肌高强度锻炼;
    int preference[4]={0};
                        //0少糖1适中2多糖 0少辣1正常2多辣 0保守1默认2探索 0经济1正常
                        //4个数代表4个喜好
    //在注册面需要的信息完毕
    //注册页修改完后，手动调用init();
    ////////////////////////////////////////////////////////////
    double basic_energy=0;
    double energy_need=0;
    double protein_need=0;
    double fat_need=0;
    double weight_vector[9]={1,1,0.5,0,0,0,0,1,1};//默认权重向量
    //内部类，存储运动记录
    class SportRecord{
    public:
        SportRecord();
        //累计时长/里程
        double badminton_time;      //羽毛球爱好者->羽毛球大师
        double pingpong_time;       //乒乓球爱好者->乒乓球大师
        double tennis_time;         //网球爱好者->网球大师
        double basketball_time;     //篮球爱好者->篮球大师
        double volleyball_time;     //排球爱好者->排球大师
        double football_time;       //足球爱好者->足球大师
        double Running_mileage;     //跑步健将->跑步大师
        double Riding_mileage;      //骑行健将->骑行大师
        double climbing_mileage;    //登山健将->登山大师
        double swimming_time;       //游泳健将->游泳大师
                                    //全一级:六边形战士 -> 全二级:满级人类
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
    //内部类，存储饮食记录
    class FoodRecord{
        FoodRecord();
        long long number; //累计吃了多少顿饭            干饭小将->干饭大师->古希腊掌管干饭的神😋
        long long veg_number; //累计吃了多少素菜        素食主义者->极端素食主义者->牛马
        long long hot_number; //累计吃了多少辣菜        吃辣小将->吃辣大师
        long long reject_number; //要求重新生成了多少次  精挑细选
        long long comment_number;//食品打分次数         美食评论家
        QString best_dish;  //最爱菜品和分数
        int best_dish_score;
          //目前就想到这么多，大家想到别的可以加，但是所有的调用函数和save&load也要跟着变

        QVector<Dish*> week_record; //一周的饮食记录，每个指针指向一餐的内容
        void reset(); //每周更新，记得delete掉week_record里面指针指向的内容，避免内存泄露
    };
    //内部类，存储成就
    class AchievementRecord{
    public:
        //成就名称  --->  0:未获得 1:一级/获得 2:二级 3:三级
        //QString可以存储中文，所有成就选取第一个名称
        QHash<QString,int> achievement_map;
        //长度固定，就先暂定5个吧，进一个出一个，用于实现最近成就
        QQueue<QString> qu;
    };

    //检查有没有触发新的成就，成就触发标准待定
    bool check_achievement();
    bool load();
    bool save();
    void init();
};

#endif // MAN_H
