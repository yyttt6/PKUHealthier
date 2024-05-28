#ifndef SINGLEDISH_H
#define SINGLEDISH_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include "./backend/cafeteria.h"

class SingleDish : public QWidget
{
    Q_OBJECT
public:
    explicit SingleDish(QWidget *parent = nullptr, Dish* d = nullptr);
    Dish* dish=new Dish;
    QFrame* frame=new QFrame;
    QVBoxLayout* vLayout=new QVBoxLayout;
    QHBoxLayout* hLayout1=new QHBoxLayout;
    QHBoxLayout* hLayout2=new QHBoxLayout;
    QHBoxLayout* hLayout3=new QHBoxLayout;
    QLabel* label1=new QLabel;
    QLabel* label2=new QLabel;
    QLabel* label3=new QLabel;
    QLabel* label4=new QLabel;
    QLabel* label5=new QLabel;
    QLabel* label6=new QLabel("高糖");
    QLabel* label7=new QLabel("辣");
    QLabel* label8=new QLabel("素菜");
    QPushButton* likeButton=new QPushButton();
    QPushButton* blockButton=new QPushButton();
    QPushButton* chooseButton=new QPushButton("选择");


    void refresh();

public slots:


signals:
};

#endif // SINGLEDISH_H
