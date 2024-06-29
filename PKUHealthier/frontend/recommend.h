#ifndef RECOMMEND_H
#define RECOMMEND_H

#include <QWidget>
#include <QLabel>
#include <QFrame>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include "./backend/cafeteria.h"

class Recommend : public QWidget
{
    Q_OBJECT
public:
    explicit Recommend(QWidget *parent = nullptr);

    //******************** dz1

    QLabel* numberLabel1=new QLabel("#6114514");
    QLabel* timeLabel1=new QLabel;
    QLabel* commentNumber=new QLabel;
    QLabel* starNumber=new QLabel;
    QLabel* commentImage=new QLabel;
    QLabel* starImage=new QLabel;
    QPixmap* commentPixmap=new QPixmap(":/recommend/comment.jpg");
    QPixmap* starPixmap=new QPixmap(":/recommend/star.jpg");
    QLabel* dzText1=new QLabel("P君决定我这顿吃什么！");

    QHBoxLayout* hLayout1=new QHBoxLayout;
    QVBoxLayout* vLayout1=new QVBoxLayout;
    QFrame* frame1=new QFrame;
    QVBoxLayout* finalLayout1=new QVBoxLayout;

    //******************** start

    QPushButton* startButton=new QPushButton(QIcon(":/recommend/start.png")," 点击开始对话 ");

    QHBoxLayout* startLayout=new QHBoxLayout;

    //******************** pku1

    QLabel* numberLabel2=new QLabel("#28571428");
    QLabel* timeLabel2=new QLabel;
    QLabel* pkuText1=new QLabel("[PKUHealthier] dz想去哪个食堂，还是我随便挑呢qwq");

    QHBoxLayout* hLayout2=new QHBoxLayout;
    QVBoxLayout* vLayout2=new QVBoxLayout;
    QFrame* frame2=new QFrame;
    QVBoxLayout* finalLayout2=new QVBoxLayout;

    //******************** cafechoose

    QLabel* label11=new QLabel("仅限 ");
    QComboBox* cafeChoose=new QComboBox;
    QPushButton* chooseButton1=new QPushButton("选择");
    QLabel* label22=new QLabel("随机选择食堂");
    QPushButton* chooseButton2=new QPushButton("选择");

    QHBoxLayout* hhLayout1=new QHBoxLayout;
    QHBoxLayout* hhLayout2=new QHBoxLayout;
    QFrame* line=new QFrame;
    QVBoxLayout* vvLayout=new QVBoxLayout;
    QFrame* chooseFrame=new QFrame;
    QHBoxLayout* chooseLayout=new QHBoxLayout;

    //******************** dz2

    QLabel* numberLabel3=new QLabel("#28571429");
    QLabel* timeLabel3=new QLabel;
    QLabel* dzText2=new QLabel;

    QHBoxLayout* hLayout3=new QHBoxLayout;
    QVBoxLayout* vLayout3=new QVBoxLayout;
    QFrame* frame3=new QFrame;
    QVBoxLayout* finalLayout3=new QVBoxLayout;

    //******************** pku2

    QLabel* numberLabel4=new QLabel("#28571430");
    QLabel* timeLabel4=new QLabel;
    QLabel* pkuText2=new QLabel;

    QHBoxLayout* hLayout4=new QHBoxLayout;
    QVBoxLayout* vLayout4=new QVBoxLayout;
    QFrame* frame4=new QFrame;
    QVBoxLayout* finalLayout4=new QVBoxLayout;

    //******************** pku3

    QLabel* numberLabel5=new QLabel("#28571431");
    QLabel* timeLabel5=new QLabel;
    QLabel* pkuText3=new QLabel("[PKUHealthier] 根据您的健康状况和饮食偏好，推荐您：");
    QString dishstr;
    QString resultstr;
    QLabel* dishText=new QLabel;
    QLabel* resultText=new QLabel;

    QHBoxLayout* hLayout5=new QHBoxLayout;
    QVBoxLayout* vLayout5=new QVBoxLayout;
    QFrame* frame5=new QFrame;
    QVBoxLayout* finalLayout5=new QVBoxLayout;

    //******************** result

    QPushButton* acceptButton=new QPushButton(" Accepted ");
    QPushButton* denyButton=new QPushButton(QIcon(":/recommend/deny.png")," 重新推荐食谱 ");
    QPushButton* restartButton=new QPushButton(QIcon(":/recommend/restart.png")," 重新开始对话 ");

    QHBoxLayout* hhhLayout=new QHBoxLayout;
    QFrame* resultFrame=new QFrame;
    QHBoxLayout* resultLayout=new QHBoxLayout;

    //********************

    QVBoxLayout* vLayout=new QVBoxLayout;
    QFrame* frame=new QFrame;
    QVBoxLayout* finalLayout=new QVBoxLayout;

    int index=-1;
    QVector<int> chosenId;

    void chooseresult();
    void recommendresult();  //在这里检查是否触发deny成就

public slots:
    void start();
    void choose1();
    void choose2();
    void deny();
    void restart();

signals:
    void hasnewach(QVector<QString>);

};

#endif // RECOMMEND_H
