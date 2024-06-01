#ifndef RECORDS_H
#define RECORDS_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QString>
#include <QVector>
#include "./backend/cafeteria.h"

class Records : public QWidget
{
    Q_OBJECT
public:
    explicit Records(QWidget *parent = nullptr);

    class SingleFoodRecord : public QWidget
    {
    public:
        explicit SingleFoodRecord(QWidget *parent, QPair<QString,Meal> mealPair);

        QLabel* nameLabel = new QLabel("饮食记录");
        QLabel* dishLabel = new QLabel();
        QLabel* intakeLabel = new QLabel();
        QLabel* timeLabel = new QLabel();
        QVBoxLayout* tempLayout=new QVBoxLayout;
        QFrame* frame=new QFrame(this);
        QVBoxLayout* finalLayout=new QVBoxLayout;

    };

    class SingleSportRecord : public QWidget
    {
    public:
        explicit SingleSportRecord(QWidget *parent, QPair<QString,int> sportPair, int sportType);

        QLabel* nameLabel = new QLabel("运动记录");
        QLabel* sportLabel = new QLabel();
        QLabel* timeLabel = new QLabel();
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
        RecordItem(QPair<QString, Meal> mealPair) : time(mealPair.first), mealItem(mealPair.second) {
            sportItem = 0; type = 0;
        }
        RecordItem(QPair<QString, int> sportPair, int sptType)
            : time(sportPair.first), sportItem(sportPair.second), sportType(sptType){
            type = 1;
        }

        friend bool operator< (const RecordItem & a, const RecordItem & b) {
            return a.time > b.time;
        }
    };

    QWidget* scrollWidget=new QWidget;
    QGridLayout* itemLayout=new QGridLayout(scrollWidget);
    QScrollArea* scrollArea=new QScrollArea;
    QVBoxLayout* finalLayout=new QVBoxLayout(this);

    void refresh();

signals:
};

#endif // RECORDS_H
