#include "man.h"
#include <assert.h>
#include <QFile>
#include <QDebug>
Man::Man() {}

double exercise_level[5] = {1.0,1.2,1.375,1.55,1.725};
double protein_rate[5] = {0.9,0.9,1.1,1.4,1.6};

void Man::init()
{
    assert(weight>0&&height>0);
    basic_energy = 10*weight + 6.25*height -5*age -161 + 166*gender;
    energy_need = basic_energy * exercise_level[target] * 2/5;
    protein_need = weight * protein_rate[target] *2/5;
    if(gender==0) protein_need *= 0.85;
    fat_need = (energy_need/45)*2/5;
    if(target<=1){
        weight_vector[5]+=10;
        if(target<=1) weight_vector[0]+=1;
    }
    if(target>=3) weight_vector[1]+=0.5;
    if(preference[0]==0) weight_vector[3]-=100;
    if(preference[0]==2) weight_vector[3]+=10;
    if(preference[1]==0) weight_vector[4]-=100;
    if(preference[1]==2) weight_vector[4]+=10;
    if(preference[3]==0) weight_vector[6]-=1;
    if(preference[2]==0) weight_vector[7]=2;
    if(preference[2]==0) weight_vector[8]=0.5;
    if(preference[2]==2) weight_vector[7]=0.5;
    if(preference[2]==2) weight_vector[8]=2;
}

QString Man::SportRecord::get_str() const{
    QString str;
    str += QString::number(badminton_time,'f',2)+',';
    str += QString::number(pingpong_time,'f',2)+',';
    str += QString::number(tennis_time,'f',2)+',';
    str += QString::number(basketball_time,'f',2)+',';
    str += QString::number(volleyball_time,'f',2)+',';
    str += QString::number(football_time,'f',2)+',';
    str += QString::number(Running_mileage,'f',2)+',';
    str += QString::number(Riding_mileage,'f',2)+',';
    str += QString::number(climbing_mileage,'f',2)+',';
    str += QString::number(swimming_time,'f',2)+',';
    str += '\n';
    str += QString::number(week_badminton_time,'f',2)+',';
    str += QString::number(week_pingpong_time,'f',2)+',';
    str += QString::number(week_tennis_time,'f',2)+',';
    str += QString::number(week_basketball_time,'f',2)+',';
    str += QString::number(week_volleyball_time,'f',2)+',';
    str += QString::number(week_football_time,'f',2)+',';
    str += QString::number(week_Running_mileage,'f',2)+',';
    str += QString::number(week_Riding_mileage,'f',2)+',';
    str += QString::number(week_climbing_mileage,'f',2)+',';
    str += '\n';
    return str;
}

Man::SportRecord Man::SportRecord::load(QTextStream& input) {
    Man::SportRecord record;
    QString str ;
    input>>str;
    assert(str[0]=='%');
    input>>str;
    QStringList parts = str.split(',');
    record.badminton_time = parts[0].toDouble();
    record.pingpong_time = parts[1].toDouble();
    record.tennis_time = parts[2].toDouble();
    record.basketball_time = parts[3].toDouble();
    record.volleyball_time = parts[4].toDouble();
    record.football_time = parts[5].toDouble();
    record.Running_mileage = parts[6].toDouble();
    record.Riding_mileage = parts[7].toDouble();
    record.climbing_mileage = parts[8].toDouble();
    record.swimming_time = parts[9].toDouble();
    input>>str;
    parts = str.split(',');
    record.week_badminton_time = parts[0].toDouble();
    record.week_pingpong_time = parts[1].toDouble();
    record.week_tennis_time = parts[2].toDouble();
    record.week_basketball_time = parts[3].toDouble();
    record.week_volleyball_time = parts[4].toDouble();
    record.week_football_time = parts[5].toDouble();
    record.week_Running_mileage = parts[6].toDouble();
    record.week_Riding_mileage = parts[7].toDouble();
    record.week_climbing_mileage = parts[8].toDouble();
    return record;
}

QString Man::FoodRecord::get_str() const{
    QString str;
    str += QString::number(number)+',';
    str += QString::number(veg_number)+',';
    str += QString::number(hot_number)+',';
    str += QString::number(reject_number)+',';
    str += QString::number(comment_number)+',';
    str += best_dish+',';
    str += QString::number(best_dish_score);
    str += '\n';
    for(auto dish : week_record)
        str += dish.save();
    return str;
}

