#ifndef ACHIEVEMENTWALL_H
#define ACHIEVEMENTWALL_H

#include <QWidget>
#include <QLayout>
#include <QFrame>
#include <QScrollArea>
#include <QString>
#include <QLabel>
#include <QPixmap>
#include "backend/man.h"

class AchievementWall : public QWidget
{
    Q_OBJECT
public:
    explicit AchievementWall(QWidget *parent = nullptr);
    QVBoxLayout* finalLayout=new QVBoxLayout(this);

    class SingleAchievement : public QWidget
    {
    public:
        explicit SingleAchievement(QWidget *parent, QString name);
        QPixmap *pic = new QPixmap();
        QLabel* picLabel = new QLabel();
        QLabel* nameLabel = new QLabel();
        QHBoxLayout* tempLayout=new QHBoxLayout;
        QFrame* frame=new QFrame(this);
        QVBoxLayout* finalLayout=new QVBoxLayout;

        Man* User = new Man;
    };

    QWidget* scrollWidget=new QWidget;
    QGridLayout* itemLayout=new QGridLayout(scrollWidget);
    QScrollArea* scrollArea=new QScrollArea;

    void refresh();

signals:
};

#endif // ACHIEVEMENTWALL_H
