#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QScrollArea>
#include "singledish.h"

class Menu : public QWidget
{
    Q_OBJECT
public:
    explicit Menu(QWidget *parent = nullptr);
    Cafeteria* cafe[12];
    QVector<Dish*> staple;
    QVector<Dish*> recipe;
    QVector<Dish*> dessert;
    QVector<Dish*> setmeal;
    QHBoxLayout* typeLayout1=new QHBoxLayout;
    QHBoxLayout* typeLayout2=new QHBoxLayout;
    QHBoxLayout* typeLayout3=new QHBoxLayout;
    QHBoxLayout* typeLayout4=new QHBoxLayout;
    QLabel* typelabel1=new QLabel("主食");
    QLabel* typelabel2=new QLabel("菜品");
    QLabel* typelabel3=new QLabel("套餐");
    QLabel* typelabel4=new QLabel("点心");
    QFrame* line1=new QFrame;
    QFrame* line2=new QFrame;
    QFrame* line3=new QFrame;
    QFrame* line4=new QFrame;
    QGridLayout* gLayout1=new QGridLayout;
    QGridLayout* gLayout2=new QGridLayout;
    QGridLayout* gLayout3=new QGridLayout;
    QGridLayout* gLayout4=new QGridLayout;
    QWidget* scrollWidget=new QWidget;
    QVBoxLayout* vLayout=new QVBoxLayout(scrollWidget);
    QScrollArea* scrollArea=new QScrollArea;
    QVBoxLayout* finalLayout=new QVBoxLayout;
    void showpage(int idx);
    void refresh();

public slots:

signals:
};

#endif // MENU_H
