#include <QRandomGenerator>
#include <QVector>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QtCore>
#include <QThread>
#include <QThreadPool>
#include <QDateTime>
#include <QRandomGenerator>
#include "cafeteria.h"
#include "dish.h"
#include "meal.h"
#include "man.h"
#define DEBUG
Cafeteria::Cafeteria() {}

bool Meal_cmp(Meal a,Meal b){
    return a.value > b.value;
}

class combineWorker : public QRunnable{
public:
    int mode;
    QVector<Meal>& ans;
    Cafeteria & cafe;
    int staple_idx;
    combineWorker(int mode,int idx,QVector<Meal>& ans,Cafeteria & cafe)
        :mode(mode),ans(ans),cafe(cafe),staple_idx(idx){};
    void run(){
        if(mode==1)
        {
            for(auto dish : cafe.setmeal){
                Meal* p = new Meal();
                p->elements.append(dish);
                p->init();
                ans.append(*p);
                delete p;
            }
        }else if(mode==2){
            for(auto dish1 : cafe.setmeal){
                for(auto dish2 : cafe.dessert){
                    Meal* p = new Meal();
                    p->elements.append(dish1);
                    p->elements.append(dish2);
                    p->init();
                    ans.append(*p);
                    delete p;
                }
            }
        }else if(mode==3){
            for(auto dish : cafe.recipe){
                Meal* p = new Meal();
                p->elements.append(cafe.staple[staple_idx]);
                p->elements.append(dish);
                p->init();
                ans.append(*p);
                delete p;
            }
        }else if(mode==4){
            int l = cafe.recipe.size();
            Dish *dish1,*dish2;
            for(int i=0;i<l;i++)
            {
                dish1 = cafe.recipe[i];
                for(int j=i+1;j<l;j++)
                {
                    dish2 = cafe.recipe[j];
                    if(dish2->id==dish1->id) continue;
                    Meal* p = new Meal();
                    p->elements.append(cafe.staple[staple_idx]);
                    p->elements.append(dish1);
                    p->elements.append(dish2);
                    p->init();
                    ans.append(*p);
                    delete p;
                }
            }
        }else if(mode==5){
            int l = cafe.recipe.size();
            Dish *dish1,*dish2,*dish3;
            for(int i=0;i<l;i++)
            {
                dish1 = cafe.recipe[i];
                for(int j=i+1;j<l;j++)
                {
                    dish2 = cafe.recipe[j];
                    for(int k=j+1;k<l;k++)
                    {
                        dish3 = cafe.recipe[k];
                        if(dish1->id==dish2->id) continue;
                        if(dish1->id==dish3->id) continue;
                        if(dish2->id==dish3->id) continue;
                        Meal* p = new Meal();
                        p->elements.append(cafe.staple[staple_idx]);
                        p->elements.append(dish1);
                        p->elements.append(dish2);
                        p->elements.append(dish3);
                        p->init();
                        ans.append(*p);
                        delete p;
                    }
                }
            }
        }else if(mode==6){
            for(auto dish1 : cafe.dessert){
                for(auto dish : cafe.recipe){
                    Meal* p = new Meal();
                    p->elements.append(cafe.staple[staple_idx]);
                    p->elements.append(dish);
                    p->elements.append(dish1);
                    p->init();
                    ans.append(*p);
                    delete p;
                }
            }
        }else if(mode==7){
            int l = cafe.recipe.size();
            Dish *dish1,*dish2;
            for(auto dish3 : cafe.dessert){
                for(int i=0;i<l;i++)
                {
                    dish1 = cafe.recipe[i];
                    for(int j=i+1;j<l;j++)
                    {
                        dish2 = cafe.recipe[j];
                        if(dish2->id==dish1->id) continue;
                        Meal* p = new Meal();
                        p->elements.append(cafe.staple[staple_idx]);
                        p->elements.append(dish1);
                        p->elements.append(dish2);
                        p->elements.append(dish3);
                        p->init();
                        ans.append(*p);
                        delete p;
                    }
                }
            }
        }else if(mode==8){
            int l = cafe.recipe.size();
            Dish *dish1,*dish2,*dish3;
            for(auto dish4:cafe.dessert){
                for(int i=0;i<l;i++)
                {
                    dish1 = cafe.recipe[i];
                    for(int j=i+1;j<l;j++)
                    {
                        dish2 = cafe.recipe[j];
                        for(int k=j+1;k<l;k++)
                        {
                            dish3 = cafe.recipe[k];
                            if(dish1->id==dish2->id) continue;
                            if(dish1->id==dish3->id) continue;
                            if(dish2->id==dish3->id) continue;
                            Meal* p = new Meal();
                            p->elements.append(cafe.staple[staple_idx]);
                            p->elements.append(dish1);
                            p->elements.append(dish2);
                            p->elements.append(dish3);
                            p->elements.append(dish4);
                            p->init();
                            ans.append(*p);
                            delete p;
                        }
                    }
                }
            }
        }
    }
};

