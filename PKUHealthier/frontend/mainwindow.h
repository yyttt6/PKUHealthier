#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>

#include "home.h"
#include "recommend.h"
#include "menu.h"
#include "sports.h"
#include "records.h"
#include "achievementwall.h"
#include "profile.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    QHBoxLayout* finalLayout=new QHBoxLayout;

    QVBoxLayout* leftlist=new QVBoxLayout;
    QPushButton* button[7];

    QStackedWidget* rightpage=new QStackedWidget;
    Home* w0=new Home;  // 主页
    Recommend* w1=new Recommend;  // 食谱推荐
    Menu* w2=new Menu;  // 饮食记录和评价
    Sports* w3=new Sports;  // 运动打卡
    Records* w4=new Records;  // 饮食和运动记录
    AchievementWall* w5=new AchievementWall;  // 成就墙
    Profile* w6=new Profile;  // 个人信息设置

    void list_refresh(int n);

public slots:
    void changePage0();
    void changePage1();
    void changePage2();
    void changePage3();
    void changePage4();
    void changePage5();
    void changePage6();
    void jumpMenu(); //推荐成功

    void notice(QVector<QString> newach);

};

#endif // MAINWINDOW_H
