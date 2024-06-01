#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QStackedWidget>
#include <QIcon>

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
    QHBoxLayout* finalLayout=new QHBoxLayout(this);

    QListWidget* leftlist=new QListWidget(this);
    QListWidgetItem *icon0 = new QListWidgetItem(QIcon(":/mainwindow/home_icon.png"),"");
    QListWidgetItem *icon1 = new QListWidgetItem(QIcon(":/mainwindow/recommend_icon.png"),"");
    QListWidgetItem *icon2 = new QListWidgetItem(QIcon(":/mainwindow/dish_icon.png"),"");
    QListWidgetItem *icon3 = new QListWidgetItem(QIcon(":/mainwindow/sport_icon.png"),"");
    QListWidgetItem *icon4 = new QListWidgetItem(QIcon(":/mainwindow/record_icon.png"),"");
    QListWidgetItem *icon5 = new QListWidgetItem(QIcon(":/mainwindow/achive_icon.png"),"");
    QListWidgetItem *icon6 = new QListWidgetItem(QIcon(":/mainwindow/profile_icon.png"),"");

    QStackedWidget* rightpage=new QStackedWidget(this);
    Home* w0=new Home(this);  // 主页
    Recommend* w1=new Recommend(this);  // 推荐菜品
    Menu* w2=new Menu(this);  // 所有菜的菜单，供评价或记录
    Sports* w3=new Sports(this);  // 记录运动
    Records* w4=new Records(this);  // 查看记录
    AchievementWall* w5=new AchievementWall(this);  // 成就墙
    Profile* w6=new Profile(this);  // 档案设置

    QIcon* pkuIcon = new QIcon(":/mainwindow/pku.png");

public slots:
    void changePage(int);

signals:
};



#endif // MAINWINDOW_H
