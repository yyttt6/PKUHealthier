#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QScrollArea>
#include "./backend/cafeteria.h"

class Menu : public QWidget
{
    Q_OBJECT
public:

    explicit Menu(QWidget *parent = nullptr);

    class SingleDish : public QWidget
    {
    public:
        explicit SingleDish(QWidget *parent, Dish* d, Menu* mm);
        Dish* dish=new Dish;
        QFrame* frame=new QFrame;
        QVBoxLayout* finalLayout=new QVBoxLayout;
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
        bool selected;
        Menu* parentMenu;

        void refresh();
        void selected_change();
        void selected_change_only();

    };

    Cafeteria* cafe[12];
    QVector<SingleDish*> stapleDishes;
    QVector<SingleDish*> recipeDishes;
    QVector<SingleDish*> dessertDishes;
    QVector<SingleDish*> setmealDishes;
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

    QPushButton* recordButton=new QPushButton("记录");
    QPushButton* cancelButton=new QPushButton("全部取消");
    QHBoxLayout* recordLayout=new QHBoxLayout;

    QVector<Dish*> selectedDishes;

    QVBoxLayout* finalLayout=new QVBoxLayout;

    void showpage(int idx);
    void checkRecordButton();
    void cancelAll();
    void save();
    void refresh();

public slots:

signals:
};

#endif // MENU_H