Man::FoodRecord Man::FoodRecord::load(QTextStream& input) {
    QString str;
    Man::FoodRecord record;
    input >> str;
    assert(str[0]=='%');
    input >> str;
    QStringList parts = str.split(',');
    record.number = parts[0].toInt();
    record.veg_number = parts[1].toInt();
    record.hot_number = parts[2].toInt();
    record.reject_number = parts[3].toInt();
    record.comment_number = parts[4].toInt();
    record.best_dish = parts[5];
    record.best_dish_score = parts[6].toDouble();
    while(1)
    {
        input>>str;
        if(str[0]=='%') return record;
        parts = str.split(',');
        Dish *pdish = new Dish(parts);
        record.week_record.append(*pdish);
    }
}

QString Man::AchievementRecord::get_str() const{
    QString str;
    QHash<QString,int>::const_iterator it = achievement_map.constBegin();
    while(it!=achievement_map.constEnd()){
        str += it.key() + ',' + QString::number(it.value()) + '\n';
        ++it;
    }
    str += "%%%\n";
    QQueue<QString>::const_iterator qit;
    for (qit = qu.constBegin(); qit != qu.constEnd(); ++qit) {
        str += *qit + ',';
    }
    str += '\n';
    return str;
}

Man::AchievementRecord Man::AchievementRecord::load(QTextStream& input) {
    Man::AchievementRecord record;
    QString str;
    while(1) {
        input>>str;
        if(str[0]=='%') break;
        QStringList parts = str.split(',');
        if (parts.size() >= 2) {
            QString achievement = parts[0];
            int value = parts[1].toInt();
            record.achievement_map[achievement] = value;
        }
    }
    while(1)
    {
        input>>str;
        if(str[0]=='%') break;
        record.qu.enqueue(str);
    }
    return record;
}

bool Man::save(){
    QFile file("../../data/man_info.csv");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        qDebug()<<"文件打开失败";
        return 0;
    }
    QTextStream output(&file);
    output<<weight<<','<<height<<','<<age<<','<<gender<<','<<name<<','
           <<password<<','<<target<<',';
    for(auto i:preference) output<<i<<',';
    output<<"\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
    output<<sptRec.get_str()<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";;
    output<<foodRec.get_str()<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
    output<<achRec.get_str()<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
    file.close();
    return 1;
}

bool Man::load()
{
    QFile file("../../data/man_info.csv");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"文件打开失败";
        return 0;
    }
    QTextStream input(&file);
    QString str;
    input >> str;
    QStringList parts = str.split(',');
    weight = parts[0].toDouble();
    height = parts[1].toDouble();
    age = parts[2].toInt();
    gender = parts[3].toInt();
    name = parts[4];
    password = parts[5];
    target = parts[6].toInt();
    preference[0] = parts[7].toInt();
    preference[1] = parts[8].toInt();
    preference[2] = parts[9].toInt();
    preference[3] = parts[10].toInt();
    sptRec = SportRecord::load(input);
    foodRec = FoodRecord::load(input);
    achRec = AchievementRecord::load(input);
    file.close();
    init();
    return 1;
}

