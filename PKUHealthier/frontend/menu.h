#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>
#include <QScrollArea>
#include <QStackedWidget>
#include <QDialog>
#include "./backend/cafeteria.h"

class Menu : public QWidget
{
    Q_OBJECT
public:

    explicit Menu(QWidget *parent = nullptr);

    class SinglePage;

    class SingleDish : public QWidget
    {
    public:
        explicit SingleDish(QWidget *parent, Dish* d, SinglePage* pp);
        Dish* dish=new Dish;
        SinglePage* parentPage;

        class ScoreDialog: public QWidget
        {
        public:
            explicit ScoreDialog(QWidget *parent, SingleDish* sd);
            SingleDish* parentDish;
            QDialog* dialog=new QDialog;
            QVBoxLayout* layout = new QVBoxLayout(dialog);
            QLabel* dishName=new QLabel;
            QHBoxLayout* buttonLayout=new QHBoxLayout;
            QPushButton* scoreButton[5];
            QIcon* kongxinStar=new QIcon(":/menu/kongxin.png");
            QIcon* shixinStar=new QIcon(":/menu/shixin.png");
            QLabel* currentLove=new QLabel;
            QLabel* loveText1=new QLabel;
            QLabel* loveText2=new QLabel;
            QHBoxLayout* resultLayout=new QHBoxLayout;
            QPushButton* CancelButton=new QPushButton("取消");
            QPushButton* ConfirmButton=new QPushButton("确认");
            int score;

            void printStar0();
            void printStar1();
            void printStar2();
            void printStar3();
            void printStar4();
            void save();
        };

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
        QPixmap* pepperPixmap=new QPixmap(":/menu/pepper.png");
        QLabel* label7=new QLabel;
        QLabel* label8=new QLabel("素菜");
        QPushButton* scoreButton=new QPushButton("评分");
        QPushButton* chooseButton=new QPushButton("选择");
        bool selected=0;


        void score_update();
        void selected_change();
        void selected_change_only();
    };


    class SinglePage : public QWidget
    {
    public:
        explicit SinglePage(QWidget *parent, int index);
        int idx=0;
        Cafeteria* cafe=new Cafeteria;
        QVector<SingleDish*> stapleDishes;
        QVector<SingleDish*> recipeDishes;
        QVector<SingleDish*> dessertDishes;
        QVector<SingleDish*> setmealDishes;
        int selected_count=0;

        QLabel* imageLabel=new QLabel;
        QPixmap* imagePixmap=new QPixmap;
        QHBoxLayout* typeLayout1=new QHBoxLayout;
        QHBoxLayout* typeLayout2=new QHBoxLayout;
        QHBoxLayout* typeLayout3=new QHBoxLayout;
        QHBoxLayout* typeLayout4=new QHBoxLayout;
        QLabel* typelabel1=new QLabel("主食");
        QLabel* typelabel2=new QLabel("菜品");
        QLabel* typelabel3=new QLabel("套餐");
        QLabel* typelabel4=new QLabel("小吃");
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
        QVBoxLayout* selectLayout=new QVBoxLayout;

        void checkRecordButton();
        void cancelAll();
        void save();
    };

    QLabel* cafeLabel=new QLabel("请选择您的食堂： ");
    QComboBox* cafeBox=new QComboBox;
    QHBoxLayout* cafeLayout=new QHBoxLayout;

    QStackedWidget* stackedPage=new QStackedWidget;
    QVBoxLayout* finalLayout=new QVBoxLayout;

    void refresh();

public slots:

signals:
};

#endif // MENU_H
