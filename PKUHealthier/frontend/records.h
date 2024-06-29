#ifndef RECORDS_H
#define RECORDS_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QVector>
#include "./backend/cafeteria.h"

class Records : public QWidget
{
    Q_OBJECT
public:
    explicit Records(QWidget *parent = nullptr);

    class SingleRecord : public QWidget
    {
    public:
        explicit SingleRecord(QWidget *parent, bool type, QString s1, QString s2, QString s3);
        QLabel* label1 = new QLabel;  //时间+饮食记录（蓝） 运动记录（绿）
        QLabel* label2 = new QLabel;
        QLabel* label3 = new QLabel;
        QVBoxLayout* tempLayout=new QVBoxLayout;
        QFrame* frame=new QFrame(this);
        QVBoxLayout* finalLayout=new QVBoxLayout;
    };

    class RecordItem
    {
    public:
        QString time;
        Meal mealItem;
        int sportItem;
        int sportType;
        bool type;
        RecordItem(QPair<QString, Meal> mealPair)
            : time(mealPair.first), mealItem(mealPair.second) {
            type = 0;
        }
        RecordItem(QPair<QString, int> sportPair, int sptType)
            : time(sportPair.first), sportItem(sportPair.second), sportType(sptType){
            type = 1;
        }

        friend bool operator< (const RecordItem & a, const RecordItem & b) {
            if(a.time.mid(0,4)!=b.time.mid(0,4))
                return a.time.mid(0,4)>b.time.mid(0,4);
            int index1m=a.time.indexOf("月");
            int index2m=b.time.indexOf("月");
            int index1d=a.time.indexOf("日");
            int index2d=b.time.indexOf("日");
            if(index1m!=index2m)
                return index1m>index2m;
            if(index1d!=index2d)
                return index1d>index2d;
            return a.time > b.time;
        }
    };

    QFrame* headframe=new QFrame;
    QFrame* tailframe=new QFrame;

    QWidget* scrollWidget=new QWidget;
    QVBoxLayout* itemLayout=new QVBoxLayout(scrollWidget);
    QScrollArea* scrollArea=new QScrollArea;
    QVBoxLayout* finalLayout=new QVBoxLayout(this);

};

#endif // RECORDS_H
