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
#include "man.h"
Cafeteria::Cafeteria() {}

class scoreWorker : public QRunnable{
public:
    int preference;
    double &my_score;
    Dish &my_dish;
    scoreWorker(Dish &dish,double &score,int r):my_score(score),my_dish(dish){preference=r;}
    void run(){my_score=my_dish.get_value(preference);}
};

QVector<Dish> Cafeteria::recommend(const Man &m,int seed,QString *pname)
{
    pname = NULL;
    bool flag = 0;
    QRandomGenerator prng(seed);
    do{
        int idx = prng.generate()%12;
        QVector<Dish> dishes = load(idx);
        int l = dishes.size();
        QVector<double> values(l);
        QThreadPool pool;
        for(int i=0;i<l;i++)
        {
            scoreWorker* pscorer = new scoreWorker(dishes[i],values[i],m.preference);
            pool.start(pscorer);
        }
        pool.waitForDone();

        QString cafe_name = names[idx];
    }while(flag==0);
}
QVector<Dish> Cafeteria::load(int id)
{
    QVector<Dish> dishes;
    QFile file(filenames[id]);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"文件打开失败";
        return dishes;
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
    return dishes;
}

class saveWorker : public QRunnable{
public:
    const Dish& my_dish;
    QString &my_str;
    saveWorker(const Dish &dish,QString &str):my_dish(dish),my_str(str){};
    void run() {my_str = my_dish.save();}
};

bool Cafeteria::save(int id,QVector<Dish> dishes)
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
