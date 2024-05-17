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
    energy_need = basic_energy * exercise_level[target] *2/5;
    protein_need = weight * protein_rate[target] *2/5;
    if(gender==0) protein_need /= 0.85;
    fat_need = (energy_need/45)*2/5;
    if(target<=1) weight_vector[5]+=10;
    if(target<=1) weight_vector[0]+=0.5;
    if(target>=3) weight_vector[1]+=1;
    if(preference[0]==0) weight_vector[3]-=5;
    if(preference[0]==2) weight_vector[3]+=5;
    if(preference[1]==0) weight_vector[4]-=5;
    if(preference[1]==2) weight_vector[4]+=5;
    if(preference[3]==0) weight_vector[6]-=0.5;
    if(preference[2]==0) weight_vector[7]=1.5;
    if(preference[2]==0) weight_vector[8]=0.5;
    if(preference[2]==2) weight_vector[7]=0.5;
    if(preference[2]==2) weight_vector[8]=1.5;
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
    record.week_pingpong_time = parts[0].toDouble();
    record.week_tennis_time = parts[0].toDouble();
    record.week_basketball_time = parts[0].toDouble();
    record.week_volleyball_time = parts[0].toDouble();
    record.week_football_time = parts[0].toDouble();
    record.week_Running_mileage = parts[0].toDouble();
    record.week_Riding_mileage = parts[0].toDouble();
    record.week_climbing_mileage = parts[0].toDouble();
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
    }
    str += "%%%\n";
    QQueue<QString>::const_iterator qit;
    for (qit = qu.constBegin(); qit != qu.constEnd(); ++qit) {
        str += *qit + ',';
    }
    str += '\n';
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
            record.achievement_map.insert(achievement, value);
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
    QFile file("man_info.csv");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        qDebug()<<"文件打开失败";
        return 0;
    }
    QTextStream output(&file);
    output<<weight<<','<<height<<','<<age<<','<<gender<<','<<name<<','
           <<password<<','<<target<<',';
    for(auto i:preference) output<<i<<',';
    output<<'\n';
    output<<sptRec.get_str()<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
    output<<foodRec.get_str()<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
    output<<achRec.get_str()<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
    file.close();
    return 1;
}

bool Man::load()
{
    QFile file("man_info.csv");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"文件打开失败";
        return 0;
    }
    QTextStream input(&file);
    QChar c;
    input>>weight>>c>>height>>c>>age>>c>>gender>>c>>name>>c>>password>>c>>target>>c;
    for(int i=0;i<4;i++) input >> preference[i] >> c;
    sptRec = SportRecord::load(input);
    foodRec = FoodRecord::load(input);
    achRec = AchievementRecord::load(input);
    file.close();
    return 1;
}