void Man::AchievementRecord::check_achievement(SportRecord sr,FoodRecord fr)
{
    int flag=2;
    if(sr.badminton_time>=600 && achievement_map["羽毛球"]<=1)
    {
        achievement_map["羽毛球"]=2;
        qu.enqueue("羽毛球");
    }else if(sr.badminton_time>=180 && achievement_map["羽毛球"]<=0)
    {
        achievement_map["羽毛球"]=1;
        qu.enqueue("羽毛球");
    }
    flag = fmin(flag,achievement_map["羽毛球"]);
    if(sr.pingpong_time>=600 && achievement_map["乒乓球"]<=1)
    {
        achievement_map["乒乓球"]=2;
        qu.enqueue("乒乓球");
    }else if(sr.pingpong_time>=180 && achievement_map["乒乓球"]<=0)
    {
        achievement_map["乒乓球"]=1;
        qu.enqueue("乒乓球");
    }
    flag = fmin(flag,achievement_map["乒乓球"]);
    if(sr.tennis_time>=600 && achievement_map["网球"]<=1)
    {
        achievement_map["网球"]=2;
        qu.enqueue("网球");
    }else if(sr.tennis_time>=180 && achievement_map["网球"]<=0)
    {
        achievement_map["网球"]=1;
        qu.enqueue("网球");
    }
    flag = fmin(flag,achievement_map["网球"]);
    if(sr.basketball_time>=600 && achievement_map["篮球"]<=1)
    {
        achievement_map["篮球"]=2;
        qu.enqueue("篮球");
    }else if(sr.basketball_time>=180 && achievement_map["篮球"]<=0)
    {
        achievement_map["篮球"]=1;
        qu.enqueue("篮球");
    }
    flag = fmin(flag,achievement_map["篮球"]);
    if(sr.volleyball_time>=600 && achievement_map["排球"]<=1)
    {
        achievement_map["排球"]=2;
        qu.enqueue("排球");
    }else if(sr.volleyball_time>=180 && achievement_map["排球"]<=0)
    {
        achievement_map["排球"]=1;
        qu.enqueue("排球");
    }
    flag = fmin(flag,achievement_map["排球"]);
    if(sr.football_time>=600 && achievement_map["足球"]<=1)
    {
        achievement_map["足球"]=2;
        qu.enqueue("足球");
    }else if(sr.football_time>=180 && achievement_map["足球"]<=0)
    {
        achievement_map["足球"]=1;
        qu.enqueue("足球");
    }
    flag = fmin(flag,achievement_map["足球"]);
    if(sr.Running_mileage>=100 && achievement_map["跑步"]<=1)
    {
        achievement_map["跑步"]=2;
        qu.enqueue("跑步");
    }else if(sr.Running_mileage>=20 && achievement_map["跑步"]<=0)
    {
        achievement_map["跑步"]=1;
        qu.enqueue("跑步");
    }
    flag = fmin(flag,achievement_map["跑步"]);
    if(sr.Riding_mileage>=500 && achievement_map["骑行"]<=1)
    {
        achievement_map["骑行"]=2;
        qu.enqueue("骑行");
    }else if(sr.Riding_mileage>=100 && achievement_map["骑行"]<=0)
    {
        achievement_map["骑行"]=1;
        qu.enqueue("骑行");
    }
    flag = fmin(flag,achievement_map["骑行"]);
    if(sr.climbing_mileage>=500 && achievement_map["登山"]<=1)
    {
        achievement_map["登山"]=2;
        qu.enqueue("登山");
    }else if(sr.climbing_mileage>=100 && achievement_map["登山"]<=0)
    {
        achievement_map["登山"]=1;
        qu.enqueue("登山");
    }
    flag = fmin(flag,achievement_map["登山"]);
    if(sr.swimming_time>=600 && achievement_map["游泳"]<=1)
    {
        achievement_map["游泳"]=2;
        qu.enqueue("游泳");
    }else if(sr.swimming_time>=180 && achievement_map["游泳"]<=0)
    {
        achievement_map["游泳"]=1;
        qu.enqueue("游泳");
    }
    flag = fmin(flag,achievement_map["游泳"]);
    if(flag==2 && achievement_map["六边形"]<=1){
        achievement_map["六边形"]=2;
        qu.enqueue("六边形");
    }else if(flag==1 && achievement_map["六边形"]<=0)
    {
        achievement_map["六边形"]=1;
        qu.enqueue("六边形");
    }
    if(fr.number>1000 && achievement_map["干饭"]<=2)
    {
        achievement_map["干饭"]=3;
        qu.enqueue("干饭");
    }else if(fr.number>100 && achievement_map["干饭"]<=1)
    {
        achievement_map["干饭"]=2;
        qu.enqueue("干饭");
    }else if(fr.number>10 && achievement_map["干饭"]<=0)
    {
        achievement_map["干饭"]=1;
        qu.enqueue("干饭");
    }
    if(fr.veg_number>100 && achievement_map["素食"]<=2)
    {
        achievement_map["素食"]=3;
        qu.enqueue("素食");
    }else if(fr.veg_number>50 && achievement_map["素食"]<=1)
    {
        achievement_map["素食"]=2;
        qu.enqueue("素食");
    }else if(fr.veg_number>20 && achievement_map["素食"]<=0)
    {
        achievement_map["素食"]=1;
        qu.enqueue("素食");
    }
    if(fr.hot_number>50 && achievement_map["吃辣"]<=1)
    {
        achievement_map["吃辣"]=2;
        qu.enqueue("吃辣");
    }else if(fr.hot_number>20 && achievement_map["吃辣"]<=0)
    {
        achievement_map["吃辣"]=1;
        qu.enqueue("吃辣");
    }
    if(fr.reject_number>50 && achievement_map["挑选"]<=1)
    {
        achievement_map["挑选"]=2;
        qu.enqueue("挑选");
    }else if(fr.reject_number>20 && achievement_map["挑选"]<=0)
    {
        achievement_map["挑选"]=1;
        qu.enqueue("挑选");
    }
    if(fr.comment_number>50 && achievement_map["评论"]<=1)
    {
        achievement_map["评论"]=2;
        qu.enqueue("评论");
    }else if(fr.comment_number>20 && achievement_map["评论"]<=0)
    {
        achievement_map["评论"]=1;
        qu.enqueue("评论");
    }
    while(qu.size()>5) qu.dequeue();
    return;
}

void Man::check_achievement(){
    return achRec.check_achievement(sptRec,foodRec);
}