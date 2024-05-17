#ifndef ACHIEVEMENTWALL_H
#define ACHIEVEMENTWALL_H

#include <QWidget>
#include <QFormLayout>
#include <QVBoxLayout>

class AchievementWall : public QWidget
{
    Q_OBJECT
public:
    explicit AchievementWall(QWidget *parent = nullptr);
    QVBoxLayout* finalLayout=new QVBoxLayout(this);
    void refresh();

signals:
};

#endif // ACHIEVEMENTWALL_H
