#ifndef RECORDS_H
#define RECORDS_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
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

        QVBoxLayout* tempLayout=new QVBoxLayout;
        QFrame* frame=new QFrame(this);
        QVBoxLayout* finalLayout=new QVBoxLayout;

    };

    class SingleSportRecord : public QWidget
    {
    public:
        explicit SingleSportRecord(QWidget *parent, QPair<QString,int> sportPair, int sportType);

        QVBoxLayout* tempLayout=new QVBoxLayout;
        QFrame* frame=new QFrame(this);
        QVBoxLayout* finalLayout=new QVBoxLayout;

    };

    QWidget* scrollWidget=new QWidget;
    QVBoxLayout* vLayout=new QVBoxLayout(scrollWidget);
    QScrollArea* scrollArea=new QScrollArea;
    QVBoxLayout* finalLayout=new QVBoxLayout(this);

    void refresh();

signals:
};

#endif // RECORDS_H
