#ifndef SPORTS_H
#define SPORTS_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QMovie>
#include <QFrame>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QScrollArea>

class Sports : public QWidget
{
    Q_OBJECT
public:
    explicit Sports(QWidget *parent = nullptr);

    class SingleSport : public QWidget
    {
    public:
        explicit SingleSport(QWidget *parent, int index, Sports* sp);
        Sports* parentSports;

        int idx;
        double param=0;
        QMovie* movie=new QMovie;
        QLabel* movieLabel=new QLabel;
        QLabel* nameLabel=new QLabel;
        QLabel* textLabel=new QLabel("运动时间（分钟）：");
        QSpinBox* spinBox=new QSpinBox;
        QHBoxLayout* hhLayout=new QHBoxLayout;
        QLabel* autoCalc=new QLabel;
        QPushButton* recordButton=new QPushButton("记录");
        QHBoxLayout* recordLayout=new QHBoxLayout;
        QVBoxLayout* calcLayout=new QVBoxLayout;
        QHBoxLayout* hLayout=new QHBoxLayout;
        QFrame* frame=new QFrame(this);
        QHBoxLayout* finalLayout=new QHBoxLayout;

        void refresh();
        void save();  //在这里检查是否触发运动成就
    };

    QWidget* scrollWidget=new QWidget;
    QGridLayout* gLayout=new QGridLayout(scrollWidget);
    QScrollArea* scrollArea=new QScrollArea;
    QVBoxLayout* finalLayout=new QVBoxLayout(this);

signals:
    void hasnewach(QVector<QString>);

};

#endif // SPORTS_H
