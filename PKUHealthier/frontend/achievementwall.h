#ifndef ACHIEVEMENTWALL_H
#define ACHIEVEMENTWALL_H

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QFrame>
#include <QPushButton>
#include <QScrollArea>
#include "backend/man.h"

class AchievementWall : public QWidget
{
    Q_OBJECT
public:
    explicit AchievementWall(QWidget *parent = nullptr);

    class SingleAchievement : public QWidget
    {
    public:
        explicit SingleAchievement(QWidget *parent, QString _name);

        QString name;
        QLabel* picLabel = new QLabel;
        QLabel* nameLabel = new QLabel;
        QLabel* textLabel = new QLabel;
        QVBoxLayout* rightLayout=new QVBoxLayout;
        QHBoxLayout* tempLayout=new QHBoxLayout;
        QFrame* frame=new QFrame(this);
        QHBoxLayout* finalLayout=new QHBoxLayout;

        void draw(Man* User);
    };

    Man* man=new Man;
    Man* fakeman=new Man;
    bool fake=true;

    QLabel* headlabel=new QLabel("成就墙");
    QPushButton* button=new QPushButton;
    QHBoxLayout* hLayout=new QHBoxLayout;

    SingleAchievement* single[16];
    QWidget* scrollWidget=new QWidget;
    QVBoxLayout* itemLayout=new QVBoxLayout(scrollWidget);
    QScrollArea* scrollArea=new QScrollArea;
    QVBoxLayout* frameLayout=new QVBoxLayout;
    QFrame* frame=new QFrame;
    QVBoxLayout* finalLayout=new QVBoxLayout(this);

    void refresh();

public slots:
    void change();

};

#endif // ACHIEVEMENTWALL_H
