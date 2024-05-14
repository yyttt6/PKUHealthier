#include <QRandomGenerator>
#include <QVector>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QtCore>
#include <QThread>
#include <QThreadPool>
#include "cafeteria.h"
#include "dish.h"
#include "meal.h"
#include "man.h"
Cafeteria::Cafeteria() {}

class combineWorker : public QRunnable{
public:
    int mode;
    QVector<Meal>& ans;
    int staple_idx;
    combineWorker(int mode,int idx,QVector<Meal>& ans):mode(mode),staple_idx(idx),ans(ans){};
    void run(){
    }
};

class scoreWorker : public QRunnable{
public:
    int preference;
    Meal &my_meal;
    scoreWorker(Meal &meal,int r):my_meal(meal){preference=r;}
    void run(){my_meal.value=my_meal.get_value(preference);}
};

QVector<Meal*> Cafeteria::recommend(const Man &m,int seed,QString *pname)
{
    pname = NULL;
    bool flag = 0; //用于判断在一个食堂中有没有找到合法菜品
    QRandomGenerator prng(seed);
    do{
        int idx = prng.generate()%12;
        load(idx);
        for(auto dish : dishes)
        {
            if(dish.type==0) staple.append(&dish);
            else if(dish.type==1) recipe.append(&dish);
            else if(dish.type==2) dessert.append(&dish);
            else if(dish.type==3) setmeal.append(&dish);
        }

        multi_meals.resize(6*staple.size()+2);
        QThreadPool cpool;
        combineWorker *worker1 = new combineWorker(1,0,multi_meals[0]);
        cpool.start(worker1);
        combineWorker *worker2 = new combineWorker(2,0,multi_meals[1]);
        cpool.start(worker2);
        int counter = 2;
        for(int i=3;i<=8;i++)
        {
            for(int j=0;j<staple.size();j++)
            {
                combineWorker *pworker = new combineWorker(i,j,multi_meals[counter++]);
                cpool.start(pworker);
            }
        }
        cpool.waitForDone();
        meals = multi_meals[0];
        multi_meals[0].clear();
        for(int i=1;i<multi_meals.size();i++)
        {
            meals += multi_meals[i];
            multi_meals[i].clear();
        }

        QThreadPool spool;
        for(int i=0;i<meals.size();i++)
        {
            scoreWorker *pworker = new scoreWorker(meals[i],m.preference);
            spool.start(pworker);
        }
        spool.waitForDone();
        qSort(meals.begin(),meals.end(),Meal_cmp);

        QString cafe_name = names[idx];
    }while(flag==0);//在非极端的情况下，只会执行一遍
}

void Cafeteria::load(int id)
{
    dishes.clear();
    QFile file(filenames[id]);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"文件打开失败";
    }
    QTextStream input(&file);
    QString line;
    while(!input.atEnd())
    {
        line = input.readLine();
        QStringList infos = line.split(',');
        Q_ASSERT(infos.size()==10);
        dishes.append(Dish(infos));
    }
}

class saveWorker : public QRunnable{
public:
    const Dish& my_dish;
    QString &my_str;
    saveWorker(const Dish &dish,QString &str):my_dish(dish),my_str(str){};
    void run() {my_str = my_dish.save();}
};

bool Cafeteria::save(int id)
{
    QFile file(filenames[id]);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        qDebug()<<"文件打开失败";
        return 0;
    }
    int l = dishes.size();
    QVector<QString> infos(l);
    QThreadPool pool;
    for(int i=0;i<l;i++)
    {
        saveWorker* psaver = new saveWorker(dishes[i],infos[i]);
        pool.start(psaver);
    }
    pool.waitForDone();
    QTextStream output(&file);
    for(auto str : infos) output<<str;
    return true;
}
