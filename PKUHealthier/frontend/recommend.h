#ifndef RECOMMEND_H
#define RECOMMEND_H

#include <QWidget>
#include <QLabel>
#include <QFrame>
#include <QPixmap>
#include <QVBoxLayout>
#include <QPushButton>
#include "./backend/cafeteria.h"

class Recommend : public QWidget
{
    Q_OBJECT
public:
    explicit Recommend(QWidget *parent = nullptr);

    QLabel* numberLabel1=new QLabel("#6114514");//Consolas
    QLabel* timeLabel1=new QLabel;//剩下是微软雅黑
    QLabel* commentNumber=new QLabel;
    QLabel* starNumber=new QLabel;
    QLabel* commentImage=new QLabel;
    QLabel* starImage=new QLabel;
    QPixmap* commentPixmap=new QPixmap(":/recommend/comment.jpg");
    QPixmap* starPixmap=new QPixmap(":/recommend/star.jpg");
    QLabel* dzText1=new QLabel("P君决定我这顿吃什么！");
    QPushButton* button1=new QPushButton("开始对话");

    QHBoxLayout* hLayout1=new QHBoxLayout;
    QHBoxLayout* hhLayout=new QHBoxLayout;
    QVBoxLayout* vLayout1=new QVBoxLayout;
    QFrame* frame1=new QFrame;  //背景#f7f7f7
    QVBoxLayout* finalLayout1=new QVBoxLayout;

    QLabel* numberLabel2=new QLabel("#28571428");
    QLabel* timeLabel2=new QLabel;
    //QLabel* pkuText1=new QLabel("[PKUHealthier] dz想去哪个食堂呢，还是我随便挑qwq");
    QLabel* pkuText1=new QLabel("[PKUHealthier] 已开盒！正在分析您的健康状况……");

    QHBoxLayout* hLayout2=new QHBoxLayout;
    QVBoxLayout* vLayout2=new QVBoxLayout;
    QFrame* frame2=new QFrame;
    QVBoxLayout* finalLayout2=new QVBoxLayout;

    QLabel* numberLabel3=new QLabel("#28571429");
    QLabel* timeLabel3=new QLabel;

    QHBoxLayout* hLayout3=new QHBoxLayout;
    QVBoxLayout* vLayout3=new QVBoxLayout;
    QFrame* frame3=new QFrame;
    QVBoxLayout* finalLayout3=new QVBoxLayout;



    QVBoxLayout* vLayout=new QVBoxLayout;
    QFrame* frame=new QFrame;
    QVBoxLayout* finalLayout=new QVBoxLayout;

    void refresh();
    void pku1();

signals:
};

#endif // RECOMMEND_H
