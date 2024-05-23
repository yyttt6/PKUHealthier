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
    QString name = "NULL";
    QString password = "NULL";
    int target=0;       //0减重;1平衡不锻炼;2平衡适度锻炼;3增肌中度锻炼;4增肌高强度锻炼;
    int preference[4]={0, 0, 0, 0};
                        //0适中1少糖2多糖 0正常1少辣2多辣 0默认1保守2探索 0正常1经济
                        //4个数代表4个喜好
    //在注册面需要的信息完毕
    //注册页修改完后，手动调用init();
    ////////////////////////////////////////////////////////////
    double basic_energy=0;
    double energy_need=0;
    double protein_need=0;
    double fat_need=0;
    double weight_vector[9]={1,1,1,0,0,0,0,1,2};//默认权重向量
    class SportRecord{
    public:
        SportRecord(){};
        //累计时长/里程
        double badminton_time=0;      //羽毛球爱好者->羽毛球大师
        double pingpong_time=0;       //乒乓球爱好者->乒乓球大师
        double tennis_time=0;         //网球爱好者->网球大师
        double basketball_time=0;     //篮球爱好者->篮球大师
        double volleyball_time=0;     //排球爱好者->排球大师
        double football_time=0;       //足球爱好者->足球大师
        double Running_mileage=0;     //跑步健将->跑步大师
        double Riding_mileage=0;      //骑行健将->骑行大师
        double climbing_mileage=0;    //登山健将->登山大师
        double swimming_time=0;       //游泳健将->游泳大师
                                    //全一级:六边形战士 -> 全二级:满级人类
        //本周时长/里程
        double week_badminton_time=0;
        double week_pingpong_time=0;
        double week_tennis_time=0;
        double week_basketball_time=0;
        double week_volleyball_time=0;
        double week_football_time=0;
        double week_Running_mileage=0;
        double week_Riding_mileage=0;
        double week_climbing_mileage=0;
        void reset(); //每周更新
        QString get_str() const;
        static SportRecord load(QTextStream& input);
    }sptRec;
    //内部类，存储饮食记录
    class FoodRecord{
    public:
        FoodRecord(){};
        long long number=0; //累计吃了多少顿饭            干饭小将->干饭大师->古希腊掌管干饭的神😋
        long long veg_number=0; //累计吃了多少素菜        素食主义者->极端素食主义者->牛马
        long long hot_number=0; //累计吃了多少辣菜        吃辣小将->吃辣大师
        long long reject_number=0; //要求重新生成了多少次  精挑细选
        long long comment_number=0;//食品打分次数         美食评论家
        QString best_dish="NULL";  //最爱菜品和分数
        int best_dish_score=0;

          //目前就想到这么多，大家想到别的可以加，但是所有的调用函数和save&load也要跟着变
        QVector<Dish> week_record; //一周的饮食记录，每个指针指向一餐的内容
        void reset(); //每周更新，记得delete掉week_record里面指针指向的内容，避免内存泄露
        QString get_str() const;
        static FoodRecord load(QTextStream& input);
    }foodRec;
    //内部类，存储成就
    class AchievementRecord{
    public:
        //成就名称  --->  0:未获得 1:一级/获得 2:二级 3:三级
        //成就名称看AChievementRecord构造函数
        QHash<QString,int> achievement_map;
        //长度固定，就先暂定5个吧，进一个出一个，用于实现最近成就
        QQueue<QString> qu;
        QString get_str() const;
        static AchievementRecord load(QTextStream& input);
        void check_achievement(SportRecord sr,FoodRecord fr);
        AchievementRecord()
        {
            achievement_map.insert("干饭",0);
            achievement_map.insert("素食",0);
            achievement_map.insert("吃辣",0);
            achievement_map.insert("挑选",0);
            achievement_map.insert("评论",0);
            achievement_map.insert("羽毛球",0);
            achievement_map.insert("乒乓球",0);
            achievement_map.insert("网球",0);
            achievement_map.insert("篮球",0);
            achievement_map.insert("排球",0);
            achievement_map.insert("足球",0);
            achievement_map.insert("跑步",0);
            achievement_map.insert("骑行",0);
            achievement_map.insert("登山",0);
            achievement_map.insert("游泳",0);
            achievement_map.insert("六边形",0);
        }
    }achRec;
    //检查有没有触发新的成就
    void check_achievement();
    bool load();
    bool save();
    void init();
};

#endif // MAN_H