class scoreWorker : public QRunnable{
public:
    const Man& man;
    Meal &my_meal;
    int rand;
    scoreWorker(Meal &meal,const Man &man,int rand):man(man),my_meal(meal),rand(rand){};
    void run(){my_meal.get_value(man,rand);}
};

QVector<Meal> Cafeteria::recommend(const Man &m,int seed,int *pint)
{
    QVector<Meal> ans;
    bool flag = 0; //用于判断在一个食堂中有没有找到合法菜品
    QRandomGenerator prng(seed);
    do{
        int idx = prng.generate()%12;
        #ifdef DEBUG
            idx = 0;
        #endif
        bool load_flag = load(idx);
        if(load_flag == 0) return ans;
        for(int i=0;i<dishes.size();i++)
        {
            Dish *pdish = &dishes[i];
            if(pdish->type==0) staple.append(pdish);
            else if(pdish->type==1) recipe.append(pdish);
            else if(pdish->type==2) dessert.append(pdish);
            else if(pdish->type==3) setmeal.append(pdish);
        }

        multi_meals.resize(6*staple.size()+2);
        QThreadPool cpool;
        combineWorker *worker1 = new combineWorker(1,0,multi_meals[0],*this);
        cpool.start(worker1);
        combineWorker *worker2 = new combineWorker(2,0,multi_meals[1],*this);
        cpool.start(worker2);
        int counter = 2;
        for(int i=3;i<=8;i++)
        {
            for(int j=0;j<staple.size();j++)
            {
                combineWorker *pworker = new combineWorker(i,j,multi_meals[counter++],*this);
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
        qint64 timestamp = QDateTime::currentMSecsSinceEpoch();
        QRandomGenerator qrand(timestamp);
        for(int i=0;i<meals.size();i++)
        {
            scoreWorker *pworker = new scoreWorker(meals[i],m,qrand.bounded(100));
            spool.start(pworker);
        }
        spool.waitForDone();
        if(meals.size()>3){
            flag=1;
            std::sort(meals.begin(),meals.end(),Meal_cmp);
            ans.append(meals[0]);
            ans.append(meals[1]);
            ans.append(meals[2]);
            meals.clear();
            *pint = idx;
        }
    }while(flag==0);//在非极端的情况下，只会执行一遍
    return ans;
}

bool Cafeteria::load(int id)
{
    dishes.clear();
    QFile file("../../data/"+filenames[id]);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"食堂文件打开失败";
        return 0;
    }
    QTextStream input(&file);
    QString line = input.readLine();
    while(!input.atEnd())
    {
        line = input.readLine();
        QStringList infos = line.split(',');
        dishes.append(Dish(infos));
    }
    file.close();
    return 1;
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
    QFile file("../../data/"+filenames[id]);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        qDebug()<<"文件打开失败";
        return 0;
    }
    int l = dishes.size();
    QVector<QString> infos(l+1);
    infos[0]="id,name,type,energy,protein,fat,sugar,pepper,all_veg,money,scores\n";
    QThreadPool pool;
    for(int i=0;i<l;i++)
    {
        saveWorker* psaver = new saveWorker(dishes[i],infos[i+1]);
        pool.start(psaver);
    }
    pool.waitForDone();
    QTextStream output(&file);
    for(auto str : infos) output<<str<<'\n';
    file.close();
    return true;
}
